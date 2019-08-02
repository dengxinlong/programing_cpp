#include <math.h>

#include <iostream>

using std::cout;
using std::endl;

class Figure            //定义一个抽象基类
{
public: 
    virtual void display(void) const = 0;   //定义纯虚函数
    virtual double area(void) const = 0;
};

void display(Figure & figure)
{
    figure.display(); 
    cout << ", the area is " << figure.area() << endl;
}


class Circle
: public Figure
{
public:
    Circle(double radius)
    : _radius(radius)
    {}

    void display(void) const
    {
        cout << "I am Circle";
    }

#if 1
    double area(void) const
    {
        return 3.14 * _radius * _radius;
    }
#endif
private:
    double _radius;
};

class Rectangle
: public Figure
{
public:
    Rectangle(double length, double width)
    : _length(length)
    , _width(width)
    {}

    void display(void) const
    {
        cout << "I am Rectangle";
    }

    double area(void) const
    {
        return _length * _width;
    }

private:
    double _length;
    double _width;
};

class Triangle
: public Figure
{
public:
    Triangle(double a, double b, double c)
    : _a(a)
    , _b(b)
    , _c(c)
    {}

    void display(void) const
    {
        cout << "I am Triangle";
    }

    double area(void) const
    {
        double p = (_a + _b + _c)/2;
		return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }

private:
    double _a;
    double _b;
    double _c;
};

int main(void)
{
    Circle circle(10);
    Rectangle rec(10, 12);
    Triangle triangle(3, 4, 5);

    display(circle);
    display(rec);
    display(triangle);


    return 0;
}