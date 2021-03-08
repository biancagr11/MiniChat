#pragma once
#include<sqlite3.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include"User.h"
#include"UserValidator.h"
#include"DatabaseRepository.h"
class UserDatabaseRepository:public DatabaseRepository<int,User>
{
private:
	UserValidator userValidator;
	sqlite3* DB;
public:
	UserDatabaseRepository(UserValidator userValidator, sqlite3* DB):
		DatabaseRepository(),
		DB{DB},
		userValidator{userValidator}{}
		void add(User entity) override;
		void remove(int id) override;
		User findOne(int id) override;
		vector<User> findAll() override;
};

