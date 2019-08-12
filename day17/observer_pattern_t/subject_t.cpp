#include "subject_t.h"
#include "observer_t.h"

#include <iostream>
#include <algorithm>

void Ring::attach(Observer * obj)
{
    auto iter = std::find(_list.begin(), _list.end(), obj);
    if (iter == _list.end())
        _list.push_back(obj);
}

void Ring::detach(Observer * obj)
{
    auto iter = std::find(_list.begin(), _list.end(), obj);
    if (iter != _list.end())
        _list.erase(iter);
}

void Ring::notify(void)
{
    for (auto & item : _list)
        item->update();
}

void Ring::is_pressed(void)
{
    if (!_is_alarming)
    {
        _is_alarming = true;
        notify();
    }
    _is_alarming = false;
}

void Guest::knock(Ring & ring)
{
    cout << ">>>Guest " << _name << "is knocked the door!" << endl;
    ring.is_pressed();
}














