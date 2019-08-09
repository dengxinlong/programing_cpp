#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template <class T>
void display(const T & cont)
{
    for (auto iter = cont.begin(); iter != cont.end(); ++iter)
        cout << *iter << " ";
    cout << endl;
}

int main(void)
{
    vector<int> vec;
    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }

    display(vec);


    return 0;
}