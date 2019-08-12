#include <stdlib.h>
#include <math.h>

#include <iostream>

using std::cout;
using std::endl;

class Figure
{
public:
    virtual 
    void display(void) const = 0;
    
    virtual 
    double area(void) const = 0;

    virtual 
    ~Figure() = default;    
};

void display(const Figure & figure)
{
    cout << "The figure is "; 
    figure.display();
    cout << "the area is " << figure.area() << endl;
}

class Triangle
: public Figure
{
public: 
    Triangle(double ix, double iy, double iz)
    : _ix(ix)
    , _iy(iy)
    , _iz(iz)
    {}

    void display(void) const override
    {
        cout << "triangle" << endl;
    }

    double area(void) const override
    {
        double p = (_ix + _iy + _iz)/2;
		return sqrt(p * (p - _iz) * (p - _iy) * (p - _ix));
    }


private:
    double _ix;
    double _iy;
    double _iz;
};

class Rectangle
: public Figure
{
public: 
    Rectangle(double length, double width)
    : _length(length)
    , _width(width)
    {}

    void display(void) const override
    {
        cout << "Rectangle" << endl;
    }

    double area(void) const override
    {
        return _length * _width;
    }


private:
    double _length;
    double _width;

};

class Circle
: public Figure
{
public: 
    Circle(double radius)
    : _radius(radius)
    {}

    void display(void) const override
    {
        cout << "Circle" << endl;
    }

    double area(void) const override
    {
        return 3.14 * _radius * _radius;
    }


private:
    double _radius;

};

//简单工厂模式/静态工厂方法
//缺点：不满足单一性原则，一个类完成其他对象的创建
//      不满足开闭原则
class Factory
{
public:
    static Rectangle create_rectangle(void)
    {
        //....一系列操作
        Rectangle rectangle(1, 2);
        return rectangle;
    }

    static Triangle create_triangle(void)
    {
        //....一系列操作
        Triangle triangle(3, 4, 5);
        return triangle;
    }

    static Circle create_circle(void)
    {
        //....一系列操作
        Circle circle(10);
        return circle;
    }
};

int main(void)
{
    Rectangle  rectangle = Factory::create_rectangle();
    Figure & figure = rectangle;
    display(figure);

    return 0;
}
