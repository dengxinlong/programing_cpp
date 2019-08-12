#ifndef __SUBJECT_T_H
#define __SUBJECT_T_H

#include <iostream>
#include <list>
#include <string>

using std::endl;
using std::cout;
using std::list;
using std::string;

class Observer;

class Subject
{
public:
    virtual
    void attach(Observer * obj) = 0;

    virtual 
    void detach(Observer * obj) = 0;

    virtual
    void notify(void) = 0;

    virtual
    ~Subject() = default;
};

class Ring
: public Subject
{
public:
    Ring()
    : _is_alarming(false)
    {}

    void attach(Observer * obj);

    void detach(Observer * obj);

    void notify(void);

    void is_pressed(void);

private:
    bool _is_alarming;
    list<Observer *> _list;

};

class Guest
{
public:
    Guest(const string & name)
    : _name(name)
    {}

    void knock(Ring & ring);

private:
    string _name;
};






#endif