#ifndef __TCP_CONNECTION_H__
#define __TCP_CONNECTION_H__

#include "socket.h"
#include "inet_address.h"
#include "socket_io.h"
#include "noncopyable.h"

#include <string.h>

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Tcp_connection
: public Noncopy
{
public:
    Tcp_connection(int fd);
    ~Tcp_connection();

    string receive(void);
    void send(const string & msg);

    string to_string(void) const;
    void shutdown(void); 

private:
    Inet_address get_local_addr(int fd);
    Inet_address get_peer_addr(int fd);

private:
    Socket _sock;
    Socket_io _sock_io;
    Inet_address _local_addr;
    Inet_address _peer_addr;
    bool _is_shutdown_write;

};










#endif
