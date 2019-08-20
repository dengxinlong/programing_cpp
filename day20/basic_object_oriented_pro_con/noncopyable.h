#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

//因为线程、互斥锁和条件变量是系统资源，不允许复制控制操作
//直接把该类的复制控制操作删除即可达到目的，如果有其他类不允许这些操作，继承这个类就可以
class Noncopy
{
protected:
    Noncopy() {}
    ~Noncopy() {}

    Noncopy(const Noncopy & rhs) = delete;
    Noncopy & operator=(const Noncopy & rhs) = delete;
};











#endif