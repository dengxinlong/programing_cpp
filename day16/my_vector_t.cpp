#include <iostream>
#include <memory>
#include <algorithm>

using std::endl;
using std::cout;

template <class T>
class My_vector
{
public:
    using iterator = T *;
    using const_iterator = const T *;

    My_vector()
    : _start(nullptr)
    , _finish(nullptr)
    , _end_of_storage(nullptr)
    {}

    ~My_vector()
    {
        if (_start)
            while (_start != _finish)
                _allocator.destroy(--_finish);          //销毁对象
        _allocator.deallocate(_start, capacity());          //销毁存储空间
    }

    iterator begin(void)
    {
        return _start;
    }

    iterator end(void)
    {
        return _finish;
    }

    size_t size(void)
    {
        return _finish - _start;
    }

    size_t capacity(void)
    {
        return _end_of_storage - _start;
    }

    T & operator[](size_t index)
    {
        return *(_start + index);
    }

    void push_back(const T & value);

    void pop_back(void);

private:
    void reallocate(void);

private:
    static std::allocator<T> _allocator;
    //std::allocator<T> _allocator;
    iterator _start;
    iterator _finish;
    iterator _end_of_storage;
};


template <class T>
std::allocator<T> My_vector<T>::_allocator;

template <class T>
void My_vector<T>::push_back(const T & value)
{
    if (size() == capacity())
        reallocate();           //容量不够，需要重新申请空间
    _allocator.construct(_finish++, value);
}

template <class T>
void My_vector<T>::pop_back(void)
{
    if (size() > 0)
        _allocator.destroy(--_finish);
}

template <class T>
void My_vector<T>::reallocate(void)
{
    size_t cap = capacity();
    size_t new_cap = cap * 2 > 0 ? cap * 2 : 1;

    iterator new_start = _allocator.allocate(new_cap);

    if (_start)
    {
        std::uninitialized_copy(_start, _finish, new_start);            //开辟空间

        //销毁对象
        while (_start != _finish)
            _allocator.destroy(--_finish);
        _allocator.deallocate(_start, cap);
    }

    _start = new_start;
    _finish = _start + cap;
    _end_of_storage = _start + new_cap;
}

template <class T>
void display(T & cont)
{
    typename T::iterator iter = cont.begin();
    for (; iter != cont.end(); ++iter)  
        cout << *iter << " ";
    cout << endl; 
}

int main(void)
{
    My_vector<int> vec;
    cout << "capacity = " << vec.capacity() << endl;
    cout << "size = " << vec.size() << endl;

    vec.push_back(1);
    cout << "capacity = " << vec.capacity() << endl;
    cout << "size = " << vec.size() << endl;

    vec.push_back(2);
    vec.push_back(3);
    cout << "capacity = " << vec.capacity() << endl;
    cout << "size = " << vec.size() << endl;
    cout << vec[0] << endl;

    display(vec);


    return 0;
}