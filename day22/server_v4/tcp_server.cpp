#include "tcp_server.h"

Tcp_server::Tcp_server(const string & ip, unsigned short port)
: _acceptor(ip, port)
, _event_loop(_acceptor)
{}

void Tcp_server::start(void)
{
    _acceptor.ready();     //等待着客户端的连接
    _event_loop.loop();
}

void Tcp_server::set_connection_callback(Tcp_connection_callback && callback)
{
    _event_loop.set_connection_callback(std::move(callback));
}   

void Tcp_server::set_massage_callback(Tcp_connection_callback && callback)
{
    _event_loop.set_massage_callback(std::move(callback));
}

void Tcp_server::set_close_callback(Tcp_connection_callback && callback)
{
    _event_loop.set_close_callback(std::move(callback));
}

