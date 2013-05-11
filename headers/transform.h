#include <math.h>
#include "Pos.h"

const float PI = 4.0 * atan( 1.0 );

class angle
{
    float value;
    
    operator float() { return value; }
}

class anglePI : angle
// Radians in terms of pi
{
    anglePI(const anglePI& an) { value = an.value }
    anglePI(const angleRAD& an) { value = an.value / PI }
    anglePI(const angleDEG& an) { value = an.value / 180 }
}

class angleRAD : angle
{
    angleRAD(const angleRAD& an) { value = an.value }
    angleRAD(const angleDEG& an) { value = an.value * (180.0 / PI); }
    angleRAD(const anglePI& an) { value = an.value * PI; }
}

class angleDEG : angle
{
    angleDEG(const angleDEG& an) { value = an.value }
    angleDEG(const angleRAD& an) { value = an.value * (PI / 180.0); }
    
}

namespace transform
{
    
    void rotateXY( PosXY& target, const PosXY& pivot, 
	       const angleRAD& angle_of_rotation, bool clockwise = true)
    {
	PosRP Ptarget( target );
	PosRP Ppivot( pivot );
	
	PosRP out;
    }
    
    void rotateXYZ( PosXYZ& target, const PosXYZ& pivot, 
	       const angleRAD& angle_of_rotation, bool clockwise = true)
    {
	PosXYZ translate;	// Final translation to be performed
	
	/* Consider a Spherical Co-ordinate system. To obtain the angles
	 * theta and phi where phi is the X -> Y angle a.k.a. azumith angle
	 * and theta is the Z -> XY angle a.k.a. the polar angle */
	/*
	translate.X = 
	
	float r = 
	angleRAD theta = */
    }   
};