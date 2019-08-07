#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

template<class T, int K_size = 10>
class Queue
{
public: 
    Queue()
    : _front(0)
    , _rear(0)
    , _data(new T[K_size]())
    {}

    ~Queue()
    {
        if (_data)
            delete [] _data;
    }

    void push(const T & t);                 //元素入队
    void pop(void);                 //元素出队             
    const T & front(void);                //读取队头元素         
    const T & back(void);                 //读取队尾元素         
    bool empty(void);                //判断队列是否为空     
    bool full(void);                //判断队列是否已满     
    int size(void) const;


private:
    int _front, _rear;
    T * _data;
};

template<class T, int K_size>       
int Queue<T, K_size>::size(void) const          //获取队列的大小
{
    return (_rear - _front + K_size) % K_size;
}

template<class T, int K_size>
void Queue<T, K_size>::push(const T & t)                 //元素入队
{
    if (!full())
    {
        _data[_rear++] = t;
        _rear %= K_size;
    }
    else
    {
        cout << "Queue is full, donot push anyone data.\n";
    }
}

template<class T, int K_size>
void Queue<T, K_size>::pop(void)                //元素出队   
{
    if (!empty())
    {
        _front = (_front + 1) % K_size;
    }
    else
    {
        cout << "Queue is emty, donot pop anyone data.\n";
    }
}

template<class T, int K_size>
const T & Queue<T, K_size>::front(void)               //读取队头元素   
{
    return _data[_front];
} 

template<class T, int K_size>
const T & Queue<T, K_size>::back(void)                 //读取队尾元素 
{
    return _data[(_rear - 1 + K_size) % K_size];
}   

template<class T, int K_size>
bool Queue<T, K_size>::empty(void)                //判断队列是否为空 
{
    return _rear == _front;
}

template<class T, int K_size>
bool Queue<T, K_size>::full(void)                //判断队列是否已满  
{
    return (_rear + 1) % K_size == _front;
}   


void test0(void)
{
    Queue<int> queue;
    cout << "queue is emty? " << queue.empty() << endl;
    for (int i = 0; i < 10; i++)        //这个队列是一个循环队列，只能放指定个数少一个元素
    {
        queue.push(i);
    }
    cout << "queue is full? " << queue.full() << endl;
    cout << "queue's size is " << queue.size() << endl;

    while (!queue.empty())
    {
        cout << queue.front() << endl;
        queue.pop();
    }
    cout << "queue's size is " << queue.size() << endl;
}

void test1(void)
{
    Queue<string> queue;
    cout << "queue is emty? " << queue.empty() << endl;
    for (int i = 0; i < 10; i++)
    {
        queue.push(string(3, 'a' + i));
    }
    cout << "queue is full? " << queue.full() << endl;
    cout << "queue's size is " << queue.size() << endl;

    while (!queue.empty())
    {
        cout << queue.front() << endl;
        queue.pop();
    }
    cout << "queue's size is " << queue.size() << endl;
}

int main(void)
{
    //test0();
    test1();

    return 0;
}