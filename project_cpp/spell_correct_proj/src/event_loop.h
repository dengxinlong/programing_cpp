#ifndef __EVENT_LOOP_H__
#define __EVENT_LOOP_H__

//#include "tcp_connection.h"
#include "acceptor.h"
#include "mutexlock_t.h"

#include <sys/epoll.h>

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <memory>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::shared_ptr;
using std::vector;


class Tcp_connection;
class Event_loop
{
public:
    using Tcp_connection_ptr = shared_ptr<Tcp_connection>;     
    using Tcp_connection_callback = std::function<void(const Tcp_connection_ptr &)>;
    using Functor = std::function<void()>;

    Event_loop(Acceptor & acceptor);
    void loop(void);
    void un_loop(void);
    void set_connection_callback(Tcp_connection_callback && callback);
    void set_massage_callback(Tcp_connection_callback && callback);
    void set_close_callback(Tcp_connection_callback && callback);

    void run_in_loop(Functor && callback);

private:
    void wait_epoll_fd(void);
    void handle_new_connnection(void);
    void handle_massage(int fd);
    int create_epoll_fd(void);

    void add_epoll_fd_read(int fd);
    void del_epoll_fd_read(int fd);
    bool is_connection_close(int fd);

    void handle_read(void);
    void wakeup(void);
    int create_eventfd(void);
    void do_pending_functors(void);

    


private:
    int _efd;
    int _eventfd;                //用于当子线程完成计算任务时，触发主线程
    Acceptor & _acceptor;
    vector<struct epoll_event> _event_list;
    map<int, Tcp_connection_ptr> _conns;
    bool _is_looping;
    Mutex_lock _mutex;
    vector<Functor> _pending_functors;

    Tcp_connection_callback _on_connection;
    Tcp_connection_callback _on_massage;
    Tcp_connection_callback _on_close;

};




#endif