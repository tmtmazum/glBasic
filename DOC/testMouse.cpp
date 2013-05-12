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
int ModelView_MatrixStack = 0;
const PosXYZ CamOriginalPos(0.0, 0.0, 0.0);
PosXYZ Cam(0.0, 0.0, 0.0);

PosXYZ moveCam( 0.0, 0.0, 0.0 );
bool CamMoveSet = false;
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
	Draw::Generic( GL_LINES, Axis );
	// Draw Cube
	
	PosXYZ cm(0,0,0); int len = 0.3f;/*
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
	glEnd();*/
	
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

void handleMouse(int button, int state,
                  int x, int y)
{
    switch(button)
    {
	case GLUT_LEFT_BUTTON:
	    if(state==GLUT_DOWN) pressLMB = true;
	    else if(state==GLUT_UP) pressLMB = false;
	    break;
	case GLUT_MIDDLE_BUTTON:
	    if(state==GLUT_DOWN) pressMMB = true;
	    else if(state==GLUT_UP) pressMMB = false;
	    break;
	case GLUT_RIGHT_BUTTON:
	    if(state==GLUT_DOWN) pressRMB = true;
	    else if(state==GLUT_UP) pressRMB = false;
	    break;
    }
}

void handleMotion(int x, int y)
{
    if(pressLMB)
    {
	cout << "LMB Motion at ( " << x << " , "
	    << y << " )" << endl;
    }
    if(pressMMB)
    {
	cout << "MMB Motion at ( " << x << " , "
	    << y << " )" << endl;
    }
    if(pressRMB)
    {
	cout << "RMB Motion at ( " << x << " , "
	    << y << " )" << endl;
    }
}

void initView()
// This is my own initialize function
{
    /*glMatrixMode(GL_PROJECTION);
    gluPerspective( 40.0, 1.0, 1.0, 10.0 ); */
  
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glPushMatrix();
    ModelView_MatrixStack += 1;
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(300,300);
  glutInitWindowPosition(10,10);
  glutCreateWindow("glTest");

  initView();
  
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