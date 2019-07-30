#ifndef __LOG4CPP_T_H__
#define __LOG4CPP_T_H__

#include <log4cpp/Category.hh>

using namespace log4cpp;

class Mylogger
{
public:
    static Mylogger * getInstance(void);

    static void destroy(void);
    

	void warn(const char * msg);

	void error(const char * msg);

	void debug(const char * msg);

	void info(const char * msg);


    
private:
	Mylogger();
	~Mylogger();
private:
    
	Category & _category;
	static Mylogger * _ptr;
	
};			















#endif