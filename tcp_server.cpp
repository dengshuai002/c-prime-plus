/*
//使用c语言来完成tcp的模拟，socket
#pragma comment(lib, "ws2_32.lib")//连接网络编程接口，手动连接
#include <winsock2.h>
#include<iostream>
#include<ctime>


WSADATA wsa;

SOCKET server_fd, client_fd;
sockaddr_in server, client;

#define port 55
int client_len= sizeof(client);


//时间定义
time_t tm_ = sizeof(time_t);

void localtime_print() {
    //获取本地的时间
    tm_ = time(nullptr);
    tm* localtime_ = localtime(&tm_);
    std::cout << localtime_->tm_year+100 <<"-"
        << localtime_->tm_mon +1<< "-"
        << localtime_->tm_mday << "  "
        << localtime_->tm_hour << ":"
        << localtime_->tm_min << ":"
        << localtime_->tm_sec << ":"
        << std::endl;
}


int main() {

    char len_word;
    char buf[1024];



    //初始化winsock库
     if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
         std::cout << "wsa_init_error!\n" << std::endl;
         return -1;
     }

    //创建socket
     server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     if (server_fd == INVALID_SOCKET) {
         std::cout << "socket_init_error!\n" << std::endl;
         WSACleanup();
         return -1;
     }

    //绑定socket
         server.sin_family = AF_INET;          // IPv4
         server.sin_addr.s_addr = INADDR_ANY;  // 监听所有网络接口
         server.sin_port = htons(port);        // 监听端口

     if (bind(server_fd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
         std::cout << "bond_init_error!\n" << std::endl;
         WSACleanup();
         closesocket(server_fd);
         return -1;
    }

    //监听lient_socket
     if (listen(server_fd, 5) == SOCKET_ERROR) {
         std::cout << "listen_init_error!\n" << std::endl;
         WSACleanup();
         closesocket(server_fd);
         return -1;
     }

    //接受 lient_socket、阻塞的去等待连接
     std::cout << "等待客户端连接上来：\n" << std::endl;
     client_fd = accept(server_fd, (struct sockaddr*)&client, &client_len);

     if (client_fd == INVALID_SOCKET) {
         std::cout << "accept_init_error!\n"<< std::endl;
         std::cout << WSAGetLastError() << std::endl;
         WSACleanup();
         closesocket(server_fd);
         return -1;
     }
     localtime_print();
     std::cout<<"/*输入shutdown关闭socket插座*\/" <<std:: endl;
         while (1) {
             //接受信息
             len_word = recv(client_fd, buf, sizeof(buf), 0);
             if (len_word == SOCKET_ERROR) {
                 std::cout << "没有收到信息！\n" << std::endl;
             }
             else {
                 buf[len_word] = '\0';
                 printf("%s\n", buf);
             }

             send(client_fd, buf, len_word, 0);
             std::string str(buf);
             if (str == "shutdown") {
                 std::cout << "关闭socket插座\n" << std::endl;
                 WSACleanup();
                 closesocket(server_fd);
                 closesocket(client_fd);
                 return 0;
             }
             std::fill(std::begin(buf), std::end(buf), 0);//清除接受数组的内容
         }
     return 0;

}

*/
