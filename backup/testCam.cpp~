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
int ModelView_MatrixStack = 0;
Camera Cam; 

PosXY WindowSize(800,640);

//	---

void draw()
{
    PosManager Axis;
    Axis.makeGridXY ( ColorRGBA(1.0, 1.0, 1.0, 1.0 ) );
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if( Cam.changed )
    {
	glLoadIdentity();
	// glTranslatef( 0.0, 0.0, 0.0  );
	// gluLookAt( 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0 );
	Cam.updateGl();
    
	Cam.changed = false;
    }
	glutBitmapCharacter( GLUT_BITMAP_8_BY_13, 't');
	glColor4f( 1.0, 1.0, 1.0, 1.0 );
      	// Draw::Generic( GL_LINES, Axis );
	Draw::Generic( Axis );
	// glMaterialf(GL_FRONT_AND_BACK, GL_SPECULAR, 1.0);
	/*
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120);
	float white[] = { 0.5, 0.5, 0.1, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	float emissiveColor[] = { 0.3, 0.3, 0.3, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissiveColor);
	*/
	// Draw::CubeLP( 0.3f, PosXYZ(), ColorRGBA(1.0, 0.1, 0.1));
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
	    Cam.rotateEyeY(-0.8);
	    break;
	case GLUT_KEY_RIGHT:
	    Cam.rotateEyeY(0.8);
	    break;
	case GLUT_KEY_UP:
	    break;
	case GLUT_KEY_DOWN:
	    break;
	case GLUT_KEY_F3:
	    glMatrixMode( GL_MODELVIEW );
	    glPopMatrix();
	    glPushMatrix();
	    break;
    } 
}

bool pressLMB = false;
bool pressMMB = false;
bool pressRMB = false;

PosXY MousePos;
void updateMouse(int x, int y)
{
    MousePos = PosXY(x, y);
}

PosXY MaxSpeed(0.0, 0.0);
PosXY getMouseDiff( int x, int y )
// Returns a ratio (0.0 to 1.0) for the
// difference in both x and y
{
    PosXY Diff( x - MousePos.X, y - MousePos.Y );
    // Diff.X /= WindowSize.X;
    // Diff.Y /= WindowSize.Y;
    Diff.X /= (glutGetModifiers()==GLUT_ACTIVE_SHIFT ? 1000 : 10000);
    Diff.Y /= (glutGetModifiers()==GLUT_ACTIVE_SHIFT ? 1000 : 10000);
    if(Diff.X > MaxSpeed.X) MaxSpeed.X = Diff.X;
    if(Diff.Y > MaxSpeed.Y) MaxSpeed.Y = Diff.Y;
    return Diff;
}

void handleMouse(int button, int state,
                  int x, int y)
{
    if(state==GLUT_UP) MaxSpeed = PosXY(0.0, 0.0);
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
    updateMouse( x, y );
}

void handleMotion(int x, int y)
{
    if(pressLMB)
    {
	PosXY diff = getMouseDiff(x, y);
	Cam.moveEye( PosXYZ(diff.X, - diff.Y, 0.0) );
	
	updateMouse(x, y);
    }
    if(pressMMB)
    {
	PosXY diff = getMouseDiff(x, y);
	// Cam.rotateEyeY( diff.X * 128);
	Cam.rotateEyeZ( diff.X * 128);
	Cam.rotateEyeX( diff.X * 128 );
	updateMouse(x, y);
    }
    if(pressRMB)
    {
	PosXY diff = getMouseDiff(x, y);
	// Cam.moveEye( PosXYZ( 0.0, 0.0, diff.Y ) );
	glScalef( 1.0 + diff.Y, 1.0 + diff.Y , 1.0 + diff.Y );
	// Cam.moveCenter( 0.0, 0.0, diff.Y );
	
	updateMouse(x, y);
    }
}

void initView()
// This is my own initialize function
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective( 45.0, WindowSize.X / WindowSize.Y, 
		    10.0, 10.0 );
  
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glRotatef(5.0, 1.0, 0.0, 0.0 );
    
    glPushMatrix();
    ModelView_MatrixStack += 1;
    
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WindowSize.X,WindowSize.Y);
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