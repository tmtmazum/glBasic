#ifndef GLBASICMAIN_H
#define GLBASICMAIN_H
#endif
#if 0
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>

#include "Color.h"
#include "Pos.h"
#include "Draw.h"
#include "transform.h"
#include "PosManager.h"
#include "GEOMETRY.h"
#include "CameraCEU.h"
#include "Material.h"

#include <GL/glut.h>

using namespace std;

class GL_CONTROL
// To use this class, first make an inherited class
// then call the required functions starting with 'CallMe..'
// from inside your main. Derive ONLY the virtual functions
// that you require, and DO NOT change this file.
{
    PosXY WindowSize;
    PosXY WindowPosition;
    string WindowTitle;
    ColorRGBA WindowBackColor;
    
    PosXY MouseDiff;
    bool pressLMB;
    bool pressMMB;
    bool pressRMB;
    int lastButton;
    PosXY MousePos;
    
private:
    void initSettings()
    {
	WindowSize = PosXY( 1024 , 800 );
	WindowPosition = PosXY( 10, 10 );
	WindowTitle = "GL Unnamed Window";
	WindowBackColor = ColorRGBA( 0.7f , 0.7f , 0.7f, 0.5f );

	pressLMB = false;
	pressMMB = false;
	pressRMB = false;
	lastButton = -1;
    }

protected:
    virtual void draw()
    {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glutSwapBuffers();
    }
    
    virtual void redraw()
    {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glutSwapBuffers();
    }
    
    virtual void handleKeyPress( unsigned char key, int x, int y )
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
    }

    virtual void handleSpecialPress( int key, int x, int y )
    {
	switch(key)
	{
	    case GLUT_KEY_F1:
		break;
	    case GLUT_KEY_F2:
		break;
	    case GLUT_KEY_F3:
		break;
	}
    }
    
    void handleMousePress( int button, int state, int x, int y )
    {
	switch(button)
	{
	    case GLUT_LEFT_BUTTON:
		if(state==GLUT_DOWN) pressLMB = true;
		else 
		{
		    pressLMB = false;
		    lastButton = 0;
		}
		MousePos = PosXY( x, y );
		break;
	    case GLUT_MIDDLE_BUTTON:
		if(state==GLUT_DOWN) pressMMB = true;
		else if(state==GLUT_UP) 
		{
		    pressMMB = false;
		    lastButton = 1;
		}
		MousePos = PosXY( x, y );
		break;
	    case GLUT_RIGHT_BUTTON:
		if(state==GLUT_DOWN) pressRMB = true;
		else if(state==GLUT_UP) 
		{
		    pressRMB = false;
		    lastButton = 2;
		}
		MousePos = PosXY( x, y );
		break;
	}
    }

    void handleMouseMotion( int x, int y )
    {
	// MouseDiff = getMouseDiff(x,y);
    }
    
public:
    GL_CONTROL() { initSettings(); }
    
    void CallMeAtEndOfMain(int argc , char** argv)
    {
	glutInit(&argc, argv);
	
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(WindowSize.X, WindowSize.Y);
	glutInitWindowPosition(WindowPosition.X,WindowPosition.Y);
	// glutCreateWindow(WindowTitle);
	
	glClearColor( WindowBackColor.R, WindowBackColor.G, WindowBackColor.B , WindowBackColor.A );
	/*glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	*/
	void (*)() = reinterpret_cast<void(*)()>( this->draw );
	// glutDisplayFunc( reinterpret_cast<void(*)()>( this->draw ) );/*
	glutIdleFunc(this->redraw);
	
	glutKeyboardFunc(this->handleKeyPress);
	glutSpecialFunc(this->handleSpecialPress);
	glutMouseFunc(this->handleMousePress);
	glutMotionFunc(this->handleMouseMotion);*/
	
	// Cam.init();
	
	glutMainLoop();
    }
};

#endif