#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include "mutexlock_t.h"
#include "thread_t.h"
#include "task_queue.h"



class Consumer
{
public:
    void run(Task_queue<int> & task_que);

};

/*
class Task_queue;
class Consumer
{
public:
    Consumer(Task_queue & task_que);

    void run(void);
private:
    Task_queue & _task_que;
};*/










#endif 