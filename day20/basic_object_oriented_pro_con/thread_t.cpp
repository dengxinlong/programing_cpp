#include "thread_t.h"

#include <iostream>

using std::cout;
using std::endl;

Thread_t::~Thread_t()
{
    if (_is_running)
    {
        pthread_detach(_pthid);
        std::cout << "~Thread_t()" << std::endl;
    }
        
}

void Thread_t::start(void)
{
    pthread_create(&_pthid, nullptr, thread_handle, this);
    _is_running = true;

}
void Thread_t::join(void)
{
    if (_is_running)
    {
        pthread_join(_pthid, nullptr);
    }
    _is_running = false;
}

void * Thread_t::thread_handle(void * ptr)
{
    Thread_t * pthread = static_cast<Thread_t *>(ptr);
    if (pthread)
        pthread->_callback();

    pthread_exit(nullptr);
}

