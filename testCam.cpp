#include <iostream>
#include <vector>
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

/* Game State Constants */
int WindowWidth = 640;
int WindowHeight = 400;
Camera* Cam;

// ---

void drawObjects()
{
	glColor3f(1.0, 1.0, 1.0);
	PosManager P;
	P.makeGridXY();
	Draw::Generic( P );
}

void drawHUD()
{
}

void draw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    Cam->resetView();
    
    drawObjects();
    
    Cam->resetAndUpdateView();
    
    glutSwapBuffers();
}

void handleKeyPress(unsigned char key, int x, int y)
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
    }   
}

void handleSpecialPress(int key, int x, int y)
{
     switch(key)
    {
	case GLUT_KEY_LEFT:
	    break;
	case GLUT_KEY_RIGHT:
	    break;
	case GLUT_KEY_UP:
	    break;
	case GLUT_KEY_DOWN:
	    break;
    } 
}

bool pressLMB = false;
bool pressMMB = false;
bool pressRMB = false;

PosXY MousePos;

PosXY getMouseDiff( int x, int y )
{
    return PosXY( (x - MousePos.X)/WindowWidth, (y - MousePos.Y)/WindowHeight );
}

void handleMouse(int button, int state,
                  int x, int y)
{
    switch(button)
    {
	case GLUT_LEFT_BUTTON:
	    if(state==GLUT_DOWN) pressLMB = true;
	    else if(state==GLUT_UP) pressLMB = false;
	    MousePos = PosXY( x, y );
	    break;
	case GLUT_MIDDLE_BUTTON:
	    if(state==GLUT_DOWN) pressMMB = true;
	    else if(state==GLUT_UP) pressMMB = false;
	    MousePos = PosXY( x, y );
	    break;
	case GLUT_RIGHT_BUTTON:
	    if(state==GLUT_DOWN) pressRMB = true;
	    else if(state==GLUT_UP) pressRMB = false;
	    MousePos = PosXY( x, y );
	    break;
    }
}
void handleMotion(int x, int y)
{
    PosXY Diff = getMouseDiff(x,y);
    if(pressLMB)
    {
	Cam->addTranslate( PosXYZ(Diff.X, Diff.Y, 0.0) );
    }
    if(pressMMB)
    {
	Cam->addRotate( PosXYZ(0.0, 0.0, Diff.X) );
    }
    if(pressRMB)
    {
	// glScalef(Diff.Y * 64,Diff.Y * 64,Diff.Y * 64);
    }
}

void glSettings()
{

    
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WindowWidth , WindowHeight);
  glutInitWindowPosition(10,10);
  glutCreateWindow("glTest");

  Camera C(WindowWidth, WindowHeight);
  Cam = &C;
  
  glSettings();
  
  glutDisplayFunc(draw);
  /* where draw(): lambda<void> */
  
  glutKeyboardFunc(handleKeyPress);
  /* where handleKeyPress(
   *		key: unsigned-char, 
   * 		x:int, 
   * 		y:int): lambda<void> */
  
  glutSpecialFunc(handleSpecialPress);
  /* where handleSpecialPress(
   *		key: int, 
   * 		x:int, 
   * 		y:int): lambda<void> */
  
  glutMouseFunc(handleMouse);
  /* where handleMouse(
   * 		button: int
   * 		state: int
   * 		x: int
   * 		y: int) : lambda<void> */
  
  glutMotionFunc( handleMotion );
  /* where handleMouse(
   * 		x: int
   * 		y: int) : lambda<void> */
  
  glutIdleFunc(draw);
  /* where draw(): lambda */
  
  glutMainLoop();

  return 0;
}
