// StarWarGame.cpp : 

#include "stdafx.h"

#include "CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h" 
#include "Character.h"
#include "ImpTimer.h"
#include "BarrackObject.h"
#include "ExplodeObject.h"
#include "TextObject.h"
#include "SoundObject.h"
#include "ButtonObject.h"

#include "InfoGameGeneral.h"
#include "InfoGame.h"
#include "InfoCharacter.h"
#include "InfoBarrack.h"

// ************************************************************************************************

// GAME INFO
int GAME_POINT ;

// GAME LEVEL
int GAME_DIFFICULTY_LEVEL ;
int LEVEL_POINT ;

// CHARACTER INFO

// Character's Health Point
int CHARACTER_MAXIMUM_HEALTH_POINT ;
int CHARACTER_GAIN_HEALTH_POINT_PER_HEART ;

// Character's Bullet
int POWER_LEVEL ;
int CHARACTER_BULLET_ATK ;

// BARRACKS INFO

int BARRACK_KILLED_POINT ;

// Shooting Barrack
int SHOOTING_BARRACK_MAXIMUM_HEALTH_POINT ;
int SHOOTING_BARRACK_BULLET_ATK ;

// Creep Barrack
int CREEP_BARRACK_MAXIMUM_HEALTH_POINT ;
int CREEP_MAXIMUM_HEALTH_POINT ; // Also Using For Creep Damge
int CREEP_KILLED_POINT ;

// ************************************************************************************************

BaseObject g_background ;
BaseObject g_background_2 ;

bool increase_background_alpha_status ;
Uint8 curr_background_alpha ;

TTF_Font* p_font = NULL ;
TTF_Font* button_font = NULL ;
TTF_Font* screen_text_font = NULL ;
TTF_Font* screen_text_font_2 = NULL ;

// Init Data
bool initData() ;

// Load Background
bool loadBackground() ;
void renderBackground( const int& temp_x , const int& temp_y ) ;

// Get Rid Of Everything
void close() ;

// Set Difficulty Level Of The Game
void setDifficultyLevel( int level ) ; 

// BARRACK***************************************************************************************************

// Create Barracks From Map
std::vector < BarrackObject* > createBarrackList( Map& map_data ) ;

// Create Barrack Exploding Effect List
ExplodeObject* createBarrackExploding( const int& temp_x , const int& temp_y ) ;

// MAIN GAME FUNCTION ***************************************************************************************

// Game Loop
GameStatus playGame( int level ) ;

// Menu
GameStatus drawMenu() ;

// Pause Tab
GameStatus pauseGame() ;

// Screen Text
GameStatus renderScreenText( std::string temp_text , int time_delay , TTF_Font* temp_font ) ;

// MAIN *****************************************************************************************************

int main( int argc , char* argv[] )
{
	srand( time( NULL ) ) ; // For Random 

	if( initData() == false ) return -1 ;

	if( loadBackground() == false ) return -1 ;

	int g_level = 1 ;

	int highest_score = 0 ;

	bool exit_game = false ;

	while( exit_game == false )
	{
		GameStatus g_status = drawMenu() ;

		if( g_status == EXIT ) 
		{
			exit_game = true ;

			break ;
		}
		else if( g_status == GAME_START ) 
		{
			// Game Point
			GAME_POINT = 0 ;	

			g_level = 1 ;

			GameStatus temp_status = GAME_START ;

			while( temp_status == GAME_START || temp_status == HIGHER_LEVEL )
			{
				if( renderScreenText( "LEVEL: " + std::to_string( g_level ) , 2 , screen_text_font ) == EXIT )
				{
					exit_game = true ;

					break ;
				}

				temp_status = playGame( g_level ) ;

				if( temp_status == HIGHER_LEVEL ) g_level ++ ;

				if( temp_status == LOST ) 
				{
					highest_score = max( highest_score , GAME_POINT ) ;

					if( renderScreenText( "GAME OVER" , 3 , screen_text_font ) == EXIT ) exit_game = true  ;
					else if( renderScreenText( "YOUR SCORE IS: " + std::to_string( GAME_POINT ) , 2 , screen_text_font_2 ) == EXIT ) exit_game = true ;
					else if( renderScreenText( "HIGHEST SCORE: " + std::to_string( highest_score ) , 2 , screen_text_font_2 ) == EXIT ) exit_game = true ;

					break ;
				}

				if( temp_status == EXIT_TO_MENU )
				{
					if( renderScreenText( "    BACK TO MENU" , 2 , screen_text_font_2 ) == EXIT ) exit_game = true ;

					break ;
				}

				if( temp_status == EXIT ) 
				{
					exit_game = true ;

					break ;
				}
			}
		}
	}

	close() ;

	return 0 ;
}

