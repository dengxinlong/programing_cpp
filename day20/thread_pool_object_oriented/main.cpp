#include "thread_t.h"
#include "task_queue.h"
#include "thread_pool.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class Mytask
: public Task
{
public:
    void process(void) override
    {
        ::srand(::time(nullptr));
        int number = ::rand() % 100;
        cout << "subthread id is " << pthread_self()
             << ": produce a number is " << number << endl;
    }
};

int main(void)
{
    Thread_pool thread_pool(4, 10);
    thread_pool.start();
    std::unique_ptr<Task> task(new Mytask);
    int cnt = 20;
    while (cnt--)
    {
        thread_pool.add_task(task.get());
        cout << ">> main thread: cnt = " << cnt << endl;
    }

    thread_pool.stop();

    return 0;
}