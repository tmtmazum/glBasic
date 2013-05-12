#include "../headers/Draw.h"
#include "../headers/PosManager.h"

#include <cassert>
#include <GL/glut.h>

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

void Draw::Generic( PosManager& PM )
{
    assert( PM.isDrawReady() );
    Generic( PM.getType() , PM.getOutput() );
}
/*
void Draw::Generic( PosManager PM )
{
    assert( PM.isDrawReady() );
    Generic( PM.getType() , PM.getOutput() );
}*/

void Draw::CubeLP( float length, PosXYZ position, ColorRGBA C )
{
    PosXYZ& cm = position;
    float& len = length;
    
	C.get();
    	glBegin(GL_POLYGON);
	    glVertex3f( cm.X + len, cm.Y + len, cm.Z + len);
	    glVertex3f( cm.X + len, cm.Y - len, cm.Z + len);
	    glVertex3f( cm.X - len, cm.Y - len, cm.Z + len);
	    glVertex3f( cm.X - len, cm.Y + len, cm.Z + len);
	glEnd();
	
	glBegin(GL_POLYGON);
	    glVertex3f( cm.X + len, cm.Y + len, cm.Z - len);
	    glVertex3f( cm.X + len, cm.Y - len, cm.Z - len);
	    glVertex3f( cm.X - len, cm.Y - len, cm.Z - len);
	    glVertex3f( cm.X - len, cm.Y + len, cm.Z - len);
	glEnd();
	
	glBegin(GL_POLYGON);
	    glVertex3f( cm.X + len, cm.Y + len, cm.Z + len);
	    glVertex3f( cm.X + len, cm.Y - len, cm.Z + len);
	    glVertex3f( cm.X + len, cm.Y - len, cm.Z - len);
	    glVertex3f( cm.X + len, cm.Y + len, cm.Z - len);
	glEnd();
	
	glBegin(GL_POLYGON);
	    glVertex3f( cm.X - len, cm.Y + len, cm.Z + len);
	    glVertex3f( cm.X - len, cm.Y - len, cm.Z + len);
	    glVertex3f( cm.X - len, cm.Y - len, cm.Z - len);
	    glVertex3f( cm.X - len, cm.Y + len, cm.Z - len);
	glEnd();
	
	glBegin(GL_POLYGON);
	    glVertex3f( cm.X + len, cm.Y + len, cm.Z + len);
	    glVertex3f( cm.X - len, cm.Y + len, cm.Z + len);
	    glVertex3f( cm.X - len, cm.Y + len, cm.Z - len);
	    glVertex3f( cm.X + len, cm.Y + len, cm.Z - len);
	glEnd();
	
	glBegin(GL_POLYGON);
	    glVertex3f( cm.X + len, cm.Y - len, cm.Z + len);
	    glVertex3f( cm.X - len, cm.Y - len, cm.Z + len);
	    glVertex3f( cm.X - len, cm.Y - len, cm.Z - len);
	    glVertex3f( cm.X + len, cm.Y - len, cm.Z - len);
	glEnd();
}
