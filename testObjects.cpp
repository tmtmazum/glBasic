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
#include "headers/Physics.h"
#include "headers/VECTOR.h"

#include <GL/glut.h>

using namespace std;
using namespace physics;

const PosXY WindowSize(1024.0, 800.0);

CameraCEU Cam;
Lighting Lights;
MouseAB Mouse;
PosXY MouseDiff;
long int keysPressed;

namespace KEYS
{
    enum 
    {
	ESCAPE=1,
	X=2,
	Z=4,
	R=8,
	T=16,
	Y=32,
    };
}

int faceNum = 1;

float cubeLength = 0.5;
float cubeWidth = 0.3;
float cubeHeight = 0.2;

float cubeX = 0.0;
float cubeY = 0.0;
float cubeZ = 0.2;
	
PosXYZ ctrlPt1(-0.4, -0.4, 0.0);
PosXYZ ctrlPt2(0.4, -0.4, 0.0);
PosXYZ ctrlPt3(0.4, 0.4, 0.0);

int selection = 0;

void drawSetting()
{
    // Draw::GridXYChequered();
    
    // TextureFace TF1( "file.bmp" , 
    // VO_UNIT_UP up1;
    // VO_UNIT_RIGHT right1;
    // GO_FACE F( up1 , right1 , 0.2, 0.5 );
    WO_SINGLE obj1( new GO_CUBOID( cubeLength , cubeWidth, cubeHeight , faceNum /*GO_CUBOID::BOTTOM*/ ) ); 
    obj1[ Colors::DarkOrange ][PosXYZ(cubeX, cubeY, cubeZ )]["Qtiles.bmp"];
    if(selection==2) obj1.GOx->SHOW_BLUEPRINT= true;
    obj1.transform.radius = 0.5;
       
    glClearStencil(0);
   glEnable(GL_STENCIL_TEST);
   glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE );
   
   glStencilFunc( GL_ALWAYS , 5, -1);
    glEnable( GL_LIGHTING );
    Draw::Generic( obj1 );
    glDisable( GL_STENCIL_TEST );
    
    glColor4f( 1.0, 1.0, 1.0, 1.0 );
    glLineWidth( 2.0 );
    Draw::GridXY();
    glLineWidth( 1.0 );
}

void drawObjects()
{
    
    GLfloat ctrlpoints[3][3] = 
    {
	    { ctrlPt1.X, ctrlPt1.Y, ctrlPt1.Z}, { ctrlPt2.X, ctrlPt2.Y , ctrlPt2.Z }, 
	    /*{ -0.2, 0.4, 0.0}, 
	    {0.2, -0.4, 0.0},*/ {ctrlPt3.X, ctrlPt3.Y, ctrlPt3.Z}    
    };

   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   
	    glDisable( GL_LINE_STIPPLE );
   Colors::Red.get();
   glBegin(GL_LINES);
   for (int i = 0; i <= 30; i += 1)
       glEvalCoord1f( (GLfloat) i/30.0);
       //  glEvalCoord2f((GLfloat) i/30.0, (GLfloat) i/20.0);
   glEnd();
   
   glClearStencil(0);
   glEnable(GL_STENCIL_TEST);
   glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE );
   
   glStencilFunc( GL_ALWAYS , 1, -1);
   Draw::Star( ctrlPt1 );
   glStencilFunc( GL_ALWAYS , 2, -1);
   Draw::Star( ctrlPt2 );
   glStencilFunc( GL_ALWAYS , 3, -1);
   Draw::Star( ctrlPt3 );
   
   glStencilFunc( GL_ALWAYS, 4, -1);
   WO_SINGLE w1( new GO_CUBOID(0.1, 0.2, 0.2, GO_CUBOID::FRONT) );
   w1[PosXYZ(-0.5, 0.5, 0.1)][Colors::Red];
   if(selection==1) w1.GOx->SHOW_BLUEPRINT = true;
   Draw::Generic( w1 );
   
   
}

