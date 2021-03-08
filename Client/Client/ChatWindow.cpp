#include "ChatWindow.h"
void ChatWindow::initGUI()
{
	this->setWindowTitle("Chat");

	QPalette pal1 = palette();
	pal1.setColor(QPalette::Background, Qt::gray);
	this->setAutoFillBackground(true);
	this->setPalette(pal1);

	QHBoxLayout* mainLy = new QHBoxLayout;
	this->setLayout(mainLy);

	QVBoxLayout* left = new QVBoxLayout;
	QVBoxLayout* right = new QVBoxLayout;
	QHBoxLayout* messageLy = new QHBoxLayout;


	userLabel->setText("All users");

	left->addWidget(userLabel);
	left->addWidget(usersList);

	messageLy->addWidget(textField);
	messageLy->addWidget(send);

	right->addWidget(messagesList);
	right->addLayout(messageLy);

	mainLy->addLayout(left);
	mainLy->addLayout(right);
	


}
void ChatWindow::connect()
{
	QObject::connect(usersList->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		
		messagesList->clear();
		auto selectedIndexes = usersList->selectionModel()->selectedIndexes();
		if (!selectedIndexes.isEmpty())
		{
			userTo = selectedIndexes.at(0).data(Qt::UserRole).toInt();
			string currentString = usersList->currentItem()->text().toStdString();
			nameTo = currentString.substr(0, currentString.find(" "));
			socket.send_string_byte("conversation");
			loadMessages();	
		}

		});
		QObject::connect(send, &QPushButton::clicked, [&]()
		{
				string text =textField->text().toStdString();
				if (text != "")
				{
					socket.send_string_byte("addMessage");
					int reply=-1;
					auto selectedIndexes = messagesList->selectionModel()->selectedIndexes();
					if(!selectedIndexes.isEmpty())
						reply= selectedIndexes.at(0).data(Qt::UserRole).toInt();
					socket.send_int_byte(userFrom);
					socket.send_int_byte(userTo);
					socket.send_string_byte(text);
					socket.send_int_byte(reply);
					string verification=socket.recv_string_byte();
					if (verification != "OK")
					{
						QMessageBox::warning(this, "!!!Eroare!!!", QString::fromStdString(verification));
					}
					else
					{
						textField->setText("");
						loadMessages();
					}
				}
		});
}
void ChatWindow::loadMessages()
{
	messagesList->clear();
	socket.send_int_byte(userFrom);
	socket.send_int_byte(userTo);
	int size = socket.recv_int_byte();
	for (int i = 0; i < size; i++)
	{
		int id = socket.recv_int_byte();
		int from = socket.recv_int_byte();
		int to = socket.recv_int_byte();
		string text = socket.recv_string_byte();
		int reply = socket.recv_int_byte();
		if (reply != -1)
		{
			int fromR = socket.recv_int_byte();
			int toR = socket.recv_int_byte();
			string textR = socket.recv_string_byte();
			QListWidgetItem* itemR = new QListWidgetItem;
			if(from==userFrom)
				itemR->setText(QString::fromStdString("   You replied to: " + textR));
			else
				itemR->setText(QString::fromStdString("   "+nameTo+" replied to: " + textR));
			itemR->setForeground(Qt::gray);
			messagesList->addItem(itemR);

		}
		QListWidgetItem* item = new QListWidgetItem;
		item->setData(Qt::UserRole,QVariant(id));
		if (from == userFrom)
			item->setText(QString::fromStdString("Me: " + text));
		else
			item->setText(QString::fromStdString(nameTo+": " + text));
		messagesList->addItem(item);
	}
}
void ChatWindow::loadUsers()
{
	int size = socket.recv_int_byte();
	for (int i = 0; i < size; i++)
	{
		int id = socket.recv_int_byte();
		string name = socket.recv_string_byte();
		if (id != userFrom)
		{
			QListWidgetItem* item = new QListWidgetItem;
			item->setData(Qt::UserRole,QVariant(id));
			item->setText(QString::fromStdString(name));
			usersList->addItem(item);
		}
	}
}