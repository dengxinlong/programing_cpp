#include <iostream>
#include <cstdlib>
#include <pthread.h>

using std::endl;
using std::cout;

class Singleton
{
public:
    static Singleton * get_instance(void)
    {
        pthread_once(&_pthread_once, Singleton_init);           //该函数是线程安全函数，所以在初始化 _ptr 时不需要使用饿汉模式
            
        return _ptr;
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

    static void Singleton_init(void)
    {
        _ptr = new Singleton();
        ::atexit(destroy);
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
    static Singleton * _ptr;
    static pthread_once_t _pthread_once;
};

Singleton * Singleton::_ptr = nullptr;                //懒汉模式。延迟初始化模式
pthread_once_t Singleton::_pthread_once = PTHREAD_ONCE_INIT;
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