// **********************************************************************************************************

// Init Data

bool initData()
{
	bool success = true ;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
	else 
	{
		SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY , "1" ) ;

		g_window = SDL_CreateWindow( GAME_NAME.c_str() , 
									 SDL_WINDOWPOS_UNDEFINED , 
									 SDL_WINDOWPOS_UNDEFINED , 
									 SCREEN_WIDTH , 
									 SCREEN_HEIGHT , 
									 SDL_WINDOW_SHOWN ) ;

		if( g_window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
		}
		else
		{
			g_screen = SDL_CreateRenderer( g_window , -1 , SDL_RENDERER_ACCELERATED ) ;

			if( g_screen == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
			}
			else
            {
                SDL_SetRenderDrawColor( g_screen , RENDER_DRAW_COLOR_R , RENDER_DRAW_COLOR_G , RENDER_DRAW_COLOR_B , RENDER_DRAW_COLOR_ALPHA ) ;

                int imgFlags = IMG_INIT_PNG ;

                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n" , IMG_GetError() ) ;
                    success = false ;
                }
            }
		}
	}

	// Init Font Text

	if( TTF_Init() == -1 ) 
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() ) ;
		success = false ;
	}
	else 
	{
		p_font = TTF_OpenFont( "media//font//dlxfont_.ttf" , FONT_SIZE ) ;
		if( p_font == NULL ) 
		{
			printf( "Failed to load font! SDL_ttf Error: %s\n" , TTF_GetError() ) ;
			success = false ;
		}

		button_font = TTF_OpenFont( "media//font//dlxfont_.ttf" , BUTTON_FONT_SIZE ) ;
		if( button_font == NULL ) 
		{
			printf( "Failed to load font! SDL_ttf Error: %s\n" , TTF_GetError() ) ;
			success = false ;
		}

		screen_text_font = TTF_OpenFont( "media//font//dlxfont_.ttf" , SCREEN_TEXT_FONT_SIZE ) ;
		if( screen_text_font == NULL ) 
		{
			printf( "Failed to load font! SDL_ttf Error: %s\n" , TTF_GetError() ) ;
			success = false ;
		}

		screen_text_font_2 = TTF_OpenFont( "media//font//dlxfont_.ttf" , SCREEN_TEXT_FONT_SIZE_2 ) ;
		if( screen_text_font_2 == NULL ) 
		{
			printf( "Failed to load font! SDL_ttf Error: %s\n" , TTF_GetError() ) ;
			success = false ;
		}
	}

	// Init Sound 

	if( SDL_Init( SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( Mix_OpenAudio( 44100 , MIX_DEFAULT_FORMAT , 2 , 2048 ) < 0 )
		{
			printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n" , Mix_GetError() ) ;
			success = false ;
		}
	}

	return success ;
}

// Load Background

bool loadBackground() 
{
	bool success = g_background.loadImage( "media//image//background.png" , g_screen ) ;

	if( g_background_2.loadImage( "media//image//background_2.png" , g_screen ) == false ) success = false ;
	else g_background_2.setBlendMode( SDL_BLENDMODE_BLEND ) ;

	curr_background_alpha = 0 ;
	increase_background_alpha_status = true ;

	return success ;
}

void renderBackground( const int& temp_x , const int& temp_y ) 
{
	if( increase_background_alpha_status == true ) 
	{
		if( curr_background_alpha >= 255 - BACKGROUND_ALPHA_CHANGE_IN_ONE_FRAME ) 
		{
			curr_background_alpha = 255 ;
			increase_background_alpha_status = false ;
		}
		else curr_background_alpha += BACKGROUND_ALPHA_CHANGE_IN_ONE_FRAME ;
	}
	else 
	{
		if( curr_background_alpha <= BACKGROUND_ALPHA_CHANGE_IN_ONE_FRAME ) 
		{
			curr_background_alpha = 0 ;
			increase_background_alpha_status = true ;
		}
		else curr_background_alpha -= BACKGROUND_ALPHA_CHANGE_IN_ONE_FRAME ;
	}

	g_background_2.setAlpha( curr_background_alpha ) ;

	int pos_x = temp_x % SCREEN_WIDTH ;
	int pos_y = temp_y % SCREEN_HEIGHT ;

	SDL_Rect temp_rect = g_background.getRect() ;

	SDL_Rect clip = { pos_x , pos_y , SCREEN_WIDTH , SCREEN_HEIGHT } ;

	SDL_Rect renderQuad = { temp_rect.x , temp_rect.y , SCREEN_WIDTH , SCREEN_HEIGHT } ;

	SDL_RenderCopy( g_screen , g_background.getObject() , &clip , &renderQuad ) ;

	SDL_RenderCopy( g_screen , g_background_2.getObject() , &clip , &renderQuad ) ;
}

