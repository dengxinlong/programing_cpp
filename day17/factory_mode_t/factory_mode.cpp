#include <math.h>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

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

void display(const Figure * figure)
{
    cout << "The figure is "; 
    figure->display();
    cout << "the area is " << figure->area() << endl;
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
        cout << "triangle ";
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
        cout << "Rectangle ";
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
        cout << "Circle ";
    }

    double area(void) const override
    {
        return 3.14 * _radius * _radius;
    }

private:
    double _radius;

};

//工厂模式
//适用于：
//      1. 针对复杂的对象
//      2. 创建批量的对象
//不适用于简单的对象
class Factory
{
public:
    virtual 
    Figure * create(void) = 0;

    virtual
    ~Factory() = default;
};

class Factory_rectangle
: public Factory
{   
public:
    Figure * create(void) override
    {
        //...一系列操作
        return new Rectangle(1, 2);
    }
};

class Factory_circle
: public Factory
{   
public:
    Figure * create(void) override
    {
        //...一系列操作
        return new Circle(10);
    }
};

class Factory_triangle
: public Factory
{   
public:
    Figure * create(void) override
    {
        //...一系列操作
        return new Triangle(3, 4, 5);
    }
};

int main(void)
{
    
    Factory * rectangle_fac = new Factory_circle();
    Figure * rectangle = rectangle_fac->create();
    display(rectangle);

    unique_ptr<Factory> triangle_fac(new Factory_triangle());
    unique_ptr<Figure> triangle(triangle_fac->create());
    display(triangle.get());
    return 0;
}