#include <iostream>
#include <cstring>
#include "cow_string.h"

using std::endl;
using std::cout;

int main(void)
{
    Cow_string str("hello, world");
    str[0] = 'x';

    cout << str << endl;
    


    return 0;
}