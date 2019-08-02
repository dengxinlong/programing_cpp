#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    virtual void print(void)
    {
        cout << "I am Base_class" << endl;
        cout << "base_val = " << _base_val << endl;
    }

protected:              //把基类的构造函数定义为protected性质，这时外部非派生类将不能对该类进行实例化，只能通过该类的派生来调用该基类的构造函数
    Base(int base_val)
    : _base_val(base_val)
    {
        
        cout << "Base(int base_val)" << endl;
    }

private:
    int _base_val;
};

class Inherit_cls
: public Base
{
public:
    Inherit_cls(int base, int inherit_val)      //通过派生类中的构造函数来调用基类中的构造函数
    : Base(base)
    , _inherit_val(inherit_val)
    {
        cout << "Inherit_cls(int base, int inherit_val) " << endl;
    }


    void print(void)
    {
        cout << "I am Inherit_cls" << endl;
        cout << "inherit_val = " << _inherit_val << endl;
    }

private:
    int _inherit_val;

};



int main(void)
{
    Inherit_cls test(12, 34);
    Base & base = test;
    base.print();

    return 0;
}