#include <cstdlib>
#include "rss_reader.h"
#include "tinyxml2.h"


using namespace tinyxml2;

//构造函数
Rss_reader::Rss_reader()                           
{
    _rss.reserve(50);
}

//解析函数
void Rss_reader::parse_rss(void)                              
{
    XMLDocument doc;
    doc.LoadFile("CoolShell.xml");

    int error_id = doc.ErrorID();
    if (error_id)              //打开xml文件失败
    {
        cout << "open CoolShell.xml fail." << endl;
        exit(-1);
    }
    XMLElement * root = doc.RootElement();              //获取根结点
    XMLElement * 

}

void Rss_reader::dump(const string & filename)             //输出到某个文件中
{

}
