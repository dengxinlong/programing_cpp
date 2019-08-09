#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <pthread.h>

using std::cout;
using std::endl;

class Computer
{
public:
    Computer() = default;
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
    Point() = default;
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
    static T * get_instance(void)          //关键之处在于解包
    {  
        pthread_once(&_once, init);
        return _ptr;
    }

    static void destroy(void)
    {
        if (_ptr)
            delete _ptr;
    }

private:
    static void init(void)
    {
        _ptr = new T();
        ::atexit(destroy);
    } 
private:
    Singleton()
    {}

    ~Singleton()
    {}

private:
    static T * _ptr;
    static pthread_once_t _once;
};

template<class T> 
T * Singleton<T>::_ptr = nullptr;

template<class T>
pthread_once_t Singleton<T>::_once = PTHREAD_ONCE_INIT;

int main(void)
{
    Computer * ptr1 = Singleton<Computer>::get_instance();
    Computer * ptr2 = Singleton<Computer>::get_instance();
    cout << "ptr1's address is " << ptr1 << endl;
    cout << "ptr2's address is " << ptr2 << endl;

#if 0
    ptr1->print();
    ptr2->print();

    Point * ptr = Singleton<Point>::get_instance(1, 2, 3);
    ptr->print();
    cout << "ptr's address is " << ptr << endl;
#endif
    return 0;
}