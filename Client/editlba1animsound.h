#ifndef EDITLBA1ANIMSOUND_H
#define EDITLBA1ANIMSOUND_H

#include <QtGui/QMainWindow>
#include "ui_editlba1animsound.h"
#include "editorhandlerBase.h"
#include "Lba1ModelMapHandler.h"
#include "ClientExtendedTypes.h"

class EditLBA1AnimSound : public QMainWindow, public EditorHandlerBase, public AnimationObserverBase
{
	Q_OBJECT

public:
	EditLBA1AnimSound(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~EditLBA1AnimSound();

	//! set the osg window
	virtual void SetOsgWindow(QWidget *osgwindow);

	//! refresh display
	virtual void RefreshDisplay();

	//! refresh gui with map info
	virtual void SetMapInfo(const std::string & mapname){}

	//! inform that map Finished Loaded;
	virtual void MapFinishedLoaded(){}

	//! player moved
	virtual void PlayerMoved(float posx, float posy, float posz){}

	// called when an object is picked
	virtual void PickedObject(const std::string & name, float px, float py, float pz){}

	//! when an editor arrow was dragged by mouse
	virtual void PickedArrowMoved(int pickedarrow){}

	//! update the number of keyframe in the anim
	virtual void UpdateNumberKeyframe(int nb);

	//! update the current keyframe
	virtual void UpdateCurrentKeyframe(int keyframe);

public slots:
	 //! quit editor
     void quit();

     void ModelChanged(int v);	
     void AnimationChanged(int v);
     void PlayAnim();
     void PauseAnim();
	 void keyframeChanged(int v);

	 void ShowDirectoryPicker();
	 void PlaySound();

	 void keyframeChanged(const QString & text);
	 void keyframeChangedc(int v);

protected:
	//! override close event
	virtual void closeEvent(QCloseEvent* event);

	//!RefreshAnimlist
	void RefreshAnimlist();

	//! refresh Keyframe info
	void RefreshKeyframeInfo(bool reset);

private:
	Ui::EditLBA1AnimSoundClass ui;

	std::map<std::string, ModelData>&				_data;
	std::vector<std::vector<std::string> >			_models;
};

#endif // EDITLBA1ANIMSOUND_H
