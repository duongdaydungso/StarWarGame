
#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "CommonFunction.h"

class TextObject 
{
public:
	TextObject() ;
	~TextObject() ;

	// Free
	void free() ;

	// Load Texture
	bool loadRenderText( TTF_Font* font , SDL_Renderer* screen ) ;

	// Set Color For Text
	void setColor( Uint8 temp_R , Uint8 temp_G , Uint8 temp_B ) ;

	// Get Text Size
	int getWidth() const ;
	int getHeight() const ;

	// Set Text Value
	void setText( const std::string& temp_text ) ;

	// Get Text Value 
	std::string getText() const ; 

	// Show Text 
	void show( SDL_Renderer* screen , int temp_x , int temp_y ) ;

private:
	// String Value Need To Show
	std::string text_val ;

	// Text Color
	SDL_Color text_color ;

	// Text Texture
	SDL_Texture* oTexture ;

	// Text Size
	int text_width ;
	int text_height ;
} ;

#endif