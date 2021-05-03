
#ifndef CREEP_OBJECT_H_
#define CREEP_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "HealthBarObject.h"

class CreepObject : public BaseObject 
{
public:	
	CreepObject() ;
	~CreepObject() ;

	// Get Creep Position
	double getPosX() const ;
	double getPosY() const ;

	// Set Creep Position
	void setPos( const int& xVal , const int& yVal ) ;

	// Get Creep Delta 
	double getXDelta() const ;
	double getYDelta() const ;

	// Set Creep Delta
	void setDelta( const int& xVal , const int& yVal ) ;

	// Get Creep Alive Status
	bool getStatus() const ;

	// Set Creep Alive Status 
	void setStatus( const bool& is_alive_ ) ;

	// Set Position Of Screen Displaying
	void setMapXY( const int& temp_x , const int& temp_y ) ;

	// Calculate Angle Direction
	double calculateAngle( const double& target_pos_x , const double& target_pos_y ) ;

	// Handling Creep Moving
	void handleCreepMoving( Map& map_data , const double& target_pos_x , const double& target_pos_y ) ;

	// Checking Collision
	void checkToMap( Map& map_data ) ;

	// Showing Creep
	void show( SDL_Renderer* des ) ;

	// Barracks Being Attacked
	void beingAttacked( const int& temp_health ) ;

	// Make Health Bar
	void makeHealthBar( SDL_Renderer* des ) ;

private:
	// Current position of Creep ( for checking collision ) Real Position On Coordinate Axis
	double pos_x ;
	double pos_y ;

	// Difference between ex Position and new Positions
	double delta_x ;
	double delta_y ;

	// Position Of Screen Displaying
	double map_x ;
	double map_y ;

	// Creep Direction Angle
	double creep_angle ;

	// Current Frame
	int curr_frame ;

	// Creep Still Alive Or Not ( Status )
	bool is_alive ;

	HealthBarObject health_bar ;
} ;

#endif