#pragma once
#include"LoginValidator.h"
#include"DatabaseRepository.h"

#include<vector>
#include<sqlite3.h>
using namespace std;

class LoginDatabaseRepository :public DatabaseRepository<int, Login>
{
private:
	LoginValidator loginValidator;
	sqlite3* DB;
public:
	LoginDatabaseRepository(LoginValidator userValidator, sqlite3* DB) :
		DatabaseRepository(),
		DB{ DB },
		loginValidator{ loginValidator }{}
	void add(Login entity) override;
	void remove(int id) override;
	Login findOne(int id) override;
	int findUserId(string username, string password);
	vector<Login> findAll() override;
};

