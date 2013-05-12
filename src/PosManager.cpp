#include "../headers/PosManager.h"
#include <GL/glut.h>

void PosManager::makeAxisXY( ColorRGBA C )
{
    clear();
    draw_type = GL_LINES;
    m_output.push_back( new PosXY( 1.0, 0.0 ));
    m_output.push_back( new PosXY( -1.0, 0.0 ));
    m_output.push_back( new PosXY( 0.0, 1.0 ));
    m_output.push_back( new PosXY( 0.0, -1.0 ));
    
    for(std::vector< Pos* >::iterator m = m_output.begin();
	    m != m_output.end(); ++m)
	{
	    (*m)->setColor( C );
	}
    
    this->placement = PosXYZ( 0.0, 0.0, 0.0 );
    drawReady = true;
}

void PosManager::genOutput( GO_SQUARE& GS1)
{
    if(draw_mode == centre_of_mass)
    {
	m_output.push_back( 
	    new PosXYZ( placement.X + (GS1.length / 2), 
		    placement.Y + (GS1.length) / 2, 
		    0.0f ) 
	);
	m_output.push_back( 
	    new PosXYZ( placement.X + (GS1.length / 2), 
		    placement.Y - (GS1.length) / 2, 
		    0.0f ) 
	);
	
	m_output.push_back( 
	    new PosXYZ( placement.X - (GS1.length / 2), 
		    placement.Y - (GS1.length) / 2, 
		    0.0f ) 
	);
	m_output.push_back( 
	    new PosXYZ( placement.X - (GS1.length / 2), 
		    placement.Y + (GS1.length) / 2, 
		    0.0f ) 
	);
    }
    draw_type = GL_POLYGON;
} 

void PosManager::genOutput( GO_CUBE& GC1 )
{
    
}

void PosManager::clear()
{
    if(drawReady)
    {
	for(std::vector< Pos* >::iterator it = m_output.begin(); it != m_output.end(); ++it)
	{
	    delete (*it);
	}
	m_output.clear();
    }
}

PosManager::~PosManager()
{
    clear();
}