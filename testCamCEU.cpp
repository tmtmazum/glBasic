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

PosXYZ MainLight( 0.0 , 0.0 , 0.5 );

void drawObjects()
{
    bool bl[6];
    for(int i = 0; i < 6; ++i) bl[i] = false;
    bl[0] = true; bl[1]=true; bl[2]=true;
    
    PosXYZ PosSphere(0.5, 0.0, 0.0);
    if( SphereRotate.X > 2*PI + PI/8) { SphereRotate = PosXY(0.0, 0.0); }
    else if( SphereRotate.Y > 2*PI + PI/8 ) SphereRotate.X += 0.002;
    else SphereRotate.Y += 0.002;
    PosSphere = 
	transform::rotateXYZaboutOrigin( PosSphere, SphereRotate.X, SphereRotate.Y );
	
	Colors::Red.get();
	// glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Colors::White.toArray());
	// Materials::chrome.get();
	// Draw::CubeLPM(0.1, PosXYZ(0.2,0.2,0.1), bl);
	

	// Draw::CubeLPM(0.1, PosXYZ(-0.2,-0.2,0.1), bl);
/*
	glTranslatef(PosSphere.X, PosSphere.Y, PosSphere.Z);
	glShadeModel( GL_SMOOTH );
	glutSolidSphere(0.1, 20, 20);
	glTranslatef(-PosSphere.X, -PosSphere.Y, -PosSphere.Z);
*/	
	glTranslatef(MainLight.X, MainLight.Y, MainLight.Z);
	glDisable( GL_LIGHTING );
	Colors::White.get();
	glutSolidSphere(0.01, 10, 10);
	glTranslatef(-MainLight.X, -MainLight.Y, -MainLight.Z);
	glEnable( GL_LIGHTING );
	// Colors::Blue.get();
	// Materials::chrome.get();
	bl[0] = false; bl[1] = false;
	PosXYZ dis(0.0, 0.0, 0.0);
	// Draw::CubeLPM(1.0, PosXYZ(0.0, 0.0, 1.0), bl);
	
	WO_SINGLE WS1( new GO_CUBOID( 0.03, 0.03, 0.03, ~GO_CUBOID::LEFT & ~GO_CUBOID::RIGHT ) );
	WS1[ PosXYZ(0.0, 0.5, 0.5) ] [ PosRPT(2.0, SphereRotate.Y, SphereRotate.X) ][ Colors::Red ];
	
	
	glShadeModel( GL_FLAT );
	Draw::Generic( WS1 );
	
	Colors::Green.get();
	glShadeModel( GL_SMOOTH );
	
	glTranslatef( 0.0, 0.0, 0.5 );
	glutSolidSphere(0.1, 20, 20);
	glTranslatef( 0.0, 0.0, -0.5 );
	
	glDepthMask(GL_FALSE);
	//Draw::GridXYChequered();
	
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	
	glClear( GL_STENCIL_BUFFER_BIT );
	glEnable(GL_STENCIL_TEST);
	glStencilFunc( GL_ALWAYS , 1, 0xFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	
	Draw::GridXYChequered();
	
	glDepthMask(GL_TRUE);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	
	ColorRGBA Gr1 = Colors::Green;
	Gr1.A = 0.3;
	Gr1.get();
	
	glTranslatef( 0.0, 0.0, -0.5 );
	glutSolidSphere(0.1, 20, 20);
	glTranslatef( 0.0, 0.0, 0.5 );
	
	WS1.C.A = 0.2;
	glScalef(1.0, 1.0, -1.0);
	glShadeModel( GL_FLAT );
	Draw::Generic( WS1 );
	glShadeModel( GL_SMOOTH);
	glScalef(1.0, 1.0, -1.0);
	
	glDisable(GL_STENCIL_TEST);
	
	// Cam.drawCenter();
}

void drawHUD()
{
    glShadeModel( GL_FLAT );
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

void setLighting(int i = 2)
{
    if(i == 1)
    {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    float tmpArray[4] = { 0.9, 0.9, 0.9, 1.0 };
    float lowArray[4] = { 0.3, 0.3, 0.3, 1.0 };
    float MainLightPos[4] = { MainLight.X , MainLight.Y , MainLight.Z , 0.0 };
    float MainLightDir[4] = { Cam.Center.X , Cam.Center.Y , Cam.Center.Z };
//	float tmpArray2[4] = { 1.0, 1.0, 1.0, 0.3 };
    float off[4] = { 0.0, 0.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, MainLightPos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, MainLightDir);
   //  glLightfv(GL_LIGHT0, GL_SPECULAR, tmpArray);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, tmpArray);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lowArray);

        glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );

		    GLfloat mat_specular[] = {0.8, 0.8, 0.8, 1.0};
GLfloat mat_shininess[] = { 10.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    // glColorMaterial( GL_FRONT_AND_BACK, GL_SPECULAR );
    // glDisable( GL_LIGHTING );
    }
    else if(i == 2)
    {
	float Top[4] = { 0.0, 0.0, 1.0, 0.0 };
	float Bottom[4] = { 0.0, 0.0, -1.0, 0.0 };
	float ambientPower[4] = { 0.1, 0.1, 0.1, 1.0 };
	
	float diffusePower[4] = { 0.8, 0.8, 0.8, 1.0 };
	float specularPower[4] = { 0.8, 0.8, 0.8, 1.0 };
	
	glLightfv(GL_LIGHT0, GL_POSITION, Top);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientPower);
	
	glLightfv(GL_LIGHT1, GL_POSITION, Bottom);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientPower);
	
	float Corner[4] = { MainLight.X, MainLight.Y, MainLight.Z, 1.0 };
	float BottomCorner[3] = {Cam.Center.X, Cam.Center.Y, Cam.Center.Z };
	
	float LightPos[4] = { Cam.Center.X , Cam.Center.Y , Cam.Center.Z - 0.2 , 1.0 };
	
	glLightfv(GL_LIGHT2, GL_POSITION, LightPos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, BottomCorner);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularPower);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffusePower);
	// glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, );
	
	glEnable(GL_LIGHTING);
	glShadeModel( GL_SMOOTH );
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	// glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	glEnable( GL_DEPTH_TEST );
    }
    else
    {
	// glDisable( GL_LIGHTING );
    }
}

