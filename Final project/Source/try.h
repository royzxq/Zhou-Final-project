/*
  ==============================================================================

    try.h
    Created: 28 Apr 2014 9:07:48pm
    Author:  XinquanZhou

  ==============================================================================
*/

#ifndef TRY_H_INCLUDED
#define TRY_H_INCLUDED


#include "APdelay.h"
#include "LPFop.h"
#include "Filter.h"

class TankBlock{
public:
    TankBlock(float gain, float LPC, float delaysec1, float delaysec2, float samplerate):m_Gain(gain),m_LPCoeff(LPC),m_DelaySec1(delaysec1),m_DelaySec2(delaysec2), m_SampleRate(samplerate){
        myDelay1 = new DelayClass(m_DelaySec1,m_SampleRate);
        myDelay2 = new DelayClass(m_DelaySec2,m_SampleRate);
        myLP = new LPFop();
        myAP1 = new APdelay(m_SampleRate);
        myAP2 = new APdelay(m_SampleRate);
        
        myAP1 -> setAPFgain(m_Gain);
        myAP2 -> setAPFgain(-m_Gain);
        
    }
    ~TankBlock(){
        delete myDelay1;
        delete myDelay2;
        delete myLP;
        delete myAP1;
        delete myAP2;
    }
    void setAPDelay(float delay1_sec,float delay2_sec);
    void process(float input, float &output1, float &output2);
private:
    float m_Gain;
    float m_LPCoeff;
    float m_DelaySec1,m_DelaySec2;
    float m_SampleRate;
    
    DelayClass * myDelay1,*myDelay2;
    LPFop * myLP;
    APdelay * myAP1, * myAP2;
};

#endif  // TRY_H_INCLUDED
