#include "MessageDatabaseRepository.h"
static int selectMax(void* max, int argc, char** argv, char** azColName) {
	int* m = (int*)max;
	*m = atoi(argv[0]);
	return 0;
}
void MessageDatabaseRepository::add(Message entity){


	char* messaggeError;

	//set message id
	string sqlSelectMax = "SELECT MAX(id) FROM MESSAGES";
	int max;
	int exit = sqlite3_exec(DB, sqlSelectMax.c_str(), selectMax, &max, &messaggeError);
	if (exit != SQLITE_OK) {
		throw new RepoError(messaggeError);
		sqlite3_free(messaggeError);
	}
	if (max >= 0)
		entity.setId(max+1);
	int id = entity.getId();
	int from = entity.getFrom();
	int to = entity.getTo();
	string text = entity.getText();
	time_t date = entity.getDate();
	tm* time = gmtime(&date);
	int reply = entity.getReply();

	string values =to_string(id)+","+ to_string(from) + ", " + to_string(to) + ", " +"'"+ text +"'"+
		"," + to_string(time->tm_year) + "," + to_string(time->tm_mon) + "," + to_string(time->tm_mday)
		+ "," + to_string(time->tm_hour) + "," + to_string(time->tm_min) + "," + to_string(time->tm_sec)+","+to_string(reply);

	string sql = "INSERT INTO MESSAGES(id,userFrom, userTo, text, year, month, day,hour, minute, second, reply) VALUES(" + values + ")";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		throw new RepoError(messaggeError);
		sqlite3_free(messaggeError);
	}
}

void MessageDatabaseRepository::remove(int id) 
{
	string query = "DELETE FROM MESSAGES WHERE id=" + to_string(id);
	char* messaggeError;
	int exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		throw new RepoError(messaggeError);
		sqlite3_free(messaggeError);
	}
	
}
static int selectOneMessage(void* message, int argc, char** argv, char** azColName) {
	Message* msg = (Message*)message;
	int i = 0;
	int id = atoi(argv[i]);
	int from = atoi(argv[i + 1]);
	int to = atoi(argv[i + 2]);
	string text = argv[i + 3];
	time_t date = time(0);
	tm* time = gmtime(&date);
	time->tm_year = atoi(argv[i + 4]);
	time->tm_mon = atoi(argv[i + 5]);
	time->tm_mday = atoi(argv[i + 6]);
	time->tm_hour = atoi(argv[i + 7]);
	time->tm_min = atoi(argv[i + 8]);
	time->tm_sec = atoi(argv[i + 9]);
	int reply = atoi(argv[i + 10]);
	time_t converted;
	converted = mktime(time);
	msg->setId(id); msg->setFrom(from); msg->setTo(to); msg->setText(text); msg->setDate(converted); msg->setReply(reply);
	return 0;
}
Message MessageDatabaseRepository::findOne(int id) 
{
	Message message;
	char* messageError;
	string query = "SELECT * FROM MESSAGES WHERE id=" + to_string(id);
	int exit = sqlite3_exec(DB, query.c_str(), selectOneMessage, &message, &messageError);
	if (exit != SQLITE_OK)
	{
		throw new RepoError("ERROR ON SELECT MESSAGE!");
	}
	return message;
}
static int selectAllMessages(void* messages, int argc, char** argv, char** azColName) {
	vector<Message>* u = (vector<Message>*)messages;
	if (argc < 11)
		return 0;
	for (int i = 0; i < argc; i += 11)
	{
		int id = atoi(argv[i]);
		int from = atoi(argv[i + 1]);
		int to = atoi(argv[i + 2]);
		string text = argv[i + 3];
		time_t date = time(0);
		tm* time = gmtime(&date);
		time->tm_year = atoi(argv[i + 4]);
		time->tm_mon = atoi(argv[i + 5]);
		time->tm_mday = atoi(argv[i + 6]);
		time->tm_hour = atoi(argv[i + 7]);
		time->tm_min = atoi(argv[i + 8]);
		time->tm_sec = atoi(argv[i + 9]);
		int reply = atoi(argv[i + 10]);
		time_t converted;
		converted = mktime(time);
		Message message(id, from, to, text, converted, reply);
		u->push_back(message);
	}
	return 0;
}
vector<Message> MessageDatabaseRepository::findAll()
{
	vector<Message> messages;
	char* messageError;
	string querySelect = "SELECT * FROM MESSAGES";
	int exit = sqlite3_exec(DB, querySelect.c_str(), selectAllMessages, &messages, &messageError);
	if (exit != SQLITE_OK)
	{
		throw new RepoError("ERROR ON SELECT MESSAGES!");
	}
	return messages;
}

vector<Message> MessageDatabaseRepository::findConversation(int user1, int user2)
{
	vector<Message> messages;
	char* messageError;
	string querySelect1 = "SELECT * FROM MESSAGES WHERE userFrom="+to_string(user1)+" AND userTo="+to_string(user2);
	string querySelect2 = "SELECT * FROM MESSAGES WHERE userFrom=" + to_string(user2) + " AND userTo=" + to_string(user1);
	int exit = sqlite3_exec(DB, querySelect1.c_str(), selectAllMessages, &messages, &messageError);
	if (exit != SQLITE_OK)
	{
		throw new RepoError("ERROR ON SELECT MESSAGES!");
	}
	exit = sqlite3_exec(DB, querySelect2.c_str(), selectAllMessages, &messages, &messageError);
	if (exit != SQLITE_OK)
	{
		throw new RepoError("ERROR ON SELECT MESSAGES!");
	}
	return messages;
}