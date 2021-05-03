
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunction.h"
#include "BaseObject.h"

class TileBlock : public BaseObject 
{
public:
	TileBlock() ;
	~TileBlock() ;
} ;

class LoadingMap 
{
public:
	LoadingMap() ;
	~LoadingMap() ;

	// Get Start Point 
	int getStartPointX() ;
	int getStartPointY() ;

	// Get Map Info
	Map getMap() ;

	// Get Info Map From Map File
	void loadMapInfo( char* file_path ) ;
	void loadCharacterStartPoint() ;

	// Load Tile Block Image
	void loadTileImage( SDL_Renderer* screen ) ;

	// Draw Map Built From Map Info And Tile Block
	void drawMap( SDL_Renderer* screen ) ;

	// Set Map Info To Directed Map
	void setMapInfo( Map& map_data ) ;

private:
	// First Spawn Point of Character by Map
	int start_point_x_ ;
	int start_point_y_ ;

	Map on_screen_map ;
	TileBlock loaded_tile_block[TILE_TYPE] ;

	// Support Item
	int curr_frame ; // Current Frame Of Support Item
	int temp_frame ;
	int end_point_curr_frame ;
	int end_point_temp_frame ;
	BaseObject heart_object ;
	BaseObject power_object ;
	BaseObject end_point_object ;
} ;


#endif