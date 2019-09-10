#ifndef __SOCKET_IO_H__
#define __SOCKET_IO_H__

class Socket_io
{
public:
    explicit
    Socket_io(int fd);

    int read_n(void * buf, int length);
    int readline(void * buf, int max_length);
    int write_n(const char * buf, int length);

private:
    int recv_peek(void * buf, int length);

private:
    int _fd;
};











#endif