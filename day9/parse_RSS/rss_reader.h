#ifndef __RSS_READER_H__
#define __RSS_READER_H__

#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Rss_item
{
    string title;
    string link;
    string descripton;
    string content;
};


class Rss_reader
{
public:
    Rss_reader();                           //构造函数

    void parse_rss(void);                               //解析
    void dump(const string & filename);             //输出到某个文件中

private:
    vector<Rss_item> _rss;
};









#endif