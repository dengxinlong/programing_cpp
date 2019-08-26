#include "eventfd_thread.h"

#include <stdio.h>
#include <unistd.h>
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
        ::srand(::clock());
        int number = ::rand() % 100;
        cout << "get a random number = " << number << endl;
    }
};

int main(void)
{
    Eventfd_thread eventfd_thread(std::bind(&Task::process, Task()));
    eventfd_thread.start();             //创建子线程以及eventfd事件
    
    int cnt = 20;
    while (cnt--)
    {
        cout << "main_thread notify sub_thread...\n";
        eventfd_thread.wakeup();
        ::sleep(1);
    }

    eventfd_thread.stop();


    return 0;
}