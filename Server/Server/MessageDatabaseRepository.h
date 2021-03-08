#pragma once
#include"DatabaseRepository.h"
#include"Message.h"
#include"MessageValidator.h"
#include<sqlite3.h>
#include<time.h>
#include<ctime>
#include<vector>
#include"User.h"

using namespace std;

class MessageDatabaseRepository: public DatabaseRepository<int, Message>
{
private:
	MessageValidator messageValidator;
	sqlite3* DB;
public:
	MessageDatabaseRepository(MessageValidator messageValidator, sqlite3* DB):DatabaseRepository()
	{
		this->messageValidator = messageValidator;
		this->DB = DB;
	}
	void add(Message entity) override;
	void remove(int id) override;
	Message findOne(int id) override;
	vector<Message> findAll() override;
	vector<Message> findConversation(int user1, int user2);
};

//time_t date = time(0);
//cout << date;
//char buf[100];
//ctime_s(buf, 100 * sizeof(char), &date);
//cout << buf;
//
//tm* time = gmtime(&date);
//cout << time->tm_year;
