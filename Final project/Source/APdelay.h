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
    APdelay(float samplerate):m_pDelay(0), APFgain(0),m_SampleRate(samplerate), nodeOutD(0), nodeInD(0){}
    virtual ~APdelay();
    
    void initInstances(float delayLengthSample);
    // gain is the filter coefficiant, if set negetive, inverted
    void setAPFgain(float gain);
    float process(float input);
    void resetInstance();
    
protected:
    CRingBuffer<float>  *m_pDelay;
    float APFgain;
    float m_SampleRate;
    float nodeOutD,nodeInD;
    
};

#endif /* defined(__MyProject__APdelay__) */
