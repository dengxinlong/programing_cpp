#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include "thread_t.h"
#include "task_queue.h"

class Thread_t;
class Producer
: public Thread_t
{
public:
    Producer(Task_queue & task_queue);

private:
    void run(void) override;

private:
    Task_queue & _task_queue;
};












#endif 