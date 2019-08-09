#include <iostream>
#include <vector>
#include <functional>

using std::cout;
using std::endl;
using std::vector;

void display(void)
{
    cout << "display() " << endl;
}

void print(void)
{ 
    cout << "print()" << endl;
}

typedef void(*Function)(void);              //重命名一个函数指针

class Example
{
public:
    Example() = default;

    void display(void)
    {
        cout << "Example::display()"  << endl;
    }

    int add(int x, int y)
    {
        return x + y;
    }

    int _data = 666;
};

void test0(void)
{
    void (*pfunc)(void);

    pfunc = display;
    pfunc();

    pfunc = print;
    pfunc();                //这里可以看成C语言的多态，一种函数对象，表现不同的行为
}

void test1(void)
{
    //pfunc称为回调函数
    Function pfunc = display;   //注册回调函数
    pfunc();        //执行回调函数

    pfunc = print;
    pfunc();
}

void test2(void)
{
    //函数类型的容器，专门用来存放函数对象，
    std::function<void()> func_cont;
    func_cont = display;
    func_cont();

    func_cont = print;
    func_cont();

    Example examp;
    //bind是一个函数模板，返回一个函数对象
    func_cont = std::bind(&Example::display, examp);
    func_cont();
}

int add(int x, int y)
{
    cout << "x = " << x
         << "; y = " << y << endl;
    
    return x + y;
}

void test3(void)
{
    auto func = std::bind(add, 1, 3);
    cout << "func(): " << func() << endl;
    cout << "func(): " << func(1, 2, 3, 666, 333) << endl;          //这里传入的参数都是无效参数，不会传入函数体内

    cout << "---------------\n";
    using namespace std::placeholders;
    auto func1 = std::bind(add, _1, 2);
     cout << "func1(): " << func1(1) << endl;

    cout << "---------------\n";
    auto func2 = std::bind(add, 1, _1);             //这里的_1只是一个占位符，也就是一个标记而已_1代表func2的第一个参数
    cout << "func2(): " << func2(2) << endl;

    Example examp;
    cout << "---------------\n";
    auto func3 = std::bind(&Example::add, examp, 1, 2);
    cout << "func3(): " << func3(2) << endl;

    cout << "---------------\n";
    auto func4 = std::bind(&Example::add, examp, _1, _2);
    cout << "func4(): " << func4(2, 55) << endl;

    cout << "---------------\n";
    auto func5 = std::bind(&Example::_data, examp);
    cout << "func5(): " << func5(2, 55) << endl;
}

void func(int x1, int x2, int x3, int & x4)
{
	cout << "(" << x1 
		 << ", " << x2 
		 << ", " << x3 
		 << ", " << x4 
		 << ")" << endl;
}

void test4(void)
{
    //bind中的占位符的位置代表着被绑定函数对象的形参的位置，
    //数字代表着生成的函数对象的实参的位置
    using namespace std::placeholders;
    int a = 10;
    auto f = std::bind(func, _3, _4, 444, a);           
    a = 555;
    f(1, 3, 4, 6);
}

int main(void)
{
    //test0();
    //test1();
    //test2();
    test4();


    return 0; 
}