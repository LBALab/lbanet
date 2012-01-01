#include "editlba1animsound.h"
#include "EventsQueue.h"
#include "ClientExtendedEvents.h"

#include "SynchronizedTimeHandler.h"
#include "MusicHandler.h"

#include <QFileDialog>

/***********************************************************
	Constructor
***********************************************************/
EditLBA1AnimSound::EditLBA1AnimSound(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), _data(Lba1ModelMapHandler::getInstance()->GetData())
{
	ui.setupUi(this);

	// show myself
	showMaximized();


	{
		std::map<std::string, ModelData>::iterator itm = _data.begin();
		std::map<std::string, ModelData>::iterator endm = _data.end();
		for(; itm != endm; ++itm)
		{
			ModelData &md = itm->second;

			std::map<std::string, OutfitData>::iterator itm2 = md.outfits.begin();
			std::map<std::string, OutfitData>::iterator endm2 =  md.outfits.end();
			for(; itm2 != endm2; ++itm2)
			{
				OutfitData &od = itm2->second;

				std::map<std::string, WeaponData>::iterator itm3 = od.weapons.begin();
				std::map<std::string, WeaponData>::iterator endm3 =  od.weapons.end();
				for(; itm3 != endm3; ++itm3)
				{
					WeaponData &wd = itm3->second;

					std::map<std::string, ModeData>::iterator itm4 = wd.modes.begin();
					std::map<std::string, ModeData>::iterator endm4 =  wd.modes.end();
					for(; itm4 != endm4; ++itm4)
					{
						std::vector<std::string> vec;
						vec.push_back(itm->first);
						vec.push_back(itm2->first);
						vec.push_back(itm3->first);
						vec.push_back(itm4->first);
						_models.push_back(vec);
					}
				}
			}
		}
	}

	for(size_t i=0; i<_models.size(); ++i)
	{
		std::string str;
		str+= _models[i][0]+ "-" + _models[i][1];
		if(_models[i][2] != "No")
			str+= "-" + _models[i][2];
		if(_models[i][3] != "Normal")
			str+= "-" + _models[i][3];

		ui.comboBox_model->addItem(str.c_str());
	}


	connect(ui.comboBox_model, SIGNAL(activated(int)) , this, SLOT(ModelChanged(int)));
	connect(ui.comboBox_anim, SIGNAL(activated(int)) , this, SLOT(AnimationChanged(int)));

	connect(ui.pushButton_play, SIGNAL(clicked()) , this, SLOT(PlayAnim()));
	connect(ui.pushButton_stop, SIGNAL(clicked()) , this, SLOT(PauseAnim()));

	connect(ui.spinBox_keyframe, SIGNAL(valueChanged(int)) , this, SLOT(keyframeChanged(int)));
	connect(ui.Slider_keyframe, SIGNAL(valueChanged(int)) , this, SLOT(keyframeChanged(int)));

	connect(ui.pushButton_directory, SIGNAL(clicked()) , this, SLOT(ShowDirectoryPicker()));
	connect(ui.pushButton_playsound, SIGNAL(clicked()) , this, SLOT(PlaySound()));


	connect(ui.lineEdit_soundpath, SIGNAL(textChanged(const QString &)) , this, SLOT(keyframeChanged(const QString &)));
	connect(ui.checkBox_starthit, SIGNAL(stateChanged(int)) , this, SLOT(keyframeChangedc(int)));
	connect(ui.checkBox_endhit, SIGNAL(stateChanged(int)) , this, SLOT(keyframeChangedc(int)));
	connect(ui.checkBox_startprojectile, SIGNAL(stateChanged(int)) , this, SLOT(keyframeChangedc(int)));
}


/***********************************************************
	Destructor
***********************************************************/
EditLBA1AnimSound::~EditLBA1AnimSound()
{

}


