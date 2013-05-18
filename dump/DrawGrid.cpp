Draw::GridXY(float indLength = 1.0)
{
	const static float indLength = 0.1 / 1.0;
	// Draw all lines
	glBegin( GL_LINES );
		ColorRGBA G = Colors::Grey;
		G.A = 0.2;
		G.get();
		for(float i = -1.0; i < 1.0; i += 0.01)
		{
			glVertex3f(i, -1.0, 0.0);
			glVertex3f(i, 1.0, 0.0);
		}
		for(float i = -1.0; i < 1.0; i += 0.01)
		{
			glVertex3f(-1.0, i, 0.0);
			glVertex3f(1.0, i, 0.0);
		}
		Colors::Red.get();
		glVertex3f(indLength, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		Colors::Green.get();
		glVertex3f(0.0, indLength, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		Colors::Blue.get();
		glVertex3f(0.0, 0.0, indLength);
		glVertex3f(0.0, 0.0, 0.0);
		
	glEnd();
}

class GO_CUBOID : public GEOMETRY_OBJECTS
{
	enum Faces { LEFT=1, FRONT=2, BOTTOM=4, RIGHT=8, BACK=16, TOP=32 };
	
	float length;
	PosXYZ placement;
	unsigned char FaceMatrix;
	
	PosXYZ CenterRotation;
	PosXYZ CenterScale;
}

template< unsigned char byte > class BIT_MASK
{
public:
	bool operator[](unsigned char a)
	{
		return (bool) (byte & a);
	}
}

Draw::CubeLPI(float length, PosXYZ placement, int FaceMatrix)
{
	bool* FaceMat[6];
	FaceMat[0] = (bool) (FaceMatrix & GO_CUBOID::LEFT) >> 0;
	FaceMat[1] = (bool) (FaceMatrix & GO_CUBOID::FRONT) >> 1;
	FaceMat[2] = (bool) (FaceMatrix & GO_CUBOID::BOTTOM) >> 2;
	FaceMat[3] = (bool) (FaceMatrix & GO_CUBOID::RIGHT) >> 3;
	FaceMat[4] = (bool) (FaceMatrix & GO_CUBOID::BACK) >> 4;
	FaceMat[5] = (bool) (FaceMatrix & GO_CUBOID::TOP) >> 5;

	CubeLPM( length, placement, FaceMat );
}

Draw::CubeLPM(float length, PosXYZ placement, bool* FaceMatrix)
// FaceMatrix { 0 .. 6 } represents the faces in the direction of
// 			  { -x, -y, -z, x, y, z }
//			  { left, front, bottom, right, back, top }
{
	if( FaceMatrix[0] )
	{
		glBegin( GL_POLYGON );
		
		glEnd();
	}
	if( FaceMatrix[1] )
	{
		glBegin( GL_POLYGON );
		
		glEnd();
	}
	if( FaceMatrix[2] )
	{
		glBegin( GL_POLYGON );
		
		glEnd();
	}
	if( FaceMatrix[3] )
	{
		glBegin( GL_POLYGON );
		
		glEnd();
	}
	if( FaceMatrix[4] )
	{
		glBegin( GL_POLYGON );
		
		glEnd();
	}
	if( FaceMatrix[5] )
	{
		glBegin( GL_POLYGON );
		
		glEnd();
	}
}

float process(unsigned int i)
{
	for(int j = 32; j >= 0; j -= 2)
	i & pow(2,j) >> j-1;
	
}
