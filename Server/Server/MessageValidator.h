#pragma once
#include"Validator.h"
#include"Message.h"
class MessageValidator:public Validator<Message>
{
public:
	MessageValidator() {}
	void Validate(Message entity) override 
	{
		int a;
	}
};

