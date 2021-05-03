
#ifndef INFO_GAME_GENERAL_H_
#define INFO_GAME_GENERAL_H_

// Some Math Const
const double PI = 3.1415926535898 ;

// Game 
const std::string GAME_NAME = "Star War Game" ;

// Window 
static SDL_Window* g_window = NULL ;
static SDL_Renderer* g_screen =	NULL ;

// Event
static SDL_Event g_event ;

// Screen 
const int SCREEN_WIDTH = 1280 ;
const int SCREEN_HEIGHT = 720 ;
const int SCREEN_BPP = 32 ;

// Render Draw Color 

const int RENDER_DRAW_COLOR_R = 0xFF ;
const int RENDER_DRAW_COLOR_G = 0xFF ;
const int RENDER_DRAW_COLOR_B = 0xFF ;
const int RENDER_DRAW_COLOR_ALPHA = 0xFF ;

// Color Key
const int COLOR_KEY_R = 170 ;
const int COLOR_KEY_G = 170 ;
const int COLOR_KEY_B = 170 ;

// Game Frame Per Second ( FPS ) 
const int FRAME_PER_SECOND = 30 ;
const int TIME_ONE_FRAME = 1000 / FRAME_PER_SECOND ;

// Game map
const int TILE_SIZE = 50 ;

const int MAX_MAP_X_BLOCK = 55 ;
const int MAX_MAP_Y_BLOCK = 55  ;

const int TILE_TYPE = 20 ;

#define BLANK_TILE 0
#define HEART_TILE 1
#define POWER_TILE 2
#define END_POINT_TILE 19

const int START_POSITION_X = 3 ;
const int START_POSITION_Y = 3 ;

// EPSILION in Calculating
const int EPSILON = 1 ;

// OBJECT
// Number of Maximum Object Sprites Frame 
const int MAX_OBJECT_FRAME = 50 ;

// BACKGROUND
const Uint8 BACKGROUND_ALPHA_CHANGE_IN_ONE_FRAME = 3 ;

// GAME LEVEL

const int START_LEVEL_POINT = 2000 ;

// HUD 
const int HUD_START_X = 339 ;
const int HUD_START_Y = 0 ;
const Uint8 HUD_ALPHA = 230 ;

const int FONT_SIZE = 12 ;

const int LEVEL_TEXT_X = 389 ;
const int LEVEL_TEXT_Y = 18 ;

const int POWER_TEXT_X = 554 ;
const int POWER_TEXT_Y = 18 ;

const int POINT_TEXT_X = 719 ;
const int POINT_TEXT_Y = 18 ;

// MAP
const int SUPPORT_ITEM_SPRITES = 12 ;
const int END_POINT_SPRITES = 16 ;

// CHARACTER 

const int CHARACTER_FRAME = 16 ;

// Character's Movement Speed 
const double MOVEMENT_SPEED = 10 ;
const double MOVEMENT_SPEED_DIAGONALLY = MOVEMENT_SPEED / 1.41421356237 ;

// Character's Health Point 
const int CHARACTER_START_HEALTH_POINT = 1000 ;
const int CHARACTER_INCREASED_HEALTH_POINT_PER_LEVEL = 500 ;

const int CHARACTER_START_GAIN_HEALTH_POINT_PER_HEARTH = 200 ;

// Character's Bullet
const double CHARACTER_BULLET_SPEED = 40 ;

const int CHARACTER_BULLET_START_ATK = 100 ;

// Character's Gain Point By Eating Support
const int HEART_POINT = 100 ;
const int POWER_POINT = 100 ;

// BARRACKS 

const int BARRACK_FRAME = 16 ; // All Barrack's Sprites Must Have Same Number Of Frame

const int BARRACK_EXPLODING_FRAME = 16 ;

const int BARRACK_START_KILLED_POINT = 500 ;

// Shooting Barrack

const int NUMBER_OF_BULLET_IN_ONE_TURN = 10 ;
const int NUMBER_OF_TICKS_PER_TURN_SHOOTING_BARRACK = 45 ;

const int SHOOTING_BARRACK_START_HEALTH_POINT = 500 ;
const int SHOOTING_BARRACK_INCREASED_HEALTH_POINT_PER_LEVER = 200 ;

