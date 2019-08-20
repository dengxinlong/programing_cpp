#include "condition_t.h"

#include <errno.h>
#include <stdlib.h>

class Mutex_lock;
Condition::Condition(Mutex_lock & mutex)
: _mutex(mutex)
{
   if (pthread_cond_init(&_cond, nullptr))
        perror("pthread_cond_init");
}

Condition::~Condition()
{
    if (pthread_cond_destroy(&_cond))
        perror("pthread_cond_destroy");
}


void Condition::wait(void)
{
    if (pthread_cond_wait(&_cond, _mutex.get_mutex()))
        perror("pthread_cond_wait");
}

void Condition::notify(void)
{
    if (pthread_cond_signal(&_cond))
        perror("pthread_cond_signal");
}

void Condition::notifyall(void)
{
    if (pthread_cond_broadcast(&_cond))
        perror("pthread_cond_broadcast");
}