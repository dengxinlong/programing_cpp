#include <iostream>
#include <initializer_list>

using std::cout;
using std::endl;
using std::initializer_list;

template <class T, class Compare = std::less<T>>
class Heap_sort
{
public:
    Heap_sort(initializer_list<T> lst)
    : _ptr(new T[lst.size() + 1]())
    , _size(lst.size())
    {
        int i = 0;
        for (auto beg = lst.begin(); beg != lst.end(); ++beg)
        {
            _ptr[i++] = *beg;
        }
    }

    void print(void) const
    {
        for (int i = 0; i < _size; ++i)
        {
            cout << _ptr[i] << " ";
        }
        cout << endl;
    }


    void sort(void);    

private:
    void heap_adjust(int adjust_pos, size_t size);         //调整为大根堆或者小根堆 
    bool compare(const T & t1, const T & t2, Compare com = Compare());     

private:
    T * _ptr;
    size_t _size;

};

template <class T, class Compare>
void Heap_sort<T, Compare>::heap_adjust(int adjust_pos, size_t size)
{
    int dad = adjust_pos;
    int son = 2 * dad + 1;
    while (son < size)
    {
        //if (son + 1 < size && _ptr[son] > _ptr[son + 1])
        if (son + 1 < size && compare(_ptr[son], _ptr[son + 1]))
        {
            ++son;
        }

        if (compare(_ptr[dad], _ptr[son]))
        {
            T temp = _ptr[dad];
            _ptr[dad] = _ptr[son];
            _ptr[son] = temp;

            dad = son;
            son = 2 * dad + 1;
        }
        else 
        {
            break;
        }
    }
}

template <class T, class Compare>
void Heap_sort<T, Compare>::sort(void)
{
    for (int i = _size; i >= 0; --i)
    {
        heap_adjust(i, _size);
    }

    T temp = _ptr[0];
    _ptr[0] = _ptr[_size - 1];
    _ptr[_size - 1] = temp;

    for (int i = _size - 1; i > 1; --i)
    {
        heap_adjust(0, i);

        T temp = _ptr[0];
        _ptr[0] = _ptr[i - 1];
        _ptr[i - 1] = temp;

    }

}

template <class T, class Compare>
bool Heap_sort<T, Compare>::compare(const T & t1, const T & t2, Compare com)
{
    return com(t1, t2);
}


int main(void)
{
    Heap_sort<int> h1 = {8, 5, 4, 0, 12, 3};
    h1.sort();
    h1.print();

    return 0;
}