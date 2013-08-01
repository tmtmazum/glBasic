#ifndef __WORLD_OBJECT_H__
#define __WORLD_OBJECT_H__

#include "Util.h"
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <cstdarg>

typedef std::vector<float> VecF;
typedef std::map<std::string, float> MapSF;
typedef std::map<int,float> MapIF;

struct GO
{
    enum
    {
    LINE,
    SQUARE,
    QUAD,
    CIRCLE,
    TRIANGLE_STRIP
    };
};

struct WO
{
    int GO_type;
    VecF GO_data;

    std::vector< int, std::vector<float> > property_data;

    enum property
    {
	POSITION,
	COLOR,
	ALPHA,
	ROTATION,
	SCALE,
	NP_SCALE,
	GEOMETRY
    };
        
    WO() {}
    
    void setGeometry( int i , ... )
    {
	GO_type = i;
	VecF PD;
	va_list ARGs;
	va_start( ARGs , i );
	while( true )
	{
	    float g = va_arg( ARGs , double );
	    if( g == END_F ) 
	    break;
	    GO_data.push_back( g );
	}
	va_end( ARGs );
    }
    
    void set( property p , ... )
    {
	VecF PD;
	va_list ARGs;
	va_start( ARGs , p );
	while( true )
	{
	    float g = va_arg( ARGs , double );
	    if( g == END_F ) break;
	    PD.push_back( g );
	}
	va_end( ARGs );
	property_data[ p ] = PD; 
    }
    VecF get(property p)
    {
	return property_data[ p ];
    }
    VecF getGeometry( int& GEO )
    {
	GEO = GO_type;
	return GO_data;
    }
};
    


#endif