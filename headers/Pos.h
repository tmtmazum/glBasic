#ifndef __POS_H__
#define __POS_H__

#include "Color.h"
#include <math.h>

#define RT_SUM_OF_SQRS(a, b, c) sqrt( pow(a, 2), pow(b, 2), pow(c, 2) )

template<class ty>
ty root_sum_of_squares( ty t1, ty t2, ty t3 )
{
    sqrt( pow(t1, 2) + pow(t2, 2) + pow(t3, 2) );
}

typedef float PosX;
typedef float PosY;
typedef float PosZ;

class Pos
{
    protected:
	ColorRGBA C;
    public:
		virtual void getVertex() = 0;	// Calls OpenGL function for plotting a vertex
										// Example: glVertex2f( X, Y );
		void getColor() { C.get(); }
		void setColor( Color& C1 ) 
		    { C = C1; }
		    
		// Pos() : C() {}
};

class PosRP;

class PosXY : public Pos
{
	public:
		PosX X;
		PosY Y;
	
	public:
		PosXY(float f1, float f2): Pos(), X(f1), Y(f2) {}
		PosXY(): Pos(), X(0), Y(0) {}
		PosXY(const PosRP& P1);
		
		void getVertex();
}; 

class PosRP : public Pos
// Polar Co-ordinates w/ r (distance from origin), phi (angle of x->y)
{
public:
    float radius;
    float angle;
    
    PosRP(float f1, float f2): Pos(), radius(f1), angle(f2) {}
    PosRP(): Pos(), radius(0), radius(0) {}
    PosRP(const PosXY& P1);
    
    float operator-( const PosXY& P1 )
    // PosXYZ - PosXYZ computes the distance between the two points
    {
	return root_sum_of_squares<float>(P1.X - X, P1.Y - Y, 0);
    }
    
    void getVertex();
};

class PosXYZ : public Pos
{
	public:
		PosX X;
		PosY Y;
		PosZ Z;
		
	public:
		PosXYZ(float f1=0, float f2=0, float f3=0): 
			    Pos(), X(f1), Y(f2), Z(f3) {}
			    
		PosXYZ(): 
			    Pos(), X(0), Y(0), Z(0) {}
		
		PosXYZ( const PosXYZ& P1 ):
			    Pos(), X(P1.X), Y(P1.Y), Z(P1.Z) {}
		
		PosXYZ operator+( const PosXYZ& P1 )
		// The + Operator represents all translations
		// (1,1,1) + (2,2,2) = (3,3,3)
		{ 
		    return PosXYZ( this->X + P1.X, 
				    this->Y + P1.Y, 
				    this->Z + P1.Z );
		}
		
		PosXYZ operator+( const float& f1 )
		{
			return PosXYZ( X + f1, Y + f1, Z + f1 ); 
		}
		
		float operator-( const PosXYZ& P1 )
		// PosXYZ - PosXYZ computes the distance between the two points
		{
		    return root_sum_of_squares<float>(P1.X - X, P1.Y - Y, P1.Z - Z);
		}
		
		PosXY toXY() { return PosXY( X, Y ); }
		
		void getVertex();
};

#endif