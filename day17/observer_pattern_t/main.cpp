#include "observer_t.h"
#include "subject_t.h"

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

int main(void)
{
    unique_ptr<Observer> baby(new Baby("xiaoming"));
    unique_ptr<Observer> nurse(new Nurse("xiaohua"));

    Ring ring;
    ring.attach(baby.get());
    ring.attach(nurse.get());

    
    Guest guest("xiaogao");

    guest.knock(ring);



    return 0;
}