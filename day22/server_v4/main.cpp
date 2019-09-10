#include "thread_t.h"
#include "task_queue.h"
#include "thread_pool.h"
#include "task.h"
#include "tcp_connection.h"
#include "tcp_server.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <memory>
#include <string>
#include <functional>

using std::cout;
using std::endl;
using std::string;

using Tcp_connection_ptr =std::shared_ptr<Tcp_connection>;

Thread_pool * gthread_pool_ptr = nullptr;


class Mytask
: public Task
{
public:
    Mytask(const string & msg, const Tcp_connection_ptr & conn)
    : _msg(msg)
    , _conn(conn)
    {}

    //这个任务由线程池中的线程来完成
    void process(void) override
    {
        //deal with _msg
        //decode
        //compute
        //encode
       // cout << "main: process\n";
        string response_str = _msg;
        //_msg.append("ddd");
        response_str.append(std::to_string(pthread_self()));
        //_conn->send(response_str); //这里由线程池中的子线程来完成数据的发送工作(应由主线程[IO线程]完成)，这样设计是不合理的
                                    //数据的发送工作应该由主线程(io线程)来完成
                                    //将send函数的执行延迟到io线程来完成
        _conn->send_in_loop(response_str);            //把io操作交给io线程来完成
    }   

private:
    string _msg;
    const Tcp_connection_ptr _conn;
};


void on_connection(const Tcp_connection_ptr & conn)
{
    cout << conn->to_string() << " has connected" << endl;
    conn->send("welcome to connect");
}

void on_massage(const Tcp_connection_ptr & conn)
{
    cout << "on_massage....." << endl;
    string msg = conn->receive();
    cout << ">>receive msg: " << msg << endl;

    /*
    //业务逻辑处理交给线程池来完成...
    //decode...
    //compute...
    //code...
    conn->send(msg);
    */

    gthread_pool_ptr->add_task(new Mytask(msg, conn));     //往线程池中添加任务
}

void on_close(const Tcp_connection_ptr & conn)
{
    cout << "on_close...." << endl;
    cout << conn->to_string() << " has closed!" << endl;
}

int main(void)
{
    Thread_pool thread_pool(4, 10);
    thread_pool.start();
    gthread_pool_ptr = &thread_pool;

    Tcp_server server("192.168.3.90", 6666);
    server.set_connection_callback(on_connection);
    server.set_massage_callback(on_massage);
    server.set_close_callback(on_close);
    server.start();


    thread_pool.stop();

    return 0;
}