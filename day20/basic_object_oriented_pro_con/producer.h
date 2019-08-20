#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include "thread_t.h"
#include "task_queue.h"

class Thread_t;
class Producer
{
public:
    void run(Task_queue<int> & task_queue);
};

/*
class Thread_t;
class Producer
{
public:
    Producer(Task_queue & task_queue);

private:
    void run(void);

private:
    Task_queue & _task_queue;
};*/













#endif 