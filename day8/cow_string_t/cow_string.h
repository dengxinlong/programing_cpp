#ifndef __COW_STRING_H__
#define __COW_STRING_H__

class Cow_string
{
public:
    Cow_string();
    Cow_string(const char * str);
    ~Cow_string();

    Cow_string(const Cow_string & rhs);
    Cow_string & operator=(const Cow_string & rhs);
    char & operator[](std::size_t index);

    int ref_cnt(void);

    std::size_t size(void) const;
    const char * c_str(void) const;

    void print(void);

    friend std::ostream & operator<<(std::ostream & os, const Cow_string & rhs);

private:
    void init_ref(void);
    void increase_ref(void);
    void descrease_ref(void);
    void release(void);

private:
    char * _pstr;
};








#endif