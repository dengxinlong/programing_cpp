#include "producer.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>

using std::endl;
using std::cout;


void Producer::run(Task_queue<int> & task_queue)
{
    int cnt = 20;
    ::srand(time(nullptr));
    while (cnt--)
    {
        int number = rand() % 100;
        task_queue.push(number);

        cout << ">>producer thread: " << pthread_self()
             << " produce a number = " << number << endl;
    }

    //cout << "-------------------------------\n";

}

#if 0
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
#endif