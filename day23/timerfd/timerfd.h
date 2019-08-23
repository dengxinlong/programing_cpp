#ifndef __TIMERFD_H__
#define __TIMERFD_H__

#include <sys/timerfd.h>

#include <iostream>
#include <functional>

using std::cout;
using std::endl;

class Timerfd
{
public:
    using Timerfd_callback = std::function<void(void)>;

    Timerfd(int, int, Timerfd_callback &&);
    ~Timerfd() {}

    void start(void);
    void stop(void);

private:
    int create_timerfd(void);
    void set_timerfd(int, int);
    void handle_read(void);

 
private:
    int _timerfd;
    Timerfd_callback _callback;
    int _init_time;
    int _periodic_time;
    bool _is_starting;

};










#endif