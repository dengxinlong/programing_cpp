#ifndef __CONDITION_T_H__
#define __CONDITION_T_H__

#include "noncopyable.h"
#include "mutexlock_t.h"

#include <pthread.h>

class Mutex_lock;
class Condition
: public Noncopy
{
public:
    Condition(Mutex_lock & mutex);
    ~Condition();

    void wait(void);
    void notify(void);
    void notifyall(void);

private:
    pthread_cond_t _cond;
    Mutex_lock & _mutex;
};








#endif