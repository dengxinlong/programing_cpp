#ifndef __PIMPL_T_H__
#define __PIMPL_T_H__
#include <iostream>
#include <cstring>

//定义一个公开的类，向外提供各种接口，接口的实现则由内部类来完成
class Student
{
private:
    class Stu_Impl;
public:
    Student();
    Student(const char * name, int id, float score);
    ~Student();

    void print(void) const;

private:
    Stu_Impl * _pimpl;
};










#endif 