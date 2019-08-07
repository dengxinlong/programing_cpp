#ifndef __LOG4CPP_T_H__
#define __LOG4CPP_T_H__

#include <log4cpp/Category.hh>
#include <string>

using std::string;

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



//日志宏定义的实现
#define  PREFIX(msg) string("[").append(__FILE__).append(": ")\
            		 .append(__FUNCTION__).append(": ")\
					 .append(std::to_string(__LINE__)).append("]: ").append(msg)

#define WARN(msg) Mylogger::getInstance()->warn(PREFIX(msg).c_str())
#define INFO(msg) Mylogger::getInstance()->info(PREFIX(msg).c_str())
#define ERROR(msg) Mylogger::getInstance()->error(PREFIX(msg).c_str())
#define DEBUG(msg) Mylogger::getInstance()->debug(PREFIX(msg).c_str())










#endif