#ifndef __STRING_T_H__
#define __STRING_T_H__

#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

class String
{
public:
    String(void)
    : _pstr(nullptr)
    {}

    String(const char * pstr)
    : _pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }

    String(const String & rhs)
    : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
    }

    ~String()
    {
        if (_pstr)
            delete [] _pstr;
    }

    void print(void) const
    {
        cout << _pstr << endl;
    }

    String & operator=(const String & rhs);
    String & operator=(const char * rhs);

    String & operator+=(const String & rhs);
    String & operator+=(const char * rhs);

    char & operator[](std::size_t index);
    const char & operator[](std::size_t index) const;

    std::size_t size() const;
    const char * c_str() const;

    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream & operator<<(std::ostream & os, const String &);
    friend std::istream & operator>>(std::istream & os, String &);

private:
    char * _pstr;

};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);










#endif