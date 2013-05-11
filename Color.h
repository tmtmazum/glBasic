#ifndef __COLOR_H__
#define __COLOR_H__

class Color
{
      virtual void get() = 0;
};

class ColorRGBA : public Color
{
    float R,G,B,A;
	  
    public: 
      ColorRGBA(float f1, float f2, float f3, float f4) : 
		R(f1), G(f2), B(f3), A(f4) {}
      ColorRGBA(float f1, float f2, float f3) : 
		R(f1), G(f2), B(f3), A(1.0) {}
      ColorRGBA(ColorRGBA& C1) : R(C1.R), G(C1.G), B(C1.B), A(C1.A) {}
      ColorRGBA(): R(255.0), G(255.0), B(255.0), A(255.0) {}
      void get();
};

#endif