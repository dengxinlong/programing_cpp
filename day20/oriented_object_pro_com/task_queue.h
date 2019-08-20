#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__


#include "mutexlock_t.h"
#include "condition_t.h"
#include <queue>

using std::queue;

class Task_queue
{
public:
    Task_queue(size_t size);

    bool empty(void) const;
    bool full(void) const;
    void push(int val);
    int pop(void);

private:
    size_t _size;
    queue<int> _que;
    Mutex_lock _mutex;
    Condition _not_full;
    Condition _not_empty;
};










#endif 