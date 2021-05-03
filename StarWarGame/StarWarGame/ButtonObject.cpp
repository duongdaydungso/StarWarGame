
#include "stdafx.h"
#include "ButtonObject.h"

ButtonObject::ButtonObject() 
{
	focus_in = false ;

	pos_x = 0 ;
	pos_y = 0 ;

	pos_text_x = 0 ;
	pos_text_y = 0 ;
}

ButtonObject::~ButtonObject()
{

}


// Load Button Image And Text
void ButtonObject::loadButton( SDL_Renderer* screen , TTF_Font* temp_font , std::string temp_text ) 
{
	button.loadImage( "media//image//button.png" , screen ) ;
	button.setBlendMode( SDL_BLENDMODE_BLEND ) ;
	button.setAlpha( BUTTON_ALPHA ) ;

	button_entered.loadImage( "media//image//button_entered.png" , screen ) ;
	button_entered.setBlendMode( SDL_BLENDMODE_BLEND ) ;
	button_entered.setAlpha( BUTTON_ALPHA ) ;

	text_on_button.setText( temp_text ) ;
	text_on_button.setColor( 0 , 0 , 0 ) ; // BLACK COLOR CODE
	text_on_button.loadRenderText( temp_font , screen ) ;
}

// Set Position Of Button
void ButtonObject::setPos( int temp_x , int temp_y , int temp_text_x , int temp_text_y ) 
{
	pos_x = temp_x ;
	pos_y = temp_y ;

	pos_text_x = temp_text_x ;
	pos_text_y = temp_text_y ;
}


// Set Button Status
void ButtonObject::setButtonIn( bool temp_b ) 
{
	focus_in = temp_b ;
}

// Get Button Status
bool ButtonObject::getButtonIn() const 
{
	return focus_in ;
}

// Check mouse on Button Or Not
void ButtonObject::checkMouse( int mouse_pos_x , int mouse_pos_y ) 
{
	if( pos_x < mouse_pos_x && mouse_pos_x < pos_x + BUTTON_WIDTH &&
		pos_y < mouse_pos_y && mouse_pos_y < pos_y + BUTTON_HEIGHT )
	{
		focus_in = true ;
	}
	else 
	{
		focus_in = false ;
	}
}


// Show Button
void ButtonObject::show( SDL_Renderer* screen ) 
{
	button.setRect( pos_x , pos_y ) ;
	button_entered.setRect( pos_x , pos_y ) ;

	if( focus_in == false ) 
	{
		button.render( screen ) ;
	}
	else 
	{
		button_entered.render( screen ) ;
	}

	text_on_button.show( screen , pos_x + pos_text_x , pos_y + pos_text_y ) ;
}
