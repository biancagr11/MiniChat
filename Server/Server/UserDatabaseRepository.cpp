#include "UserDatabaseRepository.h"
void UserDatabaseRepository::add(User entity)
{

}
void UserDatabaseRepository::remove(int id)
{

}
User UserDatabaseRepository::findOne(int id)
{
	User u;
	return u;
}
static int selectAllUsers(void* users, int argc, char** argv, char** azColName) {
	vector<User>* u = (vector<User>*)users;
	for (int i = 0; i < argc; i+=3)
	{
		User user(atoi(argv[i]), argv[i+1], argv[i+2]);
		u->push_back(user);
	}
	return 0;
}
vector<User> UserDatabaseRepository::findAll()
{
	vector<User> users;
	char* messageError;
	string querySelect = "SELECT * FROM USERS";
	int exit = sqlite3_exec(DB, querySelect.c_str(), selectAllUsers, &users, &messageError);
	if (exit != SQLITE_OK)
	{
		throw new RepoError("ERROR ON SELECT USERS!");
	}
	return users;
}