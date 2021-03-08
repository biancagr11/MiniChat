#pragma once
#include"Entity.h"
#include <string>
using namespace std;

class User : public Entity<int>
{
private:
	string firstName;
	string lastName;

public:
	User(){}
	User(int id, string firstName, string lastName) :firstName { firstName }, lastName{ lastName }
	{
		Entity<int>::setId(id);
	}
	string toString() override {
		return firstName + " " + lastName;
	}
};
