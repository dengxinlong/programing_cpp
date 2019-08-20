#include "consumer.h"
#include "task_queue.h"

#include <iostream>

using std::cout;
using std::endl;

Consumer::Consumer(Task_queue & task_que)
: _task_que(task_que)
{}

void Consumer::run(void) 
{
    int cnt = 20;
    while (cnt--)
    {
        int number = _task_que.pop();
        cout << ">>consumer thread: " << pthread_self()
             << " consum a number = " << number << endl;
    }
}