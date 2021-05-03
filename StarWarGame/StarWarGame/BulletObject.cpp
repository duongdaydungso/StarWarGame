
#include "stdafx.h"
#include "BulletObject.h"

BulletObject::BulletObject() 
{
	pos_x = 0 ;
	pos_y = 0 ;

	delta_x = 0 ;
	delta_y = 0 ;

	bullet_angle = 0 ;

	is_exist = false ;
}

BulletObject::~BulletObject() 
{

}

// Get Bullet Position
double BulletObject::getPosX() const 
{
	return pos_x ;
}

double BulletObject::getPosY() const 
{
	return pos_y ;
}

// Set Bullet Position
void BulletObject::setPos( const int& xVal , const int& yVal ) 
{
	pos_x = xVal ;
	pos_y = yVal ;
}

// Get Bullet Delta
double BulletObject::getXDelta() const 
{
	return delta_x ;
}

double BulletObject::getYDelta() const 
{
	return delta_y ;
}

// Set Bullet Delta
void BulletObject::setDelta( const int& xVal , const int& yVal ) 
{
	delta_x = xVal ;
	delta_y = yVal ;
}

// Get Center Point
double BulletObject::getCenterX() const 
{
	return pos_x + ( width_frame / 2 ) - map_x ;
}

double BulletObject::getCenterY() const 
{
	return pos_y + ( height_frame / 2 ) - map_y ;
}


// Get Bullet Exist Status
bool BulletObject::getStatus() const 
{
	return is_exist ;
}

// Set Bullet Exist Status 
void BulletObject::setStatus( const bool& is_exist_ ) 
{
	is_exist = is_exist_ ;
}

// Get Bullet Angle
double BulletObject::getBulletAngle() const 
{
	return bullet_angle ;
}

// Set Bullet Angle 
void BulletObject::setBulletAngle( const double& temp_angle ) 
{
	bullet_angle = temp_angle ;
}

// Set Position Of Screen Displaying
void BulletObject::setMapXY( const int& temp_x , const int& temp_y ) 
{
	map_x = temp_x ;
	map_y = temp_y ;
}

// Calculate Delta x and Delta y
void BulletObject::calcBulletDelta( const double& bullet_speed ) 
{
	delta_x = cos( abs( bullet_angle ) * PI / 180 ) * bullet_speed ;
	delta_y = sin( abs( bullet_angle ) * PI / 180 ) * bullet_speed ;

	if( bullet_angle < 0 ) delta_y = -delta_y ;
}


// Make Bullet Move Check Bullet Out Of Screen Or Not
void BulletObject::moveTheBullet( Map& map_data , const int& x_border , const int& y_border ) 
{
	pos_x += delta_x ;
	pos_y += delta_y ;

	oRect.x = pos_x - map_x ;
	oRect.y = pos_y - map_y ;

	real_pos_x = pos_x ;
	real_pos_y = pos_y ;

	if( oRect.x < 0 || oRect.x > x_border || oRect.y < 0 || oRect.y > y_border )
	{
		is_exist = false ;
	}

	checkToMap( map_data ) ;
}

// Check Bullet Collision With Map
void BulletObject::checkToMap( Map& map_data ) 
{
	bool checkCollision_ = false ;

	// Check Concidence
	
	int x1 = ( pos_x ) / TILE_SIZE ;
	int y1 = ( pos_y + height_frame ) / TILE_SIZE ;

	if( map_data.tile[y1][x1] != BLANK_TILE && 
		map_data.tile[y1][x1] != HEART_TILE && 
		map_data.tile[y1][x1] != POWER_TILE &&
		map_data.tile[y1][x1] != END_POINT_TILE ) checkCollision_ = true ;

	int x2 = ( pos_x + width_frame ) / TILE_SIZE ;
	int y2 = ( pos_y ) / TILE_SIZE ;

	if( map_data.tile[y2][x2] != BLANK_TILE && 
		map_data.tile[y2][x2] != HEART_TILE && 
		map_data.tile[y2][x2] != POWER_TILE &&
		map_data.tile[y2][x2] != END_POINT_TILE ) checkCollision_ = true ;

	if( checkCollision_ == true ) is_exist = false ;
}

// Load Explosion Sound
void BulletObject::loadSound( std::string path ) 
{
	if( shooting_sound.loadSound( path , BULLET_SHOOTING_VOLUME ) == false ) printf( "Can't load bullet sound" ) ;
}

// Play Explosion Sound 
void BulletObject::playSound() 
{
	shooting_sound.playSound() ;
}

// Get Bullet Sound Status ( Is Played ) 
bool BulletObject::getSoundStatus() const 
{
	return shooting_sound.isPlayed() ;
}
