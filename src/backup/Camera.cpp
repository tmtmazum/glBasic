#include "../headers/Camera.h"
#include "../headers/Pos.h"
#include "../headers/DEBUG.h"

#include <cmath>

#include <GL/glut.h>

void Camera::updateGl()
{/*
    static int i = 0;
    PosRP R( PosXY(eye.X, eye.Z) );
    R.angle.value += i/1000;
    PosXY N(R);
    eye = PosXYZ( N.X, eye.Y, N.Y );
    gluLookAt( eye.X, eye.Y, eye.Z, center.X, center.Y, center.Z,
	       up.X, up.Y, up.Z );*/
    // i++;
}
/*
void Camera::saveState()
{
    saved = new GLdouble[16];
    glGetDoublev(GL_MODELVIEW, saved);
}
*/
void Camera::moveEye(PosXYZ P)
{
    glTranslatef(P.X, P.Y, P.Z);
}

void Camera::rotateEyeY(float f1)
{
    glRotatef( f1, 0, 1.0, 0 );
}

void Camera::rotateEyeYSuspend()
{
    glRotatef( 64.0 , 0, 1.0, 0 );
}

void Camera::rotateEyeX(float f1)
{
    glRotatef( f1, 1.0, 0, 0 );
}

void Camera::rotateEyeZ(float f1)
{
    glRotatef( f1, 0, 0, 1.0 );
}