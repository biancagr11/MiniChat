#pragma once
#include"MessageDatabaseRepository.h"
#include"UserDatabaseRepository.h"
#include"LoginDatabaseRepository.h"
#include"MySocket.h"
#include<algorithm>
class Service
{
private:
	MessageDatabaseRepository& messageRepo;
	UserDatabaseRepository& userRepo;
	LoginDatabaseRepository& loginRepo;
	MySocket socket;

public:
	Service(LoginDatabaseRepository& loginRepo,UserDatabaseRepository& userRepo,MessageDatabaseRepository& messageRepo, MySocket dscSocket):
		messageRepo{messageRepo},
		userRepo{userRepo},
		loginRepo{loginRepo},
		socket{dscSocket}{}

	void login();
	void users();
	void addMessage();
	void conversation();

};
