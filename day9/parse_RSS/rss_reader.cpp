#include <cstdlib>
#include <regex>
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
    doc.LoadFile("coolshell.xml");

    int error_id = doc.ErrorID();
    if (error_id)              //打开xml文件失败
    {
        cout << "open coolshell.xml fail." << endl;
        exit(-1);
    }
    XMLElement * root_element = doc.RootElement();              //获取根结点，也就是xml文件中对的第一个
    XMLElement * channel_element = root_element->FirstChildElement("channel");      //获取channel中的信息
    XMLElement * item_element = channel_element ->FirstChildElement("item");
    
    Rss_item item;
    XMLElement * title;
    XMLElement * link;
    XMLElement * description;
    XMLElement * content;
    XMLElement * other;
    std::string patten("({,.*]})");
    std::regex reg_experss(patten);
    while (item_element)
    {
        title = item_element->FirstChildElement("title");
        item.title = title->GetText();
        cout << item.title << endl;

        link = item_element->FirstChildElement("link");
        item.link = link->GetText();
        cout << item.link << endl;

        description = item_element->FirstChildElement("description");
        item.description = description->GetText();
        cout << item.description << endl;

        content = item_element->FirstChildElement("content:encoded");
        //result = content->GetText();

        item.content = content->GetText();
        //item.content = std::regex_replace(item.content, reg_experss, "");
        cout << item.content << endl;

        _rss.push_back(item);
        item_element = item_element->NextSiblingElement();
    }

}

void Rss_reader::dump(const string & filename)             //输出到某个文件中
{

}
