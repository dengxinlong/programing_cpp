#include "thread_t.h"
#include "producer.h"
#include "consumer.h"
#include "task_queue.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

int main(void)
{
    Task_queue task_queue(10);
    std::unique_ptr<Thread_t> producer(new Producer(task_queue));
    std::unique_ptr<Thread_t> consumer(new Consumer(task_queue));
    producer->start();
    consumer->start();

    producer->join();
    consumer->join();

    return 0;
}