
#include "stdafx.h"
#include "TextObject.h"

TextObject::TextObject() 
{
	text_color.r = 255 ;
	text_color.g = 255 ;
	text_color.b = 255 ;

	oTexture = NULL ;
}

TextObject::~TextObject() 
{
	free() ;
}

// Free
void TextObject::free() 
{
	if( oTexture != NULL ) 
	{
		SDL_DestroyTexture( oTexture ) ;

		oTexture = NULL ;
	}
}

// Load Texture
bool TextObject::loadRenderText( TTF_Font* font , SDL_Renderer* screen ) 
{
	SDL_Surface* text_surface = TTF_RenderText_Solid( font , text_val.c_str() , text_color ) ;

	if( text_surface != NULL )
	{
		oTexture = SDL_CreateTextureFromSurface( screen , text_surface ) ;
		text_width = text_surface->w ;
		text_height = text_surface->h ;

		SDL_FreeSurface( text_surface ) ;
	}
	else 
	{
		printf( "Can't create Text Surface\n" ) ;

		return false ;
	}

	if( oTexture != NULL )
	{
		return true ;
	}
	else 
	{
		printf( "Can't create Text Texture\n" ) ;

		return false ;
	}
}

// Set Color For Text
void TextObject::setColor( Uint8 temp_R , Uint8 temp_G , Uint8 temp_B ) 
{
	text_color.r = temp_R ;
	text_color.g = temp_G ;
	text_color.b = temp_B ;
}

// Get Text Size
int TextObject::getWidth() const 
{
	return text_width ;
}

int TextObject::getHeight() const 
{
	return text_height ;
}

// Set Text Value
void TextObject::setText( const std::string& temp_text ) 
{
	text_val = temp_text ;
}

// Get Text Value 
std::string TextObject::getText() const 
{
	return text_val ;
}

// Show Text 
void TextObject::show( SDL_Renderer* screen , int temp_x , int temp_y ) 
{
	SDL_Rect* clip = NULL ;
	SDL_Rect renderQuad = { temp_x , temp_y , text_width , text_height } ;

	SDL_RenderCopy( screen , oTexture , clip , &renderQuad ) ;
}
