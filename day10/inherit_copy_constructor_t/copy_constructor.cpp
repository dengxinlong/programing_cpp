#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base()
    {
        cout << "Base()" << endl;
    }

    Base(int base_val)
    : _base_val(base_val)
    {
        cout << "Base(int base_val)" << endl;
    }

    Base(const Base & rhs)              //基类的拷贝构造函数
    : _base_val(rhs._base_val)
    {
        cout << "Base(const Base & rhs) " << endl;
    }
    
    int get_base_val(void)
    {
        return _base_val;
    }

private:
    int _base_val;
};

class Inherit_cls
: public Base
{
public:
    Inherit_cls(int base_val, int inherit_val)
    : Base(base_val)
    , _inherit_val(inherit_val)
    {
        cout << "Inherit_cls(int base_val, int inherit_val)" << endl;
    }

    Inherit_cls(const Inherit_cls & rhs)    //: Base(base_val)
    : Base(rhs)
    , _inherit_val(rhs._inherit_val)
    {
        cout << "Inherit_cls(int base_val, int inherit_val)" << endl;
    }

    void print(void)
    {
        cout << Base::get_base_val() << ", "
             << _inherit_val << endl;
    }

    
private:
    int _inherit_val;

};

int main(void)
{
    Inherit_cls test(123, 334);
    test.print();

    cout << "---------" << endl;

    Inherit_cls test1 = test;
    test1.print();

    return 0;
}