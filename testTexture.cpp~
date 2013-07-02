#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "headers/Color.h"
#include "headers/Pos.h"
#include "headers/Draw.h"
#include "headers/transform.h"
#include "headers/PosManager.h"
#include "headers/GEOMETRY.h"
#include "headers/CameraCEU.h"
#include "headers/Material.h"
#include "headers/Lighting.h"
#include "headers/Mouse.h"
#include "headers/Texture.h"

#include <GL/glut.h>

using namespace std;

const PosXY WindowSize(1024.0, 800.0);

CameraCEU Cam;
Lighting Lights;
MouseAB Mouse;
float tiles = 2.0;
bool selectedTexture = 0;

void drawHUD()
{
/*
    glDisable( GL_LIGHTING );
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    // glClear(GL_COLOR_BUFFER_BIT);
    glColor3f( 1.0 , 0.0 , 0.0 );
    PosXYZ PosHUD( Cam.Eye );
    PosHUD.X += Cam.Center.X;
    PosHUD.Y += Cam.Center.Y;
    PosHUD.Z += Cam.Center.Z;
    PosRPT PosHUDr( 0.001 , -Cam.Eye.getPhi() , Cam.Eye.getTheta() );
    PosXYZ PosHUDx( PosHUDr );
    glRasterPos4f( PosHUDx.X, PosHUDx.Y, PosHUDx.Z, 1.0 );
    
    for(int i = 0; i < 20; ++i)
    {
	glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
	glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
	glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
    }
    
    glEnable( GL_LIGHTING );
    */
}

void drawObjects()
{
    Draw::GridXYChequered();
    
    glLineWidth( 2.0 );
    Draw::GridXY();
    glLineWidth( 1.0 );
    
    string imageFile1 = "ocean_1.BMP";
    string imageFile2 = "Qtiles.bmp";
    Texture TXR( selectedTexture ? imageFile1.c_str() : imageFile2.c_str() );
    // TXR.drawSample();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TXR.textureId);
    
    //Use blurry texture mapping (replace GL_LINEAR with GL_NEAREST for blocky)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //Don't use special coloring
    
    const float tiling_factor = tiles;
    
    glBegin( GL_POLYGON );
	glTexCoord2f( 0.0, 0.0 );
	glVertex3f( 0.3, 0 , 0.1 );
	
	glTexCoord2f( 0.0, 1.0*tiling_factor );
	glVertex3f( -0.3, 0 , 0.1 );
	
	glTexCoord2f( 1.0*tiling_factor, 1.0*tiling_factor );
	glVertex3f( -0.3 , 0 , 0.6 );
	
	glTexCoord2f( 1.0*tiling_factor , 0.0 );
	glVertex3f( 0.3 , 0 , 0.6 );
    glEnd();
    // WO_SINGLE WS1( new GO_CUBOID( 0.1, 0, 0.1, 0 | GO_CUBOID::FRONT) );
    // WS1[ PosXYZ(0,0,0.3) ][ PosRPT(2.5, 0.0, 0.0)];
    // Draw::Generic( WS1 );
    
    glDisable( GL_TEXTURE_2D );
}

PosXY getMouseDiff( PosXY Current , PosXY Old )
{
    
    PosXY MouseDiff( -(Old.X - Current.X), -(Old.Y -Current.Y) );
    
    if(abs(MouseDiff.X) > abs(MouseDiff.Y)) MouseDiff = PosXY( MouseDiff.X, 0 );
    else MouseDiff = PosXY( 0, MouseDiff.Y );
    
    return PosXY( MouseDiff.X/WindowSize.X, MouseDiff.Y/WindowSize.Y );
}

void moderateDivEq(float* target, float rate, float snapToZeroRange = 0.00001)
{
    // if(*target != 0) { DEBUG("TARGET", *target); }
    *target = ( *target / (1+rate) );
    *target = (*target < snapToZeroRange && *target > -snapToZeroRange ? 0 : *target);
}

void moderateMinusEq(float* target, float rate, float snapToZeroRange = 0.00001)
{
    assert( copysign(rate, *target) > 0 );
    *target = ( *target - copysign( rate, *target ) );
    // *target = (*target < snapToZeroRange && *target > -snapToZeroRange ? 0 : *target);
}