/***********************************************************
set the osg window
***********************************************************/
void EditLBA1AnimSound::SetOsgWindow(QWidget *osgwindow)
{
	ui.groupBox_gl->layout()->addWidget(osgwindow);
	osgwindow->show();

	{
    LbaNet::ModelInfo DisplayDesc;
	DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
	DisplayDesc.ColorMaterialType = 4;
	DisplayDesc.ModelId = 0;
	DisplayDesc.ModelName = "Ameba";
	DisplayDesc.Outfit = "No";
	DisplayDesc.Weapon = "No";
	DisplayDesc.Mode = "Normal";
	DisplayDesc.UseLight = true;
	DisplayDesc.CastShadow = true;
	DisplayDesc.ColorR = 1;
	DisplayDesc.ColorG = 1;
	DisplayDesc.ColorB = 1;
	DisplayDesc.ColorA = 1;
	DisplayDesc.TransX = 0;
	DisplayDesc.TransY = 0;
	DisplayDesc.TransZ = 0;
	DisplayDesc.ScaleX = 3;
	DisplayDesc.ScaleY = 3;
	DisplayDesc.ScaleZ = 3;
	DisplayDesc.RotX = 0;
	DisplayDesc.RotY = 0;
	DisplayDesc.RotZ = 0;
	DisplayDesc.UseTransparentMaterial = false;

	DisplayDesc.ColorMaterialType = 4;
	DisplayDesc.MatAmbientColorR = -0.2f;
	DisplayDesc.MatAmbientColorG = -0.2f;
	DisplayDesc.MatAmbientColorB = -0.2f;
	DisplayDesc.MatDiffuseColorR = 0.4f;
	DisplayDesc.MatDiffuseColorG = 0.4f;
	DisplayDesc.MatDiffuseColorB = 0.4f;
	DisplayDesc.MatAlpha = 1;
	DisplayDesc.MatAmbientColorA = 1;
	DisplayDesc.MatDiffuseColorA = 1;
	DisplayDesc.MatSpecularColorR = 0;
	DisplayDesc.MatSpecularColorG = 0;
	DisplayDesc.MatSpecularColorB = 0;
	DisplayDesc.MatSpecularColorA = 1;
	DisplayDesc.MatEmissionColorR = 0;
	DisplayDesc.MatEmissionColorG = 0;
	DisplayDesc.MatEmissionColorB = 0;
	DisplayDesc.MatEmissionColorA = 1;
	DisplayDesc.MatShininess = 0;




    LbaNet::ObjectPhysicDesc PhysicDesc;
	PhysicDesc.TypePhysO = LbaNet::StaticAType;
	PhysicDesc.TypeShape = LbaNet::BoxShape;
	PhysicDesc.Pos.X = 10;
	PhysicDesc.Pos.Y = 0;
	PhysicDesc.Pos.Z = 10;
	PhysicDesc.Pos.Rotation = 0;
	PhysicDesc.Density = 1;
	PhysicDesc.Collidable = true;
	PhysicDesc.SizeX = 1;
	PhysicDesc.SizeY = 1;
	PhysicDesc.SizeZ = 1;
	PhysicDesc.Filename = "";


    LbaNet::LifeManaInfo LifeInfo;
	LifeInfo.Display = false;

    LbaNet::ObjectExtraInfo ExtraInfo;
	ExtraInfo.Display = false;

	EventsQueue::getReceiverQueue()->AddEvent(
					new LbaNet::AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					1, 1, -1, DisplayDesc, PhysicDesc, LifeInfo, ExtraInfo));

	EventsQueue::getReceiverQueue()->AddEvent(
					new LbaNet::UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					1, 1, new RegisterAnimationObserver(this)));
	}

	RefreshAnimlist();

}

/***********************************************************
refresh display
***********************************************************/
void EditLBA1AnimSound::RefreshDisplay()
{
	ui.groupBox_gl->setMinimumWidth(800);
	ui.groupBox_gl->setMinimumHeight(600);
}

/***********************************************************
quit editor
***********************************************************/
void EditLBA1AnimSound::quit()
{
	EventsQueue::getReceiverQueue()->AddEvent(new QuitGameEvent());
}

/***********************************************************
override close event
***********************************************************/
void EditLBA1AnimSound::closeEvent(QCloseEvent* event)
{
	quit();
}

/***********************************************************
RefreshAnimlist
***********************************************************/
void EditLBA1AnimSound::RefreshAnimlist()
{
	int idx = ui.comboBox_model->currentIndex();
	std::vector<std::string> & vec = _models[idx];

	std::vector<std::string> animations;
	Lba1ModelMapHandler::getInstance()->GetModelAvailableAnims(vec[0], vec[1], vec[2], vec[3], animations);

	ui.comboBox_anim->clear();
	for(size_t i=0; i< animations.size(); ++i)
		ui.comboBox_anim->addItem(animations[i].c_str());

	AnimationChanged(0);
}


