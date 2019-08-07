#include <stdlib.h>
#include <string.h>

#include <iostream>

using std::cout;
using std::endl;

class Computer
{
public:
    Computer(const char * name, int price)
    : _name(new char[strlen(name) + 1]())
    , _price(price)
    {
        strcpy(_name, name);
    }

    void print(void) const
    {
        cout << "The computer's name is " << _name
             << ", the price is " << _price << endl;
    }

    ~Computer()
    {
        if (_name)
            delete [] _name;
    }

private:
    char * _name;
    float _price;
};

class Point
{
public:
    Point(int x, int y, int z)
    : _x(x), _y(y), _z(z)
    {}

    void print(void) const
    {
        cout << "(" << _x << ", "
             << _y << ", " 
             << _z << ")" << endl;
    }

private:
    int _x;
    int _y;
    int _z;
};

template<class T>
class Singleton
{
public:
    template <typename... Args>
    static T * get_instance(Args... args)          //关键之处在于解包
    {
        if (_ptr == nullptr)
        {
            _ptr = new T(args...);
            ::atexit(destroy);
        }
            
        return _ptr;
    }


    static void destroy(void)
    {
        if (_ptr)
            delete _ptr;
    }

private:
    Singleton()
    {}

    ~Singleton()
    {}

private:
    static T * _ptr;
};

template<class T> 
T * Singleton<T>::_ptr = nullptr;

int main(void)
{
    Computer * ptr1 = Singleton<Computer>::get_instance("ROG", 99999);
    Computer * ptr2 = Singleton<Computer>::get_instance("lenove", 333);
    cout << "ptr1's address is " << ptr1 << endl;
    cout << "ptr2's address is " << ptr2 << endl;

    ptr1->print();
    ptr2->print();

    Point * ptr = Singleton<Point>::get_instance(1, 2, 3);
    ptr->print();
    cout << "ptr's address is " << ptr << endl;

    return 0;
}