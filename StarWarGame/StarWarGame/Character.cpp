
#include "stdafx.h"
#include "Character.h"

#include "InfoGame.h"
#include "InfoCharacter.h"

BottomOfCharacter::BottomOfCharacter()
{
	x_pos = 0 ;
	y_pos = 0 ;

	bot_input.up = 0 ;
	bot_input.down = 0 ;
	bot_input.left = 0 ;
	bot_input.right = 0 ;

	bot_curr_frame = 0 ;

	bot_status = UNKNOWN_ ;
	last_bot_status = UNKNOWN_ ;

	is_running = false ;

	delta_x = 0 ;
	delta_y = 0 ;

	map_screen_x = 0 ;
	map_screen_y = 0 ;

	power_count = 1 ;

	is_alive = true ;
	meet_end_point = false ;
}

BottomOfCharacter::~BottomOfCharacter()
{

}

// Get Position Of Character 
double BottomOfCharacter::getPosX() 
{
	return x_pos ;
}

double BottomOfCharacter::getPosY() 
{
	return y_pos ;
}

// Set Character Position To Start 

void BottomOfCharacter::spawn( int start_x , int start_y )
{
	x_pos = start_x ;
	y_pos = start_y ;
}

// Handle Object Coordinate While Moving

void BottomOfCharacter::characterMoving( Map& map_data ) 
{
	delta_x = 0 ;
	delta_y = 0 ;

	switch ( bot_status ) 
	{
	case UNKNOWN_ : 
		{
			delta_x = 0 ;
			delta_y = 0 ;
		}
		break ;
	case RIGHT_ : 
		{
			delta_x = MOVEMENT_SPEED ;
			delta_y = 0 ;
		}
		break ;
	case LEFT_ : 
		{
			delta_x = -MOVEMENT_SPEED ;
			delta_y = 0 ;
		}
		break ;
	case UP_ :
		{
			delta_x = 0 ;
			delta_y = -MOVEMENT_SPEED ;
		}
		break ;
	case DOWN_ :
		{
			delta_x = 0 ;
			delta_y = MOVEMENT_SPEED ;
		}
		break ;
	case UP_RIGHT_ :
		{
			delta_x = MOVEMENT_SPEED_DIAGONALLY ;
			delta_y = -MOVEMENT_SPEED_DIAGONALLY ;
		}
		break ;
	case UP_LEFT_ :
		{
			delta_x = -MOVEMENT_SPEED_DIAGONALLY ;
			delta_y = -MOVEMENT_SPEED_DIAGONALLY ;
		}
		break ;
	case DOWN_RIGHT_ :
		{
			delta_x = MOVEMENT_SPEED_DIAGONALLY ;
			delta_y = MOVEMENT_SPEED_DIAGONALLY ;
		}
		break ;
	case DOWN_LEFT_ :
		{
			delta_x = -MOVEMENT_SPEED_DIAGONALLY ;
			delta_y = MOVEMENT_SPEED_DIAGONALLY ;
		}
		break ;
	default : 
		break ;
	}

	checkToMap( map_data ) ;
	centerCharacterOnMap( map_data ) ;
}

// Set Map Screen Follow Character 
void BottomOfCharacter::setMapScreen( const int temp_x , const int temp_y ) 
{
	map_screen_x = temp_x ;
	map_screen_y = temp_y ;
}


// Keep Character On Middle Of Screen 
void BottomOfCharacter::centerCharacterOnMap( Map& map_data ) 
{
	// Screen moving left and right
	if( map_data.start_x + ( SCREEN_WIDTH / 3 ) > x_pos ) 
	{
		map_data.start_x = x_pos - ( SCREEN_WIDTH / 3 ) ;
	}
	else if( map_data.start_x + ( SCREEN_WIDTH / 2 ) < x_pos )
	{
		map_data.start_x = x_pos - ( SCREEN_WIDTH / 2 ) ;
	}

	if( map_data.start_x < 0 ) 
	{
		map_data.start_x = 0 ;
	}
	else if( map_data.start_x + SCREEN_WIDTH >= map_data.max_x ) 
	{
		map_data.start_x = map_data.max_x - SCREEN_WIDTH ; 
	}

	// Screen moving up and down
	if( map_data.start_y + ( SCREEN_HEIGHT / 3 ) > y_pos ) 
	{
		map_data.start_y = y_pos - ( SCREEN_HEIGHT / 3 ) ;
	}
	else if( map_data.start_y + ( SCREEN_HEIGHT / 2 ) < y_pos )
	{
		map_data.start_y = y_pos - ( SCREEN_HEIGHT / 2 ) ;
	}

	if( map_data.start_y < 0 ) 
	{
		map_data.start_y = 0 ;
	}
	else if( map_data.start_y + SCREEN_HEIGHT >= map_data.max_y ) 
	{
		map_data.start_y = map_data.max_y - SCREEN_HEIGHT ; 
	}
}