/***********************************************************
ModelChanged
***********************************************************/
void EditLBA1AnimSound::ModelChanged(int v)
{
	int idx = ui.comboBox_model->currentIndex();

    LbaNet::ModelInfo DisplayDesc;
	DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
	DisplayDesc.ColorMaterialType = 4;
	DisplayDesc.ModelId = 0;
	DisplayDesc.ModelName = _models[idx][0];
	DisplayDesc.Outfit = _models[idx][1];
	DisplayDesc.Weapon = _models[idx][2];
	DisplayDesc.Mode = _models[idx][3];
	DisplayDesc.UseLight = true;
	DisplayDesc.CastShadow = true;
	DisplayDesc.ColorR = 1;
	DisplayDesc.ColorG = 1;
	DisplayDesc.ColorB = 1;
	DisplayDesc.ColorA = 1;
	DisplayDesc.TransX = 0;
	DisplayDesc.TransY = 0;
	DisplayDesc.TransZ = 0;
	DisplayDesc.ScaleX = 3;
	DisplayDesc.ScaleY = 3;
	DisplayDesc.ScaleZ = 3;
	DisplayDesc.RotX = 0;
	DisplayDesc.RotY = 0;
	DisplayDesc.RotZ = 0;
	DisplayDesc.UseTransparentMaterial = false;

	DisplayDesc.ColorMaterialType = 4;
	DisplayDesc.MatAmbientColorR = -0.2f;
	DisplayDesc.MatAmbientColorG = -0.2f;
	DisplayDesc.MatAmbientColorB = -0.2f;
	DisplayDesc.MatDiffuseColorR = 0.4f;
	DisplayDesc.MatDiffuseColorG = 0.4f;
	DisplayDesc.MatDiffuseColorB = 0.4f;
	DisplayDesc.MatAlpha = 1;
	DisplayDesc.MatAmbientColorA = 1;
	DisplayDesc.MatDiffuseColorA = 1;
	DisplayDesc.MatSpecularColorR = 0;
	DisplayDesc.MatSpecularColorG = 0;
	DisplayDesc.MatSpecularColorB = 0;
	DisplayDesc.MatSpecularColorA = 1;
	DisplayDesc.MatEmissionColorR = 0;
	DisplayDesc.MatEmissionColorG = 0;
	DisplayDesc.MatEmissionColorB = 0;
	DisplayDesc.MatEmissionColorA = 1;
	DisplayDesc.MatShininess = 0;


	EventsQueue::getReceiverQueue()->AddEvent(
					new LbaNet::UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					1, 1, new LbaNet::ModelUpdate(DisplayDesc, false)));

	RefreshAnimlist();
}

/***********************************************************
AnimationChanged
***********************************************************/
void EditLBA1AnimSound::AnimationChanged(int v)
{
	EventsQueue::getReceiverQueue()->AddEvent(
					new LbaNet::UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					1, 1, new LbaNet::AnimationStringUpdate(ui.comboBox_anim->currentText().toAscii().data())));
}

/***********************************************************
AnimationChanged
***********************************************************/
void EditLBA1AnimSound::PlayAnim()
{
	EventsQueue::getReceiverQueue()->AddEvent(
					new LbaNet::UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					1, 1, new LbaNet::PauseAnimationUpdate(false)));

	RefreshKeyframeInfo(true);
}

/***********************************************************
AnimationChanged
***********************************************************/
void EditLBA1AnimSound::PauseAnim()
{
	EventsQueue::getReceiverQueue()->AddEvent(
					new LbaNet::UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					1, 1, new LbaNet::PauseAnimationUpdate(true)));

	RefreshKeyframeInfo(false);
}


/***********************************************************
update the number of keyframe in the anim
***********************************************************/
void EditLBA1AnimSound::UpdateNumberKeyframe(int nb)
{
	ui.spinBox_keyframe->setRange(-1, nb);
	ui.Slider_keyframe->setRange(-1, nb);
	ui.Slider_keyframe->setMaximum(nb);
}

