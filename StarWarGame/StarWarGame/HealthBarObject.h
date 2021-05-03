
#ifndef HEALTH_BAR_OBJECT_H_
#define HEALTH_BAR_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"

class HealthBarObject : public BaseObject
{
public:
	HealthBarObject() ;
	~HealthBarObject() ;

	// Set Health Point For Health Bar
	void setHealthPoint( const int& temp_max_HP , const int& temp_curr_HP ) ;

	// Load Health Bar Image Outline And Inside Image
	void loadImageHealthBar( std::string outline_path , std::string inside_path , SDL_Renderer* screen ) ;

	// Load Health Bar's Line Image
	void loadImageLine( std::string big_line_path , std::string small_line_path , SDL_Renderer* screen ) ; 

	// Set Render Position For Health Bar
	void setPos( const int& temp_x , const int& temp_y ) ;
	
	// Set Line Position Start From
	void setLinePos( const int& temp_x , const int& temp_len ) ;

	// Show Health Bar Without Line 
	void show( SDL_Renderer* des ) ;

	// Show Health Bar With Line
	void showWithLine( SDL_Renderer* des ) ;

private:
	// Current Position On Screen
	int pos_x ;
	int pos_y ;

	// Current Health Ratio
	double ratio ;

	// Health Bar Outline And Inside Image
	BaseObject outline ;
	BaseObject inside ;

	// Line Position Start From
	int pos_x_line ;

	int HP_line_len ;

	// Line In Health Bar Image
	BaseObject big_line ;
	BaseObject small_line ;
} ;

#endif