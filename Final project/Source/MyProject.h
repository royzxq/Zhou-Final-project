/*
  ==============================================================================

    MyProject.h
    Created: 8 Mar 2014 12:37:05pm
    Author:  Xinquan Zhou

  ==============================================================================
*/

#ifndef MYPROJECT_H_INCLUDED
#define MYPROJECT_H_INCLUDED

#include "RingBuffer.h"

class MultiTapDelay{
public:
    MultiTapDelay(float fs, int iChannel):delay1_sec(0),sample_rate(fs),iNumChannel(iChannel),ratio1(1.86),ratio2(2.72), m_fFBgain(0.5)
    {
        pTap1 = new CRingBuffer<float> *[iNumChannel];
        pTap2 = new CRingBuffer<float> *[iNumChannel];
        pTap3 = new CRingBuffer<float> *[iNumChannel];
        for (int i = 0 ; i < iNumChannel; i++) {
            pTap1[i] = new CRingBuffer<float>(MAX_DELAY*sample_rate);
            pTap2[i] = new CRingBuffer<float>(MAX_DELAY*sample_rate);
            pTap3[i] = new CRingBuffer<float>(MAX_DELAY*sample_rate);
        }
    }
    virtual ~MultiTapDelay()
    {
        for (int i = 0 ; i < iNumChannel; i++) {
            delete pTap1[i];
            delete pTap2[i];
            delete pTap2[i];
        }
        delete pTap1;
        delete pTap2;
        delete pTap3;
        
    }
    void setDelay(float newDelay1_sec);
    void setFBgain(float FBgain);
    void setMode(int newMode);
    void process(float ** input, float ** output, int iBlocksize);
    void processBypass(float ** input, float ** output, int iBlocksize);
    void reset();
    enum mode
    {
        singleTap = 0 ,
        multiTap,
        totalNumParams
    };
    
private:
    static const float MAX_DELAY;
    CRingBuffer<float> ** pTap1,
    ** pTap2,
    ** pTap3;
    float delay1_sec;
    float delay1_sample;
    float delay2_sample;
    float delay3_sample;
    float sample_rate;
    int iNumChannel;
    mode modeSelector;

    float ratio1;
    float ratio2;
    
    float m_fFBgain;
    
    
};



#endif  // MYPROJECT_H_INCLUDED
