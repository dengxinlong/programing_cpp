#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "thread_t.h"
#include "task_queue.h"
#include "task.h"

#include <iostream>
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class Thread_pool
{
public:
    Thread_pool(size_t, size_t);
    ~Thread_pool();

    void start(void);
    void stop(void);
    void add_task(Task * task);

private:
    friend class Work_thread;

    void thread_handle(void);
    Task * get_task(void);

private:
    size_t _thread_num;
    size_t _que_size;
    vector<unique_ptr<Thread_t>> _threads;
    Task_queue _task_queue;
    bool _is_exit;

};









#endif