#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>

#include <GL/glut.h>
#include <GL/glu.h>

#include "headers/Color.h"
#include "headers/Pos.h"
#include "headers/Draw.h"
#include "headers/transform.h"
#include "headers/PosManager.h"
#include "headers/GEOMETRY.h"

using namespace std;

PosXYZ Cam(0.0f, 0.0f, 0.0f);
float CamTranslateSpeed = -0.05f;
int ModelView_MatrixStack = 0;
bool jj_flag = false;
float jj = 0.0;

void draw_rotation()
{
    if(jj_flag) jj += 0.04f;
    static int i = 0;
    
    float len = 1.0f;
    
    vector< Pos* > Axis;
    Axis.push_back( new PosXY( 1.0, 0.0 ));
    Axis.push_back( new PosXY( -1.0, 0.0 ));
    Axis.push_back( new PosXY( 0.0, 1.0 ));
    Axis.push_back( new PosXY( 0.0, -1.0 ));
    
    vector< Pos* > V1;

    PosXY P1 = PosRP( 0.3f, 3*(PI/4) );
    PosXY Pivot( P1.X , 0.0 );
    PosXY P2 = transform::rotateXY( P1, Pivot, jj );
    // PosXY P2( transform::rotateXYaboutOrigin( P1, PI/2 ) );
    if(i == 0) std::cout << "P1 is " << P1.X << ", " << P1.Y << endl;
    if(i == 0) std::cout << "Pexp is " << P1.X << ", " << P1.Y - PI << endl;
    if(i == 0) std::cout << "P2 is " << P2.X << ", " << P2.Y << endl;
    jj_flag ? V1.push_back( &P2 ) : V1.push_back( &P1 );//

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef( Cam.X, Cam.Y, Cam.Z );
	Draw::Generic( GL_LINES, Axis );
	Draw::Generic( GL_POINTS, V1 );
    glutSwapBuffers();
    
}

void draw()
{
    PosManager PM;
    
    PM.make( GO_SQUARE( 0.5f ), PosXYZ() );
    
    vector< Pos* > Axis;
    Axis.push_back( new PosXY( 1.0, 0.0 ));
    Axis.push_back( new PosXY( -1.0, 0.0 ));
    Axis.push_back( new PosXY( 0.0, 1.0 ));
    Axis.push_back( new PosXY( 0.0, -1.0 ));
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef( Cam.X, Cam.Y, Cam.Z );
	Draw::Generic( GL_LINES, Axis );
	Draw::Generic( PM );
    glutSwapBuffers();
    
    Cam.X = 0; Cam.Y = 0; Cam.Z = 0;
}

void handleKeyPress(unsigned char key, int x, int y)
{
  
}

void handleSpecialPress(int key, int x, int y)
{
    switch(key)
    {
	    case GLUT_KEY_LEFT:
		    Cam.X -= CamTranslateSpeed;
		    break;
	    case GLUT_KEY_RIGHT:
		    Cam.X += CamTranslateSpeed;
		    break;
	    case GLUT_KEY_UP:
		    Cam.Y += CamTranslateSpeed;
		    break;
	    case GLUT_KEY_DOWN:
		    Cam.Y -= CamTranslateSpeed;
		    break;
	    case GLUT_KEY_PAGE_UP:
		    Cam.Z += CamTranslateSpeed;
		    break;
	    case GLUT_KEY_PAGE_DOWN:
		    Cam.Z -= CamTranslateSpeed;
		    break;

	    case GLUT_KEY_F1:
		    if( ModelView_MatrixStack != 0 ) { glPopMatrix(); glPushMatrix(); }
		    break;
	    case GLUT_KEY_F2:
		    // jj++;
		    jj_flag = true;
		    break;
    }
}

void initializeMain()
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
  
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glEnable( GL_DEPTH_TEST );
  glutInitWindowSize(800,600);
  glutInitWindowPosition(10,10);
  glutCreateWindow("glTest");

  glutDisplayFunc(draw);
  /* where draw(): lambda<void> */
  
  // glutKeyboardFunc(handleKeyPress);
  /* where handleKeyPress(
   *		key: unsigned-char, 
   * 		x:int, 
   * 		y:int): lambda<void> */
  
  glutSpecialFunc(handleSpecialPress);
  /* where handleSpecialPress(
   *		key: int, 
   * 		x:int, 
   * 		y:int): lambda<void> */
  
  glutIdleFunc(draw);
  /* where draw(): lambda */
  
  initializeMain();
  
  glutMainLoop();

  cout << "JOBS DONE" << endl;
  
  return 0;
}