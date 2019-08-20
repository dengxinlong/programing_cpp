#include "thread_pool.h"
#include "work_thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

Thread_pool::Thread_pool(size_t thread_num, size_t que_size)
: _thread_num(thread_num)
, _que_size(que_size)
, _task_queue(_que_size)
, _is_exit(false)
{
    _threads.reserve(_thread_num);
}

Thread_pool::~Thread_pool()
{
    if (!_is_exit)
        stop();
}

void Thread_pool::start(void)
{
    for (int i = 0; i < _thread_num; ++i)
    {
        unique_ptr<Thread_t> thread(new Work_thread(*this));
        _threads.push_back(std::move(thread));
    }

    for (auto & thread : _threads)
        thread->start();            //创建子线程
}

void Thread_pool::stop(void)
{
    if (!_is_exit)
    {
        while (!_task_queue.empty())
        {
            sleep(1);
        }

        _is_exit = true;
        _task_queue.wakeup();

        for (auto & thread : _threads)
        {
            thread->join();
        }
    }
}
void Thread_pool::add_task(Task * task)
{
    _task_queue.push(task);
}

void Thread_pool::thread_handle(void)
{
    while (!_is_exit)
    {
        Task * task = get_task();
        if (task)
            task->process();
    }   
}

Task * Thread_pool::get_task(void)
{
    return _task_queue.pop();
}