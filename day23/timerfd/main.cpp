#include "timer_thread.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

using std::cout;
using std::endl;

class Task
{
public:
    void process(void)
    {
        //......some operator
        ::srand(::clock());
        int number = ::rand() % 100;
        cout << ">>get a number is " << number << endl;
    }
};

int main(void)
{
    Timer_thread timer_thread(3, 6, std::bind(&Task::process, Task()));
    timer_thread.start();
    ::sleep(15);
    timer_thread.stop();

    return 0;
}