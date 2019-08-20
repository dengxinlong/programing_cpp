#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include "mutexlock_t.h"
#include "thread_t.h"
#include "task_queue.h"

class Task_queue;
class Consumer
: public Thread_t
{
public:
    Consumer(Task_queue & task_que);

private:
    void run(void) override;

private:
    Task_queue & _task_que;
};










#endif 