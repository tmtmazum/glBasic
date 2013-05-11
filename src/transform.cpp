#include "../headers/transform.h"
#include "../headers/DEBUG.h"

PosXY transform::rotateXY( PosXY& target, const PosXY& pivot, 
	    const angleRAD& angle_of_rotation, 
	    bool clockwise)
{
    PosXY Pn( transform::getRelativeXY( target, pivot ) );
    PosXY Origin(-pivot.X, -pivot.Y);
    PosXY Px( transform::getRelativeXY( 
	transform::rotateXYaboutOrigin( Pn, 
					angle_of_rotation, 
					clockwise ),
		    Origin ) );
    return Px;
}

PosXY transform::rotateXYaboutOrigin( PosXY& target, 
			    const angleRAD& angle_of_rotation, 
			    bool clockwise)
{
    PosRP temp( target );

    PosXY rv( rotateRPaboutOrigin( temp, angle_of_rotation, clockwise ) );
    return rv;
}

PosRP transform::rotateRPaboutOrigin( PosRP& target, 
			    const angleRAD& angle_of_rotation, 
			    bool clockwise)
{
    float direction = ( clockwise ? -1 : 1 );
    PosRP temp( target.radius, target.angle + direction*(angle_of_rotation.value) );

    return temp;
}

void transform::rotateXYZ( PosXYZ& target, const PosXYZ& pivot, 
	    const angleRAD& angle_of_rotation, bool clockwise)
{
    // PosXYZ translate;	// Final translation to be performed
    
    /* Consider a Spherical Co-ordinate system. To obtain the angles
	* theta and phi where phi is the X -> Y angle a.k.a. azumith angle
	* and theta is the Z -> XY angle a.k.a. the polar angle */
    /*
    translate.X = 
    
    float r = 
    angleRAD theta = */
}   

PosXY transform::translateXY( PosXY& target, const PosXY& translation )
{
    return PosXY( target.X + translation.X, target.Y + translation.Y );
}

PosXY transform::getRelativeXY( PosXY target, PosXY new_origin )
// Gets the relative position of 'target' from 'new_origin'
{
    return translateXY( target, PosXY( -new_origin.X, -new_origin.Y ) );
}