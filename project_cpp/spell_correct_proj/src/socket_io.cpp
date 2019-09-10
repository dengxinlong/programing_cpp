#include "socket_io.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

Socket_io::Socket_io(int fd)
: _fd(fd)
{}

int Socket_io::read_n(void * buf, int length)
{
    int left = length;
    char * p = (char *)buf;
    while (left > 0)
    {
        int ret = read(_fd, p, left);
        if (ret == -1 && errno == EINTR)
            continue;
        else if (ret == -1)
        {
            perror("read");
            return length - left;
        }
        else if (ret == 0)
        {
            return length - left;
        }
        else 
        {
            left -= ret;
            p += ret;
        }
    }
    return length - left;
    
}

//每次读取一行数据
int Socket_io::readline(void * buf, int max_length)
{
    int left = max_length - 1;
    char * p = (char *)buf;
    int ret = 0;
    int total = 0;
    while (left > 0)
    {
        ret = recv_peek(p, left);           //从内核缓冲区中读取数据，同时内核缓冲区中的数据不会消失
        //查找 '\n'
        for (int i = 0; i < ret; ++i)
        {
            if (p[i] == '\n')
            {
                int size = i + 1;
                read_n(p, size);          //真正从内核缓冲区中读取数据，同时内核缓冲区中的数据会消失
                total += size;
                p += size;
                *p = '\0';
                return total;
            }
        }
        //所需要读取的max_length个数据中不足一行，则就读取max_length个数据
        read_n(p, ret);
        left -= ret;
        p += ret;
        total += ret;
    }
    *p = '\0';
    return total;

}

int Socket_io::write_n(const char * buf, int length)
{
    int left = length;
    const char * p = buf;
    while (left > 0)
    {
        int ret = write(_fd, p, left);
        if (ret == -1 && errno == EINTR)
            continue;
        else if (ret == -1)
        {
            perror("write");
            return length - left;
        }
        else 
        {
            left -= ret;
            p += ret;
        }
    }
    return length - left;
}

int Socket_io::recv_peek(void * buf, int length)
{
    char * p = (char *)buf;
    int ret = recv(_fd, p, length, MSG_PEEK);
    if (ret == -1)
    {
        perror("recv");
        return -1;
    }
    return ret;
}
