#ifndef __MYTASK_H__
#define __MYTASK_H__

#include "task.h"
#include "tcp_connection.h"

#include <string>

using std::string;
using Tcp_connection_ptr =std::shared_ptr<Tcp_connection>;

class Mytask
: public Task
{
public:
    Mytask(const string & msg, const Tcp_connection_ptr & conn);

    //这个任务由线程池中的线程来完成
    void process(void) override;
    
private:
    string _msg;
    const Tcp_connection_ptr _conn;
};














#endif