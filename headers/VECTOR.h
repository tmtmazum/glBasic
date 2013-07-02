#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Pos.h"

struct VECTOR_OBJECT
{
    
};

struct VO_UNIT : public VECTOR_OBJECT
// A unit vector signifying 3d direction
{
    float phi, theta;
    
    VO_UNIT( PosXYZ p1 )
    {
	PosRPT rep( p1 );
	this->phi = rep.getPhi();
	this->theta = rep.getTheta();
    }
    VO_UNIT( PosRPT r1 )
    {
	this->phi = r1.getPhi();
	this->theta = r1.getTheta();
    }
    VO_UNIT( const VO_UNIT& V1 )
    {
	this->phi = V1.phi;
	this->theta= V1.theta;
    }
    
    
    operator PosRPT()
    {
	return PosRPT( 1.0, phi, theta );
    }
    
};

struct VO_UNIT_UP : VO_UNIT
{
    VO_UNIT_UP() : VO_UNIT( PosXYZ(0.0, 0.0, 1.0)) {}
};

struct VO_UNIT_RIGHT : VO_UNIT
{
    VO_UNIT_RIGHT() : VO_UNIT( PosXYZ(1.0, 0.0, 0.0)) {}
};

#endif