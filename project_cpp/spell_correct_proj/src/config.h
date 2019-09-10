#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::map;

//配置文件类，专门用于读取配置文件中的内容，获取其他文件的路径
class Config
{
public:
    Config(const string & filepath);
    map<string, string> & get_conf_map(void);
    

private:
    string _filepath;                   //配置文件的路径
    map<string, string> _conf_map;      //配置文件中的内容

};









#endif 