
#ifndef SOUND_OBJECT_H_
#define SOUND_OBJECT_H_

#include "CommonFunction.h"

class ShortSoundObject
{
public:
	ShortSoundObject() ;
	~ShortSoundObject() ;

	// Free Sound
	void free() ;

	// Load Sound From File
	bool loadSound( std::string path , int vol ) ;

	// Play Sound
	void playSound() ;

	// Get Status
	bool isPlayed() const ;

private:
	Mix_Chunk *sound ;

	bool is_played ;
} ;

// MUSIC OBJECT************************************************************************************************

class MusicObject 
{
public:
	MusicObject() ;
	~MusicObject() ;

	// Free Music
	void free() ;

	// Load Music From File
	bool loadMusic( std::string path , int vol ) ;

	// Play Music
	void playMusic() ;

	// Pause and Resume Music
	void pauseMusic() ;
	void resumeMusic() ;

	bool isPlaying() const ;
	bool isPaused() const ;

	// Stop Music
	void stopMusic() ;

private:
	Mix_Music *music ;

	bool is_playing ;
	bool is_paused ;
} ;


#endif