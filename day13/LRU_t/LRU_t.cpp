#include <iostream>
#include <map>
#include <list>
#include <algorithm>

using std::cout;
using std::endl;
using std::map;
using std::list;
using std::pair;

class LRUCache 
{
public:
    LRUCache(int capacity) 
    : _capacity(capacity)
    {}
    
    int get(int key) 
    {
        auto iter = _dict.find(key);
        if (iter != _dict.end())
        {
            //将_queue中的key值移动到队列尾部,实时更新 _list
            auto list_iter = find(_list.begin(), _list.end(), key);
            _list.erase(list_iter);
            _list.push_back(key);
            return iter->second;
        }
        return -1;
    }
    
    void put(int key, int value) 
    {
        auto iter = _dict.find(key);
        if (iter != _dict.end())
        {
            _dict.erase(iter->first);
            auto list_iter = find(_list.begin(), _list.end(), key);
            _list.erase(list_iter);

        }

        if (_dict.size() == _capacity)
        {
            int remove_key = _list.front();
            _list.pop_front();
            _dict.erase(remove_key);

            _dict.insert(std::make_pair(key, value));
            _list.push_back(key);
        }
        else
        {
            _dict.insert(std::make_pair(key, value));
            _list.push_back(key);
            cout << "------ " << key << " ---------" << endl;
            
        }
    }

    void print(void) const
    {
        for (auto elem : _dict)
        {
            cout << elem.first << "---> " << elem.second << endl;
        }
    }

private:
    list<int> _list;

private:
    int _capacity;
    map<int, int> _dict;
};

int main(void)
{
    LRUCache cache(2);

    cache.put(2, 1);
    cache.put(1, 1);
    cache.put(2, 3);
    cache.put(4, 1);
    //cache.print();
     cout << cache.get(1) << endl;
    cout << cache.get(2) << endl;


    return 0;
}