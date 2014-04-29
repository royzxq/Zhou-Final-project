/*
  ==============================================================================

    Reverb.h
    Created: 28 Apr 2014 9:46:39pm
    Author:  XinquanZhou

  ==============================================================================
*/

#ifndef REVERB_H_INCLUDED
#define REVERB_H_INCLUDED

#include "Diffusion.h"
#include "Tank.h"

class myReverb
{
public:
    myReverb(float samplerate):m_SampleRate(samplerate),m_Switch(true),m_Gain(0){
        myDiffusionL = new DiffusionLine(0.05*m_SampleRate,101,158,367,409,m_SampleRate);
        myDiffusionR = new DiffusionLine(0.050*m_SampleRate,103,147,353,389,m_SampleRate);
        myDiffusionL -> setParamerets(0.9995, 0.5, -0.75, 0.625, 0.5);
        myDiffusionR -> setParamerets(0.9995, -0.5, 0.75, 0.625, 0.5);
        myTank = new Tank();
        
        myTank -> setTankBlock(-0.5, 0.0005, 6257.0/m_SampleRate, 0.05, m_SampleRate, 1);
        myTank -> setTankBlock(-0.5, 0.05, 6599.0/m_SampleRate, 0.05, m_SampleRate, 2);
        myTank -> setTankBlock(-0.5, 0.0005, 4649.0/m_SampleRate, 0.05, m_SampleRate, 3);
        myTank -> setTankBlock(-0.5, 0.05, 5563.0/m_SampleRate, 0.05, m_SampleRate, 4);
        myTank -> setDelay(2003, 2131, 1);
        myTank -> setDelay(2417, 3001, 2);
        myTank -> setDelay(2069, 2297, 3);
        myTank -> setDelay(2777, 3203, 4);
        
    }
    ~myReverb(){
        delete myDiffusionL;
        delete myDiffusionR;
        delete myTank;
    }
    void setDecay(float delay);
    void setSwitch(bool sw);
    void setRemix(float remix);
    
    void process(float **input, float ** output, int NumChannel, int NumSample);
private:
    
    float m_SampleRate;
    bool m_Switch;
    float m_Gain;
    float m_Decay;
    float m_Remix;
    
    DiffusionLine * myDiffusionL;
    DiffusionLine * myDiffusionR;
    Tank * myTank;
};


#endif  // REVERB_H_INCLUDED
