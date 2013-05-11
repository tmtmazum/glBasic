#include <math.h>
#include "headers/Pos.h"

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
}

class angleDEG : angle
{
    angleDEG(const angleDEG& an) { value = an.value }
    angleDEG(const angleRAD& an) { value = an.value * (PI / 180.0); }
    
}

namespace transform
{
    rotateXYZ( PosXYZ target, PosXYZ pivot, angle
    
};