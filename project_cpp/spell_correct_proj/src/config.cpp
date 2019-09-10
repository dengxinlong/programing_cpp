#include "config.h"

#include <stdlib.h>

#include <fstream>
#include <sstream> 

using std::ifstream;
using std::stringstream;

//构造函数，用于存放配置文件所属的路径
Config::Config(const string & filepath)
: _filepath(filepath)
{}

map<string, string> & Config::get_conf_map(void)
{
    ifstream input_file(_filepath);
    if (!input_file.good())
    {
        cout << "open file is fail.\n";
        exit(-1);
    }

    string line;
    string title;
    string info;

    while (!input_file.eof())
    {
        std::getline(input_file, line);
        stringstream sstr(line);
        sstr >> title;
        sstr >> info;
        _conf_map[title] = info;
    }

#if 0
    for (const auto & iter : _conf_map)
    {
        cout << iter.first << ": " << iter.second << endl;
    }
#endif

    return _conf_map;
}