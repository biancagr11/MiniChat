#pragma once
#include<string>
#include<qwidget.h>
#include<qlabel.h>
#include<qpushbutton.h>
#include<qboxlayout.h>
#include<qlineedit.h>
#include<qmessagebox.h>
#include <QCloseEvent>
#include"MySocket.h"
#include"ChatWindow.h"
using namespace std;

class LoginWindow:public QWidget
{
private:

	MySocket socket;

	QPushButton* signIn = new QPushButton{ "Sign in" };
	QLabel* usernameLabel = new QLabel;
	QLabel* passwordLabel = new QLabel;
	QLabel* imageLabel = new QLabel();
	QLineEdit* usernameField = new QLineEdit;
	QLineEdit* passwordField = new QLineEdit;

	void initGUI();
	void connect();

public:
	LoginWindow(int socketDsc)
	{
		socket = MySocket(socketDsc);
		initGUI();
		connect();
	}
	void closeEvent(QCloseEvent* bar) override;
};

