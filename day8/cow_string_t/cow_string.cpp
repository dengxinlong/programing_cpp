#include <cstring>
#include <iostream>
#include "cow_string.h"

using std::cout;
using std::endl;

Cow_string::Cow_string()
:_pstr(new char[4 + 1]() + 4)
{
    cout << "Cow_string()" << endl;
}

Cow_string::Cow_string(const char * str)
: _pstr(new char[4 + strlen(str) + 1]() + 4)
{
    cout << "Cow_string(const char * str)" << endl;
    init_ref();
    strcpy(_pstr, str);
}

Cow_string::Cow_string(const Cow_string & rhs)          //拷贝构造函数，此时对象的引用计数需要加 1 
: _pstr(rhs._pstr)
{
    cout << "Cow_string(const Cow_string & rhs) " << endl;
    increase_ref();
    strcpy(_pstr, rhs._pstr);
}

Cow_string & Cow_string::operator=(const Cow_string & rhs)      //重载赋值运算符函数
{
    if (&rhs != this)
    {
        release();
        _pstr = rhs._pstr;
        increase_ref();
    }
    return *this;
}

//重载[]下标运算符函数
char & Cow_string::operator[](std::size_t index)
{
    if (index >= 0 && index < size())
    {
        if (ref_cnt() > 1)
        {
            char * temp_str = new char[strlen(_pstr) + 1 + 4]() + 4;
            strcpy(temp_str, _pstr);
        
            release();
            _pstr = temp_str;
            init_ref();
        }
        
        return _pstr[index];
    }
    static char temp_ch = '\0';
    return temp_ch;
}

//重载<<运算符函数
std::ostream & operator<<(std::ostream & o_stream, const Cow_string & rhs)
{
    if (rhs._pstr != nullptr)
        o_stream << rhs._pstr;
    return o_stream;
}


std::size_t Cow_string::size(void) const
{
    return strlen(_pstr);
}

const char * Cow_string::c_str(void) const
{
    return _pstr;
}

void Cow_string::init_ref(void)
{
    *(int *)(_pstr - 4) = 1;
}

void Cow_string::increase_ref(void)
{
    ++(*(int *)(_pstr - 4));
}

void Cow_string::descrease_ref(void)
{
    --(*(int *)(_pstr - 4));
}

void Cow_string::release(void)
{
    descrease_ref();
    if (!ref_cnt())
    {
        if (_pstr)
        {
            cout << "release(void)" << endl;
            delete [] (_pstr - 4);
            _pstr = nullptr;
        }
    }
}


int Cow_string::ref_cnt(void)
{
    return *(int *)(_pstr - 4);
}

Cow_string::~Cow_string()
{
    cout << "~Cow_string()" << endl;
    release();
}

void Cow_string::print(void)
{
    if (_pstr)
        cout << _pstr << endl;
}