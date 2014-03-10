/*
  ==============================================================================

    multiTAPdelay.h
    Created: 8 Mar 2014 5:53:36pm
    Author:  Raja Raman

  ==============================================================================
*/

#ifndef MULTITAPDELAY_H_INCLUDED
#define MULTITAPDELAY_H_INCLUDED

#include "RingBuffer.h"

class CmultiTAPdelay
{
public:
    CmultiTAPdelay(float fSampleRate, int iNumChannels) : m_fSampleRate(fSampleRate), m_iNumChannels(iNumChannels), m_fRatio1(1.86), m_fRatio2(2.72)
    {
        // Allocate RingBuffer/Delay Buffer memory
        pTap1 = new CRingBuffer<float> *[m_iNumChannels];
        pTap2 = new CRingBuffer<float> *[m_iNumChannels];
        pTap3 = new CRingBuffer<float> *[m_iNumChannels];
        
        for (int i = 0; i < m_iNumChannels; i++)
        {
            pTap1[i] = new CRingBuffer<float>(MAX_DELAY_SEC*m_fSampleRate);
            pTap2[i] = new CRingBuffer<float>(MAX_DELAY_SEC*m_fSampleRate);
            pTap3[i] = new CRingBuffer<float>(MAX_DELAY_SEC*m_fSampleRate);
        }
    }
    
    virtual ~CmultiTAPdelay()
    {
        for (int i = 0; i <  m_iNumChannels; i++)
        {
            delete pTap1[i];
            delete pTap2[i];
            delete pTap3[i];
        }
        delete [] pTap1;
        delete [] pTap2;
        delete [] pTap3;
    }
    
    void    setDelay(float first_delay_sec);
    void    setMode(int modeIdx);
    void    process(float **input, float **output, int iBlockSize);
    void    processBypass(float **input, float **output, int iBlockSize);
    
    enum mode
    {
        singleTap_only,
        MultiTap_only,
        
        NumTaps
    };
    
private:
    const float MAX_DELAY_SEC = 0.5;
    CRingBuffer<float> **pTap1,
                       **pTap2,
                       **pTap3;
    float           m_fDelay1_samps;
    float           m_fDelay2_samps;
    float           m_fDelay3_samps;
    float           m_fSampleRate;
    int             m_iNumChannels;
    
    float           m_fRatio1,
                    m_fRatio2;
    
    int modeSelector;
};




#endif  // MULTITAPDELAY_H_INCLUDED
