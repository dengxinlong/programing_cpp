#include "acceptor.h"
#include "tcp_connection.h"

#include <iostream>

using std::cout;
using std::endl;

int main(void)
{
    Acceptor acceptor("192.168.5.90", 6666);
    acceptor.ready();

    Tcp_connection connect(acceptor.accept());
    cout << connect.to_string() << "connected.\n";
    connect.send("welcome to connect.");
    cout << ">>client: " << endl;
    cout << connect.receive() << endl;


    return 0;
}
