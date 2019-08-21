#include "acceptor.h"
#include "tcp_connection.h"
#include "event_loop.h"

#include <functional>
#include <memory>
#include <iostream>

using std::cout;
using std::endl;

using Tcp_connection_ptr = std::shared_ptr<Tcp_connection>;

void on_connection(const Tcp_connection_ptr & conn)
{
    cout << conn->to_string() << " has connected" << endl;
    conn->send("welcome to connect");
}

void on_massage(const Tcp_connection_ptr & conn)
{
    string msg = conn->receive();
    cout << ">> receive msg from client: " << msg << endl;
    //....其他处理
    conn->send(msg);
}

void on_close(const Tcp_connection_ptr & conn)
{
    cout << ">> " << conn->to_string() << " has closed." << endl;
}


int main(void)
{
    Acceptor acceptor("192.168.5.90", 6666);
    acceptor.ready();

    Event_loop loop(acceptor);
    loop.set_connection_callback(on_connection);
    loop.set_massage_callback(on_massage);
    loop.set_close_callback(on_close);
    loop.loop();


    return 0;
}
