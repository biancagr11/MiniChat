#pragma once
#include<string>
#include"Entity.h"
using namespace std;
class Login : public Entity<int>
{
private:
	string username;
	string password;
	int user;

public:
	Login(){}
	Login(string username, string password, int user):
		username{username},
		password{password},
		user{user}{}

	string toString() override {
		return to_string(user)+": "+username+" ->"+password;
	}
};
