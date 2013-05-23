#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Pos.h"
#include "DEBUG.h"
#include <GL/glut.h>

struct CameraCEU
{
    PosXYZ Center;
    PosRPT Eye;		// Relative to Center
    PosXYZ Up;
    
    float translateSpeed;
    float rotateSpeed;
    float scaleSpeed;
    
    float clipNear;
    float clipFar;
    
    PosXY WindowSize;
    
    CameraCEU()
    {
    }
    
    void init()
    {
	Center = PosXYZ( 0.0, 0.0, 0.0 );
	setEyeToTop( 0.9 );
	Up = PosXYZ( 0.0 , 0.0 , 1.0 );
	
	translateSpeed = 0.01;
	rotateSpeed = 0.01;
	scaleSpeed = 0.01;
	
	WindowSize = PosXY(1024, 800);
	clipNear = 0.0001; 
	clipFar =6.0;
		
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	float tmpArray[4] = { 1.0, 1.0, 1.0, 0.6 };
//	float tmpArray2[4] = { 1.0, 1.0, 1.0, 0.3 };
	float off[4] = { 0.0, 0.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, tmpArray);
	glLightfv(GL_LIGHT0, GL_SPECULAR, tmpArray);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, tmpArray);
	glLightfv(GL_LIGHT0, GL_AMBIENT, tmpArray);
			
	glShadeModel( GL_SMOOTH );
	glEnable( GL_DEPTH_TEST );
	
    }
    
    void update()
    {
	clipNear = 0.01 * Eye.radius;
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(45, WindowSize.X/WindowSize.Y, clipNear, clipFar);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	PosXYZ DispEye = getEyeXYZ();
	printView();
	// gluLookAt( 1.1 , 1.1 , 1.1 , 0 , 0 , 0.0 , 0 , 0 , 1 );
	
	gluLookAt( DispEye.X , DispEye.Y , DispEye.Z ,
		    Center.X , Center.Y , Center.Z ,
		    Up.X , Up.Y , Up.Z );
    }
    
    void drawCenter()
    {
	glDisable(GL_LIGHTING);
	glShadeModel( GL_FLAT );
	
	Colors::Yellow.get();
	glTranslatef( Center.X , Center.Y , Center.Z );
	
	float scaleFactor = Eye.radius * 0.01;
	glScalef( scaleFactor , scaleFactor, scaleFactor );
	// glutWireOctahedron();
	glutWireSphere( 1.0 , 6 , 6 );
	glScalef( 1/scaleFactor, 1/scaleFactor, 1/scaleFactor );
	glTranslatef( -Center.X , -Center.Y , -Center.Z );
	
	glShadeModel( GL_SMOOTH );
	glEnable(GL_LIGHTING);
    }
    
    void translateXYZ( PosXY MouseDiff )
    {
	translateForward( MouseDiff.Y * translateSpeed * Eye.radius );
	translateRight( - MouseDiff.X * translateSpeed * Eye.radius );
    }
    
    void translateForward( float f )
    {
	PosRPT R( f , Eye.phi + PI , PI/2 );
	PosXYZ S( R );
	S.X += Center.X;
	S.Y += Center.Y;
	S.Z += Center.Z;
	
	Center.X = S.X;
	Center.Y = S.Y;
	Center.Z = S.Z;
    }
    
    void translateRight( float f )
    {
	PosRPT R( f , Eye.phi + (PI/2) , PI/2 );
	PosXYZ S( R );
	S.X += Center.X;
	S.Y += Center.Y;
	S.Z += Center.Z;
	
	Center.X = S.X;
	Center.Y = S.Y;
	Center.Z = S.Z;
    }
    
    void rotateXYZ( PosXY MouseDiff )
    {
	rotateZ( MouseDiff.X * rotateSpeed );
	rotateXY( MouseDiff.Y * rotateSpeed );
    }
    
    void rotateZ( float f )
    {
	Eye.phi -= f;
    }
    
    void rotateXY( float f )
    {
	if((Eye.theta - f) > (PI/2))
	    Eye.theta = PI/2;
	else if((Eye.theta - f) < 0.0)
	    Eye.theta = 0.01;
	//if( (Eye.theta - f) >= 0.0 && (Eye.theta - f) <= (PI/2))
	else    
	    Eye.theta -= f;
    }
    
    void scaleXYZ( PosXY MouseDiff )
    {
	float n_value = Eye.radius + (MouseDiff.Y * scaleSpeed);
	if(n_value < 0.1)
	    Eye.radius = 0.1;
	else if(n_value > (clipFar/2))
	    Eye.radius = clipFar/2;
	else
	    Eye.radius = n_value;
	
	// clipNear = 0.01 * Eye.radius;
    }
    
    void printView()
    {
	DEBUG("Center.X", Center.X);
	DEBUG("Center.Y", Center.Y);
	DEBUG("Center.Z", Center.Z);
	DEBUG("Eye.radius", Eye.radius);
	DEBUG("Eye.phi", Eye.phi);
	DEBUG("Eye.theta", Eye.theta);
	/*
	PosXYZ Disp = getEyeXYZ();
	DEBUG("Eye.X", Disp.X);
	DEBUG("Eye.Y", Disp.Y);
	DEBUG("Eye.Z", Disp.Z);*/
	DEBUG("clipNear", clipNear);
	
	
    }
    
    PosXYZ getEyeXYZ()
    {
	PosXYZ DispEye( Eye );
	DispEye.X += Center.X;
	DispEye.Y += Center.Y;
	DispEye.Z += Center.Z;
	return DispEye;
    }
    
    void setEyeToTop(float f1 = 1.0)
    {
	Eye = PosRPT( f1 , 0.0, 0.01 );
    }
    /*
    void setEyeToNormal(float f1 = 1.0)
    {
	
    }*/
    
    
};

#endif