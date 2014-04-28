//
//  APdelay.h
//  MyProject
//
//  Created by Raja Raman
//
//

#ifndef __MyProject__APdelay__
#define __MyProject__APdelay__

#include "RingBuffer.h"

class APdelay
{
public:
    APdelay();
    virtual ~APdelay();
    
    void initInstances(int delayLengthSamples);
    // gain is the filter coefficiant, if set negetive, inverted
    void setAPFgain(float gain);
    void process(float input, float output);
    void resetInstance();
    
protected:
    CRingBuffer<float>  *m_pDelay;
    float APFgain;
    float nodeOutD,nodeInD;
    
};

#endif /* defined(__MyProject__APdelay__) */
