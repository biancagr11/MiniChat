#pragma once
#include"Entity.h"
#include"User.h"
class Message : public Entity<int>
{
private:
	int from;
	int to;
	string text;
	time_t date;
	int reply;

public:
	Message(){}
	Message(int id,int from, int to, string text, time_t date, int reply) :
		from{ from },
		to{ to },
		text{ text },
		date{ date },
		reply{reply}
	{
		Entity<int>::setId(id);
	}

	int getFrom();
	int getTo();
	string getText();
	time_t getDate();
	int getReply();
	void setReply(int messageId);
	string toString() override {
		return to_string(from)+"-"+to_string(to)+": "+text;
	}

	void setFrom(int from) { this->from = from; }
	void setTo(int to) { this->to = to; }
	void setDate(time_t date) { this->date = date; }
	void setText(string text) { this->text = text; }
	

};

