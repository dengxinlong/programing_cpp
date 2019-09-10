#include "acceptor.h"
#include "tcp_connection.h"
#include "event_loop.h"
#include "tcp_server.h"

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
    cout << ">> receive msg from client: " << msg << "size is " << msg.size() << endl;
    //....其他处理
    conn->send(msg);
}

void on_close(const Tcp_connection_ptr & conn)
{
    cout << ">> " << conn->to_string() << " has closed." << endl;
}


int main(void)
{
    Tcp_server tcp_server("192.168.5.90", 6666);
    tcp_server.set_connection_callback(on_connection);
    tcp_server.set_massage_callback(on_massage);
    tcp_server.set_close_callback(on_close);
    tcp_server.start();         //开始tcp连接后则没办法停止，因为其中的epoll机制中的epoll_wait是循环，
                                //必须使用线程池，在主线程中使得epoll_wait退出循环，主线程终止，进程终止


    return 0;
}
