#include "event_loop.h"

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <assert.h>
#include <unistd.h>
#include <sys/eventfd.h>

Event_loop::Event_loop(Acceptor & acceptor)
: _efd(create_epoll_fd())
, _eventfd(create_eventfd())
, _acceptor(acceptor)
, _event_list(1024)
, _is_looping(false)
{
    add_epoll_fd_read(_acceptor.get_fd());
    add_epoll_fd_read(_eventfd);
}

void Event_loop::loop(void)
{
    _is_looping = true;
    while (_is_looping)
    {
        wait_epoll_fd();
    }
}

void Event_loop::run_in_loop(Functor && callback)
{
    {
    Mutex_lock_guard autolock(_mutex);
    _pending_functors.push_back(std::move(callback));
    }

    wakeup();
}

void Event_loop::un_loop(void)
{
    if (_is_looping)
        _is_looping = false;
}

void Event_loop::set_connection_callback(Tcp_connection_callback && callback)
{
    _on_connection = std::move(callback);
}

void Event_loop::set_massage_callback(Tcp_connection_callback && callback)
{
    _on_massage = std::move(callback);
}

void Event_loop::set_close_callback(Tcp_connection_callback && callback)
{
    _on_close = std::move(callback);
}


void Event_loop::wait_epoll_fd(void)
{
    int ready_n ;
    ready_n = epoll_wait(_efd, &*_event_list.begin(), _event_list.size(), 5000);
    if (ready_n == -1)
    {
        perror("epoll_wait");
        return;
    }
    else if (ready_n == 0)
    {
        cout << ">>epoll_wait timeout" << endl;
    }
    else
    {
        if (ready_n == _event_list.size())
        {
            _event_list.reserve(2 * ready_n);
        }

        for (int i = 0; i < ready_n; ++i)
        {
            if (_acceptor.get_fd() == _event_list[i].data.fd)
            {
                //新连接
                if (_event_list[i].events & EPOLLIN)
                    handle_new_connnection();
            }
            else if (_event_list[i].data.fd == _eventfd)
            {
                if (_event_list[i].events & EPOLLIN)
                {
                    handle_read();
                    cout << "do_pending_functors()\n";
                    do_pending_functors();
                }
            }
            else
            {
                //处理旧连接的请求消息
                if (_event_list[i].events & EPOLLIN)
                {
                    handle_massage(_event_list[i].data.fd);
                }
                    
            }
        }
    }
}

void Event_loop::handle_new_connnection(void)
{
    int new_sfd = _acceptor.accept();
    add_epoll_fd_read(new_sfd);                 //加入epoll监听当中
    Tcp_connection_ptr conn(new Tcp_connection(new_sfd, this));
    conn->set_connection_callback(_on_connection);
    conn->set_massage_callback(_on_massage);
    conn->set_close_callback(_on_close);

    _conns.insert(std::make_pair(new_sfd, conn));
    conn->handle_connnection_callback();
    cout << "event_loop::handle_new_connection()\n";
}

void Event_loop::handle_massage(int fd)
{
    bool is_closed = is_connection_close(fd);
    auto iter = _conns.find(fd);
    assert(iter != _conns.end());

    if (!is_closed)
    {
        iter->second->handle_massage_callback();
    }
    else
    {
        del_epoll_fd_read(fd);
        iter->second->handle_close_callback();
        _conns.erase(iter);
    }
}

int Event_loop::create_epoll_fd(void)
{
    int ret = epoll_create1(0);
    if (ret == -1)
    {
        perror("epoll_create");
        exit(-1);
    }
    return ret;
}

void Event_loop::add_epoll_fd_read(int fd)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    int ret = epoll_ctl(_efd, EPOLL_CTL_ADD, fd, &event);
    if (ret == -1)
    {
        perror("epoll_ctl");
        exit(-1);
    }
}

void Event_loop::del_epoll_fd_read(int fd)
{
    struct epoll_event event;
    event.data.fd = fd;
    int ret = epoll_ctl(_efd, EPOLL_CTL_DEL, fd, &event);
    if (ret == -1)
    {
        perror("epoll_ctl");
        exit(-1);
    }
}

bool Event_loop::is_connection_close(int fd)
{
    int ret;
    do
    {
        char buf[1024] = {0};
        ret = recv(fd, buf, sizeof(buf), MSG_PEEK);
    }while (ret == -1 && errno == EINTR);

    return (ret == 0);
}

int Event_loop::create_eventfd(void)
{
    int fd = ::eventfd(0, 0);
    if (fd == -1)
    {
        perror("eventfd");
        return -1;
    }
    return fd;
}

void Event_loop::handle_read(void)
{
    uint64_t read_n;
    int ret = ::read(_eventfd, &read_n, sizeof(read_n));
    if (ret != sizeof(read_n))
    {
        perror("read");
        exit(-1);
    }
}

void Event_loop::wakeup(void)
{
    uint64_t read_n = 666;
    int ret = ::write(_eventfd, &read_n, sizeof(read_n));
    if (ret != sizeof(read_n))
    {
        perror("write");
        exit(-1);
    }
}

void Event_loop::do_pending_functors(void)
{
    vector<Functor> vec;
    {
    Mutex_lock_guard autolock(_mutex);
    _pending_functors.swap(vec);
    }

    for (auto & functor : vec)
    {
        functor();
    }
}

