#include "Message.h"
int Message::getFrom() {
	return this->from;
}
int Message::getTo() {
	return this->to;
}
string Message::getText() {
	return this->text;
}
time_t Message::getDate() {
	return this->date;
}
int Message::getReply()
{
	return this->reply;
}
void Message::setReply(int messageId)
{
	this->reply = messageId;
}
