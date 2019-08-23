#include "timerfd.h"

#include <errno.h>
#include <stdio.h>
#include <poll.h>
#include <unistd.h>


Timerfd::Timerfd(int init_time, int periodic_time, Timerfd_callback && callback) 
: _timerfd(create_timerfd())
, _init_time(init_time)
, _periodic_time(periodic_time)
, _callback(std::move(callback))
, _is_starting(false)
{}


void Timerfd::start(void)
{
    _is_starting = true;
    set_timerfd(_init_time, _periodic_time);
    
    struct pollfd pfd;
    pfd.fd = _timerfd;
    pfd.events = POLLIN;
    
    while (_is_starting)
    {
        int ready_n = ::poll(&pfd, 1, 3000);
        if (ready_n == -1 && errno == EINTR)
        {
            continue;
        }
        else if (ready_n == -1)
        {
            perror("poll");
            exit(-1);
        }
        else if (ready_n == 0)
        {
            cout << "time_out" << endl;
        }
        else
        {
            if (pfd.revents & POLLIN)
            {
                handle_read();
                if (_callback)
                    _callback();
            }
        }
        cout << "_is_starting = " << _is_starting << endl;
     }

}

void Timerfd::stop(void)
{
    set_timerfd(0, 0);
    cout << "stop: _is_starting = " << _is_starting << endl;
    if (_is_starting)
        _is_starting = false;
    cout << "Timerfd::stop" << endl;
}

int Timerfd::create_timerfd(void)
{
    int fd = timerfd_create(CLOCK_REALTIME, 0);
    if (fd == -1)
    {
        perror("timerfd_create");
        return -1;
    }
    return fd;
}

void Timerfd::set_timerfd(int init_time, int periodic_time)
{   
    struct itimerspec itimer;
    itimer.it_value.tv_sec = init_time;
    itimer.it_value.tv_nsec = 0;
    itimer.it_interval.tv_sec = periodic_time;
    itimer.it_interval.tv_nsec = 0;
    if (timerfd_settime(_timerfd, 0, &itimer, nullptr) == -1)
    {
        perror("timerfd_settime");
        exit(-1);
    }
}

void Timerfd::handle_read(void)
{
    uint64_t size;
    int ret = ::read(_timerfd, &size, sizeof(size));
    if (ret != sizeof(size))
    {
        perror("read");
        exit(-1);
    }
}