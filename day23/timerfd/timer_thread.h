#ifndef __TIMER_THREAD_H__
#define __TIMER_THREAD_H__

#include "timerfd.h"
#include "thread_t.h"

#include <functional>

class Timer_thread
{
public:
    using Timerfd_callback = std::function<void(void)>;

    Timer_thread(int init_time, int periodic_time, Timerfd_callback && callback);

    void start(void);
    void stop(void);


private:
    Timerfd _timer_fd;
    Thread_t _thread;
};










#endif