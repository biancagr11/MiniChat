#include "LoginDatabaseRepository.h"

static int selectUser(void* user, int argc, char** argv, char** azColName) {
    int* u = (int*)user;
    *u = atoi(argv[0]);
    return 0;
}

int LoginDatabaseRepository::findUserId(string username, string password)
{
    char* messageError;
    string queryLogin = "SELECT user FROM LOGIN WHERE username='"+username+"' AND password='"+password+"'";
    int user;
    int exit=sqlite3_exec(DB, queryLogin.c_str(), selectUser, &user, &messageError);
    if (exit != SQLITE_OK)
    {
        throw new RepoError("ERROR ON SELECT USER FROM LOGIN!");
    }
    return user;
}

void LoginDatabaseRepository::add(Login entity)
{

}
void LoginDatabaseRepository::remove(int id)
{

}
Login LoginDatabaseRepository::findOne(int id)
{
    Login l;
    return l;
}
vector<Login> LoginDatabaseRepository::findAll()
{
    vector<Login> logs;
    return logs;
}