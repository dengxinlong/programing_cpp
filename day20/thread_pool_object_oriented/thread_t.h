#ifndef __THREAD_T_H__
#define __THREAD_T_H__

#include "noncopyable.h"

#include <pthread.h>

#include <iostream>


class Noncopy;              //前向声明
class Thread_t
: public Noncopy
{
public:
    Thread_t()
    : _pthid(0)
    , _is_running(false)
    {}

    virtual ~Thread_t();
    
    void start(void);
    void join(void);

    static void * thread_handle(void *);

private:
    virtual void run(void) = 0;

private:
    pthread_t _pthid;
    bool _is_running;

};












#endif 