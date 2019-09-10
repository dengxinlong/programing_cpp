#ifndef __MUTEXLOCK_T_H__
#define __MUTEXLOCK_T_H__

#include "noncopyable.h"

#include <pthread.h>

#include <iostream>

class Mutex_lock
: public Noncopy
{
public:
    Mutex_lock();
    ~Mutex_lock();

    void lock(void);

    void unlock(void);

    pthread_mutex_t * get_mutex(void) 
    {
        return &_mutex;
    }
private:
    pthread_mutex_t _mutex;
};

class Mutex_lock_guard
{
public:
    Mutex_lock_guard(Mutex_lock & mutex)
    : _mutex(mutex)
    {
        _mutex.lock();
    }

    ~Mutex_lock_guard()
    {
        _mutex.unlock();
    }

private:
    Mutex_lock & _mutex;
};














#endif