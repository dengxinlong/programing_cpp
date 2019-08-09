#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;

#if 0
void handle(int value)
{
    cout << value << " ";
}
#endif

void handle(int & value)
{
    value++;
    cout << value << " ";
}

void test0(void)
{
    vector<int> vec = {1, 2, 5, 9, 10, 3, 1};

    std::for_each(vec.begin(), vec.end(), handle);          //for_each相当于提供了一种遍历容器的操作，至于对容器中的数据执行何种操作，则由我们自己定义
    cout << endl;

    copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
}

void test1(void)
{
    vector<int> vec = {1, 2, 5, 9, 10, 3, 1};
    typename vector<int>::iterator iter = std::find(vec.begin(), vec.end(), 9);
    cout << *iter << endl;
    auto iter2 = std::upper_bound(vec.begin(), vec.end(), 2);           //查找第一个大于给定值的数，返回一个迭代器
    cout << *iter2 << endl;

    //std::sort(vec.begin(), vec.end()); 
    std::sort(vec.begin(), vec.end(), std::greater<int>());         //sort默认按照升序方式排序，也可以指定为降序方式
    copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;

    //auto iter1 = std::lower_bound(vec.begin(), vec.end(), 2);         //查找第一个大于等于给定值的数，返回指向该数的一个迭代器
    auto iter1 = std::upper_bound(vec.begin(), vec.end(), 2);           //查找第一个大于给定值的数，返回一个迭代器
    cout << *iter1 << endl;

}

int main(void)
{
    //test0();
    test1();

    return 0;
}