#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include "acceptor.h"
#include "event_loop.h"
#include "tcp_connection.h"

#include <iostream>
#include <string>
#include <functional>
#include <memory>

using std::cout;
using std::endl;

class Tcp_server
{
public:
    using Tcp_connection_ptr = std::shared_ptr<Tcp_connection>;
    using Tcp_connection_callback = std::function<void(const Tcp_connection_ptr &)>;

    Tcp_server(const string & ip, unsigned short port);
    void start(void);
    void set_connection_callback(Tcp_connection_callback && callback);
    void set_massage_callback(Tcp_connection_callback && callback);
    void set_close_callback(Tcp_connection_callback && callback);


private:
    Acceptor _acceptor;
    Event_loop _event_loop;
};











#endif 