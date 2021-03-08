#pragma once
#include<string>
#include<qwidget.h>
#include<qlabel.h>
#include<qpushbutton.h>
#include<qboxlayout.h>
#include<qlineedit.h>
#include<qmessagebox.h>
#include <QCloseEvent>
#include<qlistwidget.h>
#include"MySocket.h"
class ChatWindow:public QWidget
{
private:

	MySocket& socket;
	int userFrom;
	int userTo = 0;
	string nameTo = "";

	QPushButton* send = new QPushButton{ "Send" };
	QLabel* userLabel = new QLabel;
	QLineEdit* textField = new QLineEdit;
	QListWidget* usersList = new QListWidget();
	QListWidget* messagesList = new QListWidget();
	

public:
	ChatWindow(int userId, MySocket& socket): userFrom{userId}, socket{socket}
	{
		initGUI();
		connect();
		loadUsers();
	}
	void initGUI();
	void connect();
	void loadMessages();
	void loadUsers();
};

