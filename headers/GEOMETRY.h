#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Pos.h"

class GEOMETRY_OBJECT
{
    
};

class GO_CUBE : public GEOMETRY_OBJECT
{public:
    float length;
    PosXYZ rotational_state;
    
    GO_CUBE(float f1): length(f1), rotational_state() {}
};

class GO_SQUARE : public GEOMETRY_OBJECT
{public:
    float length;
    PosXYZ rotational_state;
    
    GO_SQUARE(float f1): length(f1) {}
};

#endif