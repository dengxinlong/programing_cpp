#include "work_thread.h"

using std::cout;

Work_thread::Work_thread(Thread_pool & thread_pool)
: _thread_pool(thread_pool)
{}

Work_thread::~Work_thread()
{
    cout << "~Worker_thread().\n";
}


void Work_thread::run(void)
{
    _thread_pool.thread_handle();
}
