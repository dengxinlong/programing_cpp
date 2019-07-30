#include <iostream>
#include <cstring>
#include "cow_string.h"

using std::endl;
using std::cout;

int main(void)
{
    Cow_string str("hello, world");
    cout << str << endl;
    cout << str.ref_cnt() << endl;

    Cow_string str1 = str;
    cout << str1 << endl;
    cout << str.ref_cnt() << endl;

    cout << "modify after" << endl;
    str1[0] = 'H';

    cout << str << endl;
    printf("str's addresss is %p.\n", str.c_str());
    cout << str.ref_cnt() << endl;

    cout << str1 << endl;
    printf("st1's addresss is %p.\n", str1.c_str());
    cout << str1.ref_cnt() << endl;


    return 0;
}