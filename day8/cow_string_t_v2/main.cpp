#include <iostream>
#include <cstring>
#include "cow_string.h"

using std::endl;
using std::cout;

int main(void)
{
    Cow_string str("hello, world");
    Cow_string str1 = str;

    cout << "str reference is " << str.ref_cnt() << endl;
    cout << "str1 reference is " << str1.ref_cnt() << endl;

    cout << "-----------------\n";
    str[0] = 'x';
    cout << "str is " << str << endl;
    cout << "str1 is " << str1 << endl;

    cout << "str reference is " << str.ref_cnt() << endl;
    cout << "str1 reference is " << str1.ref_cnt() << endl;

    printf("str's address is %p\n", str.c_str());
    printf("str1's address is %p\n", str1.c_str());

    cout << "-----------------\n";
    cout << str[0] << endl;

    cout << "str is " << str << endl;
    cout << "str1 is " << str1 << endl;

    cout << "str reference is " << str.ref_cnt() << endl;
    cout << "str1 reference is " << str1.ref_cnt() << endl;

    printf("str's address is %p\n", str.c_str());
    printf("str1's address is %p\n", str1.c_str());
    


    return 0;
}