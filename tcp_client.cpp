//使用c语言来完成tcp的模拟，socket 
#pragma comment(lib, "ws2_32.lib")//连接网络编程接口，手动连接
#include <winsock2.h>
#include<iostream>

#include <ws2tcpip.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>

#define port 5001

SOCKET socket_fd;

sockaddr_in server_struct;
WSADATA wsa;
ULONG ip_addr;

char buf[1024];
int main() {
    //初始化winsock库
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            std::cout << "wsa_init_error!\n" << std::endl;
            return -1;
        }
    //创建socket插座
    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd == INVALID_SOCKET) {
        std::cout << "socket init fail\n" << std::endl;
        WSACleanup();
        return -1;
    }
    //设置结构体服务器地址
    memset(&server_struct, 0, sizeof(server_struct));
    server_struct.sin_family  = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &ip_addr) != 1) {
        std::cout << "inet failed!\n" << std::endl;
        closesocket(socket_fd);
        WSACleanup();
        return -1;
    }
    server_struct.sin_addr.s_addr = ip_addr;
    server_struct.sin_port = htons(port);
    //连接服务器

    if (connect(socket_fd, (sockaddr*)&server_struct, sizeof(sockaddr)) != 0) {
        std::cout << "connect failed!\n" << std::endl;
        closesocket(socket_fd);
        WSACleanup();
        return -1;
    }
    while (1) {
        //发送数据
        if (send(socket_fd, "wowa!", 5, 0) == SOCKET_ERROR) {
            std::cout << "send fail\n" << std::endl;
            closesocket(socket_fd);
            WSACleanup();
            return -1;
        }
        //接受数据
        int len = sizeof(int);
        len = recv(socket_fd, buf, sizeof(buf), 0);
        if (len== SOCKET_ERROR) {
            std::cout << "recv fail\n" << std::endl;
            closesocket(socket_fd);
            WSACleanup();
            return -1;
        }
        buf[len] = '\0';
        std::cout << buf << std::endl;
    }
    
    return 0;

}
