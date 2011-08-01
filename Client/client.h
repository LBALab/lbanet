#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui/QWidget>
#include "ui_client.h"

class Client : public QWidget
{
	Q_OBJECT

public:
	Client(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Client();

private:
	Ui::ClientClass ui;
};

#endif // CLIENT_H
