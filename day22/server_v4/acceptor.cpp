#include "acceptor.h"

#include <stdlib.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <errno.h>

Acceptor::Acceptor(const string & ip, unsigned short port)
: _addr(ip, port)
, _listen_sock()
{}

void Acceptor::ready(void)
{
    set_reuse_addr(true);
    set_reuse_port(true);
    bind();
    listen();
}

int Acceptor::accept(void)
{
    int new_sfd = ::accept(_listen_sock.get_fd(), NULL, NULL);
    if (new_sfd == -1)
    {
        perror("accept");
        return -1;
    }
    return new_sfd;
}

void Acceptor::set_reuse_addr(bool on)
{
    int one = on;
    if (setsockopt(_listen_sock.get_fd(), SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0)
    {
        perror("setsockopt");
        exit(-1);
    }
}

void Acceptor::set_reuse_port(bool on)
{
    int one = on;
    if (setsockopt(_listen_sock.get_fd(), SOL_SOCKET, SO_REUSEPORT, &one, sizeof(one)) < 0)
    {
        perror("setsockopt");
        exit(-1);
    }
}

void Acceptor::bind(void)
{
    int ret = ::bind(_listen_sock.get_fd(), (struct sockaddr *)_addr.get_inet_addr_ptr(), \
                    sizeof(struct sockaddr));
    if (ret == -1)
    {
        perror("bind");
        exit(-1);
    }

}

void Acceptor::listen(void)
{
    int ret = ::listen(_listen_sock.get_fd(), 10);
    if (ret == -1)
    {
        perror("listen");
        exit(-1);
    }
}
