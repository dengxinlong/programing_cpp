#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::stringstream;
using std::ifstream;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;

class Text_query
{
public:
    void query(const string & filename, const string & word);

private:
    //
};

void Text_query::query(const string & filename, const string & search_word)
{
    ifstream input_file(filename);
    if (!input_file.good())
    {
        cout << "open file is error." << endl;
        exit(-1);
    }

    //vector<string> lines;       //存储文件中每一行的内容
    map<int, string> lines;
    map<string, set<int>> word_to_line;     //每个单词所对应的行号
    map<string, int> dict;      //每个单词出现的次数
    string line;
    int line_cnt = 1;       //行号
    string word;
    while (!input_file.eof())
    {
        std::getline(input_file, line);
        if (line[line.size() - 1] == '\r')
            line.erase(line.end() - 1);
        stringstream line_sstream(line);
        while (!line_sstream.eof())
        {
            line_sstream >> word;
            dict[word]++;
            word_to_line[word].insert(line_cnt);
        }
        //lines[line_cnt] = line;
        lines.insert(std::make_pair(line_cnt, line));
        ++line_cnt;
    }

    auto search_iter = dict.find(search_word);
    if (search_iter != dict.end())
    {
        cout << search_word << " occurs " << search_iter->second
             << " times." << endl;
        for (auto iter = word_to_line[search_word].begin(); 
            iter != word_to_line[search_word].end(); ++iter)
        {
            cout << "   (line " << *iter << ") " << lines[*iter] << endl;
        }
    }
    
    //cout << lines[2] << endl;
}

int main(int argc, char * argv[])
{
    if (argc != 3)
    {
        cout << "argument is error. The argument is ./process file_name word.\n";
        exit(-1);
    }

    Text_query test_query;
    test_query.query(argv[1], argv[2]);

    return 0;
}
/* 
	class TextQuery
			{
			public:
			    void readFile(const string filename);
			    void query(const string & word);
			private:
						//......
			};
			
			//程序测试用例
			int main(int argc, char *argv[])
			{
			   string  queryWord("hello");
			   
			   TextQuery tq;
			   tq.readFile("test.dat");
			   tq.query(queryWord);			   
			   return 0;
			}
*/