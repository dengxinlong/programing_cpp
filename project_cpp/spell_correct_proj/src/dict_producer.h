#ifndef __DICT_PRODUCER_H__
#define __DICT_PRODUCER_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using std::endl;
using std::cout;
using std::vector;
using std::string;
using std::map;
using std::stringstream;
using std::ifstream;

class Dict_producer
{
public:
    //构造函数
    Dict_producer(const string &);

    //创建英文词典
    void build_en_dict(void);

    //创建索引文件
    void build_index_file(const string &);
   
    //将词典写入文件中
    void store_dict(const string & );

    //查看文件的路径，用于测试
    void show_files(void) const; 

    //查看字典的内容，用于测试
    void show_dict(void) const;

    //获取文件的绝对路径
    void get_files(void);

    //存储某个单词到词典当中
    void store_word_to_dict(const string & word); 

private:
    string _file_path;
    map<string, int> _dict;         //创建词典
    string _path;               //语料库文件存放的路径
    vector<string> _files_path; //语料库文件存放路径集合
    //vector<string> _words;          //用于存放语料文件中的每一个单词
    //map<string, int> _dict;     //配置文件的内容，由Config类来完成

    //分词工具
};













#endif