// Close Program

void close()
{
	g_background.free() ;
	
	SDL_DestroyRenderer( g_screen ) ;
	g_screen = NULL ;

	SDL_DestroyWindow( g_window ) ;
	g_window = NULL ;

	IMG_Quit() ;
	TTF_Quit() ;
	Mix_Quit() ;
	SDL_Quit() ;
}

// Set Difficulty Level Of The Game
void setDifficultyLevel( int level ) 
{
	// Level
	GAME_DIFFICULTY_LEVEL = level ;
	LEVEL_POINT = START_LEVEL_POINT * level ;

	// Character
	CHARACTER_MAXIMUM_HEALTH_POINT = CHARACTER_START_HEALTH_POINT + ( CHARACTER_INCREASED_HEALTH_POINT_PER_LEVEL * ( level - 1 ) ) ;
	CHARACTER_GAIN_HEALTH_POINT_PER_HEART = CHARACTER_START_GAIN_HEALTH_POINT_PER_HEARTH * level ;

	POWER_LEVEL = 1 ;

	CHARACTER_BULLET_ATK = CHARACTER_BULLET_START_ATK * POWER_LEVEL ;

	// Barracks
	BARRACK_KILLED_POINT = BARRACK_START_KILLED_POINT * level ;

	SHOOTING_BARRACK_MAXIMUM_HEALTH_POINT = SHOOTING_BARRACK_START_HEALTH_POINT + ( SHOOTING_BARRACK_INCREASED_HEALTH_POINT_PER_LEVER * ( level - 1 ) ) ;
	SHOOTING_BARRACK_BULLET_ATK = SHOOTING_BARRACK_BULLET_START_ATK * level ;

	CREEP_BARRACK_MAXIMUM_HEALTH_POINT = CREEP_BARRACK_START_HEALTH_POINT + ( CREEP_BARRACK_INCREASED_HEALTH_POINT_PER_LEVER * ( level - 1 ) ) ;
	CREEP_MAXIMUM_HEALTH_POINT = CREEP_START_HEALTH_POINT * level ;
	CREEP_KILLED_POINT = CREEP_START_KILLED_POINT * level ;
}

// BARRACK************************************************************************************************************************

// Create Barracks From Map
std::vector < BarrackObject* > createBarrackList( Map& map_data ) 
{
	std::vector < BarrackObject* > list_of_barracks ;

	for( int i = 0 ; i <= MAX_MAP_Y_BLOCK ; i ++ ) 
	{
		for( int j = 0 ; j <= MAX_MAP_X_BLOCK ; j ++ ) 
		{
			int val = map_data.tile[i][j] ;

			// Create Creep Barracks

			if( val == HEART_TILE ) 
			{
				BarrackObject* p_barrack = new BarrackObject ;

				p_barrack->loadImage( "media//image//threats//creep_barrack.png" , g_screen ) ;
				p_barrack->setClipSize( BARRACK_FRAME ) ;
				p_barrack->setPos( j * TILE_SIZE , i * TILE_SIZE ) ;
				p_barrack->setBarrackType( CREEP_BARRACK ) ;
				p_barrack->setUpHPAndPos( CREEP_BARRACK_MAXIMUM_HEALTH_POINT , CREEP_BARRACK_MAXIMUM_HEALTH_POINT ) ;

				list_of_barracks.push_back( p_barrack ) ;
			}

			// Create Shooting Barracks

			if( val ==  POWER_TILE ) 
			{
				BarrackObject* p_barrack = new BarrackObject  ;

				p_barrack->loadImage( "media//image//threats//shooting_barrack.png" , g_screen ) ;
				p_barrack->setClipSize( BARRACK_FRAME ) ;
				p_barrack->setPos( j * TILE_SIZE , i * TILE_SIZE ) ;
				p_barrack->setBarrackType( SHOOTING_BARRACK ) ;
				p_barrack->setUpHPAndPos( SHOOTING_BARRACK_MAXIMUM_HEALTH_POINT , SHOOTING_BARRACK_MAXIMUM_HEALTH_POINT ) ;

				list_of_barracks.push_back( p_barrack ) ;
			}
		}
	}

	return list_of_barracks ;
}

