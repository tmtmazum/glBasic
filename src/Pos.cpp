#include "../headers/Pos.h"
#include "../headers/Color.h"
#include <GL/glut.h>


float root_sum_of_squares( float t1, float t2, float t3 )
{
    return sqrt( pow(t1, 2) + pow(t2, 2) + pow(t3, 2) );
}

void PosXY::getVertex()
{
	glVertex2f( X, Y );
}

PosXY::PosXY(const PosRP& P1)
{
    X = P1.radius * cos( P1.getAngle() );
    Y = P1.radius * sin( P1.getAngle() );
}

PosRP::PosRP(const PosXY& P1) 
{ 
    radius = root_sum_of_squares( P1.X, P1.Y, 0.0f ); 
    angle = atan2( P1.Y, P1.X );
}

void PosRP::getVertex()
{
	glVertex2f( radius * cos( angle ), radius * sin( angle ) );    
}

void PosXYZ::getVertex()
{
	glVertex3f( X, Y, Z );
}
