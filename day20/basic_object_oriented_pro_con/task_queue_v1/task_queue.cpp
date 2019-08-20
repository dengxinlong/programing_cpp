#include "task_queue.h"


Task_queue::Task_queue(size_t size)
: _size(size)
, _mutex()
, _not_full(_mutex)
, _not_empty(_mutex)
{}
/*
Task_queue::Task_queue(size_t size)
: _size(size)
, _mutex()
, _cond(_mutex)
{}*/


bool Task_queue::empty(void) const
{
    return _que.size() == 0;
}

bool Task_queue::full(void) const
{
    return _que.size() == _size;
}

void Task_queue::push(int val)
{
    Mutex_lock_guard autolock(_mutex);
    while (full())
    {
        _not_full.wait();
    }

    _que.push(val);

    _not_empty.notify();
}

int Task_queue::pop(void)
{
    Mutex_lock_guard autolock(_mutex);

    while (empty())
    {
        _not_empty.wait();
    }

    int elem = _que.front();
    _que.pop();

    _not_full.notify();

    return elem;
}