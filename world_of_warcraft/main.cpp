#include "type_t.h"
#include "game_config.h"
#include "game_time.h"
#include "warrior.h"

#include <stdlib.h>

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        cout << "argument is error, argument is ./main warrior.conf" << endl;
        exit(-1);
    }
    //武士生命值和武力值的设置顺序
    vector<Warrior_type> set_que = {
        DRAGON_TYPE,
        NINJA_TYPE,
        ICEMAN_TYPE,
        LION_TYPE,
        WOLF_TYPE
    };

    vector<Warrior_type> red_create_que = {
        ICEMAN_TYPE, 
        LION_TYPE, 
        WOLF_TYPE, 
        NINJA_TYPE,
        DRAGON_TYPE
    };

    vector<Warrior_type> blue_create_que = {
        ICEMAN_TYPE, 
        LION_TYPE, 
        WOLF_TYPE, 
        NINJA_TYPE,
        DRAGON_TYPE
    };

    cout << "game_config:\n";
    Game_config * game_config_ptr = Game_config::get_instance();
    game_config_ptr->set_warrior_order(set_que);
    //game_config->read_from_console();
    game_config_ptr->read_from_file(string(argv[1]));
    game_config_ptr->debug();

    cout << "\ngame_time:\n";
    Game_time * game_time_ptr = Game_time::get_instance();
    cout << "------------\n";
    for (int i = 0; i < 100; i++)
    {
        game_time_ptr->show_time();
        game_time_ptr->update_time();
    }

    return 0;
}

