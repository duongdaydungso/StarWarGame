
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h> 
#include <stdio.h>
#include <string> 
#include <math.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h> 
#include <SDL_ttf.h> 

#include "InfoGameGeneral.h"

// Random Function
int RandomNumber( int left_number_ , int right_number_ ) ;

// Map Structure
struct Map 
{
	//Showing Map Start From ( Coordinate ) 
	int start_x ;
	int start_y ;

	//Showing Map Maximum Coordinate
	int max_x ;
	int max_y ;

	//Map Tile Loading 
	int tile[MAX_MAP_Y_BLOCK][MAX_MAP_X_BLOCK] ;
} ;

// BB-8 Input Type

struct BottomCharacterInput
{
	int left ; 
	int right ;
	int up ; 
	int down ;
} ;

enum BottomStatus 
{
	RIGHT_ ,
	DOWN_RIGHT_ , 
	DOWN_ , 
	DOWN_LEFT_ ,
	LEFT_ , 
	UP_LEFT_ , 
	UP_ ,
	UP_RIGHT_ ,
	UNKNOWN_
} ;

enum TopStatus
{
    MOUSE_MOVING_ ,
    MOUSE_DOWN_ ,
    MOUSE_UP_ ,
	UNDETERMINED_
} ;

// define Point

struct Point 
{
	double x ;
	double y ;

	Point( double temp_x , double temp_y ) ;
	~Point() ;
} ;


// Length Of Segment From Point P1 To Point P2 

double lengthOfVector( Point P1 , Point P2 ) ;

// CCW

double ccw( Point P1 , Point P2 , Point P3 ) ;

// Calculate Angle From 3 Point

double calcAngleFromThreePoint( Point P1 , Point P2 , Point P3 ) ;

// Barracks Type 
enum BarrackType 
{
	BLANK_BARRACK ,
	CREEP_BARRACK ,
	SHOOTING_BARRACK 
} ;

// Check Collisions

bool checkCollision( const double& a_x , const double& a_y , const double& a_radius , 
					 const double& b_x , const double& b_y , const double& b_radius ) ;

enum GameStatus
{
	GAME_START ,
	HIGHER_LEVEL ,
	EXIT ,
	EXIT_TO_MENU ,
	LOST , 
	CONTINUE ,
	NOTHINGHAPPEN 
} ;



#endif 