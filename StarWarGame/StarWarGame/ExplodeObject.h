
#ifndef EXPLODE_OBJECT_H_
#define EXPLODE_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "SoundObject.h"

// EXPLODE OBJECT ************************************************************************************

class ExplodeObject : public BaseObject 
{
public:
	ExplodeObject() ;
	~ExplodeObject() ;

	// Get Status
	bool getStatus() const ;

	// Set Max Frame For Explode
	void setMaxFrame( const int& temp_max_frame ) ;

	// Show Explode
	void show( SDL_Renderer* des , const int& temp_x , const int& temp_y ) ;

	// Load Explosion Sound
	void loadSound( std::string path ) ;

	// Play Explosion Sound 
	void playSound() ;

	// Get Explosion Sound Status ( is Played ) 
	bool getSoundStatus() const ;

private: 
	int curr_frame ;
	int max_frame ;

	bool is_display ;

	// Explosion Sound
	ShortSoundObject explosion_sound ;
} ;


#endif