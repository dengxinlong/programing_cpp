#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main(void)
{
    vector<int> vec = {1,3, 4, 53, 2, 0};
    for (auto elem : vec)
    {
        cout << elem << " ";
    }
    vec.push_back(-1);
    for (auto elem : vec)
    {
        cout << elem << " ";
    }

    return 0;
}