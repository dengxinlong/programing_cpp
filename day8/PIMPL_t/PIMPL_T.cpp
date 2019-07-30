#include "PIMPL_T.h"

using std::endl;
using std::cout;

class Student::Stu_Impl
{
public:
    Stu_Impl()
    : _pname(nullptr)
    , _id(0)
    , _score(0)
    {}

    Stu_Impl(const char * name, int id, float score)
    : _pname(new char[strlen(name) + 1]())
    , _id(id)
    , _score(score)
    {
        strcpy(_pname, name);
        cout << "Stu_Impl(const char * name, const int id, const float score)" << endl;
    }
    
    ~Stu_Impl()
    {
        cout << "~Stu_Impl()" << endl;
        if (_pname)
        {
            delete _pname;
            _pname = nullptr;
        }   
    }

    void print_info(void) const
    {
        cout << "name is " << _pname << endl;
        cout << "id is " << _id << endl;
        cout << "score is " << _score << endl;
    }

private:
    char * _pname;
    int _id;
    float _score;

};

Student::Student()
: _pimpl(new Stu_Impl())
{
    cout << "Student()" << endl;
}

Student::Student(const char * name, int id, float score)
: _pimpl(new Stu_Impl(name, id, score))
{
    cout << "Student()" << endl;
}

Student::~Student()
{
    cout << "~Student()" << endl;
    if (_pimpl)
    {
        delete _pimpl;
        _pimpl = nullptr;
    }
}

void Student::print(void) const
{
    _pimpl->print_info();
}