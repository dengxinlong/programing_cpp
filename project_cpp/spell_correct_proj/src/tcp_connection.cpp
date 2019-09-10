#include "tcp_connection.h"
#include "event_loop.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include <sstream>

using std::ostringstream;

Tcp_connection::Tcp_connection(int fd, Event_loop * event_loop)
: _sock(fd)
, _sock_io(fd)
, _local_addr(get_local_addr(fd))
, _peer_addr(get_peer_addr(fd))
, _is_shutdown_write(false)
, _event_loop(event_loop)
{}

Tcp_connection::~Tcp_connection()
{
    if (!_is_shutdown_write)
        shutdown();
}

string Tcp_connection::receive(void)
{
    char buf[1024] = { 0 };
    _sock_io.readline(buf, sizeof(buf));
    return string(buf);
}

void Tcp_connection::send(const string & msg)
{
    _sock_io.write_n(msg.c_str(), msg.size());
}

void Tcp_connection::send_in_loop(const string & msg)
{
    if (_event_loop)
        _event_loop->run_in_loop(std::bind(&Tcp_connection::send, this, msg));
}

string Tcp_connection::to_string(void) const
{
    std::ostringstream oss;
    oss << _local_addr.get_ip() << ":" << _local_addr.get_port() << " --> "
        << _peer_addr.get_ip() << ":" << _peer_addr.get_port();
    return oss.str();
}

void Tcp_connection::shutdown(void)
{
    if (!_is_shutdown_write)
    {
        _is_shutdown_write = true;
        _sock.shutdown_write();
    }
}


Inet_address Tcp_connection::get_local_addr(int fd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    if (-1 == getsockname(_sock.get_fd(), (struct sockaddr *)&addr, &len))
        perror("getsockname");
    
    return Inet_address(addr);
}

Inet_address Tcp_connection::get_peer_addr(int fd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    if (-1 == getsockname(_sock.get_fd(), (struct sockaddr *)&addr, &len))
        perror("getsokname");
    
    return Inet_address(addr);
}


void Tcp_connection::set_connection_callback(const Tcp_connection_callback & callback)
{
    _on_connection = std::move(callback);
}

void Tcp_connection::set_massage_callback(const Tcp_connection_callback & callback)
{
    _on_massage = std::move(callback);
}

void Tcp_connection::set_close_callback(const Tcp_connection_callback & callback)
{
    _on_close = std::move(callback);
}

void Tcp_connection::handle_connnection_callback(void)
{
    if (_on_connection)
        _on_connection(shared_from_this());
}

void Tcp_connection::handle_massage_callback(void)
{
    if (_on_massage)
    {
        //cout << "tcp_connection::handle_massage_callback.\n";
        _on_massage(shared_from_this());
    }
       
}

void Tcp_connection::handle_close_callback(void)
{
    if (_on_close)
        _on_close(shared_from_this());
}
