#ifndef __EVENTFD_H__
#define __EVENTFD_H__

#include <iostream>
#include <functional>

using std::cout;
using std::endl;

class Eventfd
{
public:
    using Eventfd_callback = std::function<void(void)>;

    Eventfd(Eventfd_callback && callback);
    ~Eventfd();
    
    void start(void);
    void stop(void);
    void wakeup(void);

private:
    int create_eventfd(void);
    void handle_read(void);

private:
    int _fd;
    Eventfd_callback _callback;
    bool _is_starting;
};











#endif