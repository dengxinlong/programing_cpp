#ifndef __TCP_CONNECTION_H__
#define __TCP_CONNECTION_H__

#include "socket.h"
#include "inet_address.h"
#include "socket_io.h"
#include "noncopyable.h"


#include <string.h>

#include <iostream>
#include <string>
#include <memory>
#include <functional>

using std::cout;
using std::endl;
using std::string;

class Tcp_connection;
class Event_loop;

class Tcp_connection
: public Noncopy
, public std::enable_shared_from_this<Tcp_connection>
{
public:
    using Tcp_connection_ptr = std::shared_ptr<Tcp_connection>;
    using Tcp_connection_callback = std::function<void(const Tcp_connection_ptr &)>;

    Tcp_connection(int fd, Event_loop * event_loop);
    ~Tcp_connection();

    string receive(void);
    void send(const string & msg);
    void send_in_loop(const string & msg);

    string to_string(void) const;
    void shutdown(void); 

    void set_connection_callback(const Tcp_connection_callback & callback);
    void set_massage_callback(const Tcp_connection_callback & callback);
    void set_close_callback(const Tcp_connection_callback & callback);

    void handle_connnection_callback(void);  
    void handle_massage_callback(void);
    void handle_close_callback(void);

private:
    Inet_address get_local_addr(int fd);
    Inet_address get_peer_addr(int fd);

private:
    Socket _sock;
    Socket_io _sock_io;
    Inet_address _local_addr;
    Inet_address _peer_addr;
    bool _is_shutdown_write;

    Event_loop * _event_loop;

    Tcp_connection_callback _on_connection;
    Tcp_connection_callback _on_massage;
    Tcp_connection_callback _on_close;

};










#endif
