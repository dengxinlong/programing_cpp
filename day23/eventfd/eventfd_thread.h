#ifndef __EVENTFD_THREAD_H__
#define __EVENTFD_THREAD_H__

#include "thread_t.h"
#include "eventfd.h"

#include <functional>

class Eventfd_thread
{
public:
    using Eventfd_thread_callback = std::function<void(void)>;

    Eventfd_thread(Eventfd_thread_callback && callback);

    void start(void);
    void stop(void);
    void wakeup(void);

private:
    Eventfd _eventfd;
    Thread_t _thread;
};









#endif