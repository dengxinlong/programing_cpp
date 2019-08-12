#ifndef __OBSERVER_T_H
#define __OBSERVER_T_H

#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

using std::endl;
using std::cout;
using std::string;

class Observer
{
public:
    virtual
    void update(void) = 0;

    virtual
    ~Observer() = default;
};

class Baby
: public Observer
{
public:
    Baby(string name)
    : _name(name)
    {}

    void update(void)
    {
        ::srand(time(NULL));
        int value = ::rand() % 100;
        if (value > 70)
        {
            cout << "Baby " << _name << "is sleeping." << endl;
        }
        else
            cout << "Baby " << _name << "is crying." << endl;
    }


private:
    string _name;
};

class Nurse
: public Observer
{
public:
    Nurse(string name)
    : _name(name)
    {}

    void update(void)
    {
        ::srand(time(NULL));
        int value = ::rand() % 100;
        if (value > 70)
        {
            cout << "Nurse " << _name << "is working." << endl;
        }
        else
            cout << "Nurse " << _name << "is sleeping." << endl;
    }

private:
    string _name;
};

#endif