
#include "stdafx.h" 
#include "CommonFunction.h"

// Random Function
int RandomNumber( int left_number_ , int right_number_ )
{
	int res = rand() % ( right_number_ - left_number_ + 1) + left_number_ ;

	return res ;
}

// Point

Point::Point( double temp_x , double temp_y ) 
{
	x = temp_x ;
	y = temp_y ;
}

Point::~Point() 
{

}


// Length Of Segment From Point P1 To Point P2 

double lengthOfVector( Point P1 , Point P2 ) 
{
	return sqrt( ( P1.x - P2.x ) * ( P1.x - P2.x ) + ( P1.y - P2.y ) * ( P1.y - P2.y ) )  ;
}

// CCW

double ccw( Point P1 , Point P2 , Point P3 )
{
	double x2 = P2.x - P1.x ;
	double y2 = P2.y - P1.y ;

	double x3 = P3.x - P1.x ;
	double y3 = P3.y - P1.y ;

	return x2 * y3 - x3 * y2 ;
}


// Calculate Angle From 3 Point

double calcAngleFromThreePoint( Point P1 , Point P2 , Point P3 ) 
{
	double p1p2 = lengthOfVector( P1 , P2 ) ;
	double p1p3 = lengthOfVector( P1 , P3 ) ;
	double p2p3 = lengthOfVector( P2 , P3 ) ;

	double result = acos( ( p1p2 * p1p2 + p1p3 * p1p3 - p2p3 * p2p3 ) / ( 2 * p1p2 * p1p3 ) ) ;

	result = result * 180 / PI ;

	if( ccw( P1 , P2 , P3 ) < 0 ) result = -result ;

	return result ;
}

// Check Collisions

bool checkCollision( const double& a_x , const double& a_y , const double& a_radius , 
					 const double& b_x , const double& b_y , const double& b_radius ) 
{
	double length_a_to_b = lengthOfVector( Point( a_x , a_y ) , Point( b_x , b_y ) ) ;

	if( length_a_to_b <= ( a_radius + b_radius ) ) return true ;

	return false ;
}
