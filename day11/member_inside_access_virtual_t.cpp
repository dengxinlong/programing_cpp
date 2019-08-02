#include <iostream>

using std::cout;
using std::endl;

class Base 
{
public:
    Base() = default;

    Base(int base_val)
    : _base_val(base_val)
    {
        cout << "Base(int base_val)" << endl;
    }

    void func1(void)
    {
        //this->display();
        display();
    }

    void func2(void)
    {
        Base::display();
    }

    virtual void display(void) const
    {
        cout << "base_val = " << _base_val << endl;
    }

private:
    int _base_val;

};

class Derived
: public Base
{
public:
    Derived(int base_val, int derived_val)
    : Base(base_val)
    , _derived_val(derived_val)
    {
        cout << "Derived(int base_val, int derived_val)" << endl;
    }

    void display(void) const
    {
        cout << "derived_val = " << _derived_val << endl;
    }
private:
    int _derived_val;
};




int main(void)
{
    Base base(12);
    base.func1();

    Derived derived(34, 56);
    derived.func1();

    cout << "-----------" << endl;
    base.func2();
    derived.func2();

    return 0;
}