#include "mutexlock_t.h"

#include <stdlib.h>
#include <errno.h>

Mutex_lock::Mutex_lock()
{
    if (pthread_mutex_init(&_mutex, nullptr))
        perror("pthread_mutex_init: ");
}

Mutex_lock::~Mutex_lock()
{
    if (pthread_mutex_destroy(&_mutex))
        perror("pthread_mutex_destroy: ");
}

void Mutex_lock::lock(void)
{
    if (pthread_mutex_lock(&_mutex))
            perror("pthred_mutex_lock: ");
}

void Mutex_lock::unlock(void)
{
    if (pthread_mutex_unlock(&_mutex))
        perror("pthread_mutex_unlock: ");
}