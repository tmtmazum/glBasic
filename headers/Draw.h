#ifndef __DRAW_H__
#define __DRAW_H__

#include "Pos.h"
#include "Color.h"
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
	
	void CubeLP( float length, PosXYZ position, ColorRGBA C1 = 1.0);

};

#endif
