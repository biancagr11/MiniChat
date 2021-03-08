#include"Service.h"
#include"MySocket.h"
#include<iostream>
#include<string>
#include<exception>
#include<sqlite3.h>
#include<thread>
#include<sys/types.h>
#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#pragma comment (lib, "ws2_32.lib")
//#include<netinet/in.h>
#include<Ws2tcpip.h>
using namespace std;
//
//void socketThread(int c)
//{
//    MySocket socket=MySocket(c);
//    
//    for(int i=1;i<=10;i++)
//    {
//        string s = socket.recv_string();
//        cout << "Mesaj primit: " << s << endl;
//    }
//
//    //cout << username;
//
//    //Cod deservire
//}
//int main() {
//    //int s;
//    //struct sockaddr_in server, client;
//    //int c, l;
//
//    //WSADATA wsData;
//    //WORD ver = MAKEWORD(2, 2);
//
//    //int wsOK = WSAStartup(ver, &wsData);
//    //if (wsOK != 0)
//    //{
//    //    cerr << "Can't initialize winsock! quitting" << endl;
//    //    return 1;
//    //}
//
//    //s = socket(AF_INET, SOCK_STREAM, 0);
//    //if (s < 0) {
//    //    printf("Eroare la crearea socketului server\n");
//    //    return 1;
//    //}
//
//    //memset(&server, 0, sizeof(server));
//    //server.sin_port = htons(2731);
//    //server.sin_family = AF_INET;
//    //server.sin_addr.s_addr = INADDR_ANY;
//
//    //if (bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
//    //    printf("Eroare la bind\n");
//    //    return 1;
//    //}
//
//    //listen(s, 5);
//
//    //l = sizeof(client);
//    //memset(&client, 0, sizeof(client));
//
//    //thread tid[40];
//    //int i = 0;
//    //while (1) {
//
//    //    c = accept(s, (struct sockaddr*)&client, &l);
//    //    printf("S-a conectat un client\n");
//
//    //    tid[i] = thread(socketThread, s);
//    //    i++;
//
//    //    if (i >= 30) {
//    //        i = 0;
//    //        while (i < 30) {
//    //            tid[i++].join();
//    //        }
//    //        i = 0;
//    //    }
//    //}
//
//
//
//
//}
//


//static int call(void* data, int argc, char** argv, char** azColName)
//{
//
//	for (int i = 0; i < argc; i++) {
//		cout << azColName[i] << ":" << argv[i] << endl;
//	}
//
//	cout << endl;
//	return 0;
//}
//

//int main(int argc, char* argv[])
//{
//	sqlite3* DB;
//	const char* dir = "C:\\Users\\bianc\\source\\repos\\Databases\\OfflineMessages.db";
//	int exit = sqlite3_open(dir,&DB);
//	
//	UserValidator userValidator;
//	MessageValidator messageValidator;
//	LoginValidator loginValidator;
//
//	UserDatabaseRepository userRepo{ userValidator, DB };
//	MessageDatabaseRepository messageRepo{ messageValidator, DB };
//	LoginDatabaseRepository loginRepo{ loginValidator, DB };
//	
//	Message m{ 3,3,5,"Teme, tu?",time(0),-1 };
//	messageRepo.add(m);
//	vector<Message> msgs = messageRepo.findConversation(5, 3);
//	for (Message m : msgs)
//		cout << m.toString();
//	sqlite3_close(DB);
//
//	return 0;
//}
