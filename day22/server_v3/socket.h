#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <iostream>

using std::cout;
using std::endl;

class Socket
{
public:
    Socket();
    explicit
    Socket(int fd);

    void shutdown_write(void);
    int get_fd(void);

    ~Socket();

private:
    int _fd;
};













#endif
