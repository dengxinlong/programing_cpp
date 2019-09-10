/*
 *说明：该文件中的mytask类由线程池中的子线程来完成，
 *     主要完成计算类的任务，IO操作的任务交由主线程来完成
 */

#include "mytask.h"

Mytask::Mytask(const string & msg, const Tcp_connection_ptr & conn)
: _msg(msg)
, _conn(conn)
{}

//这个任务由线程池中的线程来完成
void Mytask::process(void)
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