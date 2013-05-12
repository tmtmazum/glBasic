#include <iostream>
#include <vector>
#include <cassert>

#include "headers/Color.h"
#include "headers/Pos.h"
#include "headers/Draw.h"
#include "headers/transform.h"
#include "headers/PosManager.h"
#include "headers/GEOMETRY.h"

#include <GL/glut.h>

using namespace std;

/* Game State Constants */
int WindowWidth = 640;
int WindowHeight = 400;

int ModelView_MatrixStack = 0;
const PosXYZ CamOriginalPos(0.0, 0.0, 0.0);
PosXYZ Cam(0.0, 0.0, 0.0);

PosXYZ moveCam( 0.0, 0.0, 0.0 );
PosXYZ rotateCam( 0.0, 0.0, 0.0 );

bool CamMoveSet = false;
bool CamRotateSet = false;

float moveCamSpeed = -0.05; 

//	---

void draw()
{
    vector< Pos* > Axis;
    Axis.push_back( new PosXY( 1.0, 0.0 ));
    Axis.push_back( new PosXY( -1.0, 0.0 ));
    Axis.push_back( new PosXY( 0.0, 1.0 ));
    Axis.push_back( new PosXY( 0.0, -1.0 ));
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(CamMoveSet)
	{
	    glTranslatef( moveCam.X, moveCam.Y, moveCam.Z );
	    moveCam.X = 0.0;
	    moveCam.Y = 0.0;
	    moveCam.Z = 0.0;
	    CamMoveSet = false;
	}
	if(CamRotateSet)
	{
	    glRotatef( rotateCam.X, 1.0, 0, 0 );
	    glRotatef( rotateCam.Y, 0, 1.0, 0 );
	    glRotatef( rotateCam.Z, 0, 0, 1.0 );
	    rotateCam.X = 0.0;
	    rotateCam.Y = 0.0;
	    rotateCam.Z = 0.0;
	    CamRotateSet = false;
	}
	Draw::Generic( GL_LINES, Axis );
	// Draw Cube
	// Draw::Generic( PosManager( GO_SQUARE(0.3f), PosXYZ() ));
	
	Draw::CubeLP( 0.3f, PosXYZ(), ColorRGBA(1.0, 0.1, 0.1));

    glutSwapBuffers();

}

void handleKeyPress(unsigned char key, int x, int y)
{
     switch(key)
    {
	case 'w':
	    moveCam.Y += moveCamSpeed;
	    CamMoveSet = true;
	    break;
	case 'a':
	    moveCam.X -= moveCamSpeed;
	    CamMoveSet = true;
	    break;
	case 's':
	    moveCam.Y -= moveCamSpeed;
	    CamMoveSet = true;
	    break;
	case 'd':
	    moveCam.X += moveCamSpeed;
	    CamMoveSet = true;
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
    if(pressLMB)
    {
	cout << "LMB Motion at ( " << x << " , "
	    << y << " )" << endl;
	
	float zoomX = x - MousePos.X;
	float zoomY = y - MousePos.Y;
	moveCam.X += ( 4* zoomX / WindowWidth );
	moveCam.Y -= ( 4* zoomY / WindowHeight );
	CamMoveSet = true;
	MousePos = PosXY( x, y );
    }
    if(pressMMB)
    {
	cout << "MMB Motion at ( " << x << " , "
	    << y << " )" << endl;
	
	float zoomX = x - MousePos.X;
	float zoomY = y - MousePos.Y;
	rotateCam.X -= 128*zoomY / WindowHeight;
	rotateCam.Y += 128*zoomX / WindowWidth;
	CamRotateSet = true;
	MousePos = PosXY( x, y );
    }
    if(pressRMB)
    {
	cout << "RMB Motion at ( " << x << " , "
	    << y << " )" << endl;
	    
	float zoom = y - MousePos.Y;
	moveCam.Z += ( 4*zoom / WindowHeight );
	CamMoveSet = true;
	MousePos = PosXY( x, y );
    }
}

void initViewForeign()
{
  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. 
  glTranslatef(0.0, 0.0, -1.0);
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(-20, 0.0, 0.0, 1.0);*/
}

void initView()
// This is my own initialize function
{
    /*glMatrixMode(GL_PROJECTION);
    gluPerspective( 40.0, 1.0, 1.0, 10.0 ); */
    glEnable( GL_DEPTH_TEST );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glPushMatrix();
    ModelView_MatrixStack += 1;
}


int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WindowWidth , WindowHeight);
  glutInitWindowPosition(10,10);
  glutCreateWindow("glTest");

  initViewForeign();
  
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