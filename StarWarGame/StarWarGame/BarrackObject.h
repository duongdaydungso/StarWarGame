
#ifndef BARRACK_OBJECT_H_
#define BARRACK_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "CreepObject.h"
#include "HealthBarObject.h"
#include "ExplodeObject.h"

// BARRACK OBJECT *************************************************************************************

class BarrackObject : public BaseObject
{
public:
	BarrackObject() ;
	~BarrackObject() ;

	// Get Barrack's Position 
	double getPosX() const ;
	double getPosY() const ;

	// Set Barrack's Position
	void setPos( const double& temp_x , const double& temp_y ) ;

	// Get Barrack's Active Status
	bool isActive() const ;
	bool isDied() const ;

	// Set Barrack's Active Status 
	void setActiveStatus( bool temp_bool ) ;

	// Set Barrack's Position On Map
	void setMapXY( const int& temp_x , const int& temp_y ) ;

	// Get Type Of Barrack
	BarrackType getBarrackType() const ;

	// Set Type Of Barrack
	void setBarrackType( const BarrackType& temp_type ) ;

	// Make Barracks Work
	void doBarrack( SDL_Renderer* screen , const int& number_of_ticks , Map& map_data , const double& target_pos_x , const double& target_pos_y ) ;

	// Barracks Being Attacked
	void beingAttacked( const int& temp_health ) ;

	// Make Health Bar
	void makeHealthBar( SDL_Renderer* des ) ;

	// SHOOTING BARRACK *****************************************

	// Showing Shooting Barrack
	void showShootingBarrack( SDL_Renderer* des ) ; 

	// Set Bullet List
	void setBulletList( std::vector < BulletObject* > bullet_list_temp ) ;

	// Get Bullet List
	std::vector < BulletObject* > getBulletList() const ;

	// Check Bullet List And Shoot
	void showBullet( SDL_Renderer* des , Map& map_data ) ;

	// Set Up A Bullet 
	void setUpBullet( BulletObject* bullet , SDL_Renderer* screen , const double& shooting_angle ) ;

	// Handling Shooting Action Of Barracks
	void doShootingBarrack( SDL_Renderer* screen , const int& number_of_ticks , Map& map_data ) ;

	// CREEP BARRACK *****************************************

	// Showing Creep Barrack
	void showCreepBarrack( SDL_Renderer* des , const double& target_pos_x , const double& target_pos_y ) ; 

	// Calculate Angle Creep Barrack's Direction
	double calculateAngle( const double& target_pos_x , const double& target_pos_y ) ;

	// Set Creep List
	void setCreeptList( std::vector < CreepObject* > creep_list_temp ) ;

	// Get Creep List
	std::vector < CreepObject* > getCreepList() const ;

	// Check Creep List And Shoot
	void showCreep( SDL_Renderer* des , Map& map_data , const double& target_pos_x , const double& target_pos_y ) ;

	// Spawn A Creep 
	void spawnCreep( CreepObject* creep , SDL_Renderer* screen ) ;

	// Handling Creep Barracks
	void doCreepBarrack( SDL_Renderer* screen , const int& number_of_ticks , Map& map_data , const double& target_pos_x , const double& target_pos_y ) ;

	// Create Creep Explode
	ExplodeObject* createCreepExplode( SDL_Renderer* des , const int& temp_x , const int& temp_y ) ;

private:
	// Current Position ( On All Map , Not On Screen ) 
	double pos_x ;
	double pos_y ;

	// Current On Screen Map
	int map_x ;
	int map_y ;

	// Current Frame
	int curr_frame ;

	// Barrack Status
	bool is_active ;

	bool is_died ;

	// Barrack Type
	BarrackType barrack_type ;

	// Bullet List
	std::vector < BulletObject* > bullet_list ;

	// Creep List
	std::vector < CreepObject* > creep_list ;

	// Creep Explode List
	std::vector < ExplodeObject* > explode_list ;

	HealthBarObject health_bar ;
} ;

#endif 