// Checking Collision
void BottomOfCharacter::checkToMap( Map& map_data ) 
{
	// Temporary 
	int x1 = 0 ;
	int x2 = 0 ;

	int y1 = 0 ;
	int y2 = 0 ;

	// Check Concidence
	
	x1 = ( x_pos ) / TILE_SIZE ;
	y1 = ( y_pos + height_frame ) / TILE_SIZE ;

	if( map_data.tile[y1][x1] == HEART_TILE || map_data.tile[y1][x1] == POWER_TILE || map_data.tile[y1][x1] == END_POINT_TILE )
	{
		map_data.tile[y1][x1] = BLANK_TILE ;

		if( map_data.tile[y1][x1] == HEART_TILE ) increaseHeart() ;
		else if( map_data.tile[y1][x1] == POWER_TILE ) increasePower() ;
		else if( map_data.tile[y1][x1] == END_POINT_TILE ) endMap() ;
	} 
	else if( map_data.tile[y1][x1] != BLANK_TILE ) y_pos -= EPSILON ;

	x2 = ( x_pos + width_frame ) / TILE_SIZE ;
	y2 = ( y_pos ) / TILE_SIZE ;

	if( map_data.tile[y2][x2] == HEART_TILE || map_data.tile[y2][x2] == POWER_TILE || map_data.tile[y2][x2] == END_POINT_TILE )
	{
		map_data.tile[y2][x2] = BLANK_TILE ;

		if( map_data.tile[y2][x2] == HEART_TILE ) increaseHeart() ;
		else if( map_data.tile[y2][x2] == POWER_TILE ) increasePower() ;
		else if( map_data.tile[y2][x2] == END_POINT_TILE ) endMap() ;
	} 
	else if( map_data.tile[y2][x2] != BLANK_TILE ) x_pos -= EPSILON ;

	// Check Horizontal 

	x1 = ( x_pos + delta_x ) / TILE_SIZE ;
	x2 = ( x_pos + delta_x + width_frame - EPSILON ) / TILE_SIZE ;

	y1 = ( y_pos ) / TILE_SIZE ;
	y2 = ( y_pos + height_frame ) / TILE_SIZE ;

	if( x1 >= 0 && x1 <= MAX_MAP_X_BLOCK && y1 >= 0 && y1 <= MAX_MAP_Y_BLOCK )
	{
		if( delta_x > 0 ) 
		{
			bool not_blank_tile = false ;
			bool heart_appeared = false ;
			bool power_appeared = false ;
			bool end_point_appeared = false ;

			for( int i = y1 ; i <= y2 ; i ++ ) 
			{
				if( map_data.tile[i][x2] == HEART_TILE || map_data.tile[i][x2] == POWER_TILE || map_data.tile[i][x2] == END_POINT_TILE )
				{
					if( map_data.tile[i][x2] == HEART_TILE ) heart_appeared = true ;
					else if( map_data.tile[i][x2] == POWER_TILE ) power_appeared = true ;
					else if( map_data.tile[i][x2] == END_POINT_TILE ) end_point_appeared = true ;
				}
				else if( map_data.tile[i][x2] != BLANK_TILE ) not_blank_tile = true ;
			}

			if( not_blank_tile == true ) 
			{
				delta_x = 0 ;
			}
			else if( heart_appeared == true || power_appeared == true || end_point_appeared == true )   
			{
				for( int i = y1 ; i <= y2 ; i ++ ) map_data.tile[i][x2] = BLANK_TILE ;

				if( heart_appeared == true ) increaseHeart() ;
				if( power_appeared == true ) increasePower() ;
				if( end_point_appeared == true ) endMap() ;
			}
		}
		else if( delta_x < 0 )
		{
			bool not_blank_tile = false ;
			bool heart_appeared = false ;
			bool power_appeared = false ;
			bool end_point_appeared = false ;

			for( int i = y1 ; i <= y2 ; i ++ ) 
			{
				if( map_data.tile[i][x1] == HEART_TILE || map_data.tile[i][x1] == POWER_TILE || map_data.tile[i][x1] == END_POINT_TILE )
				{
					if( map_data.tile[i][x1] == HEART_TILE ) heart_appeared = true ;
					else if( map_data.tile[i][x1] == POWER_TILE ) power_appeared = true ;
					else if( map_data.tile[i][x1] == END_POINT_TILE ) end_point_appeared = true ;
				}
				else if( map_data.tile[i][x1] != BLANK_TILE ) not_blank_tile = true ;
			}

			if( not_blank_tile == true ) 
			{
				delta_x = 0 ;
			}
			else if( heart_appeared == true || power_appeared == true || end_point_appeared == true )   
			{
				for( int i = y1 ; i <= y2 ; i ++ ) map_data.tile[i][x1] = BLANK_TILE ;

				if( heart_appeared == true ) increaseHeart() ;
				if( power_appeared == true ) increasePower() ;
				if( end_point_appeared == true ) endMap() ;
			}
		}
	}

	// Check Vertical

	x1 = ( x_pos ) / TILE_SIZE ;
	x2 = ( x_pos + width_frame ) / TILE_SIZE ;

	y1 = ( y_pos + delta_y ) / TILE_SIZE ;
	y2 = ( y_pos + delta_y + height_frame - EPSILON ) / TILE_SIZE ;

	if( x1 >= 0 && x1 <= MAX_MAP_X_BLOCK && y1 >= 0 && y1 <= MAX_MAP_Y_BLOCK )
	{
		if( delta_y > 0 ) 
		{
			bool not_blank_tile = false ;
			bool heart_appeared = false ;
			bool power_appeared = false ;
			bool end_point_appeared = false ;

			for( int i = x1 ; i <= x2 ; i ++ ) 
			{
				if( map_data.tile[y2][i] == HEART_TILE || map_data.tile[y2][i] == POWER_TILE || map_data.tile[y2][i] == END_POINT_TILE )
				{
					if( map_data.tile[y2][i] == HEART_TILE ) heart_appeared = true ;
					else if( map_data.tile[y2][i] == POWER_TILE ) power_appeared = true ;
					else if( map_data.tile[y2][i] == END_POINT_TILE ) end_point_appeared = true ;
				}
				else if( map_data.tile[y2][i] != BLANK_TILE ) not_blank_tile = true ;
			}

			if( not_blank_tile == true ) 
			{
				delta_y = 0 ;
			}
			else if( heart_appeared == true || power_appeared == true || end_point_appeared == true )   
			{
				for( int i = x1 ; i <= x2 ; i ++ ) map_data.tile[y2][i] = BLANK_TILE ;

				if( heart_appeared == true ) increaseHeart() ;
				if( power_appeared == true ) increasePower() ;
				if( end_point_appeared == true ) endMap() ;
			}
		}
		else if( delta_y < 0 )
		{
			bool not_blank_tile = false ;
			bool heart_appeared = false ;
			bool power_appeared = false ;
			bool end_point_appeared = false ;

			for( int i = x1 ; i <= x2 ; i ++ ) 
			{
				if( map_data.tile[y1][i] == HEART_TILE || map_data.tile[y1][i] == POWER_TILE || map_data.tile[y1][i] == END_POINT_TILE )
				{
					if( map_data.tile[y1][i] == HEART_TILE ) heart_appeared = true ;
					else if( map_data.tile[y1][i] == POWER_TILE ) power_appeared = true ;
					else if( map_data.tile[y1][i] == END_POINT_TILE ) end_point_appeared = true ;
				}
				else if( map_data.tile[y1][i] != BLANK_TILE ) not_blank_tile = true ;
			}

			if( not_blank_tile == true ) 
			{
				delta_y = 0 ;
			}
			else if( heart_appeared == true || power_appeared == true || end_point_appeared == true )   
			{
				for( int i = x1 ; i <= x2 ; i ++ ) map_data.tile[y1][i] = BLANK_TILE ;

				if( heart_appeared == true ) increaseHeart() ;
				if( power_appeared == true ) increasePower() ;
				if( end_point_appeared == true ) endMap() ;
			}
		}
	}

	x_pos += delta_x ;
	y_pos += delta_y ;

	delta_x = 0 ;
	delta_y = 0 ;

	if( x_pos < 0 ) 
	{
		x_pos = 0 ;
	}
	else if( x_pos + width_frame > map_data.max_x ) 
	{
		x_pos = map_data.max_x - width_frame - EPSILON ;
	}

	if( y_pos < 0 ) 
	{
		y_pos = 0 ;
	}
	else if( y_pos + height_frame > map_data.max_y ) 
	{
		y_pos = map_data.max_y - height_frame - EPSILON ;
	}

	real_pos_x = x_pos ;
	real_pos_y = y_pos ;
}



