#include "producer.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>

using std::endl;
using std::cout;

Producer::Producer(Task_queue & task_queue)
: _task_queue(task_queue)
{}

void Producer::run(void) 
{
    int cnt = 20;
    ::srand(time(nullptr));
    while (cnt--)
    {
        int number = rand() % 100;
        _task_queue.push(number);

        cout << ">>producer thread: " << pthread_self()
             << " produce a number = " << number << endl;
    }
}