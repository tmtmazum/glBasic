#include "../headers/Pos.h"
#include "../headers/Color.h"
#include <GL/glut.h>

void PosXY::getVertex()
{
	glVertex2f( X, Y );
}

PosXY(const PosRP& P1)
{
    X = radius * cos( angle );
    Y = radius * sin( angle );
}

PosRP(const PosXY& P1) 
{ 
    radius = root_sum_of_squares( P1.X, P1.Y ); 
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