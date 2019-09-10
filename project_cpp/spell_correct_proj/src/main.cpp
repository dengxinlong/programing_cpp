#include "thread_t.h"
#include "task_queue.h"
#include "thread_pool.h"
#include "task.h"
#include "tcp_connection.h"
#include "tcp_server.h"
#include "config.h"
#include "dict_producer.h"
#include "mytask.h"

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

    Config conf("./config");                        //读取配置文件
    map<string, string> conf_map = conf.get_conf_map();

    Dict_producer dict_producer(conf_map["English_path"]);
    dict_producer.build_en_dict();
    dict_producer.store_dict(conf_map["English_dict_path"]);
    dict_producer.build_index_file(conf_map["Index_file"]);

    Tcp_server server(conf_map["ip"], (unsigned short)stoi(conf_map["port"]));   //TCP连接

    server.set_connection_callback(on_connection);
    server.set_massage_callback(on_massage);
    server.set_close_callback(on_close);
    server.start();

   

/*
    Dict_producer dict_producer(conf_map["English_path"]);
    dict_producer.build_en_dict();
    dict_producer.store_dict(conf_map["English_dict_path"]);
#if 0
    dict_producer.show_dict();
#endif
    dict_producer.store_word_to_dict("zoo");
#if 0
    cout << "end of add zoo\n";
    dict_producer.show_dict();
    cout << "----------------index_file-------------\n";
#endif
    dict_producer.build_index_file(conf_map["Index_file"]);
*/

    thread_pool.stop();

    return 0;
}