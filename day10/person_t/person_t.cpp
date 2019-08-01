#include <string.h>

#include <iostream>

using std::cout;
using std::endl;

class Person
{
public:
    Person(const char * name, int age)
    : _name(new char[strlen(name) + 1]())
    , _age(age)
    {
        strcpy(_name, name);
    }

    void display(void)
    {
        cout << "The person name is " << _name
             << ", age is " << _age;
    }

private:
    char * _name;
    int _age;

};

class Employee 
: public Person             //按照public方式继承自Person
{
public:
    Employee(const char * name, int age, const char * departion, double salary)
    : Person(name, age)
    , _departion (new char[strlen(departion) + 1]())
    , _salary(salary)
    {
        strcpy(_departion, departion);
    }

    void display(void)
    {
        Person::display();
        cout << ", departion is " << _departion
             << ", _salary is " << _salary << endl;
    }

    double get_salary(void)
    {
        return _salary;
    }


private:
    char * _departion;
    double _salary;

};


int main(void)
{
    Employee em1("xiaoming", 21, "research departion", 12);
    em1.display();

    Employee em2("xiaohua", 22, "research departion", 10);
    em2.display();

    Employee em3("xiaoli", 20, "research departion", 11);
    em3.display();


    cout << "All person salary of average is " << (em1.get_salary() + em2.get_salary() + em3.get_salary()) / 3 << endl;


    return 0;
}