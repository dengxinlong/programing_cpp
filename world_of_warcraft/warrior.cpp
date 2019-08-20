#include "warrior.h"


void Warrior::march()
{

}


void Warrior::attack(Warrior_type warrior)
{

}


void Warrior::defense(Warrior_type warrior)
{

}


void Warrior::bewinner(void)       //成为奖励者
{

}


void Warrior::berewarded(void)        //被奖励
{
    
}


void Warrior::sent_elems_to_headquarters(size_t elems)  //获得一个城市的生命元，发送给司令部
{
    _earn_elems = elems;
}


void Warrior::set_hp(size_t hp)
{
    _hp = hp;
}


void Warrior::set_city(size_t city)
{
    _city_id = city;
}

/*
void set_headquarters(Headquarters * headquarters)
{

}
*/

Color Warrior::get_color(void) const
{
    return _color;
}


size_t Warrior::get_id(void) const
{
    return _id;
}


size_t Warrior::get_hp(void) const
{
    return _hp;
}


size_t Warrior::get_force(void) const
{
    return _force;
}


size_t Warrior::get_city(void) const
{
    return _city_id;
}


Warrior_type Warrior::get_type(void) const
{
    return _type;
}


size_t Warrior::get_earn_elems(void) const
{
    return _earn_elems;
}