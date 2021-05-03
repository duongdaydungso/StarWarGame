
#include "stdafx.h"
#include "BaseObject.h"

// Set Object 

BaseObject::BaseObject() 
{
	oTexture = NULL ;

	oRect.x = 0 ;
	oRect.y = 0 ;
	oRect.w = 0 ;
	oRect.h = 0 ;

	center_x = 0 ;
	center_y = 0 ;

	width_frame = 0 ;
	height_frame = 0 ;

	for( int i = 0 ; i < MAX_OBJECT_FRAME ; i ++ ) 
	{
		frame_clip[i].x = 0 ;
		frame_clip[i].y = 0 ;
		frame_clip[i].w = 0 ;
		frame_clip[i].h = 0 ;
	}

	radius = 0 ;

	max_health = 0 ;
	curr_health = 0 ;

	real_pos_x = 0 ;
	real_pos_y = 0 ;
}

BaseObject::~BaseObject() 
{
	free() ;
}

// Erase existing texture

void BaseObject::free() 
{
	if( oTexture != NULL )
    {
		SDL_DestroyTexture( oTexture ) ;

        oTexture = NULL ;

		oRect.x = 0 ;
		oRect.y = 0 ;
		oRect.w = 0 ;
		oRect.h = 0 ;

		center_x = 0 ;
		center_y = 0 ;

		width_frame = 0 ;
		height_frame = 0 ;

		for( int i = 0 ; i < MAX_OBJECT_FRAME ; i ++ ) 
		{
			frame_clip[i].x = 0 ;
			frame_clip[i].y = 0 ;
			frame_clip[i].w = 0 ;
			frame_clip[i].h = 0 ;
		}

		radius = 0 ;

		max_health = 0 ;
		curr_health = 0 ;

		real_pos_x = 0 ;
		real_pos_y = 0 ;
    }
}


// Setup Rect

void BaseObject::setRect( const int& x , const int& y ) 
{
	oRect.x = x ;
	oRect.y = y ;
}

SDL_Rect BaseObject::getRect() const
{
	return oRect ;
}

SDL_Texture* BaseObject::getObject() const 
{
	return oTexture ;
}

// Get Frame Size
int BaseObject::getFrameWidth() 
{
	return width_frame ;
}

int BaseObject::getFrameHeight() 
{
	return height_frame ;
}

// Get Center Of Object
double BaseObject::getCenterX() 
{
	return center_x ;
}

double BaseObject::getCenterY() 
{
	return center_y ;
}

// Get Real Position
double BaseObject::getRealCenterX() 
{
	return real_pos_x + ( width_frame / 2 ) ;
}
double BaseObject::getRealCenterY() 
{
	return real_pos_y + ( height_frame / 2 ) ;
}

// Get Radius
double BaseObject::getRadius() 
{
	return radius ;
}


// Calculate Center Point
void BaseObject::calculateCenterPoint() 
{
	double temp_x = oRect.x ;
	double temp_y = oRect.y ;
	double temp_w = width_frame ;
	double temp_h = height_frame ;

	center_x = temp_x + ( temp_w / 2 ) ;
	center_y = temp_y + ( temp_h / 2 ) ;
}


// Load Image From Files

bool BaseObject::loadImage( std::string path , SDL_Renderer* screen ) 
{
	free() ;

	bool success = true ;

	SDL_Texture* new_texture = NULL ;

	SDL_Surface* load_surface = IMG_Load( path.c_str() ) ;

	if( load_surface == NULL ) 
	{
		success = false ;

		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() ) ; 
	}
	else 
	{
		SDL_SetColorKey( load_surface , SDL_TRUE , SDL_MapRGB( load_surface->format , COLOR_KEY_R , COLOR_KEY_G , COLOR_KEY_B ) ) ;

		new_texture = SDL_CreateTextureFromSurface( screen , load_surface ) ;

		if( new_texture == NULL )
		{
			success = false ;

			printf( "Unable to create texture from %s! SDL Error: %s\n" , path.c_str() , SDL_GetError() ) ;
		}
		else
		{
			oRect.w = load_surface->w ;
			oRect.h = load_surface->h ;

			width_frame = oRect.w ;
			height_frame = oRect.h ;
		}

		SDL_FreeSurface( load_surface ) ;
	}

	oTexture = new_texture ;

	return success ;
}

// Set Size of each Object Sprites with LONG SPRITES
void BaseObject::setClipSize( int num_of_frame ) 
{
	width_frame = oRect.w / num_of_frame ;
	height_frame = oRect.h ;

	for( int i = 0 ; i < num_of_frame ; i ++ ) 
	{
		frame_clip[i].x = i * width_frame ;
		frame_clip[i].y = 0 ;
		frame_clip[i].w = width_frame ;
		frame_clip[i].h = height_frame ;
	}
}

// Get Clip Size
SDL_Rect BaseObject::getClipSize( const int& frame_num ) const 
{
	return frame_clip[frame_num] ;
}


// Alpha Blend Mode

void BaseObject::setBlendMode( SDL_BlendMode blending ) 
{
	SDL_SetTextureBlendMode( oTexture , blending ) ;
}

void BaseObject::setAlpha( Uint8 alpha ) 
{
	SDL_SetTextureAlphaMod( oTexture , alpha ) ;
}


// Render 

void BaseObject::render( SDL_Renderer* des , const SDL_Rect* clip ) 
{
	SDL_Rect renderQuad = { oRect.x , oRect.y , width_frame , height_frame } ;

	SDL_RenderCopy( des , oTexture , clip , &renderQuad ) ;
}
	
void BaseObject::renderFlip( SDL_Renderer* des , const SDL_Rect* clip , double angle , SDL_Point* center , SDL_RendererFlip flip ) 
{
	SDL_Rect renderQuad = { oRect.x , oRect.y , width_frame , height_frame } ;

	if( clip != NULL )
    {
        renderQuad.w = clip->w ;
        renderQuad.h = clip->h ;
    }

	SDL_RenderCopyEx( des , oTexture , clip , &renderQuad , angle , center , flip ) ;
}

// Set Up Health Point And Position For Checking Collision  
void BaseObject::setUpHPAndPos( const int& temp_max_health , const int& temp_curr_health ) 
{
	calculateCenterPoint() ;

	double temp_diameter = height_frame ;

	radius = temp_diameter / 2 ;

	max_health = temp_max_health ;
	curr_health = temp_curr_health ;
}

// Get Health Point
int BaseObject::getMaxHealth() 
{
	return max_health ;
}

int BaseObject::getCurrHealth() 
{
	return curr_health ;
}


// Change Current Health
void BaseObject::changeHealth( const int& temp_health ) 
{
	curr_health += temp_health ;

	if( curr_health > max_health ) curr_health = max_health ;
}