// Create Barrack Exploding Effect List
ExplodeObject* createBarrackExploding( const int& temp_x , const int& temp_y ) 
{
	ExplodeObject* p_explode = new ExplodeObject ;

	p_explode->loadImage( "media//image//threats//barrack_explode.png" , g_screen ) ;
	p_explode->setMaxFrame( BARRACK_EXPLODING_FRAME ) ;
	p_explode->setClipSize( BARRACK_EXPLODING_FRAME ) ;
	p_explode->setRect( temp_x , temp_y ) ;
	p_explode->loadSound( "media//audio//barrack_explosion.wav" ) ;

	return p_explode ;
}


// MAIN GAME FUNCTION **************************************************************************************************************

// GAME LOOP *************************************************************************************************
GameStatus playGame( int level ) 
{
	// Set Game Difficulty Level
	setDifficultyLevel( level ) ;

	// Load Music
	MusicObject ingame_music ;
	ingame_music.loadMusic( "media//audio//ingame_music.wav" , MUSIC_VOLUME ) ;
	ingame_music.playMusic() ;

	// Load Hud Image
	BaseObject game_hud ;
	game_hud.loadImage( "media//image//HUD.png" , g_screen ) ;
	game_hud.setRect( HUD_START_X , HUD_START_Y ) ;
	game_hud.setBlendMode( SDL_BLENDMODE_BLEND ) ;
	game_hud.setAlpha( HUD_ALPHA ) ;

	TextObject level_text ;
	level_text.setColor( 0 , 0 , 0 ) ;
	TextObject power_text ;
	power_text.setColor( 0 , 0 , 0 ) ;
	TextObject point_text ;
	point_text.setColor( 0 , 0 , 0 ) ;

	// Load Map
	LoadingMap game_map ;
	game_map.loadMapInfo( "map//map_info.dat" ) ;
	game_map.loadTileImage( g_screen ) ; 

	// Load Character 
	BottomOfCharacter bot_player ;
	bot_player.loadSprites( g_screen ) ;
	bot_player.setClipSize( CHARACTER_FRAME ) ;
	bot_player.spawn( game_map.getStartPointX() , game_map.getStartPointY() ) ;
	bot_player.setUpHPAndPos( CHARACTER_MAXIMUM_HEALTH_POINT , CHARACTER_MAXIMUM_HEALTH_POINT ) ;

	TopOfCharacter top_player ;
	top_player.loadImage( "media//image//bb_8//BB_8_head.png" , g_screen ) ;

	// Load Barracks From Map
	std::vector < BarrackObject* > barrack_list = createBarrackList( game_map.getMap() ) ;

	// Barrack Exploding Effect List
	std::vector < ExplodeObject* > exploding_list ;

	// Frame Timer 
	ImpTimer frame_timer ;
	int num_of_ticks = 0 ;

	// Game Running Loop

	bool is_playing = true ;
	bool is_paused = false ;
	bool is_exit = false ;

	while( is_playing ) 
	{
		// Start Frame Timer
		frame_timer.start() ;

		// Get Map Data
		Map map_data = game_map.getMap() ;

		while( SDL_PollEvent( &g_event ) != 0 ) 
		{
			// Quit 
			if( g_event.type == SDL_QUIT ) 
			{
				is_playing = false ;

				is_exit = true ;
			}

			if( g_event.type == SDL_KEYDOWN )
			{
				if( g_event.key.keysym.sym == SDLK_ESCAPE )
				{
					is_paused = true ;
				}
			}

			// Get BB_8 Input
			bot_player.inputAction( &g_event ) ;
			top_player.inputAction( &g_event , g_screen , bot_player.getPowerCount() , map_data.start_x , map_data.start_y ) ;
		}

		// Setup Screen 
		SDL_SetRenderDrawColor( g_screen , RENDER_DRAW_COLOR_R , RENDER_DRAW_COLOR_G , RENDER_DRAW_COLOR_B , RENDER_DRAW_COLOR_ALPHA ) ;
		SDL_RenderClear( g_screen ) ;

		// Draw Background
		renderBackground( map_data.start_x , map_data.start_y ) ;

		// Scrolling Map 
		bot_player.setMapScreen( map_data.start_x , map_data.start_y ) ;

		// Draw BB_8
		bot_player.characterMoving( map_data ) ;
		bot_player.show( g_screen ) ;
		bot_player.calculateCenterPoint() ;
		
		top_player.handleBullet( g_screen , map_data ) ;
		top_player.setPos( bot_player.getPosX() , bot_player.getPosY() ) ;
		top_player.show( g_screen , bot_player.getRect() ) ;

		// Draw Map
		game_map.setMapInfo( map_data ) ;
		game_map.drawMap( g_screen ) ;	

		// Draw Barracks
		for( int i = 0 ; i < barrack_list.size() ; i ++ ) 
		{
			BarrackObject* p_barrack = barrack_list.at( i ) ;

			if( p_barrack != NULL ) 
			{
				if( p_barrack->isDied() == false )
				{
					p_barrack->setMapXY( map_data.start_x , map_data.start_y ) ;

					if( p_barrack->getBarrackType() == SHOOTING_BARRACK ) 
					{
						p_barrack->showShootingBarrack( g_screen ) ;
					}
					else
					{
						p_barrack->showCreepBarrack( g_screen , bot_player.getCenterX() + map_data.start_x , bot_player.getCenterY() + map_data.start_y	) ;
					}

					p_barrack->doBarrack( g_screen , num_of_ticks , map_data , 
						bot_player.getCenterX() + map_data.start_x , bot_player.getCenterY() + map_data.start_y	) ;
				}
				else
				{
					exploding_list.push_back( createBarrackExploding( p_barrack->getPosX() , p_barrack->getPosY() ) ) ;

					barrack_list.erase( barrack_list.begin() + i ) ;
					if( p_barrack != NULL ) 
					{
						delete p_barrack ;
						p_barrack = NULL ;
					}
				}
			}
		}

		// Collision ************************************************************************

		// Checking Player Collision

		double player_pos_x = bot_player.getRealCenterX() ;
		double player_pos_y = bot_player.getRealCenterY() ;
		double player_radius = bot_player.getRadius() ;

		for( int i = 0 ; i < barrack_list.size() ; i ++ ) 
		{
			BarrackObject* t_barrack = barrack_list.at( i ) ;

			if( t_barrack != NULL ) 
			{
				if( t_barrack->isDied() == false )
				{
					// Checking Player x Barracks
					if( checkCollision( player_pos_x , player_pos_y , player_radius ,
										t_barrack->getRealCenterX() , t_barrack->getRealCenterY() , t_barrack->getRadius() ) == true )
					{
						bot_player.beingAttacked( t_barrack->getMaxHealth() ) ;
						t_barrack->beingAttacked( bot_player.getMaxHealth() ) ;
					}
							
					// Checking Player x Creeps
					std::vector < CreepObject* > t_creep_list = t_barrack->getCreepList() ;

					for( int j = 0 ; j < t_creep_list.size() ; j ++ ) 
					{
						CreepObject* t_creep = t_creep_list.at( j ) ;

						if( t_creep != NULL )
						{
							if( t_creep->getStatus() == true ) 
							{
								if( checkCollision( player_pos_x , player_pos_y , player_radius ,
													t_creep->getRealCenterX() , t_creep->getRealCenterY() , t_creep->getRadius() ) == true )
								{
									bot_player.beingAttacked( t_creep->getMaxHealth() ) ;
									t_creep->beingAttacked( bot_player.getMaxHealth() ) ;
								}
							}
						}
					}

					// Checking Player x Barracks's Bullet
					std::vector < BulletObject* > t_bullet_list = t_barrack->getBulletList() ;

					for( int j = 0 ; j < t_bullet_list.size() ; j ++ ) 
					{
						BulletObject* t_bullet = t_bullet_list.at( j ) ;

						if( t_bullet != NULL )
						{
							if( t_bullet->getStatus() == true ) 
							{
								if( checkCollision( player_pos_x , player_pos_y , player_radius ,
													t_bullet->getRealCenterX() , t_bullet->getRealCenterY() , t_bullet->getRadius() ) == true )
								{
									bot_player.beingAttacked( t_bullet->getMaxHealth() ) ;
									t_bullet->setStatus( false ) ;
								}
							}
						}
					}
				}
				else
				{
					exploding_list.push_back( createBarrackExploding( t_barrack->getPosX() , t_barrack->getPosY() ) ) ;

					barrack_list.erase( barrack_list.begin() + i ) ;
					if( t_barrack != NULL ) 
					{
						delete t_barrack ;
						t_barrack = NULL ;
					}
				}
			}
		}

		// Player Bullet List
		std::vector < BulletObject* > p_bullet_list = top_player.getBulletList() ;

		// Checking Player_Bullet Collision
		for( int i = 0 ; i < p_bullet_list.size() ; i ++ ) 
		{
			BulletObject* p_bullet = p_bullet_list.at( i ) ;

			double bullet_pos_x = p_bullet->getRealCenterX() ;
			double bullet_pos_y = p_bullet->getRealCenterY() ;
			double bullet_radius = p_bullet->getRadius() ;

			if( p_bullet != NULL ) 
			{
				if( p_bullet->getStatus() == false ) continue ;

				for( int j = 0 ; j < barrack_list.size() ; j ++ ) 
				{
					BarrackObject* t_barrack = barrack_list.at( j ) ;

					if( t_barrack != NULL ) 
					{
						if( t_barrack->isDied() == false )
						{
							// Checking Player_Bullet x Barracks
							if( checkCollision( bullet_pos_x , bullet_pos_y , bullet_radius ,
												t_barrack->getRealCenterX() , t_barrack->getRealCenterY() , t_barrack->getRadius() ) == true )
							{
								t_barrack->beingAttacked( p_bullet->getMaxHealth() ) ;
								p_bullet->setStatus( false ) ;
							}
							
							// Checking Player_Bullet x Creeps
							std::vector < CreepObject* > t_creep_list = t_barrack->getCreepList() ;

							for( int k = 0 ; k < t_creep_list.size() ; k ++ ) 
							{
								CreepObject* t_creep = t_creep_list.at( k ) ;

								if( t_creep != NULL )
								{
									if( t_creep->getStatus() == true ) 
									{
										if( checkCollision( bullet_pos_x , bullet_pos_y , bullet_radius ,
															t_creep->getRealCenterX() , t_creep->getRealCenterY() , t_creep->getRadius() ) == true )
										{
											t_creep->beingAttacked( p_bullet->getMaxHealth() ) ;
											p_bullet->setStatus( false ) ;
										}
									}
								}
							}
						}
						else
						{
							exploding_list.push_back( createBarrackExploding( t_barrack->getPosX() , t_barrack->getPosY() ) ) ;

							barrack_list.erase( barrack_list.begin() + j ) ;
							if( t_barrack != NULL ) 
							{
								delete t_barrack ;
								t_barrack = NULL ;
							}
						}
					}
				}
			}
		}

		// **********************************************************************************

		// Draw Barracks Explode
		for( int i = 0 ; i < exploding_list.size() ; i ++ ) 
		{
			ExplodeObject* t_explode = exploding_list.at( i ) ;

			if( t_explode->getStatus() == true ) 
			{
				t_explode->show( g_screen , map_data.start_x , map_data.start_y ) ;

				if( t_explode->getSoundStatus() == false ) t_explode->playSound() ;
			}
			else 
			{
				exploding_list.erase( exploding_list.begin() + i ) ;

				if( t_explode != NULL ) 
				{
					delete t_explode ;
					t_explode = NULL ;
				}
			}
		}

		// Draw HUD ******************************************************************************
		game_hud.render( g_screen ) ;

		level_text.setText( "LEVEL: " + std::to_string( GAME_DIFFICULTY_LEVEL ) ) ;
		level_text.loadRenderText( p_font , g_screen ) ;
		level_text.show( g_screen , LEVEL_TEXT_X , LEVEL_TEXT_Y ) ;

		power_text.setText( "POWER: " + std::to_string( POWER_LEVEL ) ) ;
		power_text.loadRenderText( p_font , g_screen ) ;
		power_text.show( g_screen , POWER_TEXT_X , POWER_TEXT_Y ) ;

		point_text.setText( "POINT: " + std::to_string( GAME_POINT ) ) ;
		point_text.loadRenderText( p_font , g_screen ) ;
		point_text.show( g_screen , POINT_TEXT_X , POINT_TEXT_Y ) ;

		// ***************************************************************************************

		// Update Screen
		SDL_RenderPresent( g_screen ) ;

		// FPS Controller
		int real_imp_time = frame_timer.getTick() ;

		if( real_imp_time < TIME_ONE_FRAME )
		{
			int delay_time = TIME_ONE_FRAME - real_imp_time ;

			SDL_Delay( delay_time ) ;
		}

		num_of_ticks ++ ;

		if( is_exit == true ) 
		{
			ingame_music.stopMusic() ;

			return EXIT ;
		}

		if( is_paused == true )
		{
			GameStatus temp_g_status = pauseGame() ;

			if( temp_g_status == EXIT )
			{
				is_playing = false ;

				ingame_music.stopMusic() ;

				return EXIT ;
			}
			else if( temp_g_status == EXIT_TO_MENU )
			{
				is_playing = false ;

				ingame_music.stopMusic() ;

				return EXIT_TO_MENU ;
			}

			is_paused = false ;
		}

		if( bot_player.getAliveStatus() == false )
		{
			is_playing = false ;

			ingame_music.stopMusic() ;

			return LOST ;
		}

		if( bot_player.isMeetEndPoint() == true ) 
		{
			is_playing = false ;

			ingame_music.stopMusic() ;

			return HIGHER_LEVEL ;
		}
	}

	ingame_music.stopMusic() ;

	return EXIT_TO_MENU ;
}

