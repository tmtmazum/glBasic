#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Pos.h"
#include <GL/glut.h>

class Camera
{public:
    PosXYZ eye;
    PosXYZ center;
    PosXYZ up;
    bool changed;
    
    GLdouble* saved;
    
    Camera(): eye( 0.0, 0.0, 0.0 ), center( 0.0, 0.0, -1.0f ), 
	up(0.0, 1.0, 0.0), changed(true) {}
    
    void setEye(float f1, float f2, float f3) { eye = PosXYZ(f1,f2,f3); changed = true; }
    void setCenter(float f1, float f2, float f3) { center = PosXYZ(f1,f2,f3); changed = true; }
    void setUp(float f1, float f2, float f3) { up = PosXYZ(f1,f2,f3); changed = true; }
    
    void moveEye(float f1, float f2, float f3) { eye = PosXYZ(eye.X + f1, eye.Y+f2, eye.Z+f3); changed=true; }
    void moveEye( PosXYZ );
    
    void rotateEyeY(float f1);
    void rotateEyeX(float f1);
    void rotateEyeZ(float f1);
    void rotateEyeYSuspend();
    
    void moveCenter(float f1, float f2, float f3) { center = PosXYZ(center.X + f1, center.Y+f2, center.Z+f3); changed=true; }
    
    void updateGl();
    
    bool MoveSet;
    bool RotateSet;
    
};

#endif