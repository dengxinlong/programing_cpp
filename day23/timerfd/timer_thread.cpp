#include "timer_thread.h"

Timer_thread::Timer_thread(int init_time, int periodic_time, Timerfd_callback && callback)
: _timer_fd(init_time, periodic_time, std::move(callback))
, _thread(std::bind(&Timerfd::start, std::ref(_timer_fd)))
{}

void Timer_thread::start(void)
{
    _thread.start();
    cout << "Timer_thread::start" << endl;
}

void Timer_thread::stop(void)
{
    _timer_fd.stop();
    _thread.join();
    cout << "Timer_thread::stop()" << endl;
}