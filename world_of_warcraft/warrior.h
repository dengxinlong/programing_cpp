#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include "type_t.h"

#include <stdlib.h>

#include <iostream>

using std::cout;
using std::endl;

class Warrior
{
public:
    Warrior(Color color, size_t id, size_t hp, size_t force, Warrior_type type)
    : _color(color)
    , _id(id)
    , _hp(hp)
    , _force(force)
    , _type(type)
    {

    }

    virtual ~Warrior() {}

    virtual void march();
    virtual void attack(Warrior_type warrior);
    virtual void defense(Warrior_type warrior);

    void bewinner(void);        //成为奖励者
    void berewarded(void);        //被奖励
    void sent_elems_to_headquarters(size_t elems);  //获得一个城市的生命元，发送给司令部

    void set_hp(size_t hp);
    void set_city(size_t city);
    //void set_headquarters(Headquarters * headquarters);

    Color get_color(void) const;
    size_t get_id(void) const;
    size_t get_hp(void) const;
    size_t get_force(void) const;
    size_t get_city(void) const;
    Warrior_type get_type(void) const;
    size_t get_earn_elems(void) const;



private:    
    Color _color;
    size_t _id;
    size_t _hp;
    size_t _force;
    Warrior_type _type;
    size_t _city_id;
    size_t _earn_elems;
    //Headquarters * _headquarters;

};

class Dragon
: public Warrior
{
public:
    Dragon(Color color, size_t id, size_t hp, size_t force)
    : Warrior(color, id, hp, force, DRAGON_TYPE)
    {}

};

class Lion
: public Warrior
{
public:
    Lion(Color color, size_t id, size_t hp, size_t force)
    : Warrior(color, id, hp, force, LION_TYPE)
    {}

};

class Iceman
: public Warrior
{
public:
    Iceman(Color color, size_t id, size_t hp, size_t force)
    : Warrior(color, id, hp, force, ICEMAN_TYPE)
    , _step(0)
    {}

    //iceman在行军时，每走两步，生命值减少9， 攻击力增加20；如果生命力不够，则不变
    void march(void) override;

private:
    size_t _step;
};

class Wolf
: public Warrior
{
public:
    Wolf(Color color, size_t id, size_t hp, size_t force)
    : Warrior(color, id, hp, force, WOLF_TYPE)
    , _kill_times(0)
    {}

    void attack(Warrior_type warrior) override;

private:
    size_t _kill_times;
};

class Ninia
: public Warrior
{
public:
    Ninia(Color color, size_t id, size_t hp, size_t force)
    : Warrior(color, id, hp, force, NINJA_TYPE)
    {}

    void defense(Warrior_type warrior) override;

};















#endif