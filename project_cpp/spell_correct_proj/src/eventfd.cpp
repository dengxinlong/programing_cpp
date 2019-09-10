#include "eventfd.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/eventfd.h>
#include <poll.h>

#include <iostream>

using std::cout;
using std::endl;

Eventfd::Eventfd(Eventfd_callback && callback)
: _fd(create_eventfd())
, _callback(std::move(callback))
, _is_starting(false)
{

}

int Eventfd::create_eventfd(void)
{
    int ret = ::eventfd(0, 0);
    if (ret == -1)
    {
        perror("eventfd");
        exit(-1);
    }

    return ret;
}

Eventfd::~Eventfd()
{
    if (_is_starting)
        stop();
}

void Eventfd::start(void)
{
    _is_starting = true;
    struct pollfd pfd;
    pfd.fd = _fd;
    pfd.events = POLLIN;
    while (_is_starting)
    {
        int ready_n = poll(&pfd, 1, 2000);
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
            cout << "time_out" << endl;
        else 
        {
            if (pfd.revents & POLLIN)
            {
                handle_read();          //处理读事件
                if (_callback)
                    _callback();        //执行任务
            }
        }
    }
}

void Eventfd::stop(void)
{
    _is_starting = false;
}

//通过wakeup方法往计数器中写入数据，然后触发poll事件，通过handle_read来读取计数器中的数据，然后执行任务
void Eventfd::wakeup(void)
{
    uint64_t value = 6666;
    int ret = ::write(_fd, &value, sizeof(value));
    if (ret != sizeof(value))
    {
        perror("write");
        exit(-1);
    }
}

void Eventfd::handle_read(void)
{
    uint64_t read_n;
    int ret = ::read(_fd, &read_n, sizeof(read_n));
    if (ret != sizeof(sizeof(read_n)))
    {
        perror("read");
        exit(-1);
    }
    cout << "sub_thread read...";
    cout << "read_value is " << read_n << endl;
}