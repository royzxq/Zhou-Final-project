//
//  ShelvingBPF.h
//  MyProject
//
//  Created by Raja Raman on 4/27/14.
//
//

#ifndef __MyProject__ShelvingBPF__
#define __MyProject__ShelvingBPF__

#include "biQuad.h"

class ShelvingBPF : public biQuad
{
public:
    
    ShelvingBPF();
    virtual ~ShelvingBPF();
    
    void initSampleRate(float fSampleRate);
    
    void calculatecoeffLPFShelf( float gaindB);
    void calculatecoeffHPFShelf( float gaindB);
    
    void process(float input, float output);
    
    
protected:
    
    biQuad m_pLPFShelf;
	biQuad m_pHPFShelf;
    
    float LPcutOff;
    float HPcutOff;
    
    float m_fGainLPF_Shelf;
	float m_fGainHPF_Shelf;
    
    float sampleRate;
};

#endif /* defined(__MyProject__ShelvingBPF__) */