// Load Bottom Sprites
bool BottomOfCharacter::loadSprites( SDL_Renderer* des ) 
{
	bool successLoadSprites = loadImage( "media//image//bb_8//running_right.png" , des ) ;

	if( successLoadSprites == false ) 
	{
		printf( "Can't load BB-8 bottom sprites\n" ) ;
	}

	return successLoadSprites ;
}

// Showing Running Character
void BottomOfCharacter::show( SDL_Renderer* des ) 
{
	if( is_running == true )
	{
		bot_curr_frame ++ ;
		bot_curr_frame %= CHARACTER_FRAME ;
	}

	oRect.x = x_pos - map_screen_x ;
	oRect.y = y_pos - map_screen_y ;

	SDL_Rect* current_clip = &frame_clip[bot_curr_frame] ;

	SDL_Rect renderQuad = { oRect.x , oRect.y , frame_clip[bot_curr_frame].w , frame_clip[bot_curr_frame].h } ;

	SDL_RendererFlip flip = SDL_FLIP_NONE ;
	SDL_Point* center = NULL ;

	double degrees = 0 ;

	degrees = last_bot_status * 45 ;

	SDL_RenderCopyEx( des , oTexture , current_clip , &renderQuad , degrees , center , flip ) ;

	makeHealthBar( des ) ;
}

