
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunction.h" 

class BaseObject
{
public:

	// Setup Object
	BaseObject() ;
	~BaseObject() ;

	// Erase Existing Texture 
	void free() ;

	// Setup Rect
	void setRect( const int& x , const int& y ) ;
	SDL_Rect getRect() const ;
	SDL_Texture* getObject() const ;

	// Get Frame Size
	int getFrameWidth() ;
	int getFrameHeight() ;

	// Get Center Of Object
	double getCenterX() ;
	double getCenterY() ;

	// Get Real Position
	double getRealCenterX() ;
	double getRealCenterY() ;

	// Get Radius
	double getRadius() ;

	// Calculate Center Point Of Object
	void calculateCenterPoint() ;
	
	// Load Image From Files
	bool loadImage( std::string path , SDL_Renderer* screen ) ;

	// Set Size of each Object Sprites with LONG SPRITES
	void setClipSize( int num_of_frame ) ; 

	// Get Clip Size
	SDL_Rect getClipSize( const int& frame_num ) const ;

	// Alpha Blend Mode
	void setBlendMode( SDL_BlendMode blending ) ;
	void setAlpha( Uint8 alpha ) ;

	// Render 
	void render( SDL_Renderer* des , const SDL_Rect* clip = NULL ) ;
	void renderFlip( SDL_Renderer* des , const SDL_Rect* clip = NULL , double angle = 0.0 , SDL_Point* center = NULL , SDL_RendererFlip flip = SDL_FLIP_NONE ) ;

	// Set Up Health Point And Position For Checking Collision  
	void setUpHPAndPos( const int& temp_max_health , const int& temp_curr_health ) ;

	// Get Health Point
	int getMaxHealth() ;
	int getCurrHealth() ;

	// Change Current Health
	void changeHealth( const int& temp_health ) ;

protected:
	// Object Texture
	SDL_Texture* oTexture ;

	// Size Rect
	SDL_Rect oRect ;

	// Frame Size Of Object
	int width_frame ;
	int height_frame ;

	// Center Of Object
	double center_x ;
	double center_y ;

	// Object Frame Clip Storage 
	SDL_Rect frame_clip[MAX_OBJECT_FRAME] ;

	// For Checking Collision ( Radius )
	double radius ;

	// Health Point Handle
	int max_health ; // Also Using For Damge
	int curr_health ;

	// Real Position on Axis 
	double real_pos_x ;
	double real_pos_y ;
} ;

#endif 