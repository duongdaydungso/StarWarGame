
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "CommonFunction.h" 
#include "BaseObject.h"
#include "SoundObject.h"

class BulletObject : public BaseObject
{
public:
	BulletObject() ;
	~BulletObject() ;

	// Get Bullet Position
	double getPosX() const ;
	double getPosY() const ;

	// Set Bullet Position
	void setPos( const int& xVal , const int& yVal ) ;

	// Get Bullet Delta 
	double getXDelta() const ;
	double getYDelta() const ;

	// Set Bullet Delta
	void setDelta( const int& xVal , const int& yVal ) ;

	// Get Center Point
	double getCenterX() const ;
	double getCenterY() const ;

	// Get Bullet Exist Status
	bool getStatus() const ;

	// Set Bullet Exist Status 
	void setStatus( const bool& is_exist_ ) ;

	// Get Bullet Angle
	double getBulletAngle() const ;

	// Set Bullet Angle 
	void setBulletAngle( const double& temp_angle ) ;

	// Set Position Of Screen Displaying
	void setMapXY( const int& temp_x , const int& temp_y ) ;

	// Calculate Delta x and Delta y
	void calcBulletDelta( const double& bullet_speed ) ;

	// Make Bullet Move Check Bullet Out Of Screen Or Not
	void moveTheBullet( Map& map_data , const int& x_border , const int& y_border ) ;

	// Check Bullet Collision With Map
	void checkToMap( Map& map_data ) ;

	// Load Explosion Sound
	void loadSound( std::string path ) ;

	// Play Explosion Sound 
	void playSound() ;

	// Get Bullet Sound Status ( Is Played ) 
	bool getSoundStatus() const ;

private:
	// Current position of bullet ( for checking collision ) Real Position On Coordinate Axis
	double pos_x ;
	double pos_y ;

	// Difference between ex Position and new Positions
	double delta_x ;
	double delta_y ;

	// Position Of Screen Displaying
	double map_x ;
	double map_y ;

	// Bullet's Angle Shooting
	double bullet_angle ;

	// Bullet Is Existing Or Not
	bool is_exist ;

	// Shooting Sound
	ShortSoundObject shooting_sound ;
} ;


#endif