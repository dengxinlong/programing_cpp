#ifndef __TYPE_H__
#define __TYPE_H__

#include <iostream>
#include <string>

enum Color
{
    RED,
    BLUE,
    NOTSET,
};

enum Warrior_type
{
    DRAGON_TYPE,
    NINJA_TYPE,
    ICEMAN_TYPE,
    LION_TYPE,
    WOLF_TYPE,
};

std::string to_string(Color color)
{
    return (color == RED) ? std::string("red") : std::string("blue");
}

std::string to_string(Warrior_type type)
{
    switch (type)
    {
        case DRAGON_TYPE: return "dragon";
        case NINJA_TYPE: return "ninia"; 
        case ICEMAN_TYPE: return "iceman"; 
        case LION_TYPE: return "lion";
        case WOLF_TYPE: return "wolf";
        default:
            return std::string();
    }
}















#endif