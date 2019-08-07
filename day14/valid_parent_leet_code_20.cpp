/*
 * 说明：判断给定的一组只包含括号的字符串是否匹配
 */
#include <iostream>
#include <stack>
#include <string>

using std::cout;
using std::endl;
using std::stack;
using std::string;

class Solution 
{
public:
    Solution() = default;
    ~Solution() = default;

    bool isValid(string s);
};

bool Solution::isValid(string s)
{
    if (s.empty())              //输入的字符串为0，也是有效的
        return true;    

    stack<char> stak;

    char top_ch;
    for (const auto & ch : s)
    {
        if (ch == '(' || ch == '[' || ch == '{')
            stak.push(ch);
        else
        {
            if (stak.empty())
                return false;
            top_ch = stak.top();
            if (ch == ')' && top_ch == '(')
                stak.pop();
            else if(ch == ']' && top_ch == '[')
                stak.pop();
            else if (ch == '}' && top_ch == '{')
                stak.pop();
            else 
                return false;
        }
    }

    return stak.empty();
}

int main(void)
{
    string str = "]";

    Solution so;
    cout << so.isValid(str) << endl;


    return 0;
}