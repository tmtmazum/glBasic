#include "../headers/Draw.h"
#include <GL/glut.h>
/*
void Draw::Points( std::vector< Pos >& V1 )
{
	glBegin( GL_POINTS );
	for(std::vector< Pos >::iterator it = V1.begin(); it != V1.end(); ++it)
	{
		V1->getColor();
		V1->getVertex();
	}
	glEnd();
}

void Draw::Line( Pos p1, Pos p2 )
{
	glBegin( GL_LINES );
		p1->getColor();
		p1->getVertex();
		
		p2->getColor();
		p2->getVertex();
	glEnd();
}

void Draw::Lines( std::vector< Pos >& V1 )
{
	glBegin( GL_LINES );
	for(std::vector< Pos >::iterator it = V1.begin(); it != V1.end(); ++it)
	{
		V1->getColor();
		V1->getVertex();
	}
	glEnd();
}
*/

// template< typename ty >
void Draw::Generic( int t1, std::vector< Pos* >& V1 )
{
    	glBegin( t1 );
	for(std::vector< Pos* >::iterator it = V1.begin(); it != V1.end(); ++it)
	{
		(*it)->getColor();
		(*it)->getVertex();
	}
	glEnd();
}
