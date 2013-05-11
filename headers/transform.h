#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <math.h>
#include "angle.h"
#include "Pos.h"



namespace transform
{
    
    PosXY rotateXY( PosXY& target, const PosXY& pivot, 
	       const angleRAD& angle_of_rotation, 
	       bool clockwise = true);
    
    PosXY rotateXYaboutOrigin( PosXY& target, 
			      const angleRAD& angle_of_rotation, 
			      bool clockwise = true);

    PosRP rotateRPaboutOrigin( PosRP& target, 
			    const angleRAD& angle_of_rotation, 
			    bool clockwise = true);   
    
    void rotateXYZ( PosXYZ& target, const PosXYZ& pivot, 
	       const angleRAD& angle_of_rotation, bool clockwise = true);
    
    PosXY translateXY( PosXY& target, const PosXY& translation );
    PosXY getRelativeXY( PosXY , PosXY );
};

#endif