const double SHOOTING_BARRACK_BULLET_SPEED = 5 ;

const int SHOOTING_BARRACK_BULLET_START_ATK = 100 ;

// Creep Barrack

const int CREEP_FRAME = 8 ;
const int CREEP_EXPLODING_FRAME = 16 ;
const int NUMBER_OF_TICKS_PER_TURN_CREEP_BARRACK = 60 ;

const int CREEP_BARRACK_START_HEALTH_POINT = 700 ;
const int CREEP_BARRACK_INCREASED_HEALTH_POINT_PER_LEVER = 200 ;

const double CREEP_SPEED = 5 ;

const int CREEP_START_HEALTH_POINT = 200 ; // Also Using For Creep Damge

const int CREEP_START_KILLED_POINT = 50 ;

// HEALTH BAR
const int HEALTH_BAR_HP_PER_BIG_LINE = 1000 ;
const int HEALTH_BAR_HP_PER_SMALL_LINE = 250 ; // hp_per_big_ling must divisible for hp_per_small_line

// Get Object HP LINE info from image

// Character
const int HEALTH_BAR_DISTANCE_FROM_CHARACTER = 30 ;
const int CHARACTER_HP_LINE_START_POS_X = 2 ;
const int CHARACTER_HP_LINE_LENGHT = 96 ;

// Barracks
const int HEALTH_BAR_DISTANCE_FROM_BARRACK = 20 ;
const int BARRACK_HP_LINE_START_POS_X = 1 ;
const int BARRACK_HP_LINE_LENGHT = 48 ;

// Creeps
const int HEALTH_BAR_DISTANCE_FROM_CREEP = 20 ;

// Sound
const int MUSIC_VOLUME = 5 ;
const int EXPLOSION_VOLUME = 20 ;
const int BULLET_SHOOTING_VOLUME = 10 ;

// MENU 
const int BUTTON_WIDTH = 300 ;
const int BUTTON_HEIGHT = 100 ;
const int BUTTON_ALPHA = 230 ;

const int BUTTON_FONT_SIZE = 30 ;

const int NEW_GAME_BUTTON_X = 489 ;
const int NEW_GAME_BUTTON_Y = 359 ;
const int NEW_GAME_BUTTON_TEXT_X = 34 ;
const int NEW_GAME_BUTTON_TEXT_Y = 34 ;

const int GUIDE_BUTTON_X = 489 ;
const int GUIDE_BUTTON_Y = 479 ;
const int GUIDE_BUTTON_TEXT_X = 79 ;
const int GUIDE_BUTTON_TEXT_Y = 34 ;

const int EXIT_BUTTON_X = 489 ;
const int EXIT_BUTTON_Y = 599 ;
const int EXIT_BUTTON_TEXT_X = 94 ;
const int EXIT_BUTTON_TEXT_Y = 34 ;

const int MENU_IMAGE_X = 330 ;
const int MENU_IMAGE_Y = 50 ;

// PAUSE TAB

const int PAUSE_TAB_X = 389 ;
const int PAUSE_TAB_Y = 159 ;
const int PAUSE_TAB_ALPHA = 230 ;

const int CONTINUE_BUTTON_X = 489 ;
const int CONTINUE_BUTTON_Y = 234 ;
const int CONTINUE_BUTTON_TEXT_X = 34 ;
const int CONTINUE_BUTTON_TEXT_Y = 34 ;

const int MENU_BUTTON_X = 489 ;
const int MENU_BUTTON_Y = 384 ;
const int MENU_BUTTON_TEXT_X = 94 ;
const int MENU_BUTTON_TEXT_Y = 34 ;

// GUIDE TAB
const int GUIDE_TAB_X = 0 ;
const int GUIDE_TAB_Y = 0 ;

const int BACK_BUTTON_X = 659 ;
const int BACK_BUTTON_Y = 599 ;
const int BACK_BUTTON_TEXT_X = 94 ;
const int BACK_BUTTON_TEXT_Y = 34 ;

// Screen Text 
const int SCREEN_TEXT_FONT_SIZE = 50 ;
const int SCREEN_TEXT_FONT_SIZE_2 = 20 ;
const int SCREEN_TEXT_X = 440 ;
const int SCREEN_TEXT_Y = 310 ;

#endif