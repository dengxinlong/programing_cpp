#ifndef __EVENT_LOOP_H__
#define __EVENT_LOOP_H__

#include "tcp_connection.h"
#include "acceptor.h"

#include <sys/epoll.h>

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::shared_ptr;

class Event_loop
{
public:
    using Tcp_connection_ptr = shared_ptr<Tcp_connection>;     
    using Tcp_connection_callback = std::function<void(const Tcp_connection_ptr &)>;

    Event_loop(Acceptor & acceptor);
    void loop(void);
    void un_loop(void);
    void set_connection_callback(Tcp_connection_callback && callback);
    void set_massage_callback(Tcp_connection_callback && callback);
    void set_close_callback(Tcp_connection_callback && callback);

private:
    void wait_epoll_fd(void);
    void handle_new_connnection(void);
    void handle_massage(int fd);
    int create_epoll_fd(void);

    void add_epoll_fd_read(int fd);
    void del_epoll_fd_read(int fd);
    bool is_connection_close(int fd);


private:
    int _efd;
    Acceptor & _acceptor;
    vector<struct epoll_event> _event_list;
    map<int, Tcp_connection_ptr> _conns;
    bool _is_looping;

    Tcp_connection_callback _on_connection;
    Tcp_connection_callback _on_massage;
    Tcp_connection_callback _on_close;

};




#endif