#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Pos.h"

class Camera
{public:
    PosXYZ eye;
    PosXYZ center;
    PosXYZ up;
    bool changed;
    
    Camera(): eye( 0.0, 0.0, 10.0f ), center( 0.0, 0.0, -100.0f ), 
	up(0.0, 1.0, 0.0), changed(true) {}
    
    void setEye(float f1, float f2, float f3) { eye = PosXYZ(f1,f2,f3); changed = true; }
    void setCenter(float f1, float f2, float f3) { center = PosXYZ(f1,f2,f3); changed = true; }
    void setUp(float f1, float f2, float f3) { up = PosXYZ(f1,f2,f3); changed = true; }
    
    bool MoveSet;
    bool RotateSet;
    
    PosXYZ NextMove;
    PosXYZ NextRotate;
    PosXYZ NextCenter;
    
    
};

#endif