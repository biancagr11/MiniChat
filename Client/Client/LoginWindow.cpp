#include "LoginWindow.h"
#include <iostream>

void LoginWindow::initGUI()
{
	
	this->setWindowTitle("Login");
	passwordField->setEchoMode(QLineEdit::Password);
	imageLabel->setPixmap(QPixmap("	C:\\Users\\bianc\\source\\repos\\Client\\Client\\chat.png"));

	QPalette pal1 = palette();
	pal1.setColor(QPalette::Background, Qt::gray);
	this->setAutoFillBackground(true);
	this->setPalette(pal1);

	QVBoxLayout* mainLy = new QVBoxLayout;

	QVBoxLayout* left = new QVBoxLayout;
	QVBoxLayout* right = new QVBoxLayout;
	QHBoxLayout* combine = new QHBoxLayout;

	combine->addWidget(imageLabel);
	usernameLabel->setText("Username:");
	passwordLabel->setText("Password:");

	left->addWidget(usernameLabel);
	right->addWidget(usernameField);
	left->addWidget(passwordLabel);
	right->addWidget(passwordField);


	combine->addLayout(left);
	combine->addLayout(right);
	mainLy->addLayout(combine);
	mainLy->addWidget(signIn);

	setLayout(mainLy);

}

void LoginWindow::closeEvent(QCloseEvent* bar)
{
	socket.send_string_byte("exit");
	bar->accept();
}

void LoginWindow::connect()
{
	QObject::connect(signIn, &QPushButton::clicked, [&]() 
		{
		
		string username = usernameField->text().toStdString();
		string password = passwordField->text().toStdString();

		if(username=="" || password=="")
		{
			QMessageBox::warning(this, "!!!Eroare!!!", QString::fromStdString("Empty fields are not allowed!"));

		}
		else {
			socket.send_string_byte("login");
			socket.send_string_byte(username);
			socket.send_string_byte(password);
			string validation = socket.recv_string_byte();
			if (validation != "OK")
			{
				QMessageBox::warning(this, "!!!Eroare!!!", QString::fromStdString(validation));
			}
			else
			{
				int user = socket.recv_int_byte();
				ChatWindow* chatWindow=new ChatWindow( user,socket );
				chatWindow->show();	
			}
		}
		});
}

