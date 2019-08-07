#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::set;

template <class Containter>
void display(const Containter & cont)
{
    for (const auto & elem : cont)
    {
        cout << elem << " ";
    }
    cout << endl;
}

void test0(void)
{
    set<int> numbers;

    cout << "numbers's size is " << numbers.size() << endl;

    numbers.insert(1);
    numbers.insert(2);
    numbers.insert(3);

    cout << "numbers's size is " << numbers.size() << endl;
    display(numbers);
}

void test1(void)
{
    int arr[5] = {2, 5, 1, 0, 6}; 
    set<int> numbers(arr, arr + 5);
    display(numbers);

    //numbers[0];  //error
    set<int>::iterator iter = numbers.begin();
    cout << *iter << endl;
    //*iter = 10; //error，红黑树不支持修改元素，只能删除元素和增加元素
    numbers.erase(iter);
    display(numbers);

    std::pair<set<int>::iterator, bool> ret = numbers.insert(-1);
    if (ret.second)
    {
        cout << "插入成功" << endl;
        cout << "插入的值为：" << *ret.first << endl;
    }
    else
    {
        cout << "插入失败\n";
    }

    if (numbers.count(2))
        cout << "查找成功.\n";
    else
        cout << "查找失败， numbers中没有该元素.\n";
    
    auto iter_find = numbers.find(2);
    if (iter_find != numbers.end())
    {
        cout << "查找成功.\n";
        cout << *iter_find << endl;
    }  
    else
        cout << "查找失败.\n";
}

int main(void)
{
    //test0();
    test1();
    return 0;
}