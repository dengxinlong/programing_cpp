#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

class Noncopy
{
protected:
    Noncopy() {}
    ~Noncopy() {}
protected:
    Noncopy(const Noncopy & ) = delete;
    Noncopy & operator=(const Noncopy &) = delete;


};











#endif