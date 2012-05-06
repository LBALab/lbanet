#include "servermaintenancetool.h"
#include "RemoteConnectionHandler.h"

ServerMaintenanceTool::ServerMaintenanceTool(RemoteConnectionHandler &rch, 
											 QWidget *parent, Qt::WFlags flags)
	: _rch(rch), QMainWindow(parent, flags)
{
	ui.setupUi(this);

	connect(ui.cb_WorldName, SIGNAL(activated(int)) , this, SLOT(WorldNameModified(int)));		
	connect(ui.b_Update, SIGNAL(clicked()) , this, SLOT(update_clicked()));
	connect(ui.b_Start, SIGNAL(clicked()) , this, SLOT(start_clicked()));
	connect(ui.b_Stop, SIGNAL(clicked()) , this, SLOT(stop_clicked()));
}

ServerMaintenanceTool::~ServerMaintenanceTool()
{

}


void ServerMaintenanceTool::SetServerStatus(const std::string &status)
{
	if(_status != status)
	{
		_status = status;
		ui.l_serverstatus->setText(status.c_str());
	}
}

void ServerMaintenanceTool::AppendOutput(const std::string &text)
{
	ui.plainTextEdit->appendPlainText(text.c_str());
}


void ServerMaintenanceTool::SetWorldsList(const std::vector<std::string> & wlist)
{
	ui.cb_WorldName->clear();

	for(size_t i=0; i<wlist.size(); ++i)
	{
		ui.cb_WorldName->addItem( wlist[i].c_str());
	}

	ui.cb_WorldName->setCurrentIndex(0);
	WorldNameModified(0);
}


void ServerMaintenanceTool::WorldNameModified(int index)
{
	_rch.setWorldName(ui.cb_WorldName->currentText().toAscii().data());
}

void ServerMaintenanceTool::update_clicked()
{
	std::string worldname = ui.cb_WorldName->currentText().toAscii().data();
	AppendOutput("Updating world " + worldname + "...");
	AppendOutput(_rch.UpdateWorld(worldname));
}

void ServerMaintenanceTool::start_clicked()
{
	std::string worldname = ui.cb_WorldName->currentText().toAscii().data();
	AppendOutput("Starting world " + worldname + "...");
	AppendOutput(_rch.StartWorld(worldname));
}

void ServerMaintenanceTool::stop_clicked()
{
	std::string worldname = ui.cb_WorldName->currentText().toAscii().data();
	AppendOutput("Stoping world " + worldname + "...");
	AppendOutput(_rch.StopWorld(worldname));
}
