#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <string>

#include "VECTOR.h"
#include "Pos.h"
#include "Material.h"
#include "Color.h"
#include "Texture.h"

struct GEOMETRY_OBJECT
{
    bool SHOW_BLUEPRINT;
    virtual void dummy() {}
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

class GO_FACE : public GEOMETRY_OBJECT
{public:
    float width, height;
    VO_UNIT up, right;
    
    GO_FACE( const VO_UNIT& V1, const VO_UNIT& V2 ,
	     float wid, float hei ) : width(wid), height( hei ),
			up(V1), right(V2) {}
};

class GO_CUBOID : public GEOMETRY_OBJECT
{public:
  float length, width, height;
  int enabledFaces; //bool SHOW_BLUEPRINT;
  enum FACE
  {
    BOTTOM = 1, TOP = 8,
    LEFT = 2, RIGHT = 16,
    BACK = 4, FRONT = 32
  };
  
  GO_CUBOID(float f1, float f2, float f3, int enable = -1):
    length( f1 ) , width( f2 ), height( f3 ) , enabledFaces( enable ){ SHOW_BLUEPRINT=false; }
    
  int getType() { return 2; }
};

struct GO_CYLINDER : public GEOMETRY_OBJECT
{
    float radius, height;
    int splits, enabledFaces;
    
    enum FACE
    {
	SIDES = 1,
	FRONT = 2,
	BACK = 4
    };
    
    GO_CYLINDER( float f1 , float f2 , int i3, int enable = -1 ): radius(f1), height(f2), splits(i3), enabledFaces(enable) {}
};

struct GO_BEZIER_CURVE : public GEOMETRY_OBJECT
{
    std::vector< PosXYZ > ctrlPts;
    
    GO_BEZIER_CURVE( PosXYZ start, PosXYZ end )
    {
	ctrlPts.push_back( start );
	ctrlPts.push_back( end );
    }
    
    void operator[] (PosXYZ pt)
    {
	std::vector< PosXYZ >::reverse_iterator it = ctrlPts.rbegin();
	it++;
	// ctrlPts.insert( it , pt );
    }
};

class WORLD_OBJECT : public PosXYZ
{
    
};

class WO_SINGLE : public WORLD_OBJECT
{public:
    GEOMETRY_OBJECT* GOx;
    Material M; ColorRGBA C; TextureIF* T;
    PosRPT transform;	// Rotation + Scale
    
    int enabledOptions;
    
    enum OPTION
    {
	LIGHTING= 1,
	SMOOTH_SHADING = 2,
    };
    
private:
    WO_SINGLE(): M() , C(), transform(1.0, 0.0, 0.0), enabledOptions(-1), T() {}
    
    void defaultSettings()
    {
	M = Material();
	C = ColorRGBA(0.5, 0.5, 0.5, 0.5);
	transform = PosRPT( 1.0, 0.0, 0.0 );
	enabledOptions = -1;
	T = 0;
    }
public:
    
    WO_SINGLE( GEOMETRY_OBJECT* GO1 ):
	GOx( GO1 ) { defaultSettings(); }	// GO1 MUST be newed
	
    WO_SINGLE( const WO_SINGLE& WS1 ):
	GOx( WS1.GOx ) , M( WS1.M ) , C( WS1.C ),
	transform( WS1.transform ), enabledOptions( WS1.enabledOptions ) { defaultSettings(); }
	
    ~WO_SINGLE() { delete GOx; if(T) delete T;}
	
    WO_SINGLE& operator[]( const Material& M1 )
    {
	M = M1;
	return *this;
    }
    	
    WO_SINGLE& operator[]( const Color& C1 )
    {
	C = C1;
	return *this;
    }
    	
    WO_SINGLE& operator[]( const PosRPT& P1 )
    {
	transform = P1;
	return *this;
    }
    
    WO_SINGLE& operator[]( const int& i )
    {
	enabledOptions = i;
	return *this;
    }
    
    WO_SINGLE& operator[]( const PosXYZ& X1 )
    {
	X = X1.X;
	Y = X1.Y;
	Z = X1.Z;
	return *this;
    }
    
    WO_SINGLE& operator[]( TextureIF* Tx )
    {
	T = Tx;
    }
};

#endif