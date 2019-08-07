#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::ifstream;
using std::stringstream;
using std::string;

int main(void)
{
    //打开圣经文件
    ifstream input_file("The_Holy_Bible.txt");
    if (!input_file.good())         //判断文件是否打开成功
    {
        cout << "open file is error.\n";
        return -1;
    }

    string line;
    string word;
    map<string, int> word_cnt;
    while (!input_file.eof())
    {
        std::getline(input_file, line);
        if (line[line.size() - 1] == '\r')          //每次读取一行时，最后都会将/r读取到，所以应该取出该字符
            line.erase(line.end() - 1);
        //cout << line << endl;
        stringstream sstr(line);
        while (!sstr.eof())
        {
            sstr >> word;
            //判断是否为单词
            if (::isalpha(word[0]))
                word_cnt[word]++;
        }
    }

    for (auto elem : word_cnt)
    {
        cout << elem.first << " "
             << elem.second << endl;
    }
    

    return 0;
}