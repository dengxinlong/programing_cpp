#include "tcp_connection.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#include <sstream>

using std::ostringstream;

Tcp_connection::Tcp_connection(int fd)
: _sock(fd)
, _sock_io(fd)
, _local_addr(get_local_addr(fd))
, _peer_addr(get_peer_addr(fd))
, _is_shutdown_write(false)
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

