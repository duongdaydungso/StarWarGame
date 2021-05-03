
#include "stdafx.h"
#include "ExplodeObject.h"

// EXPLODE OBJECT ************************************************************************************

ExplodeObject::ExplodeObject() 
{
	curr_frame = 0 ;
	max_frame = 0 ;

	is_display = true ;
}

ExplodeObject::~ExplodeObject()
{

}

// Get Status
bool ExplodeObject::getStatus() const 
{
	return is_display ;
}

// Set Max Frame For Explode
void ExplodeObject::setMaxFrame( const int& temp_max_frame ) 
{
	max_frame = temp_max_frame ;
}

// Show Explode
void ExplodeObject::show( SDL_Renderer* des , const int& temp_x , const int& temp_y ) 
{
	SDL_Rect* current_clip = &frame_clip[curr_frame] ;

	SDL_Rect renderQuad = { oRect.x - temp_x , oRect.y - temp_y , width_frame , height_frame } ;

	SDL_RenderCopy( des , oTexture , current_clip , &renderQuad ) ;

	curr_frame ++ ;

	if( curr_frame > max_frame )
	{
		is_display = false ;
		return ;
	}
}

// Load Explosion Sound
void ExplodeObject::loadSound( std::string path ) 
{
	if( explosion_sound.loadSound( path , EXPLOSION_VOLUME ) == false ) printf( "Can't load Explosion Sound " ) ;
}

// Play Explosion Sound 
void ExplodeObject::playSound() 
{
	explosion_sound.playSound() ;
}

// Get Explosion Sound Status ( is Played ) 
bool ExplodeObject::getSoundStatus() const 
{
	return explosion_sound.isPlayed() ;
}
