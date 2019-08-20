#include "type_t.h"

#include <stdlib.h>

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <istream>
#include <fstream>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::istream;

#define DEBUG 

class Game_config
{
public:
    static Game_config * get_instance()
    {
        if (!_pinstance)
        {
            _pinstance = new Game_config();
            ::atexit(destroy);
        }   
        return _pinstance;
    }

    static void destroy(void)
    {
        if (_pinstance)
            delete _pinstance;
    }

    void read_from_console(void);   //由用户从终端输入数据
    void read_from_file(const string & file_name);
    void next_group_id(void);

    size_t groups(void) const;
    size_t current_group_id(void) const;
    size_t city_count(void) const;
    size_t headquarters_init_elems(void) const;
    size_t warrior_init_life(Warrior_type warrior_type) const;
    size_t warrior_init_force(Warrior_type warrior_type) const;
    void set_warrior_order(const vector<Warrior_type> &);

#ifdef DEBUG
    void debug(void) const
    {
        for (auto elem : _groups)
        {
            cout << elem._init_elems << " " 
                 << elem._city_count << " "
                 << elem._minutes << endl;
            for (auto elem1 : elem._init_lifes)
            {
                cout << elem1.second << " "; 
            }
            cout << endl;
            for (auto elem2 : elem._init_force)
            {
                cout << elem2.second << " ";
            }
            cout << endl;
        }
    }
#endif

private:
    struct Init_data
    {
        size_t _init_elems;
        size_t _city_count;
        size_t _minutes;
        map<Warrior_type, size_t> _init_lifes;
        map<Warrior_type, size_t> _init_force;
    };

    void read_from_istream(istream & is);

    Game_config()
    : _current_group_id(0)
    {}

    ~Game_config()  {}

private:
    static Game_config * _pinstance;
    

    vector<Init_data> _groups;
    size_t _current_group_id;
    vector<Warrior_type> _init_warrior_order;
};

Game_config * Game_config::_pinstance = nullptr;

void Game_config::set_warrior_order(const vector<Warrior_type> & set_que)
{
    _init_warrior_order = set_que;
}

void Game_config::read_from_console(void)   //由用户从终端输入数据
{
    Init_data init_data;
    cout << "please enter some data to initial game_config" << endl;
    cout << "please enter elements, city_count and time: ";
    size_t elems;
    size_t city_cnt;
    size_t time;

    while (!(cin >> init_data._init_elems).good())
    {
        cin.ignore();
        cin.clear();
    }
    while (!(cin >> init_data._city_count).good())
    {
        cin.ignore();
        cin.clear();
    }
    while (!(cin >> init_data._minutes).good())
    {
        cin.ignore();
        cin.clear();
    }

    size_t temp_val = 0;
    for (int i = 0; i < 5; i++)
    {
        cin >> temp_val;
        init_data._init_lifes[_init_warrior_order[i]] = temp_val;
    }

    for (int i = 0; i < 5; i++)
    {
        cin >> temp_val;
        init_data._init_force[_init_warrior_order[i]] = temp_val;
    }

    _groups.push_back(init_data);
}

//从配置文件读取数据
void Game_config::read_from_file(const string & file_name)
{
    Init_data init_data;
    std::ifstream input_file(file_name);
    if (!input_file.good())
    {
        cout << "open file is error" << endl;
        exit(-1);
    }
    //cout << file_name << "--------\n";
    string line;
    string word;

    getline(input_file, line);
    std::istringstream i_sstream(line);
    i_sstream >> word; 
    init_data._init_elems = atoi(word.c_str());
    i_sstream >> word; 
    init_data._city_count = atoi(word.c_str());
    i_sstream >> word; 
    init_data._minutes = atoi(word.c_str());

    getline(input_file, line);
    std::istringstream i_sstream1(line);
    size_t i = 0;
    while (!i_sstream1.eof())
    {
        i_sstream1 >> word;
        init_data._init_lifes[_init_warrior_order[i++]] = atoi(word.c_str()); 
    }

    getline(input_file, line);
    std::istringstream i_sstream2(line);
    i = 0;
    while (!i_sstream2.eof())
    {
        i_sstream2 >> word;
        //cout << wor
        init_data._init_force[_init_warrior_order[i++]] = atoi(word.c_str()); 
    }
    _groups.push_back(init_data);

}


void Game_config::next_group_id(void)
{
    _current_group_id++;
}

size_t Game_config::groups(void) const
{
    return _groups.size();
}


size_t Game_config::current_group_id(void) const
{
    return _current_group_id;
}


size_t Game_config::city_count(void) const
{
    return _groups[_current_group_id]._city_count;
}


size_t Game_config::headquarters_init_elems(void) const
{

}


size_t Game_config::warrior_init_life(Warrior_type warrior_type) const
{

}


size_t Game_config::warrior_init_force(Warrior_type warrior_type) const
{

}


void Game_config::read_from_istream(istream & is)
{

}






