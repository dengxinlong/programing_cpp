#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Number
{
public:
    Number(int data)
    : _data(data)
    {}

    void display(void)
    {
        cout << _data << " ";
    }

    bool is_even(void)
    {
        return _data % 2 == 0;
    }

    bool is_primer(void)
    {
        if (_data == 0 || _data == 1)
        {
            return false;
        }

        for (int i = 2; i <= _data / 2; ++i)
        {
            if (_data % i == 0)
                return false;
        }
        return true;
    }

private:
    int _data;
};

int main(void)
{
    vector<Number> numbers;
    for (int i = 0; i < 30; i++)
    {
        numbers.emplace_back(i);
    }

    for_each(numbers.begin(), numbers.end(), mem_fn(&Number::display));
    cout << endl;

    numbers.erase(remove_if(numbers.begin(), numbers.end(), mem_fn(&Number::is_even)), numbers.end());
    for_each(numbers.begin(), numbers.end(), mem_fn(&Number::display));

    cout << endl;
    numbers.erase(remove_if(numbers.begin(), numbers.end(), mem_fn(&Number::is_primer)), numbers.end());
    for_each(numbers.begin(), numbers.end(), mem_fn(&Number::display));
    cout << endl;


    return 0;
}