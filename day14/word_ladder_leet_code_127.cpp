#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class Solution 
{
public:
    Solution() = default;
    ~Solution() = default;

    int ladderLength(string beginWord, string endWord, vector<string>& wordList);

};

int Solution::ladderLength(string beginWord, string endWord, vector<string>& wordList)
{
    if (find(wordList.begin(), wordList.end(), endWord) == wordList.end())
        return false;
    string find_str;
    while ()

}


int main(void)
{
    string begin_word("hit");
    string end_word("cog");
    vector<string> word_list = {"hot","dot","dog","lot","log","cog"};

    Solution so;
    so.ladderLength(begin_word, end_word, word_list);

    return 0;
}