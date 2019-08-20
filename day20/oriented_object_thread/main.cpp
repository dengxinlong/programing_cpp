#include "thread_t.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class Thread_test
: public Thread_t
{
public:
    Thread_test() = default;
    ~Thread_test() = default;

    void run(void) override
    {
        int cnt = 20;

        ::srand(time(NULL));
        while (cnt--)
        {
            int number = rand() % 100;
            cout << ">>>random_num: " << number << endl;
            
        }
        //sleep(1);
    }
};



int main(void)
{
    std::unique_ptr<Thread_test> thread(new Thread_test());
    thread->start();

    thread->join();

    return 0;
}