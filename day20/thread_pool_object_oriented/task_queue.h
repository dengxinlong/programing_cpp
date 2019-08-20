#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__


#include "mutexlock_t.h"
#include "condition_t.h"
#include "task.h"
#include <queue>

using std::queue;

using ElemType = Task *;

class Task_queue
{
public:
    Task_queue(size_t size);

    bool empty(void) const;
    bool full(void) const;
    void push(ElemType val);
    ElemType pop(void);
    void wakeup(void);

private:
    size_t _size;
    queue<ElemType> _que;
    Mutex_lock _mutex;
    Condition _not_full;
    Condition _not_empty;
    bool _flag;
};










#endif 