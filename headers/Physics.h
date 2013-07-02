#ifndef __PHYSICS_H__
#define __PHYSICS_H__

namespace physics
{
    void moderateDivEq(float* target, float rate, float snapToZeroRange = 0.00001)
    {
	// if(*target != 0) { DEBUG("TARGET", *target); }
	*target = ( *target / (1+rate) );
	*target = (*target < snapToZeroRange && *target > -snapToZeroRange ? 0 : *target);
    }  
    
    void moderateEaseIn(float* target, float rate, float snapToZeroRange = 0.00001)
    // Assumes max value for target is 1 and min is 0
    // Divide by Max before passing in target
    // Do inverse after
    {
	float tr = *target;
	moderateDivEq(target, rate*(1 + (*target)), snapToZeroRange);
    }
};

#endif