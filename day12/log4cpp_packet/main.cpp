#include <iostream>
#include "log4cpp_t.h"

using std::cout;
using std::endl;

int main(void)
{
    WARN("I am warn");

#if 0
    int value = 10;
    const char * str = "hello, world";
    WARN("I am warn, value is %d, str is %s\n", value, str);
#endif

    return 0;
}






