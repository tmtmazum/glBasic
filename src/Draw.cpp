#include "../headers/Draw.h"
#include "../headers/PosManager.h"
#include "../headers/DEBUG.h"

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
	for(float i = -1.0; i < 1.0; i += 0.1)
	{
		glVertex3f(i, -1.0, zUnder);
		glVertex3f(i, 1.0, zUnder);
	}
	for(float i = -1.0; i < 1.0; i += 0.1)
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

void Draw::GridXYChequered()
{   
    float interval = 0.1;
    float zUnder = 0.0001;
    
    ColorRGBA Black( 0.0, 0.0, 0.0, 0.95 );
    ColorRGBA White( 1.0, 1.0, 1.0, 0.95 );
    
    bool alternate = false;
    
    for(float i = -1.0; i < (1.0 - interval); i += interval)
    {
	if( alternate ) Black.get();
	else White.get();
	
	for(float j = -1.0; j < (1.0 - interval); j += interval)
	{   
	    glBegin( GL_POLYGON );
	    if( alternate ) Black.get();
	    else White.get();
		glVertex3f( i , j , zUnder );
		glVertex3f( i+interval , j , zUnder );
		glVertex3f( i+interval , j+interval , zUnder );
		glVertex3f( i , j+interval , zUnder );
	    glEnd();
	    
	    alternate = !alternate;
	}
    }
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

void Draw::Generic( const GO_FACE& GF1 )
{
    int draw_type = GL_TRIANGLE_STRIP;
    
    PosRPT dir_up = PosRPT( 1.0, GF1.up.phi , GF1.up.phi ); //(PosRPT) GF1.up ;
    dir_up.radius = -GF1.height;
    
    PosRPT dir_right =  PosRPT(1.0, GF1.right.phi , GF1.right.phi );;
    dir_right.radius = -GF1.width;
    
    PosRPT P1( dir_up );
    DEBUG( "DIR_UP radius" , P1.radius );
    DEBUG( "DIR_UP phi " , P1.phi );
    DEBUG( "DIR_UP radius" , P1.theta );
    
    PosXYZ BottomLeft, BottomRight, TopLeft, TopRight;
    
    BottomLeft = PosXYZ( dir_up ) + PosXYZ( dir_right );
    dir_right.radius = -dir_right.radius;
    BottomRight = PosXYZ( dir_up ) + PosXYZ( dir_right );
    dir_up.radius = -dir_up.radius;
    TopRight = PosXYZ( dir_up ) + PosXYZ( dir_right );
    dir_right.radius = -dir_right.radius;
    TopLeft = PosXYZ( dir_up ) + PosXYZ( dir_right );
    
    glBegin( draw_type );
	BottomLeft.getVertex();
	BottomRight.getVertex();
	TopLeft.getVertex();
	TopRight.getVertex();
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
    
    angleDEG transPhi( angleRAD( WS1.transform.getPhi() ) );
    angleDEG transTheta( angleRAD( WS1.transform.getTheta() ) );
    glRotatef( transPhi , 0.0, 0.0, 1.0f );
    glRotatef( transTheta , 0.0 , 1.0 , 0.0 );
    
    //glRotatef( (angleDEG) angleRAD( WS1.transform.phi ), 0.0, 0.0, 1.0f );
    
    bool hasTexture = WS1.T.textureId != -1;
    
    if( hasTexture )
    {
	WS1.T.enable();
    }
    
    ColorRGBA C2 = WS1.C;
    C2.get();
    
    GO_CUBOID* GCx = dynamic_cast<GO_CUBOID*>( WS1.GOx );
    if(GCx != 0) Draw::Generic( *GCx , hasTexture , WS1.T.tilingFactor );
    
    if( hasTexture )
    {
	WS1.T.disable();
    }
    
    glRotatef( -transTheta , 0.0 , 1.0 , 0.0 );
    glRotatef( -transPhi , 0.0, 0.0, 1.0f );
    // glRotatef( (angleDEG) angleRAD( WS1.transform.phi ), 0.0, 0.0, -1.0f );
    if( toggleScale ) glScalef( 1/WS1.transform.radius , 1/WS1.transform.radius , 1/WS1.transform.radius );
    if( toggleTranslate ) glTranslatef( -P1.X , -P1.Y , -P1.Z );
}

void Draw::Outline( PosXYZ* DrawPosV )
{
	    float currentColor[4];
	    glGetFloatv( GL_CURRENT_COLOR , currentColor );
	    
	    glColor4f(1.0, 1.0, 1.0, 1.0);
	    
	    glDisable( GL_LIGHTING );
	    
	    glEnable( GL_LINE_STIPPLE );
	    unsigned short pattern = 43690;
	    glLineStipple(5 , pattern);
	    
	    glBegin( GL_LINE_STRIP );
		glVertex3f( 0.0, 0.0, 0.0 );
		for(int i = 0; i < 4; ++i) DrawPosV[i].getVertex();
		DrawPosV[0].getVertex();
	    glEnd();
	    glDisable( GL_LINE_STIPPLE );

	    glColor4fv( currentColor );
	    
	    glEnable( GL_LIGHTING );
    
}

void Draw::Generic( const GO_CUBOID& GC1, bool hasTexture, float tilingFactor)
{
    int draw_type = GL_POLYGON;
    
    PosXYZ DrawPosV[4];
    if( GC1.enabledFaces & GO_CUBOID::BOTTOM )
    {
	DrawPosV[0] = PosXYZ( + GC1.length, + GC1.width, - GC1.height);
	DrawPosV[1] = PosXYZ( + GC1.length, - GC1.width, - GC1.height);
	DrawPosV[2] = PosXYZ( - GC1.length, - GC1.width, - GC1.height);
	DrawPosV[3] = PosXYZ( - GC1.length, + GC1.width, - GC1.height);
	
	glBegin( draw_type );
	    for(int i = 0; i < 4; ++i) 
	    {
		DrawPosV[i].getVertex();
		if(hasTexture)
		{
		    float x = tilingFactor*bool(i > 1);
		    float y = tilingFactor*bool(i==1 || i==2);
		    glTexCoord2f( x, y );
		}
	    }
	glEnd();
	
	if(GC1.SHOW_BLUEPRINT)
	{
	    Outline( DrawPosV );
	}
    }
    
    if( GC1.enabledFaces & GO_CUBOID::LEFT )
    {
	DrawPosV[0] = PosXYZ( - GC1.length, + GC1.width, + GC1.height);
	DrawPosV[1] = PosXYZ( - GC1.length, - GC1.width, + GC1.height);
	DrawPosV[2] = PosXYZ( - GC1.length, - GC1.width, - GC1.height);
	DrawPosV[3] = PosXYZ( - GC1.length, + GC1.width, - GC1.height);
	
	glBegin( draw_type );
	    for(int i = 0; i < 4; ++i) 
	    {
		DrawPosV[i].getVertex();
		if(hasTexture)
		{
		    glTexCoord2f( (i & 1)*tilingFactor, (i & 2)*tilingFactor );
		}
	    }
	/*
	    glVertex3f( -GC1.length, GC1.width, GC1.height);
	    glVertex3f( -GC1.length, - GC1.width, GC1.height);
	    glVertex3f( -GC1.length, -GC1.width, - GC1.height);
	    glVertex3f( -GC1.length, + GC1.width, - GC1.height);
	*/glEnd();
	
	if(GC1.SHOW_BLUEPRINT)
	{
	    Outline( DrawPosV );
	}
    }
    
    if( GC1.enabledFaces & GO_CUBOID::BACK )
    {
	DrawPosV[0] = PosXYZ( + GC1.length, - GC1.width, + GC1.height);
	DrawPosV[1] = PosXYZ( - GC1.length, - GC1.width, + GC1.height);
	DrawPosV[2] = PosXYZ( - GC1.length, - GC1.width, - GC1.height);
	DrawPosV[3] = PosXYZ( + GC1.length, - GC1.width, - GC1.height);
	glBegin( draw_type );
	    for(int i = 0; i < 4; ++i) 
	    {
		DrawPosV[i].getVertex();
		if(hasTexture)
		{
		    glTexCoord2f( (i & 1)*tilingFactor, (i & 2)*tilingFactor );
		}
	    }
	glEnd();/*
	glBegin( draw_type );
	    glVertex3f( + GC1.length, - GC1.width,  + GC1.height);
	    glVertex3f( - GC1.length, - GC1.width,  + GC1.height);
	    glVertex3f( - GC1.length, - GC1.width,  - GC1.height);
	    glVertex3f( + GC1.length, - GC1.width,  - GC1.height);
	glEnd();*/
	
	if(GC1.SHOW_BLUEPRINT)
	{
	    Outline( DrawPosV );
	}
    }
    
    if( GC1.enabledFaces & GO_CUBOID::TOP )
    {
	DrawPosV[0] = PosXYZ( + GC1.length, + GC1.width, + GC1.height);
	DrawPosV[1] = PosXYZ( + GC1.length, - GC1.width, + GC1.height);
	DrawPosV[2] = PosXYZ( - GC1.length, - GC1.width, + GC1.height);
	DrawPosV[3] = PosXYZ( - GC1.length, + GC1.width, + GC1.height);
	glBegin( draw_type );
	    for(int i = 0; i < 4; ++i) 
	    {
		DrawPosV[i].getVertex();
		if(hasTexture)
		{
		    glTexCoord2f( (i & 1)*tilingFactor, (i & 2)*tilingFactor );
		}
	    }
	glEnd();/*
	glBegin( draw_type );
	    glVertex3f(  + GC1.length,  + GC1.width,  + GC1.height);
	    glVertex3f(  + GC1.length,  - GC1.width,  + GC1.height);
	    glVertex3f(  - GC1.length,  - GC1.width,  + GC1.height);
	    glVertex3f(  - GC1.length,  + GC1.width,  + GC1.height);
	glEnd();*/
	
	if(GC1.SHOW_BLUEPRINT)
	{
	    Outline( DrawPosV );
	}
    }
    
    if( GC1.enabledFaces & GO_CUBOID::RIGHT )
    {
	DrawPosV[0] = PosXYZ( + GC1.length, + GC1.width, + GC1.height);
	DrawPosV[1] = PosXYZ( + GC1.length, - GC1.width, + GC1.height);
	DrawPosV[2] = PosXYZ( + GC1.length, - GC1.width, - GC1.height);
	DrawPosV[3] = PosXYZ( + GC1.length, + GC1.width, - GC1.height);
	glBegin( draw_type );
	    for(int i = 0; i < 4; ++i) 
	    {
		DrawPosV[i].getVertex();
		if(hasTexture)
		{
		    glTexCoord2f( (i & 1)*tilingFactor, (i & 2)*tilingFactor );
		}
	    }
	glEnd();
	/*glBegin( draw_type );
	    glVertex3f(  + GC1.length,  + GC1.width,  + GC1.height);
	    glVertex3f(  + GC1.length,  - GC1.width,  + GC1.height);
	    glVertex3f(  + GC1.length,  - GC1.width,  - GC1.height);
	    glVertex3f(  + GC1.length,  + GC1.width,  - GC1.height);
	glEnd();
	*/
	if(GC1.SHOW_BLUEPRINT)
	{
	    Outline( DrawPosV );
	}
    }
    
    if( GC1.enabledFaces & GO_CUBOID::FRONT )
    {
	DrawPosV[0] = PosXYZ(  + GC1.length,  + GC1.width,  + GC1.height);
	DrawPosV[1] = PosXYZ( - GC1.length, + GC1.width, + GC1.height);
	DrawPosV[2] = PosXYZ( - GC1.length, + GC1.width, - GC1.height);
	DrawPosV[3] = PosXYZ( + GC1.length, + GC1.width, - GC1.height);
	glBegin( draw_type );
	    for(int i = 0; i < 4; ++i) 
	    {
		DrawPosV[i].getVertex();
		if(hasTexture)
		{
		    glTexCoord2f( (i & 1)*tilingFactor, (i & 2)*tilingFactor );
		}
	    }
	glEnd();
	/*
	 * glBegin( draw_type );
	    glVertex3f(  + GC1.length,  + GC1.width,  + GC1.height);
	    glVertex3f(  - GC1.length,  + GC1.width,  + GC1.height);
	    glVertex3f(  - GC1.length,  + GC1.width,  - GC1.height);
	    glVertex3f(  + GC1.length,  + GC1.width,  - GC1.height);
	glEnd();
	*/
	if(GC1.SHOW_BLUEPRINT)
	{
	    Outline( DrawPosV );
	}
    }
    
    if(GC1.SHOW_BLUEPRINT)
    {
	    float currentColor[4];
	    glGetFloatv( GL_CURRENT_COLOR , currentColor );
	    
	    glDisable( GL_LIGHTING );
	    PosXYZ SketchPosV[6];
	    
	    SketchPosV[0] = PosXYZ( DrawPosV[0].X , 0 , 0 );
	    SketchPosV[1] = PosXYZ( 0 , 0 , 0 );
	    
	    SketchPosV[2] = PosXYZ( 0 , DrawPosV[0].Y, 0 );
	    SketchPosV[3] = PosXYZ( 0 , 0 , 0 );
	    
	    SketchPosV[4] = PosXYZ( 0  , 0 , DrawPosV[3].Z );
	    SketchPosV[5] = PosXYZ( 0 , 0 , 0 );
	    
	    glTranslatef( 0 , 0.0, 0.02 );
	    Colors::Red.get();
	    
	    glBegin( GL_LINES );
		SketchPosV[0].getVertex();
		SketchPosV[1].getVertex();
		
		SketchPosV[0].getVertex( 0, -0.01, 0 );
		SketchPosV[0].getVertex( 0, 0.01, 0 );
		SketchPosV[1].getVertex( 0, -0.01, 0 );
		SketchPosV[1].getVertex( 0, 0.01, 0 );
	    glEnd();
	    
	    glTranslatef( 0, 0.0, -0.02 );
	    
	    glTranslatef( -0.02 , 0, 0.0 );
	    Colors::Green.get();
	    glBegin( GL_LINES );
		SketchPosV[2].getVertex();
		SketchPosV[3].getVertex();
		
		SketchPosV[2].getVertex( -0.01, 0, 0 );
		SketchPosV[2].getVertex( 0.01, 0, 0 );
		SketchPosV[3].getVertex( -0.01, 0, 0 );
		SketchPosV[3].getVertex( 0.01, 0, 0 );
	    glEnd();
	    
	    glTranslatef( 0.02, 0, 0.0 );
	    Colors::Blue.get();
	    // glTranslatef( 0.0 , 0.0, 0.0 );
	    
	    glBegin( GL_LINES );
		SketchPosV[4].getVertex();
		SketchPosV[5].getVertex();
		
		SketchPosV[4].getVertex( -0.01, 0, 0 );
		SketchPosV[4].getVertex( 0.01, 0, 0 );
		SketchPosV[5].getVertex( -0.01, 0, 0 );
		SketchPosV[5].getVertex( 0.01, 0, 0 );
	    glEnd();
	    // glutStrokeCharacter( GLUT_STROKE_MONO_ROMAN , '0' );
	    // glTranslatef( 0, 0, -0.02 );
	    
	    Colors::Yellow.get();
	    float r = 0.01;
	    glBegin( GL_LINES );
		glVertex3f( -r , -r , 0 );
		glVertex3f( r , r , 0 );
		glVertex3f( 0 , -r , -r );
		glVertex3f( 0 , r , r );
		glVertex3f( -r , 0 , -r );
		glVertex3f( r , 0 , r );
		glVertex3f( -r , -r , -r );
		glVertex3f( r , r , r );
		glVertex3f( -r , r , 0 );
		glVertex3f( r , -r , 0 );
		glVertex3f( 0 , r , -r );
		glVertex3f( 0 , -r , r );
		glVertex3f( -r , 0 , r );
		glVertex3f( r , 0 , -r );
	    glEnd();
	    
	    glColor4f( 1.0, 1.0, 1.0, 1.0 );
	    
	    std::string text;
	    
	    glRasterPos3f(SketchPosV[0].X / 2, 0, 0);
	    text = "X/Z + Left-Click:" + toString( GC1.length );
	    for(std::string::iterator i = text.begin(); i != text.end(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *i);
	    
	    
	    glRasterPos3f(0, SketchPosV[2].Y / 2, 0);
	    text = "X/Z + Middle-Mouse:" + toString( GC1.width );
	    for(std::string::iterator i = text.begin(); i != text.end(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *i);
	    
	    glRasterPos3f(0, 0, SketchPosV[4].Z / 2);
	    text = "X/Z + Right-Click:" + toString( GC1.height );
	    for(std::string::iterator i = text.begin(); i != text.end(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *i);
	    
	    glEnable( GL_LIGHTING );
	    glColor4fv( currentColor );
    }
}

void Draw::Star( const PosXYZ& P1 )
{
    glTranslatef( P1.X , P1.Y , P1.Z );
    float r = 0.01;
    glBegin( GL_LINES );
	glVertex3f( -r , -r , 0 );
	glVertex3f( r , r , 0 );
	glVertex3f( 0 , -r , -r );
	glVertex3f( 0 , r , r );
	glVertex3f( -r , 0 , -r );
	glVertex3f( r , 0 , r );
	glVertex3f( -r , -r , -r );
	glVertex3f( r , r , r );
	glVertex3f( -r , r , 0 );
	glVertex3f( r , -r , 0 );
	glVertex3f( 0 , r , -r );
	glVertex3f( 0 , -r , r );
	glVertex3f( -r , 0 , r );
	glVertex3f( r , 0 , -r );
    glEnd();
    glTranslatef( -P1.X , -P1.Y , -P1.Z );
}