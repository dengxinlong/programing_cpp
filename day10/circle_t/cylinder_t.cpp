#include <iostream>

#define PI 3.14

using std::cout;
using std::endl;

class Circle
{
public:
    Circle()
    : _radius(0)
    {}

    Circle(double radius)
    : _radius(radius)
    {}

    //获取圆的面积 
    double get_area(void)       
    {
        return PI * _radius * _radius;
    }

    //获取圆的周长
    double get_perimeter(void)      
    {
        return 2 * PI * _radius;
    }

    //将圆的半径、周长、面积输出到屏幕 
    void show(void)
    {
        cout << "circle's radius is " << _radius
             << " perimeter is " << get_perimeter()
             << " area is " << get_area() << endl;
    }

private:
    double _radius;
};

class Cylinder
: public Circle         //按照public的方式继承Circle
{
public:
    Cylinder(double radius, double high)
    : Circle(radius)
    , _high(high)
    {}

    //获取圆柱体的体积
    double get_volume(void)         
    {
        return _high * get_area();
    }

    //将圆柱体的体积输出到屏幕  
    void show_volume(void)              //The bottom surface of the cylinder
    {
        cout << "The bottom surface of the cylinder's radius is " << get_perimeter() / (2 * PI)
             << ", perimeter is " << get_perimeter()
             << ", area is " << get_area() << endl;
        cout << "The cylinder volume is " << get_volume() << endl;
    }

private:
    double _high;

};


int main(void)
{
    Cylinder cylinder(10, 10);

    cylinder.show_volume();

    return 0;
}