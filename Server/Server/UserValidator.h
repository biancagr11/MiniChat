#pragma once
#include"Validator.h"
#include"User.h"
class UserValidator: public Validator<User>
{
public:
	UserValidator(){}
	void Validate(User entity) override
	{

	}
};

