#include "acceptor.h"
#include "tcp_connection.h"
#include "event_loop.h"
#include "tcp_server.h"
#include "thread_pool.h"

#include <functional>
#include <memory>
#include <iostream>

using std::cout;
using std::endl;

Thread_pool * gthread_pool_ptr = nullptr;

using Tcp_connection_ptr = std::shared_ptr<Tcp_connection>;

class My_task
{
public:

private:

}

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
    //decode
    //com
    //code
    //业务逻辑等操作交给线程池处理,  然后将业务逻辑处理好的数据交给主线程(IO线程)，由主线程将该数据发送给客户端，
    //这样做同时减轻了主线程计算的压力，同时又减少了子线程进行IO操作的压力，完成计算和IO操作的分离
    

    conn->send(msg);
}

void on_close(const Tcp_connection_ptr & conn)
{
    cout << ">> " << conn->to_string() << " has closed." << endl;
}


int main(void)
{
    Thread_pool thread_pool(3, 6);
    gthread_pool_ptr = &thread_pool;
    gthread_pool_ptr->start();

    Tcp_server tcp_server("192.168.5.90", 6666);
    tcp_server.set_connection_callback(on_connection);
    tcp_server.set_massage_callback(on_massage);
    tcp_server.set_close_callback(on_close);
    tcp_server.start();

    gthread_pool_ptr->stop();               //等待子线程完成任务
    return 0;
}
