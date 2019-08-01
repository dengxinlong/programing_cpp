#include <string.h>

#include <iostream>

using std::cout;
using std::endl;

//定义一个基类
class Car
{
public:
    Car()
    : _category(nullptr)
    , _function(nullptr)
    {}
    
    Car(const char * category, const char * function)
    : _category(new char[strlen(category) + 1]())
    , _function(new char[strlen(function) + 1]())
    {
        strcpy(_category, category);
        strcpy(_function, function);
    }

    void print(void)
    {
        cout << "The car's category is " << _category << " and funtion is " << _function << endl;
    }

    ~Car()
    {
        if (_category)
            delete [] _category;
        if (_function)
            delete _function;
    }
protected:
    int Protected_val = 10;

private:
    char * _category;
    char * _function;
};

//定义一个派生类
class Little_car
: public Car
{
public:
    Little_car(const char * category, const char * function, const char * name, float price)          //定义构造函数
    : Car(category, function)
    , _name(new char[strlen(name) + 1]())
    , _price(price)
    {
        strcpy(_name, name);
    }

    void print(void)
    {
        cout << Protected_val << endl;
        Car::print();
    }

    ~Little_car()
    {
        if (_name)
            delete [] _name;
    }



private:
    char * _name;            //车的名字
    float _price;           //车的价格

};

int main(void)
{
    //Car car("little car", "self-driving");
    //car.print();
    
    
    Little_car mycar("little car", "self-driving", "BMW", 6666);
    mycar.print();
    mycar.Car::print();
    //cout << mycar.Car::Protected_val << endl;


    return 0;
}