/***********************************************************
update the current keyframe
***********************************************************/
void EditLBA1AnimSound::UpdateCurrentKeyframe(int keyframe)
{
	disconnect(ui.spinBox_keyframe, SIGNAL(valueChanged(int)) , this, SLOT(keyframeChanged(int)));
	disconnect(ui.Slider_keyframe, SIGNAL(valueChanged(int)) , this, SLOT(keyframeChanged(int)));

	ui.spinBox_keyframe->setValue(keyframe);
	ui.Slider_keyframe->setValue(keyframe);

	connect(ui.spinBox_keyframe, SIGNAL(valueChanged(int)) , this, SLOT(keyframeChanged(int)));
	connect(ui.Slider_keyframe, SIGNAL(valueChanged(int)) , this, SLOT(keyframeChanged(int)));
}

/***********************************************************
update the current keyframe
***********************************************************/
void EditLBA1AnimSound::keyframeChanged(int v)
{
	disconnect(ui.spinBox_keyframe, SIGNAL(valueChanged(int)) , this, SLOT(keyframeChanged(int)));
	disconnect(ui.Slider_keyframe, SIGNAL(valueChanged(int)) , this, SLOT(keyframeChanged(int)));

	ui.spinBox_keyframe->setValue(v);
	ui.Slider_keyframe->setValue(v);

	connect(ui.spinBox_keyframe, SIGNAL(valueChanged(int)) , this, SLOT(keyframeChanged(int)));
	connect(ui.Slider_keyframe, SIGNAL(valueChanged(int)) , this, SLOT(keyframeChanged(int)));


	if(v >= 0)
		EventsQueue::getReceiverQueue()->AddEvent(
						new LbaNet::UpdateDisplayObjectEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(),
						1, 1, new SetAnimationKeyframe(v)));

	RefreshKeyframeInfo(false);
}


/***********************************************************
ShowDirectoryPicker
***********************************************************/
void EditLBA1AnimSound::ShowDirectoryPicker()
{
	QString currfile = ui.lineEdit_soundpath->text();
	if(currfile != "")
		currfile = "Data/" + currfile;
	else
		currfile = "Data/Worlds/Lba1Original/Sound/SAMPLES001.wav";

	QStringList selectedfile =
		QFileDialog::getOpenFileNames (this, "Select a sound file", currfile,
										"Sound (*.mp3 *.wav *.Ogg)");

	if(selectedfile.size() > 0)
	{
		QString selected = 	selectedfile[0];
		selected.replace("\\", "/");

		// check if choosen file is in the directory data
		if(selected.contains(QDir::currentPath()+"/Data/"))
			selected = selected.remove(QDir::currentPath()+"/Data/");
		ui.lineEdit_soundpath->setText(selected);
	}
}

/***********************************************************
PlaySound
***********************************************************/
void EditLBA1AnimSound::PlaySound()
{
	std::string sound = ui.lineEdit_soundpath->text().toAscii().data();
	if(sound != "")
	{
		if(sound == "#ground1")
			sound = "Worlds/Lba1Original/Sound/SAMPLES128.wav";
		if(sound == "#ground2")
			sound = "Worlds/Lba1Original/Sound/SAMPLES143.wav";

		MusicHandler::getInstance()->PlaySample2D("Data/"+sound, false, true);
	}
}


