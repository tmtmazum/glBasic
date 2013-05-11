#ifndef __POS_H__
#define __POS_H__

#include "Color.h"

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

class PosXY : public Pos
{
	public:
		PosX X;
		PosY Y;
	
	public:
		PosXY(float f1, float f2): Pos(), X(f1), Y(f2) {}
		PosXY(): Pos(), X(0), Y(0) {}
		
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
		
		void getVertex();
};

#endif