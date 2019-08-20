#include "consumer.h"
#include "task_queue.h"

#include <iostream>

using std::cout;
using std::endl;

void Consumer::run(Task_queue<int> & task_que)
{
    int cnt = 20;
    while (cnt--)
    {
        int number = task_que.pop();
        cout << ">>consumer thread: " << pthread_self()
             << " consum a number = " << number << endl;
    }
}

/*()
void Consumer::run(void) 
{
    int cnt = 20;
    while (cnt--)
    {
        int number = _task_que.pop();
        cout << ">>consumer thread: " << pthread_self()
             << " consum a number = " << number << endl;
    }
}*/