void moderateEaseOut(float* target, float rate, float snapToZeroRange = 0.00001)
// Assumes max value for target is 1 and min is 0
// Divide by Max before passing in target
// Do inverse after
{
    moderateMinusEq(target, max<float>(0.0,abs(rate*(1 - (*target)))), snapToZeroRange);
}

void moderateEaseIn(float* target, float rate, float snapToZeroRange = 0.00001)
// Assumes max value for target is 1 and min is 0
// Divide by Max before passing in target
// Do inverse after
{
    float tr = *target;
    moderateDivEq(target, rate*(1 + (*target)), snapToZeroRange);
}

/*
float* normalizeRange( float* target , float min, float max )
{
    
}*/

void draw()
{
    
}
PosXY MouseDiff;

void redraw1()
{
    
}

void redraw()
{
    static int i = 0;
    
    if(Mouse.buttonsPressed & MouseAB::MMB) { Cam.translateXYZ( MouseDiff ); }
    if(Mouse.buttonsPressed & MouseAB::LMB) { Cam.rotateXYZ( MouseDiff ); }
    if(Mouse.buttonsPressed & MouseAB::RMB) { Cam.scaleXYZ( MouseDiff ); }
    
    if(Mouse.buttonsPressed == 0)
    {
	// Still keep transitioning a while even after all buttons 
	// have been released
	switch(Mouse.lastButton)
	{
	    case MouseAB::LMB: Cam.rotateXYZ( MouseDiff ); break;
	    // case 1: Cam.rotateXYZ( MouseDiff ); break;
	    case MouseAB::RMB: Cam.scaleXYZ( MouseDiff ); break;
	}
	moderateDivEq( &MouseDiff.X , 0.007 );
	moderateDivEq( &MouseDiff.Y , 0.007 );
    }
    if(Mouse.buttonsPressed==0 && Cam.Eye.theta > (PI/2))
    {
	float nw_angle = Cam.Eye.theta - (PI/2);
	nw_angle /= (PI/2);
	moderateEaseIn( &nw_angle, 0.07 );
	// moderateDivEq( &nw_angle, 0.07*((PI/2) -nw_angle) );
	nw_angle *= (PI/2);
	// moderateMinusEq( &nw_angle, 0.07*nw_angle );
	Cam.Eye.theta = (PI/2 + nw_angle);
    }
    Cam.update();
    Lights.setCenter( Cam.Center );
    Lights.setMode();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// drawHUD();
	drawObjects();
	drawHUD();
	
    glutSwapBuffers();
    
    i++;
}

void handleKeyPress( unsigned char key, int x, int y )
{
    switch(key)
    {
	case 'w':
	    tiles += 0.1;
	    break;
	case 'a':
	    selectedTexture = !selectedTexture;
	    break;
	case 's':
	    tiles -= 0.1;
	    break;
	case 'd':
	    selectedTexture = !selectedTexture;
	    break;
	case 'q':
	    break;
	case 'e':
	    break;
	case 'l':
	    break;
    }
}

void handleSpecialPress( int key, int x, int y )
{
    switch(key)
    {
	case GLUT_KEY_F1:
	    Cam.setEyeToNormal();
	    break;
	case GLUT_KEY_F2:
	    Cam.setCenterToOrigin();
	    break;
	case GLUT_KEY_F3:
	    Cam.setEyeToTop();
	    break;
    }
}

void handleMousePress( int button, int state, int x, int y )
{
    Mouse.toggleButton( button , state );
    Mouse.setPosition( x, y );
    //if( state == GLUT_DOWN )
    //{
    if(state == GLUT_DOWN) Mouse.savePos();
    //}
}

void handleMouseMotion( int x, int y )
{
    Mouse.setPosition( x, y );
    MouseDiff = getMouseDiff( Mouse.At , Mouse.loadPos() );
}

void preSettings()
{
	
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
 
    glutInitWindowSize(WindowSize.X, WindowSize.Y);
    glutInitWindowPosition(10,10);
    glutCreateWindow("glTest");
    
    // Background Color
    glClearColor( 0.7f, 0.7f, 0.7f , 0.5f );
    
    // Enable Transparency
    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glutDisplayFunc(redraw);
    glutIdleFunc(redraw);
    
    glutKeyboardFunc(handleKeyPress);
    glutSpecialFunc(handleSpecialPress);
    glutMouseFunc(handleMousePress);
    glutMotionFunc(handleMouseMotion);
    
    Cam.init();
    
    glutMainLoop();
    
}