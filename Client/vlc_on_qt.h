/* libVLC and Qt sample code
 * Copyright © 2009 Alexander Maringer <maringer@maringer-it.de>
 * simplified version
 */
#ifndef VLC_ON_QT_H
#define VLC_ON_QT_H

#include <vlc/vlc.h>
#include <QWidget>

class VLCPlayer : public QWidget
{
    Q_OBJECT

    bool _isPlaying;
    libvlc_instance_t *_vlcinstance;
    libvlc_media_player_t *_mp;
    libvlc_media_t *_m;

public:
    VLCPlayer();
    ~VLCPlayer();

	// callback when video is finished
	void PlayFinished();

public slots:
    void playFile(QString file);
    void stop();

signals:
     void finished();

};
#endif
