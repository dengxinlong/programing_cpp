#include "inet_address.h"

#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>

Inet_address::Inet_address(const string & ip, unsigned short port)
{
    ::memset(&_addr, 0, sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}


Inet_address::Inet_address(const struct sockaddr_in & addr)
: _addr(addr)
{}


string Inet_address::get_ip(void) const
{
    return string(::inet_ntoa(_addr.sin_addr));
}


unsigned short Inet_address::get_port(void) const
{
    return ::ntohs(_addr.sin_port);
}


struct sockaddr_in * Inet_address::get_inet_addr_ptr(void)
{
    return &_addr;
}




