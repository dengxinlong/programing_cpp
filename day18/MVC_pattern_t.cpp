#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::map;

class Student 
{
public:
    Student(size_t id = 0, const string & name = string())
    : _id(id)
    , _name(name)
    {   cout << "Student()" << endl;    }

    size_t get_id(void) const
    {
        return _id;
    }

    string  get_name(void) const
    {
        return _name;
    }

    ~Student()
    {   cout << "~Student()" << endl;   }

private:
    size_t _id;
    string _name;
};

class View
{
public:
    View(Student * stu = nullptr)
    : _stu(stu)
    {   cout << "View()" << endl;   }

    void set_stu(Student * stu)
    {
        _stu = stu;
    }

    virtual
    void show(void) const
    {
        cout << "id = " << _stu->get_id()
             << ", name = " << _stu->get_name() << endl;
    }

protected:
    Student * _stu;
};

class Sub_view
: public View
{
public:
    void show(void) const override
    {
        cout << "{id: " << _stu->get_id() 
             << ", name: " << _stu->get_name() 
             << "}" << endl;
    }
};

class Controller
{
public:
    Controller()
    {
        cout << "Controller()\n";
    }

    void attach(const Student & stu)
    {
        _students[stu.get_id()] = stu;
    }

    void attach(Student && stu)
    {
        _students[stu.get_id()] = std::move(stu);
    }

    void detach(const Student & stu)
    {
        auto iter = _students.find(stu.get_id());
        if (iter != _students.end())
        {
            _students.erase(iter);
        }
    }

    void detach(const size_t id)
    {
        auto iter = _students.find(id);
        if (iter != _students.end())
        {
            _students.erase(iter);
        }
    }

    void show(View & view)
    {
        for (auto & elem : _students)
        {
            view.set_stu(&elem.second);
            view.show();
        }
    }

private:
    map<size_t, Student> _students;
};


int main(void)
{
    Controller controller;
    controller.attach(Student(1, "xiaoming"));
    controller.attach(Student(2, "xiaohua"));
    controller.attach(Student(3, "xiaoli"));

    View view;
    controller.show(view);

    Sub_view sub_view;
    controller.show(sub_view);

    return 0;
}