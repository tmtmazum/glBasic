#if 0
#define __CAMERA_H__

#include <cmath>

#include "Pos.h"
#include "DEBUG.h"
#include <GL/glut.h>

class Camera
{public:
    PosXYZ translateXYZ;
    PosXYZ rotateXYZ;
    PosXYZ scaleXYZ;
    /*
    PosXYZ rateTranslateXYZ;
    PosXYZ rateRotateXYZ;
    PosXYZ rateScaleXYZ;
    */
    
    float rotateSpeed;
    float translateSpeed;
    float scaleSpeed;
    
    PosXY Aspect;
    PosXY WindowSize;
    
    float* transform;
    
    Camera() : Aspect(2.5, 2.5), WindowSize(800,600),
    translateXYZ(0.0,0.0,0.0), rotateXYZ(0.0, 0.0, 0.0),
    scaleXYZ(1.0,1.0,1.0)
    {
    }
    
    void init()
    {
	rotateSpeed= 0.5;
	translateSpeed= 0.01;
	scaleSpeed= 1.0;
	
	setView1();
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(45, WindowSize.X/WindowSize.Y, Aspect.X, Aspect.Y);
	
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
    
    void setView1()
    {
	translateXYZ = PosXYZ(0,0,0);
	rotateXYZ = PosXYZ(450,0,95);
	scaleXYZ = PosXYZ(10,10,10);
    }
    
    void printView()
    {
	DEBUG("Transl.X", translateXYZ.X);
	DEBUG("Transl.Y", translateXYZ.Y);
	DEBUG("Transl.Z", translateXYZ.Z);
	
	DEBUG("Rot.X", rotateXYZ.X);
	DEBUG("Rot.Y", rotateXYZ.Y);
	DEBUG("Rot.Z", rotateXYZ.Z);
	
	DEBUG("Scale.X", scaleXYZ.X);
	DEBUG("Scale.Y", scaleXYZ.Y);
	DEBUG("Scale.Z", scaleXYZ.Z);
    }
    
    void printMatrix()
    {
	float mat44[16];
	glGetFloatv( GL_MODELVIEW , mat44 );
	for(int i = 0; i < 16; ++i)
	{
	    DEBUG("mat44", mat44[i]); 
	}
    }
    
    void addRotate(PosXY MouseDiff)
    {
	if(rotateXYZ.X-MouseDiff.Y > 180
	    && rotateXYZ.X-MouseDiff.Y < 540 )
	    rotateXYZ.X -= MouseDiff.Y;
	/*
	if(rotateXYZ.Z-MouseDiff.X > -180
	    && rotateXYZ.Z-MouseDiff.X < 180)*/
	    rotateXYZ.Z -= MouseDiff.X;
    }
    
    void addTranslate( PosXY MouseDiff )
    {
	translateXYZ.Y += MouseDiff.Y;
	translateXYZ.X += MouseDiff.X;
	/*
	transform = new float[16];
	float* mat = transform;
	for(int i = 0; i < 16; ++i)
	{
	    mat[i] = 0;
	}
	mat[0] = 1;
	mat[5] = 1;
	mat[10] = 1;
	
	mat[13] = MouseDiff.X;
	mat[14] = MouseDiff.Y;
	mat[15] = 1;*/
    }
    
    void addScale( PosXY MouseDiff )
    {
	float del = scaleXYZ.X - (MouseDiff.Y/100);
	del = 0.0 > del ? 0.0 : del;
	scaleXYZ.X = del;
	scaleXYZ.Y = del;
	scaleXYZ.Z = del;
    }
    
    void update()
    {
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	glRotatef(rotateSpeed*rotateXYZ.X, 1.0, 0.0, 0.0);
	glRotatef(rotateSpeed*rotateXYZ.Y, 0.0, 1.0, 0.0);
	glRotatef(rotateSpeed*rotateXYZ.Z, 0.0, 0.0, 1.0);
    
	updateTranslate();
	
	glScalef( scaleXYZ.X * scaleSpeed,
		  scaleXYZ.Y * scaleSpeed,
		    scaleXYZ.Z * scaleSpeed);
	
	//glMultMatrixf( transform );
    }
    
    void updateTranslate()
    {
	/*
	float mat[16];
	glGetFloatv( GL_MODELVIEW, mat );
	mat[0] += translateXYZ.X;
	mat[1] += translateXYZ.Y;
	glLoadMatrixf( mat );*/
	
	glTranslatef(translateXYZ.X * translateSpeed, 
		     translateXYZ.Y * translateSpeed,
		    translateXYZ.Z * translateSpeed);
		    
    }

};

#endif