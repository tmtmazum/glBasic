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
#include "headers/CameraCEU.h"
#include "headers/Material.h"

#include <GL/glut.h>

using namespace std;

const PosXY WindowSize(1024.0, 800.0);

PosXY MouseDiff;
bool pressLMB = false;
bool pressMMB = false;
bool pressRMB = false;
int lastButton = -1;
PosXY MousePos;

CameraCEU Cam;

PosXY SphereRotate(0.0, 0.0);

void drawObjects()
{
    bool bl[6];
    for(int i = 0; i < 6; ++i) bl[i] = false;
    bl[0] = true; bl[1]=true; bl[2]=true;
    
    PosXYZ PosSphere(0.5, 0.0, 0.0);
    // SphereRotate.X += 0.01;
    SphereRotate.Y += 0.001;
    PosSphere = 
	transform::rotateXYZaboutOrigin( PosSphere, SphereRotate.X, SphereRotate.Y );
	// Materials::all.get();
	glDisable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
	Draw::GridXY();
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	
	Colors::Red.get();
	// glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Colors::White.toArray());
	// Materials::chrome.get();
	// Draw::CubeLPM(0.1, PosXYZ(0.2,0.2,0.1), bl);
	

	// Draw::CubeLPM(0.1, PosXYZ(-0.2,-0.2,0.1), bl);

	glTranslatef(PosSphere.X, PosSphere.Y, PosSphere.Z);
	// Materials::pearl.get();
	// Colors::Blue.get();
	glutSolidSphere(0.1, 20, 20);
	glTranslatef(-PosSphere.X, -PosSphere.Y, -PosSphere.Z);
	
	Colors::Blue.get();
	// Materials::chrome.get();
	bl[0] = false; bl[1] = false;
	glShadeModel(GL_SMOOTH);
	Draw::CubeLPM(1.0, PosXYZ(0.0, 0.0, 1.0), bl);
	
	Cam.drawCenter();
}

void drawHUD()
{
    glShadeModel( GL_FLAT );
    glEnable( GL_LIGHTING );
    Colors::Green.get();
    PosXYZ CamS( Cam.getEyeXYZ() );
    glTranslatef( CamS.X , CamS.Y , CamS.Z );
	glBegin( GL_POLYGON );
	    glVertex3f( 1.0, 1.0, 0.0 );
	    glVertex3f( 1.0, -1.0, 0.0 );
	    glVertex3f( -1.0, -1.0, 0.0 );
	    glVertex3f( -1.0, 1.0, 0.0 );
	glEnd();
    
    glTranslatef( -CamS.X , -CamS.Y ,-CamS.Z );
    
}

void draw()
{
    Cam.update();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawObjects();
	drawHUD();
	
    glutSwapBuffers();
}

void redraw()
{
    
    if(pressLMB) Cam.translateXYZ( MouseDiff );
    if(pressMMB) Cam.rotateXYZ( MouseDiff );
    if(!pressLMB && !pressMMB && !pressRMB/* && lastButton==1*/)
    {
	switch(lastButton)
	{
	    // case 0: Cam.translateXYZ( MouseDiff ); break;
	    case 1: Cam.rotateXYZ( MouseDiff ); break;
	    case 2: Cam.scaleXYZ( MouseDiff ); break;
	}
	MouseDiff.X = (MouseDiff.X < 0.00001 && MouseDiff.X > -0.0000001 ? 0 : MouseDiff.X / 1.007 );
	MouseDiff.Y = (MouseDiff.Y < 0.00001 && MouseDiff.Y > -0.0000001 ? 0 : MouseDiff.Y / 1.007 );
    
	// MouseDiff.X = (MouseDiff.X < 0.0000001 && MouseDiff.X > -0.0000001 ? 0 : MouseDiff.X - copysign(0.0005,MouseDiff.X) );
	// MouseDiff.Y = (MouseDiff.Y < 0.0000001 && MouseDiff.Y > -0.0000001 ? 0 : MouseDiff.Y - copysign(0.0005,MouseDiff.Y) );
    }
    if(pressRMB) Cam.scaleXYZ( MouseDiff );
    
    Cam.update();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawObjects();
	drawHUD();
	
    glutSwapBuffers();
}


void handleKeyPress( unsigned char key, int x, int y )
{
    switch(key)
    {
	case 'w':
	    // SphereRotate.X += 0.1;
	    break;
	case 'a':
	    // SphereRotate.Y -= 0.1;
	    break;
	case 's':
	    // SphereRotate.X -= 0.1;
	    break;
	case 'd':
	    // SphereRotate.Y += 0.1;
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
	    // Cam.printView();
	    Cam.setEyeToNormal();
	    break;
	case GLUT_KEY_F2:
	    Cam.setCenterToOrigin();
	    // Cam.setView1();
	    break;
	case GLUT_KEY_F3:
	    Cam.setEyeToTop();
	    // Cam.printMatrix();
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
    MouseDiff = getMouseDiff(x,y);
//	    MousePos = PosXY( x, y );
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