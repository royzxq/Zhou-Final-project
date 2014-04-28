//
//  biQuad.h
//  MyProject
//
//  Created by Raja Raman on 4/27/14.
//
//

#ifndef __MyProject__biQuad__
#define __MyProject__biQuad__

class biQuad
{
public:
	biQuad();
	virtual ~biQuad();
    
    float m_f_a0;
	float m_f_a1;
	float m_f_a2;
	float m_f_b1;
	float m_f_b2;
   
    void flushDelays()
	{
		m_f_Xz_1 = 0;
		m_f_Xz_2 = 0;
		m_f_Yz_1 = 0;
		m_f_Yz_2 = 0;
	}
    
    float doBiQuad(float f_xn)
	{
		// just do the difference equation: y(n) = a0x(n) + a1x(n-1) + a2x(n-2) - b1y(n-1) - b2y(n-2)
		
        yn = m_f_a0*f_xn + m_f_a1*m_f_Xz_1 + m_f_a2*m_f_Xz_2 - m_f_b1*m_f_Yz_1 - m_f_b2*m_f_Yz_2;
        
        
		// shuffle delays
		// Y delays
		m_f_Yz_2 = m_f_Yz_1;
		m_f_Yz_1 = yn;
        
		// X delays
		m_f_Xz_2 = m_f_Xz_1;
		m_f_Xz_1 = f_xn;
        
		return  yn;
	}
    
protected:
    float m_f_Xz_1; // x z-1 delay element
	float m_f_Xz_2; // x z-2 delay element
	float m_f_Yz_1; // y z-1 delay element
	float m_f_Yz_2; // y z-2 delay element
    
    float yn;
};

#endif /* defined(__MyProject__biQuad__) */
