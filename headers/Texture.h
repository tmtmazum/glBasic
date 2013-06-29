#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Pos.h"
#include <string>
#include <vector>
#include "DEBUG.h"
#include "imageloader.h"

#include <GL/glut.h>

struct Texture
{
    // std::vector< char >	 ImagePixels;
    // PosXY ImageSize;
    
    // GL Variables:
    // GLuint texBufferID;
    GLuint textureId;
    
    Texture( const char* filepath )
    {
	ImagePWH* myImage = ImagePWH::loadBMP( filepath );
	textureId = this->load( myImage );
	delete myImage;
    }
    
    void drawSample()
    {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	//Use blurry texture mapping (replace GL_LINEAR with GL_NEAREST for blocky)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glColor3f(1.0f, 1.0f, 1.0f); //Don't use special coloring
	
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 2.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
	
	glDisable(GL_TEXTURE_2D); //Switch back to using colors instead of textures
    }
     
    ~Texture()
    {
	glDeleteTextures( 1, &textureId );
    }
    
private:
    GLuint load(ImagePWH* image)
    {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
		    0,
		    GL_RGB,
		    image->width, image->height,
		    0,
		    GL_RGB,
		    GL_UNSIGNED_BYTE,
		    image->pixels);
	return textureId;
    }
    
};

#endif