#ifndef __WORK_THREAD_H__
#define __WORK_THREAD_H__

#include "thread_t.h"
#include "thread_pool.h"
#include <iostream>

class Work_thread
: public Thread_t
{
public:
    Work_thread(Thread_pool & thread_pool);
    ~Work_thread();
private:
    void run(void) override;
    Thread_pool & _thread_pool;
};






#endif