#include <iostream>
#include "log4cpp_t.h"

using std::cout;
using std::endl;
using namespace log4cpp;

int main(void)
{
    Mylogger * ptr = Mylogger::getInstance();
    ptr->warn("fkja;lf");

    return 0;
}