#include "eventfd_thread.h"

Eventfd_thread::Eventfd_thread(Eventfd_thread_callback && callback)
: _eventfd(std::move(callback))
, _thread(std::bind(&Eventfd::start, std::ref(_eventfd)))
{}

void Eventfd_thread::start(void)
{
    _thread.start();
}

void Eventfd_thread::stop(void)
{
    _eventfd.stop();
    _thread.join();
}

void Eventfd_thread::wakeup(void)
{
    _eventfd.wakeup();
}