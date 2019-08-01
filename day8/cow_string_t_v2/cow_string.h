#ifndef __COW_STRING_H__
#define __COW_STRING_H__

using std::cout;
using std::endl;

//上一个版本中无法区分读写操作，这里使用设计模式之代理模式来完成需求
class Cow_string
{
private:
    class Char_proxy                //设计一个代理来完成要求
    {
    public:
        Char_proxy(Cow_string & self, int index)
        : _self(self)
        , _index(index)
        {}

        char & operator=(const char & ch)
        {
            if (_index >= 0 && _index < _self.size())           //嵌套类可以使用外部类定义的所有成员
            {
                cout << "Char_proxy: char & operator=(const char & ch)" << endl;
                if (_self.ref_cnt() > 1)
                {
                    char * temp_str = new char[strlen(_self._pstr) + 1 + 4]() + 4;
                    strcpy(temp_str, _self._pstr);
                
                    _self.release();
                    _self._pstr = temp_str;
                    _self.init_ref();
                }
                _self._pstr[_index] = ch;
                return _self._pstr[_index];
            }
            static char temp_ch = '\0';
            return temp_ch;
        }

        operator char()                 //这里使用类型转换函数作为读操作，而不是使用重载 << 运算符函数
        {
            return _self._pstr[_index];
        }
        //friend std::ostream & operator<<(std::ostream & os, const Char_proxy & rhs);

    private:
        Cow_string & _self;
        int _index;
    };

public:
    Cow_string();
    Cow_string(const char * str);
    ~Cow_string();

    Cow_string(const Cow_string & rhs);
    Cow_string & operator=(const Cow_string & rhs);
    Char_proxy operator[](std::size_t index);

    int ref_cnt(void);

    std::size_t size(void) const;
    const char * c_str(void) const;

    void print(void);

    friend std::ostream & operator<<(std::ostream & os, const Cow_string & rhs);
    //friend std::ostream & operator<<(std::ostream & os, const Char_proxy & rhs);

private:
    void init_ref(void);
    void increase_ref(void);
    void descrease_ref(void);
    void release(void);

private:
    char * _pstr;
};








#endif