void draw()
{
    static int i = 0;
    
    if(keysPressed & KEYS::X)
    {
	if(Mouse.buttonsPressed & MouseAB::LMB) { cubeLength += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else if(Mouse.buttonsPressed & MouseAB::MMB) { cubeWidth += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else if(Mouse.buttonsPressed & MouseAB::RMB) { cubeHeight += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else { MouseDiff = PosXY(0,0); }
    }
    else if(keysPressed & KEYS::Z)
    {
	if(Mouse.buttonsPressed & MouseAB::LMB) { cubeX += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else if(Mouse.buttonsPressed & MouseAB::MMB) { cubeY += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else if(Mouse.buttonsPressed & MouseAB::RMB) { cubeZ += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else { MouseDiff = PosXY(0,0); }
    }
    else if(keysPressed & KEYS::R)
    {
	if(Mouse.buttonsPressed & MouseAB::LMB) { ctrlPt1.X += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else if(Mouse.buttonsPressed & MouseAB::MMB) { ctrlPt1.Y += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else if(Mouse.buttonsPressed & MouseAB::RMB) { ctrlPt1.Z += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else { MouseDiff = PosXY(0,0); }
    }
    else if(keysPressed & KEYS::T)
    {
	if(Mouse.buttonsPressed & MouseAB::LMB) { ctrlPt2.X += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else if(Mouse.buttonsPressed & MouseAB::MMB) { ctrlPt2.Y += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else if(Mouse.buttonsPressed & MouseAB::RMB) { ctrlPt2.Z += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else { MouseDiff = PosXY(0,0); }
    }
    else if(keysPressed & KEYS::Y)
    {
	if(Mouse.buttonsPressed & MouseAB::LMB) { ctrlPt3.X += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else if(Mouse.buttonsPressed & MouseAB::MMB) { ctrlPt3.Y += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else if(Mouse.buttonsPressed & MouseAB::RMB) { ctrlPt3.Z += 0.02*(MouseDiff.X ? MouseDiff.X : MouseDiff.Y ); }
	else { MouseDiff = PosXY(0,0); }
    }
    else
    {
	if(Mouse.buttonsPressed & MouseAB::MMB) { Cam.translateXYZ( MouseDiff ); }
	if(Mouse.buttonsPressed & MouseAB::LMB) { Cam.rotateXYZ( MouseDiff ); }
	if(Mouse.buttonsPressed & MouseAB::RMB) { Cam.scaleXYZ( MouseDiff ); }
    
	if(keysPressed==0 && Mouse.buttonsPressed == 0)
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
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    Cam.update();
    Lights.setCenter( Cam.Center );
    Lights.setMode();

	// drawHUD();
	drawSetting();
	drawObjects();
	
	glDisable( GL_DEPTH_TEST );
	
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glColor3f(0.0f, 255.0f, 1.0f);
	
	glBegin( GL_LINES );
	    glVertex2f(0.0, 0.0);
	    glVertex2f(1.0, 1.0);
	glEnd();
	
    glutSwapBuffers();
    
    i++;
    
}

PosXY getMouseDiff( PosXY Current , PosXY Old )
{
    
    PosXY MouseDiff( -(Old.X - Current.X), -(Old.Y -Current.Y) );
    
    if(abs(MouseDiff.X) > abs(MouseDiff.Y)) MouseDiff = PosXY( MouseDiff.X, 0 );
    else MouseDiff = PosXY( 0, MouseDiff.Y );
    
    return PosXY( MouseDiff.X/WindowSize.X, MouseDiff.Y/WindowSize.Y );
}

void handleKeyPress( unsigned char key, int x, int y )
{
    switch(key)
    {
	case 'w':
	    faceNum ^= 8;
	    break;
	case 'a':
	    faceNum ^= 2;
	    break;
	case 's':
	    faceNum ^= 1;
	    break;
	case 'd':
	    faceNum ^= 16;
	    break;
	case 'q':
	    faceNum ^= 4;
	    break;
	case 'e':
	    faceNum ^= 32;
	    break;
	    
	case 'x':
	    keysPressed |= KEYS::X;
	    break;
	case 'z':
	    keysPressed |= KEYS::Z;
	    break;
	case 'r':
	    keysPressed |= KEYS::R;
	    break;
	case 't':
	    keysPressed |= KEYS::T;
	    break;
	case 'y':
	    keysPressed |= KEYS::Y;
	    break;
    }
}

void handleKeyUp( unsigned char key , int x , int y )
{
    switch(key)
    {
	case 'x':
	    keysPressed &= ~(KEYS::X);
	    break;
	case 'z':
	    keysPressed &= ~(KEYS::Z);
	    break;
	case 'r':
	    keysPressed &= ~(KEYS::R);
	    break;
	case 't':
	    keysPressed &= ~(KEYS::T);
	    break;
	case 'y':
	    keysPressed &= ~(KEYS::Y);
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
    
    if(state==GLUT_DOWN && glutGetModifiers()==GLUT_ACTIVE_SHIFT)
    {
	MouseDiff = PosXY(0,0);
    GLfloat color[4];
    GLfloat depth;
    GLuint select_index;
    glReadPixels(x, WindowSize.Y - y - 1, 1, 1, GL_RGBA, GL_FLOAT, color);
    glReadPixels(x, WindowSize.Y - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, WindowSize.Y - y - 1 - 50, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &select_index);
    
    DEBUG("ColorR", color[0]);
    DEBUG("ColorG", color[1]);
    DEBUG("ColorB", color[2]);
    DEBUG("ColorA", color[3]);
    
    if(select_index==4) selection=1;
    else if(select_index==5) selection=2;
    }
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
    
    glutDisplayFunc(draw);
    glutIdleFunc(draw);
    
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyUp);
    glutSpecialFunc(handleSpecialPress);
    glutMouseFunc(handleMousePress);
    glutMotionFunc(handleMouseMotion);
    
    Cam.init();
    
    glutMainLoop();
    
}
