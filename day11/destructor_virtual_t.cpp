#include <string.h>

#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base(const char * base)
    : _base(new char[strlen(base) + 1]())
    {
        strcpy(_base, base);
        cout << "Base(const char * base)" << endl;
    }

    virtual void print(void) const
    {
        cout << "base = " << _base << endl;
    }

    virtual
    ~Base()
    {
        if (_base)
            delete [] _base;
        cout << "~Base()" << endl;
    }

private:
    char * _base;
};

class Derived
: public Base
{
public:
    Derived(const char * base, const char * derived)
    : Base(base)
    , _derived(new char[strlen(base) + 1]())
    {
        strcpy(_derived, derived);
        cout << "Derived(const char * base, const char * derived)" << endl;
    }
    
    void print(void) const 
    {
        cout << "derived = " << _derived << endl;
    }

    ~Derived()
    {
        if (_derived)
            delete [] _derived;
        cout << "~Derived()" << endl;
    }
private:
    char * _derived;

};

int main(void)
{
    Base * base = new Derived("hello", "world");
    base->print();

    delete base;

    Base bb("ghost");
    bb.print();

    return 0;
}