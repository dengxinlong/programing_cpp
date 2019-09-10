#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

using std::cout;
using std::endl;

void do_server(int sfd);

int main(void)
{
    int sfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.3.90");
    server_addr.sin_port = htons(6666);
    socklen_t len = sizeof(struct sockaddr_in);
    if (connect(sfd, (struct sockaddr *)&server_addr, len) == -1)
    {
        perror("connect");
        exit(-1);
    }

    char buf[1024] = {0};
    read(sfd, buf, sizeof(buf));
    cout << buf << endl;

    do_server(sfd);

    return 0;
}

void do_server(int sfd)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while (1)           //循环发送以及接收server端的数据
    {
        cout << ">>please enter msg: ";
        fgets(sendbuf, sizeof(sendbuf), stdin);
        int ret = write(sfd, sendbuf, strlen(sendbuf));
        //cout << "ret = " << ret << endl;
        //cout << "sizeof(sendbuf) is " << sizeof(sendbuf) << endl;
        int read_n = read(sfd, recvbuf, sizeof(recvbuf));
        if (read_n == -1)
        {
            perror("read");
            exit(-1);
        }
        else if (read_n == 0)
        {
            cout << "byebye.\n";//连接已经断开
            close(sfd);
            exit(EXIT_SUCCESS);
        }

        cout << "receive data is: " << recvbuf << endl;
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }
}
