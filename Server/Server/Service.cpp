#include"Service.h"
void Service::login()
{
	string username = socket.recv_string_byte();
	string password = socket.recv_string_byte();
	try
	{
		int user = loginRepo.findUserId(username, password);
		if (user < -1)
		{
			socket.send_string_byte("Incorect USERNAME or PASSWORD!");
		}
		else
		{
			socket.send_string_byte("OK");
			socket.send_int_byte(user);
			users();

		}
	}
	catch (RepoError& error)
	{
		socket.send_string_byte("Server error!");
	}

}
void Service::users()
{
	vector<User> users = userRepo.findAll();
	socket.send_int_byte(users.size());
	for (int i = 0; i < users.size(); i++)
	{
		socket.send_int_byte(users.at(i).getId());
		socket.send_string_byte(users.at(i).toString());
	}
}
void Service::addMessage()
{
	int from = socket.recv_int_byte();
	int to = socket.recv_int_byte();
	string text = socket.recv_string_byte();
	int reply = socket.recv_int_byte();
	Message message(0, from, to, text, time(0),reply);
	try 
	{
		messageRepo.add(message);
		socket.send_string_byte("OK");
		conversation();
	}
	catch(RepoError& error)
	{
		socket.send_string_byte(error.what());
	}

}
void Service::conversation()
{
	int user1 = socket.recv_int_byte();
	int user2 = socket.recv_int_byte();
	vector<Message> conversation = messageRepo.findConversation(user1, user2);
	sort(conversation.begin(), conversation.end(), []( Message& m1,  Message& m2) 
		{return m1.getDate() < m2.getDate(); });
	socket.send_int_byte(conversation.size());
	for (int i = 0; i < conversation.size(); i++)
	{
		socket.send_int_byte(conversation.at(i).getId());	      //id
		socket.send_int_byte(conversation.at(i).getFrom());	      //from
		socket.send_int_byte(conversation.at(i).getTo());	      //to
		socket.send_string_byte(conversation.at(i).getText());    //text
		int reply = conversation.at(i).getReply();
		socket.send_int_byte(reply);							 //reply
		if (reply != -1)
		{
			Message message = messageRepo.findOne(reply);
			socket.send_int_byte(message.getFrom());	     
			socket.send_int_byte(message.getTo());
			socket.send_string_byte(message.getText());
		}
	}
}
