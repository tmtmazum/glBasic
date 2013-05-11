#include "../headers/Pos.h"
#include "../headers/Color.h"
#include <GL/glut.h>

void PosXY::getVertex()
{
	glVertex2f( X, Y );
}

void PosXYZ::getVertex()
{
	glVertex3f( X, Y, Z );
}