#ifndef __THREAD_T_H__
#define __THREAD_T_H__

#include "noncopyable.h"

#include <pthread.h>

#include <iostream>
#include <functional>


class Noncopy;              //前向声明
class Thread_t
: public Noncopy
{
public:
    using Thread_callback = std::function<void(void)>;
    explicit
    Thread_t(Thread_callback && callback);

    ~Thread_t();
    
    void start(void);
    void join(void);

private:
    static void * thread_handle(void * ptr);

private:
    pthread_t _pthid;
    bool _is_running;
    Thread_callback _callback;

};












#endif 