// Input Action for Bottom of BB-8
void BottomOfCharacter::inputAction( SDL_Event* events )
{
	if( events->type == SDL_KEYDOWN )
	{
		switch ( events->key.keysym.sym )
		{
		case SDLK_w : 
			{
				bot_input.up = 1 ;
				bot_input.down = 0 ;
			}
			break ;

		case SDLK_s : 
			{
				bot_input.down = 1 ;
				bot_input.up = 0 ;
			}
			break ;
		
		case SDLK_a : 
			{
				bot_input.left = 1 ;
				bot_input.right = 0 ;
			}
			break ;

		case SDLK_d : 
			{
				bot_input.right = 1 ;
				bot_input.left = 0 ;
			}
			break ;

		default:
			break ;
		}
	}
	else if( events->type == SDL_KEYUP ) 
	{
		switch ( events->key.keysym.sym )
		{
		case SDLK_w : 
			{
				bot_input.up = 0 ;
			}
			break ;

		case SDLK_s : 
			{
				bot_input.down = 0 ;
			}
			break ;
		
		case SDLK_a : 
			{
				bot_input.left = 0 ;
			}
			break ;

		case SDLK_d : 
			{
				bot_input.right = 0 ;
			}
			break ;

		default:
			break ;
		}
	}

	if( bot_input.up == 1 ) bot_status = UP_ ;
	if( bot_input.down == 1 ) bot_status = DOWN_ ;
	if( bot_input.left == 1 ) bot_status = LEFT_ ;
	if( bot_input.right == 1 ) bot_status = RIGHT_ ;
	if( bot_input.up == 1 && bot_input.left == 1 ) bot_status = UP_LEFT_ ;
	if( bot_input.up == 1 && bot_input.right == 1 ) bot_status = UP_RIGHT_ ;
	if( bot_input.down == 1 && bot_input.left == 1 ) bot_status = DOWN_LEFT_ ;
	if( bot_input.down == 1 && bot_input.right == 1 ) bot_status = DOWN_RIGHT_ ;

	if( bot_input.up == 0
		&& bot_input.down == 0 
		&& bot_input.left == 0 
		&& bot_input.right == 0 ) bot_status = UNKNOWN_ ;

	if( bot_status != UNKNOWN_ ) is_running = true ;
	else is_running = false ;

	if( bot_status != UNKNOWN_ ) last_bot_status = bot_status ;
}

