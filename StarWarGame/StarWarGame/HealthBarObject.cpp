
#include "stdafx.h"
#include "HealthBarObject.h"

HealthBarObject::HealthBarObject()
{
	pos_x = 0 ;
	pos_y = 0 ;

	ratio = 0 ;

	pos_x_line = 0 ;

	HP_line_len = 0 ;
}

HealthBarObject::~HealthBarObject()
{

}

// Set Health Point For Health Bar
void HealthBarObject::setHealthPoint( const int& temp_max_HP , const int& temp_curr_HP ) 
{
	max_health = temp_max_HP ;
	curr_health = temp_curr_HP ;

	double max_HP = temp_max_HP ;
	double curr_HP = temp_curr_HP ;

	ratio = curr_HP / max_HP ;
}

// Load Health Bar Image Outline And Inside Image
void HealthBarObject::loadImageHealthBar( std::string outline_path , std::string inside_path , SDL_Renderer* screen ) 
{
	outline.loadImage( outline_path , screen ) ;
	inside.loadImage( inside_path , screen ) ;
}

// Load Health Bar's Line Image
void HealthBarObject::loadImageLine( std::string big_line_path , std::string small_line_path , SDL_Renderer* screen ) 
{
	big_line.loadImage( big_line_path , screen ) ;
	small_line.loadImage( small_line_path , screen ) ;
}

// Set Render Position For Health Bar
void HealthBarObject::setPos( const int& temp_x , const int& temp_y ) 
{
	outline.setRect( temp_x , temp_y ) ;
	inside.setRect( temp_x , temp_y ) ;

	pos_x = temp_x ;
	pos_y = temp_y ;
}

// Set Line Position Start From
void HealthBarObject::setLinePos( const int& temp_x , const int& temp_len ) 
{
	pos_x_line = temp_x ;
	HP_line_len = temp_len ;
}

// Show Health Bar Without Line 
void HealthBarObject::show( SDL_Renderer* des ) 
{
	SDL_Rect temp_outline = outline.getRect() ;
	SDL_Rect temp_inside = inside.getRect() ;

	double temp_width_frame = inside.getFrameWidth() ;
	double showing_width_frame = temp_width_frame * ratio ; 

	int outline_width_frame = outline.getFrameWidth() ;
	int outline_height_frame = outline.getFrameHeight() ;
	int inside_width_frame = ( int ) showing_width_frame ;
	int inside_height_frame = inside.getFrameHeight() ;

	SDL_Rect outline_clip = { 0 , 0 , outline_width_frame , outline_height_frame } ;
	SDL_Rect inside_clip = { 0 , 0 , inside_width_frame , inside_height_frame } ;

	SDL_Rect outline_renderQuad = { temp_outline.x , temp_outline.y , outline_width_frame , outline_height_frame } ;
	SDL_Rect inside_renderQuad = { temp_inside.x , temp_inside.y , inside_width_frame , inside_height_frame } ;

	SDL_RenderCopy( des , outline.getObject() , &outline_clip , &outline_renderQuad ) ;
	SDL_RenderCopy( des , inside.getObject() , &inside_clip , &inside_renderQuad ) ;
}


// Show Health Bar With Line
void HealthBarObject::showWithLine( SDL_Renderer* des ) 
{
	show( des ) ;

	SDL_Rect big_line_clip = { 0 , 0 , big_line.getFrameWidth() , big_line.getFrameHeight() } ;
	SDL_Rect small_line_clip = { 0 , 0 , small_line.getFrameWidth() , small_line.getFrameHeight() } ;

	// HP Length
	int small_len = HEALTH_BAR_HP_PER_SMALL_LINE ;
	int big_len = HEALTH_BAR_HP_PER_BIG_LINE ;

	// Showing On Screen Distance
	int num_of_distance = max_health / small_len ;

	int showing_len = HP_line_len / num_of_distance  ; 
	int start_point_x = pos_x + pos_x_line ;

	for( int i = small_len ; i <= curr_health ; i += small_len )
	{
		int increased_len = i / small_len * showing_len ;

		if( i % big_len == 0 )
		{
			big_line.setRect( start_point_x + increased_len  , pos_y ) ;

			big_line.render( des , &big_line_clip ) ;
		}
		else 
		{
			small_line.setRect( start_point_x + increased_len , pos_y ) ;

			small_line.render( des , &small_line_clip ) ;
		}
	}
}
