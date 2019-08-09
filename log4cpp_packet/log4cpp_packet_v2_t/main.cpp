#include <iostream>
#include "log4cpp_t.h"

using std::cout;
using std::endl;

int main(void)
{
    int value = 19;
    WARN("I am warn");
    WARN("I am warn. %d", value);

    ERROR("I am ERROR");
    ERROR("I am ERROR. %d", value);

    INFO("I am INFO");
    INFO("I am INFO. %d", value);

    DEBUG("I am DEBUG");
    DEBUG("I am DEBUG. %d", value);

    return 0;
}