// Handling Heart And Power Count 
void BottomOfCharacter::increaseHeart() 
{
	curr_health += CHARACTER_GAIN_HEALTH_POINT_PER_HEART ;

	curr_health = min( curr_health , max_health ) ;

	GAME_POINT += HEART_POINT ;
}

void BottomOfCharacter::increasePower() 
{
	power_count ++ ;

	power_count = min( power_count , 3 ) ;

	POWER_LEVEL = power_count ;

	CHARACTER_BULLET_ATK = CHARACTER_BULLET_START_ATK * POWER_LEVEL ;

	GAME_POINT += POWER_POINT ;
}

// Meet End Point And End Map
void BottomOfCharacter::endMap()
{
	meet_end_point = true ;

	GAME_POINT += LEVEL_POINT ;
}


// Get Power Count
int BottomOfCharacter::getPowerCount() const 
{
	return power_count ;
}

// Get Alive Status
bool BottomOfCharacter::getAliveStatus() const 
{
	return is_alive ;
}

// Get Meet End Point Status
bool BottomOfCharacter::isMeetEndPoint() const 
{
	return meet_end_point ;
}

void BottomOfCharacter::beingAttacked( const int& temp_health ) 
{
	changeHealth( -temp_health ) ;

	if( curr_health <= 0 )  is_alive = false ;
}

// Make Health Bar
void BottomOfCharacter::makeHealthBar( SDL_Renderer* des ) 
{
	health_bar.loadImageHealthBar( "media//image//health_bar//Character_HP_bar_outline.png" , 
								   "media//image//health_bar//Character_HP_bar_inside.png" , des ) ;

	health_bar.loadImageLine( "media//image//health_bar//Character_HP_bar_big_line.png" , 
							  "media//image//health_bar//Character_HP_bar_small_line.png" , des ) ;

	health_bar.setPos( oRect.x , oRect.y - HEALTH_BAR_DISTANCE_FROM_CHARACTER ) ;
	health_bar.setHealthPoint( max_health , curr_health ) ;
	health_bar.setLinePos( CHARACTER_HP_LINE_START_POS_X , CHARACTER_HP_LINE_LENGHT ) ;

	health_bar.showWithLine( des ) ;
}


// BB-8 TOP **********************************************************************************************************

TopOfCharacter::TopOfCharacter()
{
	x_pos = 0 ;
	y_pos = 0 ;

	top_status = UNDETERMINED_ ;
}

TopOfCharacter::~TopOfCharacter()
{

}


// Get Position Of Character's Head
double TopOfCharacter::getPosX() 
{
	return x_pos ;
}

double TopOfCharacter::getPosY() 
{
	return y_pos ;
}

// Set Top To Body Position

void TopOfCharacter::setPos( int point_x , int point_y )
{
	x_pos = point_x ;
	y_pos = point_y ;
}


// Showing BB-8 head

void TopOfCharacter::show( SDL_Renderer* des , SDL_Rect character_rect ) 
{
	oRect.x = character_rect.x ;
	oRect.y = character_rect.y ;

	SDL_Rect current_clip = { 0 , 0 , width_frame , height_frame } ;

	SDL_Rect renderQuad = { oRect.x , oRect.y , width_frame , height_frame } ;

	SDL_RendererFlip flip = SDL_FLIP_NONE ;
	SDL_Point* center = NULL ;

	calculateCenterPoint() ;

	double degrees = calculateAngle() ;

	SDL_RenderCopyEx( des , oTexture , &current_clip , &renderQuad , degrees , center , flip ) ;
}

