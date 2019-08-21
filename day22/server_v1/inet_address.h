#ifndef __INET_ADDRESS_H__
#define __INET_ADDRESS_H__

#include <arpa/inet.h>

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Inet_address
{
public:
    explicit
    Inet_address(const string & ip, unsigned short port);
    Inet_address(const struct sockaddr_in & addr);

    string get_ip(void) const;
    unsigned short get_port(void) const;
    struct sockaddr_in * get_inet_addr_ptr(void);

    ~Inet_address() {}

private:
    struct sockaddr_in _addr;
};












#endif