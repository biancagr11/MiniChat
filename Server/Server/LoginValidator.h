#pragma once
#include"Login.h"
#include"Validator.h"
class LoginValidator:public Validator<Login>
{
public:
	LoginValidator() {}
	void Validate(Login entity) override
	{
		int a;
	}
};