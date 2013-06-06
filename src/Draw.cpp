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
    
    // Actual Axis is drawn a bit lower
    // than z=0, so that other objects at
    // 0 appear above grid
    float zUnder = -0.00001;
    
    ColorRGBA G = Colors::Grey;
    G.A = 0.2;
 
    ColorRGBA R = Colors::Red;
    ColorRGBA Gr = Colors::Green;
    ColorRGBA B = Colors::Blue;
    
    glBegin( GL_LINES );
	G.get();		
	for(float i = -1.0; i < 1.0; i += 0.01)
	{
		glVertex3f(i, -1.0, zUnder);
		glVertex3f(i, 1.0, zUnder);
	}
	for(float i = -1.0; i < 1.0; i += 0.01)
	{
		glVertex3f(-1.0, i, zUnder);
		glVertex3f(1.0, i, zUnder);
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
	int draw_type = GL_POLYGON;
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

void Draw::Generic( const WO_SINGLE& WS1 )
{
    bool toggleTranslate = ((WS1.X != 0) || (WS1.Y != 0) || (WS1.Z != 0) );
    bool toggleScale = (WS1.transform.radius != 1);
    bool toggleRotate = false;
    
    PosXYZ P1( WS1.X , WS1.Y , WS1.Z );
	
    if( toggleRotate )
    {
	PosRPT R1( P1 );
	R1.phi += WS1.transform.phi;
	R1.theta += WS1.transform.theta;
	P1 = PosXYZ( R1 );
	/*WS1.X = P1.X;
	WS1.Y = P1.Y;
	WS1.Z = P1.Z;*/
    }
    
    if( toggleTranslate ) glTranslatef( P1.X , P1.Y , P1.Z );
    if( toggleScale ) glScalef( WS1.transform.radius , WS1.transform.radius , WS1.transform.radius );
    
    glRotatef( (angleDEG) angleRAD( WS1.transform.phi ), 0.0, 0.0, 1.0f );
    
    GO_CUBOID* GCx = dynamic_cast<GO_CUBOID*>( WS1.GOx );
    if(GCx != 0) Draw::Generic( *GCx );
    
    // glRotatef( (angleDEG) angleRAD( WS1.transform.phi ), 0.0, 0.0, -1.0f );
    if( toggleScale ) glScalef( 1/WS1.transform.radius , 1/WS1.transform.radius , 1/WS1.transform.radius );
    if( toggleTranslate ) glTranslatef( -P1.X , -P1.Y , -P1.Z );
}

void Draw::Generic( const GO_CUBOID& GC1 )
{
    int draw_type = GL_POLYGON;
    
    if( GC1.enabledFaces & GO_CUBOID::BOTTOM )
    {
	glBegin( draw_type );
	    glVertex3f( + GC1.length, + GC1.width, - GC1.height);
	    glVertex3f( + GC1.length, - GC1.width, - GC1.height);
	    glVertex3f( - GC1.length, - GC1.width, - GC1.height);
	    glVertex3f( - GC1.length, + GC1.width, - GC1.height);
	glEnd();
    }
    
    if( GC1.enabledFaces & GO_CUBOID::LEFT )
    {
	glBegin( draw_type );
	    glColor4f( 1.0f, 0.0f, 0.0f, 0.5f );
	    glVertex3f( -GC1.length, GC1.width, GC1.height);
	    glVertex3f( -GC1.length, - GC1.width, GC1.height);
	    glVertex3f( -GC1.length, -GC1.width, - GC1.height);
	    glVertex3f( -GC1.length, + GC1.width, - GC1.height);
	glEnd();
    }
    
    if( GC1.enabledFaces & GO_CUBOID::BACK )
    {
	glBegin( draw_type );
	    glVertex3f( + GC1.length, - GC1.width,  + GC1.height);
	    glVertex3f( - GC1.length, - GC1.width,  + GC1.height);
	    glVertex3f( - GC1.length, - GC1.width,  - GC1.height);
	    glVertex3f( + GC1.length, - GC1.width,  - GC1.height);
	glEnd();
    }
    
    if( GC1.enabledFaces & GO_CUBOID::TOP )
    {
	glBegin( draw_type );
	    glVertex3f(  + GC1.length,  + GC1.width,  + GC1.height);
	    glVertex3f(  + GC1.length,  - GC1.width,  + GC1.height);
	    glVertex3f(  - GC1.length,  - GC1.width,  + GC1.height);
	    glVertex3f(  - GC1.length,  + GC1.width,  + GC1.height);
	glEnd();
    }
    
    if( GC1.enabledFaces & GO_CUBOID::RIGHT )
    {
	glBegin( draw_type );
	    glVertex3f(  + GC1.length,  + GC1.width,  + GC1.height);
	    glVertex3f(  + GC1.length,  - GC1.width,  + GC1.height);
	    glVertex3f(  + GC1.length,  - GC1.width,  - GC1.height);
	    glVertex3f(  + GC1.length,  + GC1.width,  - GC1.height);
	glEnd();
    }
    
    if( GC1.enabledFaces & GO_CUBOID::FRONT )
    {
	glBegin( draw_type );
	    glVertex3f(  + GC1.length,  + GC1.width,  + GC1.height);
	    glVertex3f(  - GC1.length,  + GC1.width,  + GC1.height);
	    glVertex3f(  - GC1.length,  + GC1.width,  - GC1.height);
	    glVertex3f(  + GC1.length,  + GC1.width,  - GC1.height);
	glEnd();
    }
}