// MENU *************************************************************************************************

GameStatus drawMenu() 
{
	// Load Menu Image
	BaseObject menu_image ;
	menu_image.loadImage( "media//image//menu_image.png" , g_screen ) ;
	menu_image.setRect( MENU_IMAGE_X , MENU_IMAGE_Y ) ;

	// Load Music
	MusicObject menu_music ;
	menu_music.loadMusic( "media//audio//menu_music.wav" , MUSIC_VOLUME ) ;
	menu_music.playMusic() ;

	// Load button
	ButtonObject newgame_button ;
	newgame_button.loadButton( g_screen , button_font , "NEW GAME" ) ;
	newgame_button.setPos( NEW_GAME_BUTTON_X , NEW_GAME_BUTTON_Y , NEW_GAME_BUTTON_TEXT_X , NEW_GAME_BUTTON_TEXT_Y ) ;

	ButtonObject exit_button ;
	exit_button.loadButton( g_screen , button_font , "EXIT" ) ;
	exit_button.setPos( EXIT_BUTTON_X , EXIT_BUTTON_Y , EXIT_BUTTON_TEXT_X , EXIT_BUTTON_TEXT_Y ) ;

	// Frame Timer 
	ImpTimer frame_timer ;

	bool showingMenu = true ;
	bool is_game_start = false ;
	bool is_exit = false ;

	while( showingMenu == true )
	{
		// Start Frame Timer
		frame_timer.start() ;

		while( SDL_PollEvent( &g_event ) != 0 ) 
		{
			// Quit 
			if( g_event.type == SDL_QUIT ) 
			{
				showingMenu = false ;

				is_exit = true ;
			}

			int mouse_pos_x ;
			int mouse_pos_y ;

			// Handle Button Input
			if( g_event.type == SDL_MOUSEMOTION || g_event.type == SDL_MOUSEBUTTONDOWN || g_event.type == SDL_MOUSEBUTTONUP )
			{
				// Get Mouse Position
				SDL_GetMouseState( &mouse_pos_x , &mouse_pos_y ) ;

				// Check Mouse On Button
				newgame_button.checkMouse( mouse_pos_x , mouse_pos_y ) ;
				exit_button.checkMouse( mouse_pos_x , mouse_pos_y ) ;

				if( g_event.button.button == SDL_BUTTON_LEFT ) 
				{
					if( newgame_button.getButtonIn() == true ) 
					{
						is_game_start = true ;
					}
					else if( exit_button.getButtonIn() == true ) 
					{
						is_exit = true ;
					}
				}
			}
		}

		// Setup Screen 
		SDL_SetRenderDrawColor( g_screen , RENDER_DRAW_COLOR_R , RENDER_DRAW_COLOR_G , RENDER_DRAW_COLOR_B , RENDER_DRAW_COLOR_ALPHA ) ;
		SDL_RenderClear( g_screen ) ;

		// Render Background
		renderBackground( 0 , 0 ) ;

		// Showing Menu Image
		menu_image.render( g_screen ) ;

		// Showing Button
		newgame_button.show( g_screen ) ;
		exit_button.show( g_screen ) ;
		
		// Update Screen
		SDL_RenderPresent( g_screen ) ;

		// FPS Controller
		int real_imp_time = frame_timer.getTick() ;

		if( real_imp_time < TIME_ONE_FRAME )
		{
			int delay_time = TIME_ONE_FRAME - real_imp_time ;

			SDL_Delay( delay_time ) ;
		}

		if( is_exit == true ) 
		{
			menu_music.stopMusic() ;

			return EXIT ;
		}

		if( is_game_start == true )
		{
			menu_music.stopMusic() ;

			return GAME_START ;
		}
	}

	menu_music.stopMusic() ;

	return EXIT ;
}

