#pragma once

#include<string>
#include<vector>
#include<exception>

using namespace std;

template<typename ID, typename T=Entity<ID> >
class DatabaseRepository
{   
public:
    
    DatabaseRepository() {};
    virtual void add(T entity)=0;
    virtual void remove(ID id)=0;
    virtual T findOne(ID id)=0;
    virtual vector<T> findAll()=0;

};

class RepoError:public exception{
private:
    string message;
public:
    RepoError(string message) :message{ message } {}
    string getMessage() { return this->message; }
};