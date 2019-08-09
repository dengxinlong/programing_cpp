/*
 *说明：本次日志服务的封装是在上一个版本中的改进，增加了可变参数
 */
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
    
	template <typename... Args> 
	void warn(Args... args)
	{
		_category.warn(args...);
	}

	template <typename... Args> 
	void error(Args... args)
	{
		_category.error(args...);
	}

	template <typename... Args> 
	void debug(Args... args)
	{
		_category.debug(args...);
	}

	template <typename... Args> 
	void info(Args... args)
	{
		_category.info(args...);
	}


    
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

#define WARN(msg, args...) Mylogger::getInstance()->warn(PREFIX(msg).c_str(), ##args)
#define INFO(msg, args...) Mylogger::getInstance()->info(PREFIX(msg).c_str(), ##args)
#define ERROR(msg, args...) Mylogger::getInstance()->error(PREFIX(msg).c_str(), ##args)
#define DEBUG(msg, args...) Mylogger::getInstance()->debug(PREFIX(msg).c_str(), ##args)










#endif