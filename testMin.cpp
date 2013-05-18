#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

#include "headers/Color.h"
#include "headers/Pos.h"
#include "headers/Draw.h"
#include "headers/transform.h"
#include "headers/PosManager.h"
#include "headers/GEOMETRY.h"
#include "headers/Camera.h"

#include <GL/glut.h>

using namespace std;

const PosXY WindowSize(800.0, 600.0);

PosXYZ rotate(0.0, 0.0, 0.0);
const float RotateSpeed = 0.5;
PosXYZ MouseDiff;
bool pressLMB = false;
bool pressMMB = false;
bool pressRMB = false;
PosXY MousePos;

void addRotate(PosXYZ P)
{
    rotate.X += P.X;
    rotate.Y += P.Y;
    rotate.Z += P.Z;
}

void applyRotate()
{
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    // gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glRotatef(RotateSpeed*rotate.X, 1.0, 0.0, 0.0);
    glRotatef(RotateSpeed*rotate.Y, 0.0, 1.0, 0.0);
    glRotatef(RotateSpeed*rotate.Z, 0.0, 0.0, 1.0);
}

void drawObjects()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	PosManager PM;
	PM.makeGridXY();
	Draw::Generic( PM );
    glutSwapBuffers();
}

float zNear = 1.5;
float zFar = 1.5;

void draw()
{
    drawObjects();
}

void redraw()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(50, WindowSize.X/WindowSize.Y, zNear, zFar );
    // addRotate(MouseDiff);
    if(pressMMB)
    {
    rotate.X -= MouseDiff.Y;
    rotate.Z -= MouseDiff.X;
    }
    applyRotate();
    drawObjects();
}


void handleKeyPress( unsigned char key, int x, int y)
{
    switch(key)
    {
	case 'w':
	    // glTranslatef(0.0, -0.1, 0.0);
	    // glRotatef(RotateSpeed, 0.0, -1.0, 0.0);
	    // addRotate( PosXYZ( -1.0, 0.0, 0.0) );
	    zNear += 0.1;
	    break;
	case 'a':
	    // glTranslatef(0.1, 0.0, 0.0);
	    // glRotatef(RotateSpeed, 0.0, 0.0, 1.0);
	    // addRotate( PosXYZ( 0.0, 0.0, 1.0 ));
	    zFar -= 0.1;
	    break;
	case 's':
	    // glTranslatef(0.0, 0.1, 0.0);
	    // glRotatef(RotateSpeed, 0.0, 1.0, 0.0);
	    // addRotate( PosXYZ( 1.0, 0.0, 0.0 ) );
	    zNear -= 0.1;
	    break;
	case 'd':
	    // glTranslatef(-0.1, 0.0, 0.0)
	    // glRotatef(RotateSpeed, 0.0, 0.0, -1.0);
	    // addRotate( PosXYZ( 0.0, 0.0, -1.0 ) );
	    zFar += 0.1;
	    break;
	case 'l':
	    std::cout << zNear << ", " << zFar << std::endl;
	    break;
    }
    // applyRotate();
}


PosXY getMouseDiff( int x, int y )
{
    PosXY MouseDiff( (x - MousePos.X), (y-MousePos.Y) );
    
    if(abs(MouseDiff.X) > abs(MouseDiff.Y)) MouseDiff = PosXY( MouseDiff.X, 0 );
    else MouseDiff = PosXY( 0, MouseDiff.Y );
    
    return PosXY( MouseDiff.X/WindowSize.X, MouseDiff.Y/WindowSize.Y );
}
void handleMousePress( int button, int state, int x, int y )
{
    switch(button)
    {
	case GLUT_LEFT_BUTTON:
	    if(state==GLUT_DOWN) pressLMB = true;
	    else pressLMB = false;
	    MousePos = PosXY( x, y );
	    break;
	case GLUT_MIDDLE_BUTTON:
	    if(state==GLUT_DOWN) pressMMB = true;
	    else if(state==GLUT_UP) 
	    {
		pressMMB = false;
		MouseDiff = PosXYZ(0,0,0);
	    }
	    MousePos = PosXY( x, y );
	    break;
	case GLUT_RIGHT_BUTTON:
	    if(state==GLUT_DOWN) pressRMB = true;
	    else if(state==GLUT_UP) pressRMB = false;
	    MousePos = PosXY( x, y );
	    break;
    }
}

void handleMouseMotion( int x, int y )
{
    MouseDiff = getMouseDiff(x,y);/*
    if(MouseDiff.X > MouseDiff.Y) MouseDiff = PosXY( MouseDiff.X, 0 );
    else MouseDiff = PosXY( 0, MouseDiff.Y );*/
    /*
    if(pressLMB)
    {
    }
    if(pressMMB)
    {
	addRotate( PosXYZ( Diff.Y , 0.0,Diff.X ) );
    }
    if(pressRMB)
    {

    }*/
    // applyRotate();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize(WindowSize.X, WindowSize.Y);
    glutInitWindowPosition(10,10);
    glutCreateWindow("glTest");
    
    glutDisplayFunc(draw);
    glutIdleFunc(redraw);
    
    glutKeyboardFunc(handleKeyPress);
    glutMouseFunc(handleMousePress);
    glutMotionFunc(handleMouseMotion);
    
    glutMainLoop();
}