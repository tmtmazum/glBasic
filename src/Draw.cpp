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

void Draw::GridXY()
{
    float indLength = 0.1;
    
    ColorRGBA G = Colors::Grey;
    G.A = 0.2;
 
    ColorRGBA R = Colors::Red;
    ColorRGBA Gr = Colors::Green;
    ColorRGBA B = Colors::Blue;
    
    glBegin( GL_LINES );
	G.get();		
	for(float i = -1.0; i < 1.0; i += 0.01)
	{
		glVertex3f(i, -1.0, 0.0);
		glVertex3f(i, 1.0, 0.0);
	}
	for(float i = -1.0; i < 1.0; i += 0.01)
	{
		glVertex3f(-1.0, i, 0.0);
		glVertex3f(1.0, i, 0.0);
	}
	R.get();
	glVertex3f(indLength, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	Gr.get();
	glVertex3f(0.0, indLength, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	B.get();
	glVertex3f(0.0, 0.0, indLength);
	glVertex3f(0.0, 0.0, 0.0);
    glEnd();
}

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

void Draw::CubeLPM(float length, PosXYZ placement, bool* FaceMatrix)
// FaceMatrix { 0 .. 6 } represents the faces in the direction of
// 			  { -x, -y, -z, x, y, z }
//			  { left, front, bottom, right, back, top }
{
	PosXYZ cm = placement;
	float len = length;
	int draw_type = GL_TRIANGLE_FAN;
	if( FaceMatrix[0] )
	{
		glBegin( draw_type );
		    glVertex3f( cm.X - len, cm.Y + len, cm.Z + len);
		    glVertex3f( cm.X - len, cm.Y - len, cm.Z + len);
		    glVertex3f( cm.X - len, cm.Y - len, cm.Z - len);
		    glVertex3f( cm.X - len, cm.Y + len, cm.Z - len);
		glEnd();
	}
	if( FaceMatrix[1] )
	{
		glBegin( draw_type );
		    glVertex3f( cm.X + len, cm.Y - len, cm.Z + len);
		    glVertex3f( cm.X - len, cm.Y - len, cm.Z + len);
		    glVertex3f( cm.X - len, cm.Y - len, cm.Z - len);
		    glVertex3f( cm.X + len, cm.Y - len, cm.Z - len);
		glEnd();
	}
	if( FaceMatrix[2] )
	{
		glBegin( draw_type );
		    glVertex3f( cm.X + len, cm.Y + len, cm.Z - len);
		    glVertex3f( cm.X + len, cm.Y - len, cm.Z - len);
		    glVertex3f( cm.X - len, cm.Y - len, cm.Z - len);
		    glVertex3f( cm.X - len, cm.Y + len, cm.Z - len);
		glEnd();
	}
	if( FaceMatrix[3] )
	{
		glBegin( draw_type );
		    glVertex3f( cm.X + len, cm.Y + len, cm.Z + len);
		    glVertex3f( cm.X + len, cm.Y - len, cm.Z + len);
		    glVertex3f( cm.X + len, cm.Y - len, cm.Z - len);
		    glVertex3f( cm.X + len, cm.Y + len, cm.Z - len);
		glEnd();
	}
	if( FaceMatrix[4] )
	{
		glBegin( draw_type );
		    glVertex3f( cm.X + len, cm.Y + len, cm.Z + len);
		    glVertex3f( cm.X - len, cm.Y + len, cm.Z + len);
		    glVertex3f( cm.X - len, cm.Y + len, cm.Z - len);
		    glVertex3f( cm.X + len, cm.Y + len, cm.Z - len);
		glEnd();
	}
	if( FaceMatrix[5] )
	{
		glBegin( draw_type );
		    glVertex3f( cm.X + len, cm.Y + len, cm.Z + len);
		    glVertex3f( cm.X + len, cm.Y - len, cm.Z + len);
		    glVertex3f( cm.X - len, cm.Y - len, cm.Z + len);
		    glVertex3f( cm.X - len, cm.Y + len, cm.Z + len);
		glEnd();
	}
}