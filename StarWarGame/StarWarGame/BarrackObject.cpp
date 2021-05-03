
#include "stdafx.h"
#include "BarrackObject.h"

#include "InfoGame.h"
#include "InfoBarrack.h"

// BARRACK OBJECT***********************************************************************************************

BarrackObject::BarrackObject() 
{
	pos_x = 0 ;
	pos_y = 0 ;

	map_x = 0 ;
	map_y = 0 ;

	is_active = false ;

	is_died = false ;

	curr_frame = 0 ;

	barrack_type = BLANK_BARRACK ;
}

BarrackObject::~BarrackObject() 
{

}

// Get Barrack's Position 
double BarrackObject::getPosX() const 
{
	return pos_x ;
}

double BarrackObject::getPosY() const 
{
	return pos_y ;
}

// Set Barrack's Position
void BarrackObject::setPos( const double& temp_x , const double& temp_y ) 
{
	pos_x = temp_x ;
	pos_y = temp_y ;

	real_pos_x = temp_x ;
	real_pos_y = temp_y ;
}

// Get Barrack's Active Status
bool BarrackObject::isActive() const 
{
	return is_active ;
}

bool BarrackObject::isDied() const 
{
	return is_died ;
}

// Set Barrack's Active Status 
void BarrackObject::setActiveStatus( bool temp_bool ) 
{
	is_active = temp_bool ;
}

// Set Barrack's Position On Map
void BarrackObject::setMapXY( const int& temp_x , const int& temp_y ) 
{
	map_x = temp_x ;
	map_y = temp_y ;
}

// Get Type Of Barrack
BarrackType BarrackObject::getBarrackType() const 
{
	return barrack_type ;
}

// Set Type Of Barrack
void BarrackObject::setBarrackType( const BarrackType& temp_type ) 
{
	barrack_type = temp_type ;
}

// Make Barracks Work
void BarrackObject::doBarrack( SDL_Renderer* screen , const int& number_of_ticks , Map& map_data , const double& target_pos_x , const double& target_pos_y ) 
{
	if( barrack_type == CREEP_BARRACK ) doCreepBarrack( screen , number_of_ticks , map_data , target_pos_x , target_pos_y ) ;
	else if( barrack_type == SHOOTING_BARRACK ) doShootingBarrack( screen , number_of_ticks , map_data ) ;
}


// Barracks Being Attacked
void BarrackObject::beingAttacked( const int& temp_health ) 
{
	changeHealth( -temp_health ) ;

	if( curr_health <= 0 ) 
	{
		is_active = false ;
		is_died = true ;

		GAME_POINT += BARRACK_KILLED_POINT ;
	}
}

// Make Health Bar
void BarrackObject::makeHealthBar( SDL_Renderer* des ) 
{
	health_bar.loadImageHealthBar( "media//image//health_bar//Barrack_HP_bar_outline.png" , 
								   "media//image//health_bar//Barrack_HP_bar_inside.png" , des ) ;

	health_bar.loadImageLine( "media//image//health_bar//Barrack_HP_bar_big_line.png" , 
							  "media//image//health_bar//Barrack_HP_bar_small_line.png" , des ) ;

	health_bar.setPos( oRect.x , oRect.y - HEALTH_BAR_DISTANCE_FROM_BARRACK ) ;
	health_bar.setHealthPoint( max_health , curr_health ) ;
	health_bar.setLinePos( BARRACK_HP_LINE_START_POS_X , BARRACK_HP_LINE_LENGHT ) ;

	health_bar.showWithLine( des ) ;
}

// SHOOTING BARRACK *****************************************

// Showing Barrack
void BarrackObject::showShootingBarrack( SDL_Renderer* des ) 
{
	if( pos_x >= ( map_x - TILE_SIZE ) && pos_x <= ( map_x + SCREEN_WIDTH ) &&
		pos_y >= ( map_y - TILE_SIZE ) && pos_y <= ( map_y + SCREEN_HEIGHT ) ) is_active = true ;
	else is_active = false ;

	if( is_active == true ) 
	{
		oRect.x = pos_x - map_x ;
		oRect.y = pos_y - map_y ;

		curr_frame ++ ;

		if( curr_frame >= BARRACK_FRAME ) 
		{
			curr_frame = 0 ;
		}

		SDL_Rect* current_clip = &frame_clip[curr_frame] ; 
		SDL_Rect renderQuad = { oRect.x , oRect.y , current_clip->w , current_clip->h } ;

		SDL_RenderCopy( des , oTexture , current_clip , &renderQuad ) ;

		makeHealthBar( des ) ;
	}
}

