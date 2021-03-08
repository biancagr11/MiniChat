#include"Service.h"
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

void socketThread(void* descriptorSocket, void* descriptorDB ) 
{
    int c = *((int*)descriptorSocket);
    sqlite3* DB = (sqlite3*)descriptorDB;

    MySocket socket{ c };

    UserValidator userValidator;
    MessageValidator messageValidator;
    LoginValidator loginValidator;

    UserDatabaseRepository userRepo{ userValidator, DB };
    MessageDatabaseRepository messageRepo{ messageValidator, DB };
    LoginDatabaseRepository loginRepo = LoginDatabaseRepository( loginValidator, DB );

    Service service{ loginRepo, userRepo, messageRepo, socket };

    string cmd = socket.recv_string_byte();
    try {

        while (cmd != "exit")
        {
            if (cmd == "login") {
                service.login();
            }
            else if (cmd == "conversation")
            {
                service.conversation();
            }
            else if (cmd == "addMessage")
            {
                service.addMessage();
            }
            cmd = socket.recv_string_byte();
        }
    }
    catch (MySocketError error)
    {
        cout << error.getMessage();
    }
    cout << "Bye!" << endl;


}
int main() {
    int s;
    struct sockaddr_in server, client;
    int c, l;

    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOK = WSAStartup(ver, &wsData);
    if (wsOK != 0)
    {
        cerr << "Can't initialize winsock! quitting"<<endl;
        return 1;
    }

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) 
    {
        printf("Error on creating socket server\n");
        return 1;
    }
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(2731);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) 
    {
        printf("Error on bind\n");
        return 1;
    }

    listen(s, 5);

    l = sizeof(client);
    memset(&client, 0, sizeof(client));

    //prepare backend
    sqlite3* DB;
    const char* dir = "C:\\Users\\bianc\\source\\repos\\Databases\\OfflineMessages.db";
  
    int exit = 0;
    exit = sqlite3_open(dir,&DB);
    if (exit != SQLITE_OK)
    {
        cout << "Error on open!!!" << endl;
    }
        		

    thread tid[40];
    int i = 0;
    printf("Waiting for clients!!!!\n");
    while (1) {
        
        c = accept(s, (struct sockaddr*)&client, &l);
        printf("New client connected\n");
        tid[i] = thread(socketThread,&c,DB);
        i++;

        if (i >= 30) {
            i = 0;
            while (i < 30) {
                tid[i++].join();
            }
            i = 0;
        }
    }

}

