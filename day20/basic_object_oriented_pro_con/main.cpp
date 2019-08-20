#include "thread_t.h"
#include "producer.h"
#include "consumer.h"
#include "task_queue.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <memory>
#include <functional>

using std::cout;
using std::endl;

void func(int & val)
{
    cout << "test func, val: " << val << endl;
}

int main(void)
{

    Task_queue<int> task_queue(10);
    std::unique_ptr<Thread_t> producer(new Thread_t(std::bind(&Producer::run, Producer(), std::ref(task_queue))));
    std::unique_ptr<Thread_t> cunsumer(new Thread_t(std::bind(&Consumer::run, Consumer(), std::ref(task_queue))));
    producer->start();
    cunsumer->start();

    producer->join();
    cunsumer->join();

    return 0;
}