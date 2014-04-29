/*
  ==============================================================================

    Diffusion.h
    Created: 28 Apr 2014 9:39:26pm
    Author:  XinquanZhou

  ==============================================================================
*/

#ifndef DIFFUSION_H_INCLUDED
#define DIFFUSION_H_INCLUDED


#include "LPFop.h"
#include "APdelay.h"
#include "Filter.h"

class DiffusionLine
{
public:
    DiffusionLine(float preDelay_Sec, float APF1delay, float APF2delay,float APF3delay, float APF4delay, float samplerate): myDelay(0),m_SampleRate(samplerate) {
        myDelay = new DelayClass(preDelay_Sec,m_SampleRate);
        AP1 = new APdelay(m_SampleRate);
        AP2 = new APdelay(m_SampleRate);
        AP3 = new APdelay(m_SampleRate);
        AP4 = new APdelay(m_SampleRate);
        AP1 -> initInstances(APF1delay);
        AP2 -> initInstances(APF2delay);
        AP3 -> initInstances(APF3delay);
        AP4 -> initInstances(APF4delay);
        
        LPbw = new LPFop();
    }
    
    virtual ~DiffusionLine(){
        delete myDelay;
        delete AP1;
        delete AP2;
        delete AP3;
        delete AP4;
        delete LPbw;
    }
    
    void setParamerets(float LPFgain, float APF1gain, float APF2gain, float APF3gain, float APF4gain );
    float process(float input);
    
protected:
    DelayClass * myDelay;
    LPFop *LPbw;
    APdelay *AP1;
    APdelay *AP2;
    APdelay *AP3;
    APdelay *AP4;
    
    float m_SampleRate;
    
};



#endif  // DIFFUSION_H_INCLUDED
