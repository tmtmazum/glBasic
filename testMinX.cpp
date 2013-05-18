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
#include "headers/Material.h"

#include <GL/glut.h>

using namespace std;

const PosXY WindowSize(800.0, 600.0);

PosXY MouseDiff;
bool pressLMB = false;
bool pressMMB = false;
bool pressRMB = false;
PosXY MousePos;

Camera Cam;

void drawObjects()
{
    bool bl[6];
    for(int i = 0; i < 6; ++i) bl[i] = false;
    bl[0] = true; bl[1]=true; bl[2]=true;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Materials::all.get();
	glDisable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
	Draw::GridXY();
	glEnable(GL_LIGHTING);
	
	Colors::Red.get();
	// glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Colors::White.toArray());
	Materials::chrome.get();
	Draw::CubeLPM(0.1, PosXYZ(0.2,0.2,0.1), bl);
	
	glShadeModel(GL_SMOOTH);
	Draw::CubeLPM(0.1, PosXYZ(-0.2,-0.2,0.1), bl);
    glutSwapBuffers();
}

void draw()
{
    drawObjects();
}

void redraw()
{
    // if(pressLMB) Cam.addTranslate( MouseDiff );
    if(pressMMB) Cam.addRotate( MouseDiff );
    if(pressRMB) Cam.addScale( MouseDiff );
    Cam.update();
    drawObjects();
}


void handleKeyPress( unsigned char key, int x, int y)
{
    switch(key)
    {
	case 'w':
	    break;
	case 'a':
	    break;
	case 's':
	    break;
	case 'd':
	    break;
	case 'l':
	    break;
    }
    // applyRotate();
}

void handleSpecialPress( int key, int x, int y )
{
    switch(key)
    {
	case GLUT_KEY_F1:
	    Cam.printView();
	    break;
	case GLUT_KEY_F2:
	    Cam.setView1();
	    break;
    }
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
		MouseDiff = PosXY(0,0);
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
    MouseDiff = getMouseDiff(x,y);
    if(pressLMB)
    {
	glTranslatef(0.01* MouseDiff.X, 0.01* MouseDiff.Y, 0.0);
	/*
	Cam.addTranslate( MouseDiff );
	Cam.updateTranslate();*/
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize(WindowSize.X, WindowSize.Y);
    glutInitWindowPosition(10,10);
    glutCreateWindow("glTest");
    
    glutDisplayFunc(draw);
    glutIdleFunc(redraw);
    
    glutKeyboardFunc(handleKeyPress);
    glutSpecialFunc(handleSpecialPress);
    glutMouseFunc(handleMousePress);
    glutMotionFunc(handleMouseMotion);
    
    Cam.init();
    
    glutMainLoop();
}