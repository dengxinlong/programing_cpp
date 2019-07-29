#include <limits>
#include "string_t.h"

 //拷贝构造函数
String & String::operator=(const String & rhs)         
{
    if (this != &rhs)
    {
        delete [] _pstr;
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }
    return *this;
}

//拷贝构造函数
String & String::operator=(const char * rhs)
{
    delete [] _pstr;
    _pstr = new char[strlen(rhs) + 1]();
    strcpy(_pstr, rhs);
}

//重载+=运算符函数
String & String::operator+=(const String & rhs)
{
    char * ptr = new char[strlen(_pstr) + strlen(rhs._pstr) + 1]();
    strcpy(ptr, _pstr);
    strcat(ptr, rhs._pstr);
    delete [] _pstr;
    _pstr = new char[strlen(ptr) + 1](); 
    strcpy(_pstr, ptr);

    delete [] ptr;
    return *this;
}

//重载+=运算符函数
String & String::operator+=(const char * rhs)
{
    char * ptr = new char[strlen(_pstr) + strlen(rhs) + 1]();
    strcpy(ptr, _pstr);
    strcat(ptr, rhs);
    delete [] _pstr;
    _pstr = new char[strlen(ptr) + 1](); 
    strcpy(_pstr, ptr);

    delete [] ptr;
    return *this;
}

//重载[]下标运算符函数
char & String::operator[](std::size_t index)
{
    if (index >= 0  && index < size())
        return _pstr[index];
}

//重载[]下标运算符函数
const char & String::operator[](std::size_t index) const
{
    if (index >= 0 && index < size())
        return _pstr[index];
}


std::size_t String::size() const
{
    return strlen(_pstr);
}

const char * String::c_str() const
{
    return _pstr;
}


//友元重载函数
//重载==运算符函数
bool operator==(const String & str1, const String & str2)
{
    cout << "operator==" << endl;
    if (!strcmp(str1._pstr, str2._pstr))
        return true;
    else 
        return false;
}

//重载!=运算符函数
bool operator!=(const String & str1, const String & str2)
{
    if (strcmp(str1._pstr, str2._pstr) != 0)
        return true;
    else   
        return false;
}

//重载<运算符函数
bool operator<(const String & str1, const String & str2)
{
    if (strcmp(str1._pstr, str2._pstr) < 0)
        return true;
    return false;
}

//重载>运算符函数
bool operator>(const String & str1, const String & str2)
{
    if (strcmp(str1._pstr, str2._pstr) > 0)
        return true;
    else
        return false;
}

//重载<=运算符函数
bool operator<=(const String & str1, const String & str2)
{
    if (strcmp(str1._pstr, str2._pstr) <= 0)
        return true;
    else
        return false;
}

//重载>=运算符函数
bool operator>=(const String & str1, const String & str2)
{
    if (strcmp(str1._pstr, str2._pstr) >= 0)
        return true;
    else
        return false;
}

//重载<<运算符函数
std::ostream & operator<<(std::ostream & o_stream, const String & rhs)
{
    if (rhs._pstr != nullptr)
        o_stream << rhs._pstr;
    return o_stream;
}

//重载>>运算符函数
std::istream & operator>>(std::istream & i_stream, String & rhs)
{
    rhs._pstr = new char[256]();            //这样做太愚蠢，需要改进
    
    
    i_stream >> rhs._pstr;
    return i_stream;
}