// Set Bullet List
void BarrackObject::setBulletList( std::vector < BulletObject* > bullet_list_temp ) 
{
	bullet_list = bullet_list_temp ;
}

	
// Get Bullet List
std::vector < BulletObject* > BarrackObject::getBulletList() const 
{
	return bullet_list ;
}

// Check Bullet List And Shoot
void BarrackObject::showBullet( SDL_Renderer* des , Map& map_data ) 
{
	for( int i = 0 ; i < bullet_list.size() ; i ++ )
	{
		BulletObject* bullet = bullet_list.at( i ) ;

		if( bullet != NULL ) 
		{
			if( bullet->getStatus() == true ) 
			{
				bullet->setMapXY( map_x , map_y ) ;
				bullet->moveTheBullet( map_data , SCREEN_WIDTH , SCREEN_HEIGHT ) ;
				bullet->render( des ) ;
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

// Set Up A Bullet 
void BarrackObject::setUpBullet( BulletObject* bullet , SDL_Renderer* screen , const double& shooting_angle ) 
{
	if( bullet != NULL )
	{
		bullet->loadImage( "media//image//threats//barrack_bullet.png" , screen ) ;

		calculateCenterPoint() ;

		bullet->setBulletAngle( shooting_angle ) ;
		bullet->calcBulletDelta( SHOOTING_BARRACK_BULLET_SPEED ) ;
		bullet->setStatus( true ) ;

		double temp_x = bullet->getXDelta() * bullet->getFrameWidth() / SHOOTING_BARRACK_BULLET_SPEED ; 
		double temp_y = bullet->getYDelta() * bullet->getFrameWidth() / SHOOTING_BARRACK_BULLET_SPEED ;

		bullet->setPos( map_x + center_x - ( bullet->getFrameWidth() / 2 ) + temp_x , 
						map_y + center_y - ( bullet->getFrameHeight() / 2 ) + temp_y ) ; 

		bullet->setUpHPAndPos( SHOOTING_BARRACK_BULLET_ATK , SHOOTING_BARRACK_BULLET_ATK ) ;

		bullet_list.push_back( bullet ) ;
	}
}

// Handling Shooting Action Of Barracks

void BarrackObject::doShootingBarrack( SDL_Renderer* screen , const int& number_of_ticks , Map& map_data ) 
{
	if( is_active == true && ( number_of_ticks % NUMBER_OF_TICKS_PER_TURN_SHOOTING_BARRACK == 0 ) ) 
	{
		int random_variable_angle = RandomNumber( 0 , 359 ) ;

		for( int i = 0 ; i < 360 ; i += ( 360 / NUMBER_OF_BULLET_IN_ONE_TURN ) ) // 360 DEGREES
		{
			BulletObject* p_bullet = new BulletObject() ;

			int angle_temp = ( i + random_variable_angle ) % 360 ;

			setUpBullet( p_bullet , screen , angle_temp ) ;
		}
	}

	showBullet( screen , map_data ) ;
}


// CREEP BARRACK *****************************************

// Showing Creep Barrack
void BarrackObject::showCreepBarrack( SDL_Renderer* des , const double& target_pos_x , const double& target_pos_y ) 
{
	if( pos_x >= ( map_x - TILE_SIZE ) && pos_x <= ( map_x + SCREEN_WIDTH ) &&
		pos_y >= ( map_y - TILE_SIZE ) && pos_y <= ( map_y + SCREEN_HEIGHT ) ) is_active = true ;
	else is_active = false ;

	if( is_active == true ) 
	{
		oRect.x = pos_x - map_x ;
		oRect.y = pos_y - map_y ;

		curr_frame ++ ;

		if( curr_frame >= BARRACK_FRAME ) 
		{
			curr_frame = 0 ;
		}

		SDL_Rect* current_clip = &frame_clip[curr_frame] ; 
		SDL_Rect renderQuad = { oRect.x , oRect.y , current_clip->w , current_clip->h } ;

		SDL_RendererFlip flip = SDL_FLIP_NONE ;
		SDL_Point* center = NULL ;

		double temp_angle = calculateAngle( target_pos_x , target_pos_y ) ;

		SDL_RenderCopyEx( des , oTexture , current_clip , &renderQuad , temp_angle , center , flip ) ;

		makeHealthBar( des ) ;
	}
}

// Calculate Angle Creep Barrack's Direction
double BarrackObject::calculateAngle( const double& target_pos_x , const double& target_pos_y ) 
{
	double temp_x = pos_x + width_frame ;
	double temp_y = pos_y + ( height_frame / 2 ) ;

	double center_x_temp = pos_x + ( width_frame / 2 ) ;
	double center_y_temp = pos_y + ( height_frame / 2 ) ;

	return calcAngleFromThreePoint( Point( center_x_temp , center_y_temp ) , Point( temp_x , temp_y ) , Point( target_pos_x , target_pos_y ) ) ;
}

// Set Creep List
void BarrackObject::setCreeptList( std::vector < CreepObject* > creep_list_temp ) 
{
	creep_list = creep_list_temp ;
}

// Get Creep List
std::vector < CreepObject* > BarrackObject::getCreepList() const 
{
	return creep_list ;
}

// Check Creep List And Shoot
void BarrackObject::showCreep( SDL_Renderer* des , Map& map_data , const double& target_pos_x , const double& target_pos_y ) 
{
	for( int i = 0 ; i < creep_list.size() ; i ++ )
	{
		CreepObject* creep = creep_list.at( i ) ;

		if( creep != NULL ) 
		{
			if( creep->getStatus() == true ) 
			{
				creep->setMapXY( map_x , map_y ) ;
				creep->handleCreepMoving( map_data , target_pos_x , target_pos_y ) ;
				creep->show( des ) ;
			}
			else
			{
				explode_list.push_back( createCreepExplode( des , creep->getPosX() , creep->getPosY() ) ) ;

				creep_list.erase( creep_list.begin() + i ) ;
				if( creep != NULL ) 
				{
					delete creep ;
					creep = NULL ;
				}
			}
		}
	}

	// Draw Creeps Explode
		for( int i = 0 ; i < explode_list.size() ; i ++ ) 
		{
			ExplodeObject* t_explode = explode_list.at( i ) ;

			if( t_explode->getStatus() == true ) 
			{
				t_explode->show( des , map_data.start_x , map_data.start_y ) ;

				if( t_explode->getSoundStatus() == false ) t_explode->playSound() ;
			}
			else 
			{
				explode_list.erase( explode_list.begin() + i ) ;

				if( t_explode != NULL ) 
				{
					delete t_explode ;
					t_explode = NULL ;
				}
			}
		}
}

// Spawn A Creep 
void BarrackObject::spawnCreep( CreepObject* creep , SDL_Renderer* screen ) 
{
	if( creep != NULL )
	{
		creep->loadImage( "media//image//threats//creep.png" , screen ) ;
		creep->setClipSize( CREEP_FRAME ) ;

		calculateCenterPoint() ;

		creep->setStatus( true ) ;

		creep->setPos( map_x + center_x , map_y + center_y ) ; 

		creep->setUpHPAndPos( CREEP_MAXIMUM_HEALTH_POINT , CREEP_MAXIMUM_HEALTH_POINT ) ;

		creep_list.push_back( creep ) ;
	}
}

// Handling Creep Barracks
void BarrackObject::doCreepBarrack( SDL_Renderer* screen , const int& number_of_ticks , Map& map_data , const double& target_pos_x , const double& target_pos_y ) 
{
	if( is_active == true && ( number_of_ticks % NUMBER_OF_TICKS_PER_TURN_CREEP_BARRACK == 0 ) ) 
	{
		CreepObject* p_creep = new CreepObject() ;

		spawnCreep( p_creep , screen ) ;
	}

	showCreep( screen , map_data , target_pos_x , target_pos_y ) ;
}

// Create Creep Explode
ExplodeObject* BarrackObject::createCreepExplode( SDL_Renderer* des , const int& temp_x , const int& temp_y ) 
{
	ExplodeObject* c_explode = new ExplodeObject ;

	c_explode->loadImage( "media//image//threats//creep_explode.png" , des ) ;
	c_explode->setMaxFrame( CREEP_EXPLODING_FRAME ) ;
	c_explode->setClipSize( CREEP_EXPLODING_FRAME ) ;
	c_explode->setRect( temp_x , temp_y ) ;
	c_explode->loadSound( "media//audio//creep_explosion.wav" ) ;

	return c_explode ;
}