// Pause Tab *************************************************************************************************
GameStatus pauseGame() 
{
	// Load button
	ButtonObject continue_button ;
	continue_button.loadButton( g_screen , button_font , "CONTINUE" ) ;
	continue_button.setPos( CONTINUE_BUTTON_X , CONTINUE_BUTTON_Y , CONTINUE_BUTTON_TEXT_X , CONTINUE_BUTTON_TEXT_Y ) ;

	ButtonObject menu_button ;
	menu_button.loadButton( g_screen , button_font , "MENU" ) ;
	menu_button.setPos( MENU_BUTTON_X , MENU_BUTTON_Y , MENU_BUTTON_TEXT_X , MENU_BUTTON_TEXT_Y ) ;

	// Pause Tab
	BaseObject pause_tab ;
	pause_tab.loadImage( "media//image//pause_tab.png" , g_screen ) ;
	pause_tab.setBlendMode( SDL_BLENDMODE_BLEND ) ;
	pause_tab.setAlpha( PAUSE_TAB_ALPHA ) ;
	pause_tab.setRect( PAUSE_TAB_X , PAUSE_TAB_Y ) ;

	// Frame Timer 
	ImpTimer frame_timer ;

	bool showingPauseTab = true ;
	bool is_exit = false ;

	GameStatus temp_status = NOTHINGHAPPEN ;

	while( showingPauseTab == true )
	{
		// Start Frame Timer
		frame_timer.start() ;

		while( SDL_PollEvent( &g_event ) != 0 ) 
		{
			// Quit 
			if( g_event.type == SDL_QUIT ) 
			{
				showingPauseTab = false ;

				is_exit = true ;
			}

			int mouse_pos_x ;
			int mouse_pos_y ;

			// Handle Button Input
			if( g_event.type == SDL_MOUSEMOTION || g_event.type == SDL_MOUSEBUTTONDOWN || g_event.type == SDL_MOUSEBUTTONUP )
			{
				// Get Mouse Position
				SDL_GetMouseState( &mouse_pos_x , &mouse_pos_y ) ;

				// Check Mouse On Button
				continue_button.checkMouse( mouse_pos_x , mouse_pos_y ) ;
				menu_button.checkMouse( mouse_pos_x , mouse_pos_y ) ;

				if( g_event.button.button == SDL_BUTTON_LEFT ) 
				{
					if( continue_button.getButtonIn() == true ) temp_status = CONTINUE ;
					else if( menu_button.getButtonIn() == true ) temp_status = EXIT_TO_MENU ;
				}
			}
		}

		// Setup Screen 
		SDL_SetRenderDrawColor( g_screen , RENDER_DRAW_COLOR_R , RENDER_DRAW_COLOR_G , RENDER_DRAW_COLOR_B , RENDER_DRAW_COLOR_ALPHA ) ;
		SDL_RenderClear( g_screen ) ;

		// Render Background
		renderBackground( 0 , 0 ) ;

		// Show Pause Tab
		pause_tab.render( g_screen ) ;

		// Showing Button
		continue_button.show( g_screen ) ;
		menu_button.show( g_screen ) ;
		
		// Update Screen
		SDL_RenderPresent( g_screen ) ;

		// FPS Controller
		int real_imp_time = frame_timer.getTick() ;

		if( real_imp_time < TIME_ONE_FRAME )
		{
			int delay_time = TIME_ONE_FRAME - real_imp_time ;

			SDL_Delay( delay_time ) ;
		}
		
		if( is_exit == true ) return EXIT ;

		if( temp_status == CONTINUE ) return CONTINUE ;
		else if( temp_status == EXIT_TO_MENU ) return EXIT_TO_MENU ;
	}

	return EXIT_TO_MENU ;
}