// Input Action for Top of BB-8
void TopOfCharacter::inputAction( SDL_Event* events , SDL_Renderer* screen , const int& power_count , const int& map_start_x , const int& map_start_y ) 
{
	if( events->type == SDL_MOUSEMOTION || events->type == SDL_MOUSEBUTTONDOWN || events->type == SDL_MOUSEBUTTONUP )
    {
        // Get Mouse Position
        SDL_GetMouseState( &mouse_pos_x , &mouse_pos_y ) ;

		if( events->type == SDL_MOUSEBUTTONDOWN ) 
		{
			if( events->button.button == SDL_BUTTON_LEFT ) 
			{
				BulletObject* bullet = new BulletObject() ;

				if( power_count == 1 ) bullet->loadImage( "media//image//bb_8//BB_8_bullet_1.png" , screen ) ;
				else if( power_count == 2 ) bullet->loadImage( "media//image//bb_8//BB_8_bullet_2.png" , screen ) ;
				else if( power_count == 3 ) bullet->loadImage( "media//image//bb_8//BB_8_bullet_3.png" , screen ) ;

				bullet->setBulletAngle( calculateAngle() ) ;
				bullet->calcBulletDelta( CHARACTER_BULLET_SPEED ) ;
				bullet->setStatus( true ) ;

				double temp_x = bullet->getXDelta() * bullet->getFrameWidth() / CHARACTER_BULLET_SPEED ; 
				double temp_y = bullet->getYDelta() * bullet->getFrameWidth() / CHARACTER_BULLET_SPEED ;

				bullet->setPos( map_start_x + this->center_x - ( bullet->getFrameWidth() / 2 ) + temp_x , 
								map_start_y + this->center_y - ( bullet->getFrameHeight() / 2 ) + temp_y ) ; 

				bullet->setUpHPAndPos( CHARACTER_BULLET_ATK , CHARACTER_BULLET_ATK ) ;

				bullet->loadSound( "media//audio//charracter_shooting.wav" ) ;

				if( bullet->getSoundStatus() == false ) bullet->playSound() ;

				bullet_list.push_back( bullet ) ;
			}
		}
	}
}

// Calculate Angle Between Center Of Character And Mouse Pointer

double TopOfCharacter::calculateAngle() 
{
	double temp_x = oRect.x + oRect.w ;
	double temp_y = oRect.y + ( oRect.h / 2 ) ;

	return calcAngleFromThreePoint( Point( center_x , center_y ) , Point( temp_x , temp_y ) , Point( mouse_pos_x , mouse_pos_y ) ) ;
}

// Set Bullet List
void TopOfCharacter::setBulletList( std::vector < BulletObject* > bullet_list_temp ) 
{
	bullet_list = bullet_list_temp ;
}

	
// Get Bullet List
std::vector < BulletObject* > TopOfCharacter::getBulletList() const 
{
	return bullet_list ;
}

// Check Bullet List And Shoot
void TopOfCharacter::handleBullet( SDL_Renderer* des , Map& map_data ) 
{
	int map_x = map_data.start_x ;
	int map_y = map_data.start_y ;

	for( int i = 0 ; i < bullet_list.size() ; i ++ )
	{
		BulletObject* bullet = bullet_list.at( i ) ;

		if( bullet != NULL ) 
		{
			if( bullet->getStatus() == true ) 
			{
				bullet->setMapXY( map_x , map_y ) ;
				bullet->moveTheBullet( map_data , SCREEN_WIDTH , SCREEN_HEIGHT ) ;
				bullet->renderFlip( des , NULL , bullet->getBulletAngle() ) ;
			}
			else
			{
				bullet_list.erase( bullet_list.begin() + i ) ;
				if( bullet != NULL ) 
				{
					delete bullet ;
					bullet = NULL ;
				}
			}
		}
	}
}
