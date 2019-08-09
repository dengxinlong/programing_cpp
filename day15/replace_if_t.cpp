#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::replace_if;
using std::ostream_iterator;

bool contidion(int val)
{
    return val > 5;
}

void test0(void)
{
    vector<int> vec = {1, 2, 5, 9, 10, 3, 1};

    replace_if(vec.begin(), vec.end(), contidion, 666);             //采用直接调用函数对象的形式
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
}

void test1(void)
{
    vector<int> vec = {1, 2, 5, 9, 10, 3, 1};

    replace_if(vec.begin(), vec.end(), std::bind1st(std::less<int>(), 5), 666);         //采用bind1st的方式来调用需要两个参数的函数对象
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
}

void test2(void)
{
    vector<int> vec = {1, 2, 5, 9, 10, 3, 1};

    replace_if(vec.begin(), vec.end(), std::bind2nd(std::less<int>(), 5), 666);         //采用bind2nd的方式来调用需要两个参数的函数对象
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
}

int main(void)
{
    //test0();
    //test1();
    test2();
    
    return 0;
}