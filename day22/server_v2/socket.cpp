#include "socket.h"

#include <sys/types.h>         
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

Socket::Socket()
{
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd == -1)
    {
        perror("socket");
    }
}

Socket::Socket(int fd)
: _fd(fd)
{}

//使得服务器端处于半关闭状态，告诉对端本端将不会发数据给对方了
void Socket::shutdown_write(void)
{
    ::shutdown(_fd, SHUT_WR);
}

int Socket::get_fd(void)
{
    return _fd;
}

//析构该套接字对象时，把该套接字关闭
Socket::~Socket()
{
    ::close(_fd);
}