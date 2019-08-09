#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>


using std::cout;
using std::endl;
using std::list;
using std::unordered_map;

class LRU_cache
{
public:
    LRU_cache(int capacity)
    : _capacity(capacity)
    {}

    void put(int key, int value);
    int get(int key);

private:
    struct Cache_node
    {
        Cache_node(int key, int value)
        : _key(key)
        , _value(value)
        {}
    
        int _key;
        int _value;
    };

private:
    int _capacity;
    list<Cache_node> _visit_list;
    unordered_map<int, list<Cache_node>::iterator> _hash_map; 
};

int LRU_cache::get(int key)
{
    auto iter = _hash_map.find(key);
    if (iter != _hash_map.end())
    {
        _visit_list.splice(_visit_list.begin(), _visit_list, iter->second);
        _hash_map[key] = _visit_list.begin();
        return iter->second->_value;
    }
    else
        return -1;
}
void LRU_cache::put(int key, int value)
{
    auto iter = _hash_map.find(key);
    if (iter != _hash_map.end())            //此时map中已经存在的相应的元素
    {
        iter->second->_value = value;
        _visit_list.splice(_visit_list.begin(), _visit_list, iter->second);
        _hash_map[key] = _visit_list.begin();
    }
    else            //不存在相同关键字的元素
    {
        if (_visit_list.size() == _capacity)            //已经存在满了数据，需要根据最近最少访问来删除结点
        {
            int delete_key = _visit_list.back()._key;
            _visit_list.pop_back();
            _hash_map.erase(delete_key);
        }
        _visit_list.push_front(Cache_node(key, value));
        _hash_map[key] = _visit_list.begin();
    }
}

int main(void)
{
    LRU_cache cache(2);



    return 0;
}