
#include "stdafx.h"
#include "CreepObject.h"

#include "InfoGame.h"
#include "InfoBarrack.h"

CreepObject::CreepObject()
{
	pos_x = 0 ;
	pos_y = 0 ;

	delta_x = 0 ;
	delta_y = 0 ;

	map_x = 0 ;
	map_y = 0 ;

	creep_angle = 0 ;

	curr_frame = 0 ;

	is_alive = true ;
}

CreepObject::~CreepObject()
{

}

// Get Creep Position
double CreepObject::getPosX() const 
{
	return pos_x ;
}

double CreepObject::getPosY() const 
{
	return pos_y ;
}

// Set Creep Position
void CreepObject::setPos( const int& xVal , const int& yVal ) 
{
	pos_x = xVal ;
	pos_y = yVal ;
}

// Get Creep Delta
double CreepObject::getXDelta() const 
{
	return delta_x ;
}

double CreepObject::getYDelta() const 
{
	return delta_y ;
}

// Set Creep Delta
void CreepObject::setDelta( const int& xVal , const int& yVal ) 
{
	delta_x = xVal ;
	delta_y = yVal ;
}


// Get Creep Alive Status
bool CreepObject::getStatus() const 
{
	return is_alive ;
}

// Set Creep Alive Status 
void CreepObject::setStatus( const bool& is_alive_ ) 
{
	is_alive = is_alive_ ;
}

// Set Position Of Screen Displaying
void CreepObject::setMapXY( const int& temp_x , const int& temp_y ) 
{
	map_x = temp_x ;
	map_y = temp_y ;
}

// Calculate Angle Direction
double CreepObject::calculateAngle( const double& target_pos_x , const double& target_pos_y ) 
{
	double temp_x = pos_x + width_frame ;
	double temp_y = pos_y + ( height_frame / 2 ) ;

	double center_x_temp = pos_x + ( width_frame / 2 ) ;
	double center_y_temp = pos_y + ( height_frame / 2 ) ;

	return calcAngleFromThreePoint( Point( center_x_temp , center_y_temp ) , Point( temp_x , temp_y ) , Point( target_pos_x , target_pos_y ) ) ;
}

// Handling Creep Moving
void CreepObject::handleCreepMoving( Map& map_data , const double& target_pos_x , const double& target_pos_y ) 
{
	creep_angle = calculateAngle( target_pos_x , target_pos_y ) ;

	delta_x = cos( abs( creep_angle ) * PI / 180 ) * CREEP_SPEED ;
	delta_y = sin( abs( creep_angle ) * PI / 180 ) * CREEP_SPEED ;

	if( creep_angle < 0 ) delta_y = -delta_y ;	

	checkToMap( map_data ) ;
}

