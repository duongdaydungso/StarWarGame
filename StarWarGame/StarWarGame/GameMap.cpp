
#include "stdafx.h"
#include "GameMap.h"

TileBlock::TileBlock() 
{

}

TileBlock::~TileBlock()
{

}

LoadingMap::LoadingMap() 
{
	on_screen_map.start_x = 0 ;
	on_screen_map.start_y = 0 ;

	on_screen_map.max_x = 0 ;
	on_screen_map.max_y = 0 ;

	start_point_x_ = 0 ;
	start_point_y_ = 0 ;

	curr_frame = 0 ;
	temp_frame = 0 ;
	end_point_curr_frame = 0 ;
	end_point_temp_frame = 0 ;
}

LoadingMap::~LoadingMap()
{

}

// Get Start Point 
int LoadingMap::getStartPointX() 
{
	return start_point_x_ ;
}

int LoadingMap::getStartPointY() 
{
	return start_point_y_ ;
}

// Get Map Info
Map LoadingMap::getMap() 
{
	return on_screen_map ;
}


void LoadingMap::loadMapInfo( char* file_path ) 
{
	FILE* fp = NULL ;

	fopen_s( &fp , file_path , "rb" ) ;

	if( fp == NULL ) 
	{
		printf( "Can't load map info\n" ) ;

		return ;
	}

	on_screen_map.max_x = 0 ;
	on_screen_map.max_y = 0 ;

	for( int i = 0 ; i < MAX_MAP_Y_BLOCK ; i ++ ) 
	{
		for( int j = 0 ; j < MAX_MAP_X_BLOCK ; j ++ )  
		{
			fscanf_s( fp , "%d" , &on_screen_map.tile[i][j] ) ;

			int val = on_screen_map.tile[i][j] ;

			if( val > 0 ) 
			{
				on_screen_map.max_x = max( on_screen_map.max_x , j ) ;
				on_screen_map.max_y = max( on_screen_map.max_y , i ) ;
			}
		}
	}

	on_screen_map.max_x = ( on_screen_map.max_x + 1 ) * TILE_SIZE ;
	on_screen_map.max_y = ( on_screen_map.max_y + 1 ) * TILE_SIZE ;

	on_screen_map.start_x = 0 ;
	on_screen_map.start_y = 0 ;

	fclose( fp ) ;

	loadCharacterStartPoint() ;
}

void LoadingMap::loadCharacterStartPoint() 
{
	start_point_x_ = ( START_POSITION_X - 1 ) * TILE_SIZE ;
	start_point_y_ = ( START_POSITION_Y - 1 ) * TILE_SIZE ;
}


void LoadingMap::loadTileImage( SDL_Renderer* screen ) 
{
	char tile_file_path[200] ;

	FILE* fp = NULL ;

	for( int i = 0 ; i < TILE_TYPE ; i ++ ) 
	{
		sprintf_s( tile_file_path , "media//image//tile_block//%d.png" , i ) ;

		fopen_s( &fp , tile_file_path , "rb" ) ;

		if( fp == NULL ) 
		{
			printf( "Can't load tile block image number %d\n" , i ) ;

			continue ;
		}

		fclose( fp ) ;

		loaded_tile_block[i].loadImage( tile_file_path , screen ) ;
	}

	heart_object.loadImage( "media//image//tile_block//heart_sprites.png" , screen ) ;
	heart_object.setClipSize( SUPPORT_ITEM_SPRITES ) ;

	power_object.loadImage( "media//image//tile_block//power_sprites.png" , screen ) ;
	power_object.setClipSize( SUPPORT_ITEM_SPRITES ) ;

	end_point_object.loadImage( "media//image//tile_block//end_point_sprites.png" , screen ) ;
	end_point_object.setClipSize( END_POINT_SPRITES ) ;
}

void LoadingMap::drawMap( SDL_Renderer* screen ) 
{
	// Coordinates of Showing Map from ( x1 , y1 ) to ( x2 , y2 ) 
	int x1 = 0 ;
	int x2 = 0 ;

	int y1 = 0 ; 
	int y2 = 0 ;

	// Calculate coordinates
	x1 = ( on_screen_map.start_x % TILE_SIZE ) * -1 ;
	x2 = x1 + SCREEN_WIDTH + ( ( x1 == 0 ) ? 0 : TILE_SIZE ) ;

	y1 = ( on_screen_map.start_y % TILE_SIZE ) * -1 ;
	y2 = y1 + SCREEN_HEIGHT + ( ( y1 == 0 ) ? 0 : TILE_SIZE ) ;

	// Index Tile Block
	int tile_x = 0 ;
	int tile_y = 0 ;

	// Calculate Index Tile Block
	tile_x = on_screen_map.start_x / TILE_SIZE ;
	tile_y = on_screen_map.start_y / TILE_SIZE ;
	
	temp_frame ++ ;
	temp_frame %= SUPPORT_ITEM_SPRITES * 2 ;
	curr_frame = temp_frame / 2 ;

	end_point_temp_frame ++ ;
	end_point_temp_frame %= END_POINT_SPRITES * 2 ;
	end_point_curr_frame = end_point_temp_frame / 2 ;

	for( int i = y1 ; i < y2 ; i += TILE_SIZE ) 
	{
		tile_x = on_screen_map.start_x / TILE_SIZE ;

		for( int j = x1 ; j < x2 ; j += TILE_SIZE ) 
		{
			int val = on_screen_map.tile[tile_y][tile_x] ;

			if( val > 0 && val != HEART_TILE && val != POWER_TILE && val != END_POINT_TILE ) 
			{
				loaded_tile_block[val].setRect( j , i ) ;
				loaded_tile_block[val].render( screen ) ;
			}
			else
			{
				if( val == HEART_TILE ) 
				{
					heart_object.setRect( j , i ) ;

					SDL_Rect current_clip = heart_object.getClipSize( curr_frame ) ;

					SDL_Rect renderQuad = { j , i , heart_object.getFrameWidth() , heart_object.getFrameHeight() } ;

					SDL_RenderCopy( screen , heart_object.getObject() , &current_clip , &renderQuad ) ;

				}
				else if( val == POWER_TILE ) 
				{
					power_object.setRect( j , i ) ;

					SDL_Rect current_clip = power_object.getClipSize( curr_frame ) ;

					SDL_Rect renderQuad = { j , i , power_object.getFrameWidth() , power_object.getFrameHeight() } ;

					SDL_RenderCopy( screen , power_object.getObject() , &current_clip , &renderQuad ) ;
				}
				else if( val == END_POINT_TILE ) 
				{
					end_point_object.setRect( j , i ) ;

					SDL_Rect current_clip = end_point_object.getClipSize( end_point_curr_frame ) ;

					SDL_Rect renderQuad = { j , i , end_point_object.getFrameWidth() , end_point_object.getFrameHeight() } ;

					SDL_RenderCopy( screen , end_point_object.getObject() , &current_clip , &renderQuad ) ;
				}
			}

			tile_x ++ ;
		}

		tile_y ++ ;
	}

}

// Set Map Info To Directed Map
void LoadingMap::setMapInfo( Map& map_data ) 
{
	on_screen_map = map_data ;
}



