#include "dict_producer.h"
#include "DEBUG.h"

#include <stdlib.h>
#include <set>

using std::ofstream;
using std::set;

Dict_producer::Dict_producer(const string & file_path)
: _file_path(file_path)
{}

void Dict_producer::build_en_dict(void)
{
    ifstream input_file(_file_path);
    if (!input_file.good())
    {
        cout << "open file " << _file_path << " is error" << endl;
        exit(-1);
    }
    string line;
    string word_info;
    
    map<string, int> word_cnt;
    int i = 0;
    while (!input_file.eof())
    {
        std::getline(input_file, line);
        stringstream sstr(line);
        
        while (!sstr.eof())
        {
            string word;
            sstr >> word_info;
            if (word_info[0] <= 0 + 48 && word_info[0] >= 9 + 48)
            {
                continue;
            }
            
            for (auto i : word_info)
            {
                if ((i <= 90 && i >= 65) || (i <= 122 && i >= 97))
                {
                    i = tolower(i);
                    word.push_back(i);
                }
            }
            if (word.size() > 0)
            {
                _dict[word]++;
                //_words.push_back(word);             //从语料中读取的单词都存入_words中，主要用于后面创建索引文件使用，因为vector中遍历的效率比map更高
            }    
        }
    } 

#if 0
    for (const auto & elem : _dict)
    {
        cout << elem.first << "-->" 
             << elem.second << endl;
    }
#endif 
}

void Dict_producer::store_dict(const string & store_file_path)
{
    ofstream output_file(store_file_path);
    for (const auto & elem : _dict)
    {
        output_file << elem.first << " "
                    << elem.second << endl;
    }
}

void Dict_producer::build_index_file(const string & file_path)
{
    map<char, set<string>> index_dict;       //索引字典，用于存放26个字母所对应的单词

    for (const auto & elem : _dict)
    {
        for (const auto & ch : elem.first)
        {
            index_dict[ch].insert(elem.first);
        }
    }

#if 0
    for (const auto & elem : index_dict)
    {
        cout << elem.first << ": ";
        for (auto word : elem.second)
        {
            cout << word << " ";
        }
        cout << endl;
    }
#endif
    ofstream output_file(file_path);
    for (const auto & elem : index_dict)   
    {
        output_file << elem.first << " ";
        for (const auto & word : elem.second)
        {
            output_file << word << " ";
        }
        output_file << endl;
    }
}

void Dict_producer::show_files(void) const
{

}

void Dict_producer::show_dict(void) const
{
    for (const auto & elem : _dict)
    {
        cout << elem.first << " "
                    << elem.second << endl;
    }
}

void Dict_producer::get_files(void)
{

}

void Dict_producer::store_word_to_dict(const string & word)
{
    //检查单词的合法性
    string store_word;
    for (auto i : word)
    {
        if ((i <= 90 && i >= 65) || (i <= 122 && i >= 97))
        {
            store_word.push_back(i);
        }
    }

    if (store_word.size() > 0)
        _dict[store_word]++;
}