#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using std::vector;
using std::cout;
using std::endl;

void test0(void)
{
    vector<int> vec = {1, 3, 5, 0, 3, 6, 8, 1, 4};
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;

#if 0
    std::remove(vec.begin(), vec.end(), 1);                 //remove本质上并没有删除元素，只是把不符合条件的元素移动到序列的前面，
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));           
    cout << endl;
#endif
    typename vector<int>::iterator iter = std::remove(vec.begin(), vec.end(), 1);           //要删除元素还需要通过容器测成员函数erase
    vec.erase(iter, vec.end());
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}

//迭代器失效问题
void test1(void)
{
    vector<int> vec = {1, 3, 5, 0, 3, 6, 8, 1, 4};
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;

    //这里产生迭代器失效问题
    bool flag = true;
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)        
    {
        cout << *iter << " ";
        if (flag)
        {
            vec.push_back(666);
            flag = false;
        }
    }
    cout << endl;

}

//迭代器失效问题
void test2(void)
{
    vector<int> vec;
    cout << "vec.size() = " << vec.size() << endl;
    cout << "vec.capacity() = " << vec.capacity() << endl;

    vec.push_back(1);
    cout << "vec.size() = " << vec.size() << endl;
    cout << "vec.capacity() = " << vec.capacity() << endl;

    vec.push_back(2);
    cout << "vec.size() = " << vec.size() << endl;
    cout << "vec.capacity() = " << vec.capacity() << endl;

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl;

    //这里产生迭代器失效问题
    bool flag = true;
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)            //迭代器失效问题直接导致段错误   
    {
        cout << *iter << " ";
        if (flag)
        {
            vec.push_back(666);
            cout << "vec.size() = " << vec.size() << endl;
            cout << "vec.capacity() = " << vec.capacity() << endl;
            //iter = vec.begin();// + 1;                //一种解决办法
            flag = false;
        }
    }
    cout << endl;

}



int main(void)
{
    //test0();
    //test1();
    test2();

    return 0;
}