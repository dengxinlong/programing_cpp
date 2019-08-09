#include <math.h>

#include <iostream>
#include <vector>
#include <functional>

using std::cout;
using std::endl;

//function + bind 取代虚函数
class Figure            
{
public: 
    using Display_call = std::function<void(void)>;
    using Area_call = std::function<double(void)>;

    void set_display_call(const Display_call & display_call)
    {
        _display_call = display_call;
    }

    void set_area_call(const Area_call & area_call)
    {
        _area_call = area_call;
    }

    void handle_display(void)
    {
        if (_display_call)
            _display_call();
    }

    double handle_area(void)
    {
        if (_area_call)
            return _area_call();
        else 
            return 0;
    }

private: 
    Display_call _display_call;
    Area_call _area_call;
};

void display(Figure & figure)
{
    figure.handle_display(); 
    cout << ", the area is " << figure.handle_area() << endl;
}

class Circle
{
public:
    Circle(double radius)
    : _radius(radius)
    {}

    void display(void) const
    {
        cout << "I am Circle";
    }

    double area(void) const
    {
        return 3.14 * _radius * _radius;
    }

private:
    double _radius;
};

class Rectangle
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

    Figure figure;

    figure.set_display_call(std::bind(&Circle::display, circle));
    figure.set_area_call(std::bind(&Circle::area, circle));
    display(figure);

    figure.set_display_call(std::bind(&Rectangle::display, rec));
    figure.set_area_call(std::bind(&Rectangle::area, rec));
    display(figure);

    figure.set_display_call(std::bind(&Triangle::display, triangle));
    figure.set_area_call(std::bind(&Triangle::area, triangle));
    display(figure);
    


    return 0;
}