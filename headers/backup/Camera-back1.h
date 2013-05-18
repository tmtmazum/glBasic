#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Pos.h"
#include "DEBUG.h"
#include <GL/glut.h>

class Camera
{public:
	int ModelViewMatrixStack;
	int previousView;
	int currentView;
	int maxNumViews;
	bool viewChanged;
	
	PosXYZ* Views;
	
	double zoomFactor;
	float zNear, zFar;
	
	PosXYZ appliedTranslate;
	PosXYZ appliedRotate;
	PosXYZ appliedScale;
	
	PosXYZ defaultEye;
	PosXYZ defaultCenter;
	PosXYZ defaultUp;
	
	Camera(float windowWidth, float windowHeight): 
	ModelViewMatrixStack(0), currentView(0), maxNumViews(7), zoomFactor(1.0),
	zFar(1.0), zNear(3.5), viewChanged(false)
	{
		Views = new PosXYZ[ 3*maxNumViews ];
	
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective(50* zoomFactor, windowWidth/windowHeight, zNear, zFar );
		
		// setDefaultLookAt( PosXYZ( 0.9, 0.9, 0.9 ), PosXYZ( 0.0, 0.0, 0.0 ), PosXYZ( 0.0, 0.0, 1.0 ) );
		appliedTranslate = PosXYZ(0.0, 0.0, 0.0);
		appliedRotate = PosXYZ(0.0, 0.0, 0.0);
		appliedScale = PosXYZ(0.0, 0.0, 0.0);
		
		
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		GLfloat lightDir[] = { 0.0, 0.0, 1.0, 1.0 };
		GLfloat Pos[] = { 0.0, 0.0, -1.0 };
		GLfloat white[] = { 1.0, 0.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, lightDir);
		
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Pos); 

		// glLightfv(GL_LIGHT0, GL_AMBIENT, white);
		// glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
		glLightfv(GL_LIGHT0, GL_SPECULAR, white);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.9f); 
		
		glShadeModel( GL_SMOOTH );
	
		glEnable( GL_DEPTH_TEST );
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt( 0.9, 0.9, 0.9, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
		
		glPushMatrix();
		// refreshView();		
	}
	
	void resetView()
	// Recommended: Call this once at the beginning 
	// of your draw handler
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
	}
	
	void resetAndUpdateView()
	// Recommended: Call this once at the end 
	// of your draw handler
	{
		glMatrixMode( GL_MODELVIEW );
		
		if( viewChanged )
		{
			glPopMatrix();
			glLoadIdentity(); // Get rid of saved view 
			
			applyTranslate();
			applyRotate();
			applyScale();	// Make this the new view
			
			viewChanged=false;
		}
		else
		{
			glPopMatrix();	// Reload the saved view
		}
		glPushMatrix();
	}
	
	void saveViewAs(int i)
	{
		assert(i < maxNumViews);
		Views[i] = appliedTranslate;
		Views[i+1] = appliedRotate;
		Views[i+2] = appliedScale;
	}
	
	void goToView(int i)
	{
		assert(i < maxNumViews);
		appliedTranslate = Views[i];
		appliedRotate = Views[i+1];
		appliedScale = Views[i+3];
		currentView = i;
	}
	
	void goToDefaultView() 
	{ 
		appliedTranslate = PosXYZ(); 
		appliedRotate = PosXYZ(); 
		appliedScale = PosXYZ(); 
	}
	
	void addTranslate(PosXYZ P) { appliedTranslate = P; viewChanged=true;}
	void addRotate(PosXYZ P) { appliedRotate = P; viewChanged=true;}
	void addScale(PosXYZ P) { appliedTranslate = P; viewChanged=true;}
	
	void setDefaultLookAt( PosXYZ eye, PosXYZ center, PosXYZ up)
	{
		defaultEye = eye;
		defaultCenter = center;
		defaultUp = up;
	}
	
	private:
		void applyTranslate()
		{DEBUG("GAH", 1);
			const static float translateFactor = 10.0;
			glTranslatef( -appliedTranslate.X * translateFactor, -appliedTranslate.Y * translateFactor, -appliedTranslate.Z * translateFactor );
		}
		void applyRotate()
		{
			const static float rotateFactor = 10.0;
			glRotatef( -appliedTranslate.X * rotateFactor, 1.0f, 0.0f, 0.0f );
			glRotatef( -appliedTranslate.Y * rotateFactor, 0.0f, 1.0f, 0.0f );
			glRotatef( -appliedTranslate.Z * rotateFactor, 0.0f, 0.0f, 1.0f );
		}
		void applyScale()
		{
			glScalef( appliedScale.X, appliedScale.Y, appliedScale.Z );
		}

};

#endif
