#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base(long base_val)
    : _base_val(base_val)
    {
        cout << "Base(int base_val)" << endl;
    }

    virtual 
    void func1(void)    {   cout << "Base::func1()" << endl;    }

    virtual 
    void func2(void)    {   cout << "Base::func2()" << endl;    }

    virtual 
    void func3(void)    {   cout << "Base::func3()" << endl;    }

private:
    long _base_val;

};

class Derived
: public Base
{
public:
    Derived(long base_val, long derived_val)
    : Base(base_val)
    , _derived_val(derived_val)
    {
        cout << "Derived(long base_val, long derived_val)" << endl;
    }

    virtual 
    void func1(void)    {   cout << "Derived::func1()" << endl;    }

    virtual 
    void func2(void)    {   cout << "Derived::func2()" << endl;    }

    virtual 
    void func3(void)    {   cout << "Derived::func3()" << endl;    }

private:
    long _derived_val;
    
};

int main(void)
{
    Base base(10);
    cout << "sizeof(Base) = " << sizeof(Base) << endl;  

    long * p = (long *)&base;
    cout << p[0] << endl;
    cout << p[1] << endl; 

    typedef void (*Function)(void);

    long * p2 = (long *)p[0];
    Function f = (Function)p2[0];
    //Function f = (Function)p[0][0];
    f();

    f = (Function)p2[1];
    f();

    f = (Function)p2[2];
    f();

    return 0;
}