#pragma once
#include<string>
#include<vector>
#include<sys/types.h>
#include<winsock2.h>
#include<iostream>
#include<stdlib.h>
#include<exception>

using namespace std;

class MySocketError: public exception {
private:
	string message;
public:
	MySocketError(string message) :message{ message } {}
	string getMessage() { return this->message; }
};

class MySocket
{
private:
	int dsc;
public:
	MySocket() {}
	MySocket(int dsc) :dsc{ dsc } {}
	//void send_string(string message)
	//{
	//	string lenght = to_string(message.length() + 1);
	//	if (send(dsc, lenght.data(), lenght.size(), NULL) == SOCKET_ERROR)
	//		throw new MySocketError("Error on sending lenght");
	//	if(send(dsc, message.data(), message.size(), NULL) == SOCKET_ERROR)
	//		throw new MySocketError("Error on sending message");
	//}
	//string recv_string()
	//{

	//	string finalString="";

	//	int lenght;
	//	//memset(lenght, 0, 10);
	//	if (recv(dsc, (char*)&lenght, sizeof(int), NULL) == SOCKET_ERROR)
	//		throw new MySocketError("Error on recv lenght");
	//	else
	//	{
	//		int intLenght = lenght;//atoi(lenght);
	//		char* message = new char(intLenght);
	//		memset(message, 0, intLenght);
	//		if (recv(dsc, message, intLenght*sizeof(char), NULL) == SOCKET_ERROR)
	//			throw new MySocketError("Error on recv message");
	//		else 
	//		{
	//			message[intLenght-1] = '\0';
	//			finalString = string(message);
	//		}
	//	}
	//	//fflush(stdint);
	//	return finalString;
	//	
	//}
	string recv_string_byte()
	{
		string str = "";
		char ch;
		if (recv(dsc, &ch, sizeof(char), NULL) == SOCKET_ERROR)
			throw new MySocketError("Error on recv message");
		while (ch != '\n')
		{
			str = str + ch;
			if (recv(dsc, &ch, sizeof(char), NULL) == SOCKET_ERROR)
				throw new MySocketError("Error on recv message");
		}
		return str;
	}
	void send_string_byte(string message)
	{
		message = message + '\n';
		for (int i = 0; i < message.size(); i++)
		{
			char ch = message[i];
			if (send(dsc, &ch, sizeof(char), 0) == SOCKET_ERROR)
				throw new MySocketError("Error on sending message");
		}
	}
	void send_int_byte(int number)
	{
		string message =to_string(number)+ '\n';
		for (int i = 0; i < message.size(); i++)
		{
			char ch = message[i];
			if (send(dsc, &ch, sizeof(char), 0) == SOCKET_ERROR)
				throw new MySocketError("Error on sending message");
		}
	}
	int recv_int_byte()
	{
		string str = "";
		char ch;
		if (recv(dsc, &ch, sizeof(char), NULL) == SOCKET_ERROR)
			throw new MySocketError("Error on recv message");
		while (ch != '\n')
		{
			str = str + ch;
			if (recv(dsc, &ch, sizeof(char), NULL) == SOCKET_ERROR)
				throw new MySocketError("Error on recv message");
		}
		int nr = atoi(str.c_str());
		return nr;
	}

};
