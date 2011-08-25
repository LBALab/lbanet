/* libVLC and Qt sample code
 * Copyright © 2009 Alexander Maringer <maringer@maringer-it.de>
 * simplified version
 */
#include "vlc_on_qt.h"



static void callbackfinished(const struct libvlc_event_t * evt, void * userd)
{
	if(userd)
	{
		VLCPlayer* vlcP = static_cast<VLCPlayer *>(userd);
		if(vlcP)
			vlcP->PlayFinished();
	}
}



//constructor
VLCPlayer::VLCPlayer()
: QWidget()
{
    //preparation of the vlc command
    const char * const vlc_args[] = {
              "-I", "dummy", /* Don't use any interface */
              "--ignore-config", /* Don't use VLC's config */
			  "--no-video-title-show",
              "--plugin-path=.\\vlcplugins\\" };

    _isPlaying=false;

    //Initialize an instance of vlc
    //create a new libvlc instance
    _vlcinstance=libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);  //tricky calculation of the char space used
 
    // Create a media player playing environement 
    _mp = libvlc_media_player_new (_vlcinstance);

	libvlc_event_manager_t * evman = libvlc_media_player_event_manager(_mp);
	if(evman)
		libvlc_event_attach(evman, libvlc_MediaPlayerEndReached , callbackfinished, static_cast<void *>(this));
}


//destructor
VLCPlayer::~VLCPlayer()
{
    /* Stop playing */
    libvlc_media_player_stop (_mp);

    /* Free the media_player */
    libvlc_media_player_release (_mp);

    libvlc_release (_vlcinstance);
}

void VLCPlayer::playFile(QString file)
{
    /* Create a new LibVLC media descriptor */
    _m = libvlc_media_new_path (_vlcinstance, file.toAscii());
    
    /* Set media to player */
    libvlc_media_player_set_media (_mp, _m);
    
    /* Get our media instance to use our window */
    libvlc_media_player_set_hwnd(_mp, this->winId());

    /* Play */
    libvlc_media_player_play (_mp);

    /* Set volume */
    libvlc_audio_set_volume (_mp, 100);

    _isPlaying=true;
}

void VLCPlayer::stop()
{
	if(_isPlaying)
	{
		/* Stop playing */
		libvlc_media_player_stop (_mp);
		_isPlaying=false;
	}
}

// callback when video is finished
void VLCPlayer::PlayFinished()
{
   _isPlaying=false;
   emit finished();
}
