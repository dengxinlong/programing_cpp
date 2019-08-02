#include <iostream>

using std::cout;
using std::endl;

class Grandpa 
{
public:
    Grandpa(int grandpa_val)
    : _grandpa_val(grandpa_val)
    {
        cout << "Grandpa(int grandpa_val)" << endl;
    }

    virtual
    void func1(void)
    {
        cout << "Grandpa: func1()" << endl;
    }

    virtual
    void func2(void)
    {
        cout << "Grandpa: func2()" << endl;
    }

    ~Grandpa()
    {
        cout << "~Grandpa()" << endl;
    }
private:
    int _grandpa_val;

};

class Son
: public Grandpa
{
public:
    Son(int grandpa_val, int son_val)
    : Grandpa(grandpa_val)
    , _son_val(son_val)
    {
        cout << "Son(int grandpa_val, int son_val)" << endl;
        func1();
    }

#if 1
    void func1(void)
    {
        cout << "Son: func1()" << endl;
    }

    void func2(void)
    {
        cout << "Son: func2()" << endl;
    }

#endif 

    ~Son()
    {
        cout << "~Son()" << endl;
        func2();
    }
private:
    int _son_val;
};

class Grandson
: public Son
{
public:
    Grandson(int grandpa_val, int son_val, int grandson_val)
    : Son(grandpa_val, son_val)
    , _grandson_val(grandpa_val)
    {
        cout << "Grandson(int grandpa_val, int son_val, int grandson_val)" << endl;
    }

    void func1(void)
    {
        cout << "Grandson: func1()" << endl;
    }

    void func2(void)
    {
        cout << "Grandson: func2()" << endl;
    }

    ~Grandson()
    {
        cout << "~Grandson()" << endl;
    }

private:
    int _grandson_val;
};




int main(void)
{
    Grandson test(1, 2, 3);
    //cout << "-------------/\n";
    Grandpa  & tt = test;
    cout << "-------------/\n";
    tt.func1();
    return 0;
}