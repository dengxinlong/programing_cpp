#ifndef __GAME_TIME_H__
#define __GAME_TIME_H__

#include <stdlib.h>

#include <iostream>

using std::cout;
using std::endl;

class Game_time
{
public:
    static Game_time * get_instance(void)
    {
        if (!_pinstance)
        {
             _pinstance = new Game_time();
             ::atexit(destroy);
        } 
        return _pinstance;
    }

    void show_time(void) const;
    void update_time(void);
    void reset(void);

    static void destroy(void)
    {
        if (_pinstance)
            delete _pinstance;
    }

private:
    Game_time(size_t hour = 0, size_t minutes = 0)
    : _hour(hour)
    , _minutes(minutes)
    {
        cout << _hour << _minutes << endl;
    }

    ~Game_time() = default;

private:
    static Game_time * _pinstance;
    size_t _hour;
    size_t _minutes;

};

Game_time * Game_time::_pinstance = nullptr;

void Game_time::show_time(void) const
{
    
    cout << "hour: " << _hour
         << ", minutes: " << _minutes << endl; 
}


void Game_time::update_time(void)
{
    _minutes += 10;
    if (_minutes == 60)
    {
        _minutes = 0;
        _hour += 1;
    }
}

/*
size_t Game_time::get_time(void)
{
}
*/


void Game_time::reset(void)
{
    _hour = 0;
    _minutes = 0;
}


#endif