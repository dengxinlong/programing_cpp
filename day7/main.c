#include <iostream>
#include <cstring>
#include "string_t.h"

using std::cout;
using std::endl;
using std::cin;

int main(void)
{

    String str = "hello, world";
    str.print();

    String str1 = "addd";
    str1.print();
    //cout << "--------------\n";
    if (str1 <= str)
        cout << "--------------\n";
    
    String str5 = "god and ghost";
    //cout << str5 << endl;

    cout << str5.c_str() << endl; 

    String str6;
    cin >> str6;

    return 0;
}