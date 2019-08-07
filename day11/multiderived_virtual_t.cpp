#include <iostream>

using std::cout;
using std::endl;

class A
{
public: 
    virtual
    void f(void)    {   cout << "A::f()" << endl;   }

    virtual 
    void g(void)    {   cout << "A::g()" << endl;   }

    virtual 
    void h(void)    {   cout << "A::h()" << endl;   }
};

class B
{
public: 
    virtual
    void f(void)    {   cout << "B::f()" << endl;   }

    virtual 
    void g(void)    {   cout << "B::g()" << endl;   }
 
    void h(void)    {   cout << "B::h()" << endl;   }

    void j(void)    {   cout << "B::j()" << endl;   }
};

class C 
: public A
, public B
{
public:
    virtual
    void f(void)    {   cout << "C::f()" << endl;   }

    void h(void)    {   cout << "C::g()" << endl;   }

    void j(void)    {   cout << "C::j()" << endl;   }
};


int main(void)
{
    C c;
    cout << "sizeof(A) = " << sizeof(A) << endl;

    A & a = c;
    a.f();
    a.g();
    a.h();
    cout << "-----------------" << endl;

    B & b = c;
    b.f();
    b.g();
    b.h();
    b.j();

    cout << "---------------" << endl;
    c.f();
    //c.g();
    c.h();
    c.j();

    return 0;
}