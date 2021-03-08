//#include "Client.h"
//#include <QtWidgets/QApplication>
//#include<exception>
//#include<thread>
//#include<sys/types.h>
//#include<winsock2.h>
//#include<stdio.h>
//#include<Ws2tcpip.h>
//#include<iostream>
//#include"MySocket.h"
//#pragma comment (lib, "ws2_32.lib")
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//
//    int c;
//    struct sockaddr_in server;
//
//    WSADATA wsData;
//    WORD ver = MAKEWORD(2, 2);
//
//    int wsOK = WSAStartup(ver, &wsData);
//    if (wsOK != 0)
//    {
//        cerr << "Can't initialize winsock! quitting" << endl;
//        return 1;
//    }
//
//
//    c = socket(AF_INET, SOCK_STREAM, 0);
//    if (c < 0) {
//        printf("Eroare la crearea socketului client\n");
//        return 1;
//    }
//
//    memset(&server, 0, sizeof(server));
//    server.sin_port = htons(2731);
//    server.sin_family = AF_INET;
//    server.sin_addr.s_addr = inet_addr("127.0.0.1");
//
//    if (connect(c, (struct sockaddr*)&server, sizeof(server)) < 0) {
//        printf("Eroare la conectarea la server\n");
//        return 1;
//    }
//
//    MySocket socket = MySocket(c);
//    for (int i = 1; i <= 10; i++)
//    {
//        socket.send_string("hei!");
//    }
//
//    //close(c);
//
//    return 0;
//}