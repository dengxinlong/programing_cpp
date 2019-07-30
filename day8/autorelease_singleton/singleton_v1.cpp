#include <iostream>
#include <cstdlib>

using std::endl;
using std::cout;

class Singleton
{
public:
    static Singleton * get_instance(void)
    {
        if (!_ptr)
        {
            _ptr = new Singleton();
            ::atexit(destroy);
        }
        return _ptr;
    }

    static void destroy(void)
    {
        if (_ptr)
        {
            delete _ptr;
            _ptr = nullptr;
        }
    }


private:
    Singleton()
    {
        cout << "Singleton()" << endl;
    }
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }

private:
    static Singleton * _ptr;
};

Singleton * Singleton::_ptr = nullptr;                //懒汉模式。延迟初始化模式



int main(void)
{
    Singleton * ptr1 = Singleton::get_instance();
    Singleton * ptr2 = Singleton::get_instance();
    Singleton * ptr3 = Singleton::get_instance();

    cout << "ptr1's address is " << ptr1 << endl;
    cout << "ptr2's address is " << ptr2 << endl;
    cout << "ptr3's address is " << ptr3 << endl;


    return 0;
}