void draw()
{
    setLighting();
    Cam.update();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawObjects();
	drawHUD();
	
    glutSwapBuffers();
}

void redraw()
{
    setLighting();
    if(pressMMB) Cam.translateXYZ( MouseDiff );
    if(pressLMB) Cam.rotateXYZ( MouseDiff );
    if(!pressLMB && !pressMMB && !pressRMB/* && lastButton==1*/)
    {
	switch(lastButton)
	{
	    case 0: Cam.rotateXYZ( MouseDiff ); break;
	    // case 1: Cam.rotateXYZ( MouseDiff ); break;
	    case 2: Cam.scaleXYZ( MouseDiff ); break;
	}
	MouseDiff.X = (MouseDiff.X < 0.00001 && MouseDiff.X > -0.0000001 ? 0 : MouseDiff.X / 1.007 );
	MouseDiff.Y = (MouseDiff.Y < 0.00001 && MouseDiff.Y > -0.0000001 ? 0 : MouseDiff.Y / 1.007 );
	
	// if(Cam.Eye.theta > (PI/2)) assert(false);
	Cam.Eye.theta = (Cam.Eye.theta > (PI/2) ? (Cam.Eye.theta - Cam.Eye.theta*abs(Cam.Eye.theta-(PI/2)))  : Cam.Eye.theta);// 0.00001 && MouseDiff.X > -0.0000001 ? 0 : MouseDiff.X / 1.007 );
	// MouseDiff.Y = (MouseDiff.Y < 0.00001 && MouseDiff.Y > -0.0000001 ? 0 : MouseDiff.Y / 1.007 );
    
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
	    MainLight.Z += 0.1;
	    break;
	case 'a':
	    MainLight.X -= 0.1;
	    break;
	case 's':
	    // SphereRotate.X -= 0.1;
	    MainLight.Z -= 0.1;
	    break;
	case 'd':
	    MainLight.X += 0.1;
	    break;
	case 'q':
	    MainLight.Y -= 0.1;
	    break;
	case 'e':
	    MainLight.Y += 0.1;
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
    glClearColor( 0.7f, 0.7f, 0.7f , 0.5f );
    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(draw);
    glutIdleFunc(redraw);
    
    glutKeyboardFunc(handleKeyPress);
    glutSpecialFunc(handleSpecialPress);
    glutMouseFunc(handleMousePress);
    glutMotionFunc(handleMouseMotion);
    
    Cam.init();
    
    glutMainLoop();
}