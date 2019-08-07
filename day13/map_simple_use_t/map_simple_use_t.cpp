#include <math.h>

#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;
using std::ostream;

//定义一个显示函数，用于显示map中的数据
template <class Containter>
void display(const Containter & cont)
{
    for (auto elem : cont)
    {
        cout << elem.first << "-->" << elem.second << endl;
    }

#if 0
    for (auto iter = cont.begin(); iter != cont.end(); ++iter)
    {
        cout << iter->first << "-->" << iter->second << endl;
    }

    typename Containter::const_iterator iter = cont.begin();
    while (iter != cont.end())
    {
        cout << iter->first << "-->" << iter->second << endl;
        ++iter;
    }
#endif

}

void test0(void)
{
    map<int, string> status;
    status.insert(std::make_pair(1, "xiaoming"));
    status.insert(pair<int, string>(2, "xiaohua"));
    status.insert(std::make_pair(3, "xiaoli"));

    display(status);           //隐式调用
    //display<map<int, string>>(status); //显示调用
}

void test1(void)
{
    map<int, string> status = {
        std::make_pair(1, "xiaoming"),
        std::make_pair(2, "xiaohua"),
        pair<int, string>(2, "xiaozhang"),
        pair<int, string>(3, "xiaoli")
    };

    display(status);

    pair<map<int, string>::const_iterator, bool> insert_pair = status.insert(std::make_pair(3, "xiaogao"));
    //auto insert_pair = status.insert(std::make_pair(3, "xiaogao"));
    if (insert_pair.second)
    {
        cout << "插入元素成功" << endl;
        cout << "插入的元素为 " << insert_pair.first->first
             << "-->" << insert_pair.first->second << endl;
    }
    else
    {
        cout << "insert is error, the element is exit.\n";
    }
}

void test2(void)
{
    map<int, string> status = {
        std::make_pair(1, "xiaoming"),
        std::make_pair(2, "xiaohua"),
        pair<int, string>(3, "xiaoli")
    };

    display(status);

    status[2] = "xiaolong";     //如果关键字存在，则修改该元素
    cout << "使用下标运算符访问map" << endl;
    cout << "2-->" << status[2] << endl;
    cout << "4-->" << status[4] << endl;
    display(status);

    cout << "--------------\n";

    status[5] = "xiaoyu";           //没有对应关键字的元素，则直接添加
    display(status);

    map<int, string>::const_iterator iter = status.find(5);
    if (iter != status.end())
    {
        cout << "查找元素成功" << endl;
        cout << "结果为：\n" << iter->first << "-->"
             << iter->second << endl;
    }
    else
        cout << "查找元素失败" << endl;
    cout << "------------------\n";
    display(status);
}



class Point
{
public:
    Point(int ix, int iy)
    : _ix(ix)
    , _iy(iy)
    {
        cout << "Point(int, int)" << endl;
    }

    ~Point() = default;

    double get_instance(void) const
    {
        return sqrt(_ix * _ix + _iy * _iy);
    }


    friend ostream & operator<<(ostream & os, const Point & rhs);

private:
    int _ix;
    int _iy;
};

ostream & operator<<(ostream & os, const Point & rhs)
{
    os << "(" << rhs._ix << ", "
       << rhs._iy << ")";
    return os;
}


bool operator<(const Point & rhs, const Point & lhs)
{
    return rhs.get_instance() < lhs.get_instance();
}

//定义一个函数对象
struct Compator
{
    bool operator()(const Point & rhs, const Point & lhs)
    {
        cout << "operator()" << endl;
        return rhs.get_instance() < lhs.get_instance();
    }
};

void test3(void)
{
    map<Point, string, Compator> point_info = {
        std::make_pair(Point(0, 0), "原点"),
        std::make_pair(Point(1, 2), "一个点"),
        pair<Point, string>(Point(2, 2), "点")
    };
    auto iter = point_info.find(Point(1, 2));
    if (iter != point_info.end())
    {
        cout << "查找成功" << endl;
        cout << iter->first << "-->" << iter->second << endl;
    }

    display(point_info);
}

int main(void)
{
    //test0();
    //test1();
    //test2();
    test3();

    return 0;
}








