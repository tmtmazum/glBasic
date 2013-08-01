#ifndef __DRAW_H__
#define __DRAW_H__

#include "Pos.h"
#include "Color.h"
#include "GEOMETRY.h"
#include <vector>

class PosManager;

namespace Draw
{/*
	void Points( std::vector< Pos >& );

	void Line( Pos, Pos );
	void Lines( std::vector< Pos >& );
	void LineStrip( std::vector< Pos >& );*/
	
	// template< typename ty >
	void Generic( int , std::vector< Pos* >& );
	void Generic( PosManager& );
	// void Generic( PosManager );
	
	void Outline( PosXYZ* DrawPosV );
	void Generic( const WO_SINGLE& WS1 );
	void Generic( const GO_CUBOID& GC1, bool hasTexture=false , PosXY tilingFactor=PosXY(0.0,0.0) );
	void Generic( const GO_FACE& GF1 );
	void Generic( const GO_CYLINDER& GC );
	void Generic( const GO_BEZIER_CURVE& BC );
	void Star( const PosXYZ& P1 );
	void TriangleStrip( const std::vector< PosXYZ >& V );
	void TriangleStrip( const std::vector< PosXY >& V );
	
	void GridXY();
	void GridXYChequered();
	
	void CubeLP( float length, PosXYZ position, ColorRGBA C1 = 1.0);
	void CubeLPM( float length, PosXYZ position, bool* FaceMatrix );
};

#endif
