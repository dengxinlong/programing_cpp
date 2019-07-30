#include <iostream>
#include <cstdlib>

using std::endl;
using std::cout;

class Singleton
{
public:
    static Singleton * get_instance(void)
    {
        if (!_ptr)              //当是多线程时，将导致不是线程安全的，所以在初始化_ptr是采用饿汉模式
        {
            _ptr = new Singleton();
        }
        return _ptr;
    }

private:
    class Release
    {
    public:
        Release()
        {
            cout << "Release()" << endl;
        }
        ~Release()
        {
            cout <<  "~Release()" << endl;
            if (_ptr)
            {
                delete _ptr;
                _ptr = nullptr;
            }
        }
    };

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
    static Release auto_release;
};

Singleton * Singleton::_ptr = nullptr;                //懒汉模式。延迟初始化模式

Singleton::Release Singleton::auto_release;


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