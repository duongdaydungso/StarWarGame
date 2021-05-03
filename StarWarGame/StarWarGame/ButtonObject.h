
#ifndef BUTTON_OBJECT_H_
#define BUTTON_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "TextObject.h"

class ButtonObject 
{
public:
	ButtonObject() ;
	~ButtonObject() ;

	// Load Button Image And Text
	void loadButton( SDL_Renderer* screen , TTF_Font* temp_font , std::string temp_text ) ;

	// Set Position Of Button
	void setPos( int temp_x , int temp_y , int temp_text_x , int temp_text_y ) ;

	// Set Button Status
	void setButtonIn( bool temp_b ) ;

	// Get Button Status
	bool getButtonIn() const ;

	// Check mouse on Button Or Not
	void checkMouse( int mouse_pos_x , int mouse_pos_y ) ;

	// Show Button
	void show( SDL_Renderer* screen ) ;

private:
	BaseObject button ;
	BaseObject button_entered ;

	TextObject text_on_button ;

	bool focus_in ;

	int pos_x ;
	int pos_y ;

	int pos_text_x ;
	int pos_text_y ;
} ;

#endif	