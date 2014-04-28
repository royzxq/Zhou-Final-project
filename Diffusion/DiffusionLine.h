//
//  DiffusionLine.h
//  MyProject
//
//  Created by Raja Raman on 4/27/14.
//
//

#ifndef __MyProject__DiffusionLine__
#define __MyProject__DiffusionLine__

#include "LPFop.h"
#include "APdelay.h"
#include "RingBuffer.h"

class DiffusionLine
{
    
public:
    void initInstance(float preDelay_Samples, float APF1delay_Sample, float APF2delay);
    void setParamerets(float LPFgain, float APF1gain, float APF2gain);
    float process(float input);
    
    
    
protected:
    DiffusionLine();
    virtual ~DiffusionLine();
    
    CRingBuffer<float> *preDelay;
    LPFop LPbw;
    APdelay AP1;
    APdelay AP2;
    
    float LPinput;
    float AP1input;
    float AP2input;
};

#endif /* defined(__MyProject__DiffusionLine__) */
