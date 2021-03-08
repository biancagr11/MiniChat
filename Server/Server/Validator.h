#pragma once
#include"Entity.h"
template<typename T>
class Validator
{
public:
	virtual void Validate(T entity) = 0;
};


class ValidationError {
private:
	string message;
public:
	ValidationError(string message):message{message}{}
	string getMessage() { return this->message; }
};