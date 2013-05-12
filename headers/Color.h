#ifndef __COLOR_H__
#define __COLOR_H__

class Color
{public:
      virtual void get() = 0;
      
      Color() {}
};

class ColorRGBA : public Color
{
    float R,G,B,A;
	  
    public: 
    /* Constructors */
	ColorRGBA(float f1, float f2, float f3, float f4) : Color(),
			R(f1), G(f2), B(f3), A(f4) 
	{}
		
	ColorRGBA(float f1, float f2, float f3) : Color(),
			R(f1), G(f2), B(f3), A(1.0) 
	{}
		
	ColorRGBA(const ColorRGBA& C1) : Color(),
			R(C1.R), G(C1.G), B(C1.B), A(C1.A) 
	{}
	
	ColorRGBA(): Color(),
			R(255.0), G(255.0), B(255.0), A(255.0) 
	{}
	
	ColorRGBA(float f): Color(),
			R(f), G(f), B(f), A(f) 
	{}
	

    /* Overloaded Operators */
	void operator=(const Color& C1) { (*this) = (ColorRGBA&) C1; }
	void operator=(const ColorRGBA& C1) { this->R = C1.R; this->G = C1.G;
					this->B = C1.B; this->A = C1.A; }
	
      void get();
};

#endif