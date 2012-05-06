#ifndef SERVERMAINTENANCETOOL_H
#define SERVERMAINTENANCETOOL_H

#include <QtGui/QMainWindow>
#include "ui_servermaintenancetool.h"

class RemoteConnectionHandler;

class ServerMaintenanceTool : public QMainWindow
{
	Q_OBJECT

public:
	ServerMaintenanceTool(RemoteConnectionHandler &rch, QWidget *parent = 0, Qt::WFlags flags = 0);
	~ServerMaintenanceTool();

	void SetServerStatus(const std::string &status);
	void AppendOutput(const std::string &text);

	void SetWorldsList(const std::vector<std::string> & wlist);

public slots:

	void WorldNameModified(int index);
	void update_clicked();
	void start_clicked();
	void stop_clicked();

private:
	Ui::ServerMaintenanceToolClass ui;
	std::string _status;
	RemoteConnectionHandler &_rch;
};

#endif // SERVERMAINTENANCETOOL_H
