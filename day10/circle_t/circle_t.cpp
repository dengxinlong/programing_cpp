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

int main(void)
{
    Circle circle1(10);

    //cout << circle1.get_area() << endl;
    circle1.show();

    return 0;
}