
#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "CommonFunction.h"
#include "BaseObject.h" 
#include "BulletObject.h"
#include "HealthBarObject.h"

// BB-8 BOTTOM **************************************************


class BottomOfCharacter : public BaseObject 
{
public:
	BottomOfCharacter() ;
	~BottomOfCharacter() ;

	// Get Position Of Character 
	double getPosX() ;
	double getPosY() ;

	// Set Character Position To Start 
	void spawn( int start_x , int start_y ) ;

	// Handle Object Coordinate While Moving
	void characterMoving( Map& map_data ) ;

	// Set Map Screen Follow Character 
	void setMapScreen( const int temp_x , const int temp_y ) ;

	// Keep Character On Middle Of Screen 
	void centerCharacterOnMap( Map& map_data ) ;

	// Checking Collision
	void checkToMap( Map& map_data ) ;

	// Load Bottom Sprites
	bool loadSprites( SDL_Renderer* des ) ;

	// Showing Running Character
	void show( SDL_Renderer* des ) ;

	// Input Action for Bottom of BB-8
	void inputAction( SDL_Event* events ) ;

	// Handling Heart And Power Support
	void increaseHeart() ;
	void increasePower() ;

	// Meet End Point And End Map
	void endMap() ;

	// Get Power Count
	int getPowerCount() const ;

	// Get Alive Status
	bool getAliveStatus() const ;

	// Get Meet End Point Status 
	bool isMeetEndPoint() const ;

	// Being Attacked
	void beingAttacked( const int& temp_health ) ;

	// Make Health Bar
	void makeHealthBar( SDL_Renderer* des ) ;

private:	
	// Current position
	double x_pos ;
	double y_pos ;

	// Changing Coordinate
	double delta_x ; 
	double delta_y ;

	// Bottom Input 
	BottomCharacterInput bot_input ;

	// Current Frame
	int bot_curr_frame ;

	// Current Status 
	BottomStatus bot_status ;
	BottomStatus last_bot_status ;

	// BB-8 Running Or Not 
	bool is_running ;

	// Map Screen Start From
	int map_screen_x ;
	int map_screen_y ;

	// Power count
	int power_count ;

	// Alive Status
	bool is_alive ;

	// Meet End Point Status
	bool meet_end_point ;

	HealthBarObject health_bar ;
} ;

// BB-8 TOP **************************************************

class TopOfCharacter : public BaseObject 
{
public:
	TopOfCharacter() ;
	~TopOfCharacter() ;

	// Get Position Of Character's Head
	double getPosX() ;
	double getPosY() ;

	// Set Top To Body Position
	void setPos( int point_x , int point_y ) ;

	// Showing BB-8 head
	void show( SDL_Renderer* des , SDL_Rect character_rect ) ;

	// Input Action for Top of BB-8
	void inputAction( SDL_Event* events , SDL_Renderer* screen , const int& power_count , const int& map_start_x , const int& map_start_y ) ;

	// Calculate Angle Between Center Of Character And Mouse Pointer
	double calculateAngle() ;

	// Set Bullet List
	void setBulletList( std::vector < BulletObject* > bullet_list_temp ) ;
	
	// Get Bullet List
	std::vector < BulletObject* > getBulletList() const ;

	// Check Bullet List And Shoot
	void handleBullet( SDL_Renderer* des , Map& map_data ) ;

private:
	// Current position
	double x_pos ;
	double y_pos ;

	// Mouse Position
	int mouse_pos_x ;
	int mouse_pos_y ;

	TopStatus top_status ;

	// List Of Bullet
	std::vector < BulletObject* > bullet_list ;
} ;

#endif