#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Category.hh>
#include <cstdlib>

#include "log4cpp_t.h"

using namespace log4cpp;

Mylogger * Mylogger::_ptr = Mylogger::getInstance();            //饿汉模式，保证是线程安全的
				
Mylogger::Mylogger()
: _category(Category::getRoot().getInstance("category"))
{
    PatternLayout * _pattern_layout1 = new PatternLayout();
    _pattern_layout1->setConversionPattern("'%c' %d: [%p] %x %m %n");
            
    OstreamAppender * _ostream_appender = new OstreamAppender("ostream_appender", &std::cout);
    _ostream_appender->setLayout(_pattern_layout1);

    PatternLayout * _pattern_layout2 = new PatternLayout();
    _pattern_layout2->setConversionPattern("'%c' %d: [%p] %x %m %n");

    FileAppender * _file_appender = new FileAppender("file_appender", "test_t.log");
    _file_appender->setLayout(_pattern_layout2);
            
    _category.setPriority(Priority::DEBUG);
    _category.addAppender(_ostream_appender);
    _category.addAppender(_file_appender);
}

Mylogger::~Mylogger()
{
    Category::shutdown();
}


Mylogger * Mylogger::getInstance(void)
{
    if (_ptr == nullptr)
    {
        _ptr = new Mylogger();
        ::atexit(destroy);
    }
            
    return _ptr;
}

void Mylogger::destroy(void)
{
    if (_ptr)
    {
        delete _ptr;
    }    
}
    
void Mylogger::warn(const char * msg)          
{
    //_category.warn(msg);
     _category.warn(msg);
}

void Mylogger::error(const char * msg)
{
    _category.error(msg);
}

void Mylogger::debug(const char * msg)
{
    _category.debug(msg);
}

void Mylogger::info(const char * msg)
{
    _category.info(msg);
}

