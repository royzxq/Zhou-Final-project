/*
  ==============================================================================

    multiTAPdelay.cpp
    Created: 8 Mar 2014 5:53:36pm
    Author:  Raja Raman

  ==============================================================================
*/

#include "multiTAPdelay.h"

void CmultiTAPdelay::setDelay(float first_delay_sec)
{
    m_fDelay1_samps = first_delay_sec * m_fSampleRate;
    m_fDelay2_samps = m_fDelay1_samps * m_fRatio1;
    m_fDelay3_samps = m_fDelay1_samps * m_fRatio2;
}

void CmultiTAPdelay::setMode(int modeIdx)
{
    switch (modeIdx) {
        case singleTap_only:
            modeSelector = 1;
            break;
        case MultiTap_only:
            modeSelector = 2;
            break;
        default:
            break;
    }
}

void CmultiTAPdelay::process(float **input, float **output, int iBlockSize)
{
    if (modeSelector == 1)
    {
        for (int c = 0; c < m_iNumChannels; c++)
        {
            for (int i = 0; i < iBlockSize; i++)
            {
                pTap1[c]->putPostInc(input[c][i]);
                pTap2[c]->putPostInc(input[c][i]);
                pTap3[c]->putPostInc(input[c][i]);
                output[c][i] = pTap1[c]->get(m_fDelay1_samps);
            }
        }
    }
    
    else if (modeSelector == 2)
    {
        for (int c = 0; c < m_iNumChannels; c++)
        {
            for (int i = 0; i < iBlockSize; i++)
            {
                pTap1[c]->putPostInc(input[c][i]);
                pTap2[c]->putPostInc(input[c][i]);
                pTap3[c]->putPostInc(input[c][i]);
                output[c][i] = pTap1[c]->get(m_fDelay1_samps) + pTap2[c]->get(m_fDelay2_samps), pTap3[c]->get(m_fDelay3_samps);
                output[c][i] /= 3;
                output[c][i] += input[c][i];
            }
        }
    }
}

void CmultiTAPdelay::processBypass(float **input, float **output, int iBlockSize)
{
    if (modeSelector == 1)
    {
        for (int c = 0; c < m_iNumChannels; c++)
        {
            for (int i = 0; i < iBlockSize; i++)
            {
                pTap1[c]->putPostInc(input[c][i]);
                pTap2[c]->putPostInc(input[c][i]);
                pTap3[c]->putPostInc(input[c][i]);
                output[c][i] = input[c][i];
            }
        }
    }
    
    else if (modeSelector == 2)
    {
        for (int c = 0; c < m_iNumChannels; c++)
        {
            for (int i = 0; i < iBlockSize; i++)
            {
                pTap1[c]->putPostInc(input[c][i]);
                pTap2[c]->putPostInc(input[c][i]);
                pTap3[c]->putPostInc(input[c][i]);
                output[c][i] = pTap1[c]->get(m_fDelay1_samps) + pTap2[c]->get(m_fDelay2_samps), pTap3[c]->get(m_fDelay3_samps);
                output[c][i] = input[c][i];
            }
        }
    }
}

