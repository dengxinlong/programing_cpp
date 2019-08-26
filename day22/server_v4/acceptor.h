#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "socket.h"
#include "inet_address.h"
#include "socket_io.h"
#include "tcp_connection.h"

#include <iostream>

using std::cout;
using std::endl;

class Acceptor
{
public:
    Acceptor(const string & ip, unsigned short port);
    void ready(void);

    int accept(void);
    int get_fd(void) 
    {
        return _listen_sock.get_fd();
    }

private:
    void set_reuse_addr(bool on);
    void set_reuse_port(bool on);
    void bind(void);
    void listen(void);


private:
    Inet_address _addr;
    Socket _listen_sock;
};









#endif