/***********************************************************
keyframeChanged
***********************************************************/
void EditLBA1AnimSound::keyframeChangedc(int v)
{
	int idx = ui.comboBox_model->currentIndex();
	int kf = ui.spinBox_keyframe->value();
	std::string anim = ui.comboBox_anim->currentText().toAscii().data();

	AnimationFrameData afd;
	afd.starthit = ui.checkBox_starthit->isChecked();
	afd.endthit = ui.checkBox_endhit->isChecked();
	afd.startprojectile = ui.checkBox_startprojectile->isChecked();
	afd.soundpath = ui.lineEdit_soundpath->text().toAscii().data();

	if(afd.starthit || afd.endthit || afd.startprojectile || afd.soundpath != "")
	{
		if(kf < 0)
			_data[_models[idx][0]].outfits[_models[idx][1]].
			weapons[_models[idx][2]].modes[_models[idx][3]].
			animationsD[anim].repeatedsoundpath = afd.soundpath;
		else
			_data[_models[idx][0]].outfits[_models[idx][1]].
			weapons[_models[idx][2]].modes[_models[idx][3]].
			animationsD[anim].animationframes[kf] = afd;
	}
	else
	{
		if(kf < 0)
			_data[_models[idx][0]].outfits[_models[idx][1]].
			weapons[_models[idx][2]].modes[_models[idx][3]].
			animationsD[anim].repeatedsoundpath = afd.soundpath;
		else
		{
			std::map<int, AnimationFrameData > & map =
				_data[_models[idx][0]].outfits[_models[idx][1]].
				weapons[_models[idx][2]].modes[_models[idx][3]].
				animationsD[anim].animationframes;

			std::map<int, AnimationFrameData >::iterator itm = map.find(kf);
			if(itm != map.end())
				map.erase(itm);
		}
	}

	Lba1ModelMapHandler::getInstance()->SaveAnimationData();

	EventsQueue::getReceiverQueue()->AddEvent(
					new LbaNet::UpdateDisplayObjectEvent(
					SynchronizedTimeHandler::GetCurrentTimeDouble(),
					1, 1, new UpdateAnimationKeyframeInfo(kf, new AnimationFrameData(afd))));
}

/***********************************************************
keyframeChanged
***********************************************************/
void EditLBA1AnimSound::keyframeChanged(const QString & text)
{
	keyframeChangedc(0);
}




/***********************************************************
refresh Keyframe info
***********************************************************/
void EditLBA1AnimSound::RefreshKeyframeInfo(bool reset)
{
	disconnect(ui.lineEdit_soundpath, SIGNAL(textChanged(const QString &)) , this, SLOT(keyframeChanged(const QString &)));
	disconnect(ui.checkBox_starthit, SIGNAL(stateChanged(int)) , this, SLOT(keyframeChangedc(int)));
	disconnect(ui.checkBox_endhit, SIGNAL(stateChanged(int)) , this, SLOT(keyframeChangedc(int)));
	disconnect(ui.checkBox_startprojectile, SIGNAL(stateChanged(int)) , this, SLOT(keyframeChangedc(int)));

	if(reset)
	{
		ui.lineEdit_soundpath->setText("");
		ui.checkBox_starthit->setChecked(false);
		ui.checkBox_endhit->setChecked(false);
		ui.checkBox_startprojectile->setChecked(false);
	}
	else
	{
		int idx = ui.comboBox_model->currentIndex();
		int kf = ui.spinBox_keyframe->value();
		std::string anim = ui.comboBox_anim->currentText().toAscii().data();

		if(kf < 0)
		{
			std::string soundr = _data[_models[idx][0]].outfits[_models[idx][1]].
								weapons[_models[idx][2]].modes[_models[idx][3]].
								animationsD[anim].repeatedsoundpath;

			ui.lineEdit_soundpath->setText(soundr.c_str());
			ui.checkBox_starthit->setChecked(false);
			ui.checkBox_endhit->setChecked(false);
			ui.checkBox_startprojectile->setChecked(false);
		}
		else
		{
			AnimationFrameData &afd = _data[_models[idx][0]].outfits[_models[idx][1]].
			weapons[_models[idx][2]].modes[_models[idx][3]].
			animationsD[anim].animationframes[kf];

			ui.lineEdit_soundpath->setText(afd.soundpath.c_str());
			ui.checkBox_starthit->setChecked(afd.starthit);
			ui.checkBox_endhit->setChecked(afd.endthit);
			ui.checkBox_startprojectile->setChecked(afd.startprojectile);
		}

	}

	connect(ui.lineEdit_soundpath, SIGNAL(textChanged(const QString &)) , this, SLOT(keyframeChanged(const QString &)));
	connect(ui.checkBox_starthit, SIGNAL(stateChanged(int)) , this, SLOT(keyframeChangedc(int)));
	connect(ui.checkBox_endhit, SIGNAL(stateChanged(int)) , this, SLOT(keyframeChangedc(int)));
	connect(ui.checkBox_startprojectile, SIGNAL(stateChanged(int)) , this, SLOT(keyframeChangedc(int)));
}