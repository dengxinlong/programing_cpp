#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

#include "mutexlock_t.h"
#include "condition_t.h"
#include <queue>

using std::queue;

template <class T>
class Task_queue
{
public:
    Task_queue(size_t size)
    : _size(size)
    , _mutex()
    , _cond(_mutex)
    {}

    bool empty(void) const
    {
        return _que.size() == 0;
    }

    bool full(void) const
    {
        return _que.size() == _size;
    }

    void push(T elem)
    {
        Mutex_lock_guard autolock(_mutex);
        while (full())
        {
            _cond.wait();
        }

        _que.push(elem);

        _cond.notify();
    }

    T pop(void)
    {
        Mutex_lock_guard autolock(_mutex);

        while (empty())
        {
            _cond.wait();
        }

        int elem = _que.front();
        _que.pop();

        _cond.notify();

        return elem;
    }

private:
    size_t _size;
    queue<T> _que;
    Mutex_lock _mutex;
    //Condition _not_full;
    //Condition _not_empty;
    Condition _cond;
};










#endif 