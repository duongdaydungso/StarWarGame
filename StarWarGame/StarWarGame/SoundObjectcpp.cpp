
#include "stdafx.h"
#include "SoundObject.h"

ShortSoundObject::ShortSoundObject()
{
	sound = NULL ;

	is_played = false ;
}

ShortSoundObject::~ShortSoundObject()
{
	free() ;
}

// Free Sound
void ShortSoundObject::free() 
{
	Mix_FreeChunk( sound ) ;

	sound = NULL ;
}

// Load Sound From File
bool ShortSoundObject::loadSound( const std::string path , int vol ) 
{
	sound = Mix_LoadWAV( path.c_str() ) ;

	if( sound == NULL ) 
	{
		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n" , Mix_GetError() ) ;

		return false ;
	}

	Mix_VolumeChunk( sound , vol ) ;

	return true ;
}

// Play Sound
void ShortSoundObject::playSound() 
{
	Mix_PlayChannel( -1 , sound , 0 ) ;

	is_played = true ;
}

// Get Status
bool ShortSoundObject::isPlayed() const 
{
	return is_played ;
}



// MUSIC OBJECT************************************************************************************************

MusicObject::MusicObject()
{
	music = NULL ;

	is_playing = false ;
	is_paused = false ;
}

MusicObject::~MusicObject() 
{
	free() ;

	is_playing = false ;
	is_paused = false ;
}

// Free Music
void MusicObject::free() 
{
	Mix_FreeMusic( music ) ;

	music = NULL ;
}

// Load Music From File
bool MusicObject::loadMusic( std::string path , int vol ) 
{
	music = Mix_LoadMUS( path.c_str() ) ;

	if( music == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n" , Mix_GetError() ) ;
		
		return false ;
	}
	
	Mix_VolumeMusic( vol ) ;

	return true ;
}

// Play Music
void MusicObject::playMusic() 
{
	if( Mix_PlayingMusic() == 0 ) 
	{
		Mix_PlayMusic( music , -1 ) ;

		is_playing = true ;
		is_paused = false ;
	}
}

// Pause and Resume Music
void MusicObject::pauseMusic() 
{
	if( is_playing == false ) return ;

	if( Mix_PausedMusic() != 1 ) 
	{
		Mix_PauseMusic() ;

		is_paused = true ;
	}
}

void MusicObject::resumeMusic() 
{
	if( is_playing == false ) return ;

	if( Mix_PausedMusic() == 1 )
	{
		Mix_ResumeMusic() ;

		is_paused = false ;
	}
}

bool MusicObject::isPlaying() const 
{
	return is_playing ;
}

bool MusicObject::isPaused() const 
{
	return is_paused ;
}

// Stop Music
void MusicObject::stopMusic() 
{
	if( is_playing == true ) 
	{
		Mix_HaltMusic() ;

		is_playing = false ;
	}
}