// Screen Text *************************************************************************************************
GameStatus renderScreenText( std::string temp_text , int time_delay , TTF_Font* temp_font ) 
{
	// Create Text
	TextObject screen_text ;
	screen_text.setColor( 255 , 255 , 255 ) ; // WHITE COLOR CODE 
	screen_text.setText( temp_text ) ;
	screen_text.loadRenderText( temp_font , g_screen ) ;

	// Setup Screen 
	SDL_SetRenderDrawColor( g_screen , RENDER_DRAW_COLOR_R , RENDER_DRAW_COLOR_G , RENDER_DRAW_COLOR_B , RENDER_DRAW_COLOR_ALPHA ) ;
	SDL_RenderClear( g_screen ) ;

	// Render Background
	renderBackground( 0 , 0 ) ;

	// Draw Text
	screen_text.show( g_screen , SCREEN_TEXT_X , SCREEN_TEXT_Y ) ;

	// Update Screen
	SDL_RenderPresent( g_screen ) ;

	// Frame Timer 
	ImpTimer frame_timer ;

	int sum_of_time = 0 ;

	bool showingText = true ;
	bool is_exit = false ;

	while( showingText == true )
	{
		// Start Frame Timer
		frame_timer.start() ;

		while( SDL_PollEvent( &g_event ) != 0 ) 
		{
			// Quit 
			if( g_event.type == SDL_QUIT ) 
			{
				showingText = false ;

				is_exit = true ;
			}
		}

		sum_of_time += frame_timer.getTick() ;

		if( sum_of_time > time_delay * 1000 ) showingText = false ;

		if( is_exit == true ) return EXIT ;
	}

	return NOTHINGHAPPEN ;
}