// Checking Collision
void CreepObject::checkToMap( Map& map_data ) 
{
	// Temporary Variable
	int x1 = 0 ;
	int x2 = 0 ;

	int y1 = 0 ;
	int y2 = 0 ;

	// Check Concidence
	
	x1 = ( pos_x ) / TILE_SIZE ;
	y1 = ( pos_y + height_frame ) / TILE_SIZE ;

	if( map_data.tile[y1][x1] != BLANK_TILE && map_data.tile[y1][x1] != HEART_TILE && map_data.tile[y1][x1] != POWER_TILE ) pos_y -= EPSILON ;

	x2 = ( pos_x + width_frame ) / TILE_SIZE ;
	y2 = ( pos_y ) / TILE_SIZE ;

	if( map_data.tile[y2][x2] != BLANK_TILE && map_data.tile[y2][x2] != HEART_TILE && map_data.tile[y2][x2] != POWER_TILE ) pos_x -= EPSILON ;

	// Check Horizontal 

	x1 = ( pos_x + delta_x ) / TILE_SIZE ;
	x2 = ( pos_x + delta_x + width_frame - EPSILON ) / TILE_SIZE ;

	y1 = ( pos_y ) / TILE_SIZE ;
	y2 = ( pos_y + height_frame ) / TILE_SIZE ;

	if( x1 >= 0 && x1 <= MAX_MAP_X_BLOCK && y1 >= 0 && y1 <= MAX_MAP_Y_BLOCK )
	{
		if( delta_x > 0 ) 
		{
			bool not_blank_tile = false ;

			for( int i = y1 ; i <= y2 ; i ++ ) 
				if( map_data.tile[i][x2] != BLANK_TILE && map_data.tile[i][x2] != HEART_TILE && map_data.tile[i][x2] != POWER_TILE ) not_blank_tile = true ;

			if( not_blank_tile == true ) delta_x = 0 ;
		}
		else if( delta_x < 0 )
		{
			bool not_blank_tile = false ;

			for( int i = y1 ; i <= y2 ; i ++ ) 
				if( map_data.tile[i][x1] != BLANK_TILE && map_data.tile[i][x1] != HEART_TILE && map_data.tile[i][x1] != POWER_TILE ) not_blank_tile = true ;

			if( not_blank_tile == true ) delta_x = 0 ;
		}
	}

	// Check Vertical

	x1 = ( pos_x ) / TILE_SIZE ;
	x2 = ( pos_x + width_frame ) / TILE_SIZE ;

	y1 = ( pos_y + delta_y ) / TILE_SIZE ;
	y2 = ( pos_y + delta_y + height_frame - EPSILON ) / TILE_SIZE ;

	if( x1 >= 0 && x1 <= MAX_MAP_X_BLOCK && y1 >= 0 && y1 <= MAX_MAP_Y_BLOCK )
	{
		if( delta_y > 0 ) 
		{
			bool not_blank_tile = false ;

			for( int i = x1 ; i <= x2 ; i ++ ) 
				if( map_data.tile[y2][i] != BLANK_TILE && map_data.tile[y2][i] != HEART_TILE && map_data.tile[y2][i] != POWER_TILE ) not_blank_tile = true ;

			if( not_blank_tile == true ) delta_y = 0 ;
		}
		else if( delta_y < 0 )
		{
			bool not_blank_tile = false ;

			for( int i = x1 ; i <= x2 ; i ++ ) 
				if( map_data.tile[y1][i] != BLANK_TILE && map_data.tile[y1][i] != HEART_TILE && map_data.tile[y1][i] != POWER_TILE ) not_blank_tile = true ;

			if( not_blank_tile == true ) delta_y = 0 ;
		}
	}

	pos_x += delta_x ;
	pos_y += delta_y ;

	delta_x = 0 ;
	delta_y = 0 ;

	if( pos_x < 0 ) 
	{
		pos_x = 0 ;
	}
	else if( pos_x + width_frame > map_data.max_x ) 
	{
		pos_x = map_data.max_x - width_frame - EPSILON ;
	}

	if( pos_y < 0 ) 
	{
		pos_y = 0 ;
	}
	else if( pos_y + height_frame > map_data.max_y ) 
	{
		pos_y = map_data.max_y - height_frame - EPSILON ;
	}

	real_pos_x = pos_x ;
	real_pos_y = pos_y ;
}

// Showing Creep
void CreepObject::show( SDL_Renderer* des )
{
	if( is_alive == true )
	{
		curr_frame ++ ;
		curr_frame %= CREEP_FRAME ;
	}
	else return ;

	oRect.x = pos_x - map_x ;
	oRect.y = pos_y - map_y ;

	SDL_Rect* current_clip = &frame_clip[curr_frame] ;

	SDL_Rect renderQuad = { oRect.x , oRect.y , width_frame , height_frame } ;

	SDL_RendererFlip flip = SDL_FLIP_NONE ;
	SDL_Point* center = NULL ;

	SDL_RenderCopyEx( des , oTexture , current_clip , &renderQuad , creep_angle , center , flip ) ;

	makeHealthBar( des ) ;
}

// Barracks Being Attacked
void CreepObject::beingAttacked( const int& temp_health ) 
{
	changeHealth( -temp_health ) ;

	if( curr_health < 0 ) curr_health = 0 ;

	if( curr_health <= 0 )  
	{
		is_alive = false ;

		GAME_POINT += CREEP_KILLED_POINT ;
	}
}

// Make Health Bar
void CreepObject::makeHealthBar( SDL_Renderer* des ) 
{
	health_bar.loadImageHealthBar( "media//image//health_bar//Creep_HP_bar_outline.png" , 
								   "media//image//health_bar//Creep_HP_bar_inside.png" , des ) ;

	health_bar.setPos( oRect.x , oRect.y - HEALTH_BAR_DISTANCE_FROM_CREEP ) ;
	health_bar.setHealthPoint( max_health , curr_health ) ;

	health_bar.show( des ) ;
}
