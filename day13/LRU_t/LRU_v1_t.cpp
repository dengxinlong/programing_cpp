#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>


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
    int _capacity;
    list<int> _visit_list;
    unordered_map<int, int> _hash_map; 
};

int LRU_cache::get(int key)
{
    auto iter = _hash_map.find(key);
    if (iter != _hash_map.end())
    {
        _visit_list.splice(_visit_list.begin(), _visit_list, std::find(_visit_list.begin(), _visit_list.end(), key));
        return iter->second;
    }
    else
        return -1;
}
void LRU_cache::put(int key, int value)
{
    auto iter = _hash_map.find(key);
    if (iter != _hash_map.end())            //此时map中已经存在的相应的元素
    {
        _hash_map[key] = value;
        _visit_list.splice(_visit_list.begin(), _visit_list, std::find(_visit_list.begin(), _visit_list.end(), key));
    }
    else            //不存在相同关键字的元素
    {
        if (_visit_list.size() == _capacity)            //已经存在满了数据，需要根据最近最少访问来删除结点
        {
            int delete_key = _visit_list.back();
            _visit_list.pop_back();
            _hash_map.erase(delete_key);
        }
        _visit_list.push_front(key);
        _hash_map[key] = value;
    }
}

int main(void)
{
    LRU_cache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;
    cache.put(3, 3);
    cout << cache.get(2) << endl;
    cache.put(4, 4);
    cout << cache.get(1) << endl;
    cout << cache.get(3) << endl;
    cout << cache.get(4) << endl;


    cache.put(1, 1);

    return 0;
}