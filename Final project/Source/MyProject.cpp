/*
  ==============================================================================

    MyProject.cpp
    Created: 8 Mar 2014 12:37:05pm
    Author:  Xinquan Zhou
    
  ==============================================================================
*/

#include "MyProject.h"
const float MultiTapDelay::MAX_DELAY = 10;

void MultiTapDelay::setDelay(float newDelay1_sec)
{
    delay1_sec = newDelay1_sec;
    
    delay1_sample = delay1_sec * sample_rate;
    
    delay2_sample = delay1_sample * ratio1;
    delay3_sample = delay1_sample * ratio2;
//    int curent_wirte = pTap1[0]->getWriteIdx();
    
    for (int i = 0 ; i < iNumChannel; i++)
    {
        pTap1[i]->setWriteIdx(static_cast<int> (delay1_sample) + pTap1[i]->getReadIdx());
        pTap2[i]->setWriteIdx(static_cast<int>(delay2_sample) + pTap2[i]->getReadIdx());
        pTap3[i]->setWriteIdx(static_cast<int>(delay3_sample) + pTap3[i]->getReadIdx());
        oTap1[i]->setWriteIdx(static_cast<int> (delay1_sample) + oTap1[i]->getReadIdx());
        oTap2[i]->setWriteIdx(static_cast<int>(delay2_sample) + oTap2[i]->getReadIdx());
        oTap3[i]->setWriteIdx(static_cast<int>(delay3_sample) + oTap3[i]->getReadIdx());
        
    }
}

void MultiTapDelay::setFBgain(float Fbgain)
{
    m_fFBgain = Fbgain;
}

void MultiTapDelay::setMode(int idx)
{
    if(idx==2 && iNumChannel!=2)
        idx = 1;
    modeSelector = static_cast<mode>(idx);
    
}

void MultiTapDelay::process(float **input, float **output, int iBlocksize)
{
    if (modeSelector == singleTap || modeSelector == singleTapwithReverb) {
        for (int i = 0 ; i < iNumChannel; i++) {
            for (int j = 0 ; j < iBlocksize; j++) {
                pTap1[i]->putPostInc(input[i][j]);
                pTap2[i]->putPostInc(input[i][j]);
                pTap3[i]->putPostInc(input[i][j]);
                float mm = input[i][j];
                if (mm!=0) {
                    mm ++;
                }
                output[i][j] =  m_fFBgain*oTap1[i]->getPostInc() + pTap1[i]->getPostInc();
                oTap1[i]->putPostInc(output[i][j]);
                oTap2[i]->putPostInc(output[i][j]);
                oTap3[i]->putPostInc(output[i][j]);
                output[i][j] /= 2;
                output[i][j] += input[i][j];
                //

            }
        }
    }
    else if(modeSelector == multiTap){
        for (int i = 0 ; i < iNumChannel; i++) {
            for (int j = 0 ; j < iBlocksize; j++) {
                pTap1[i]->putPostInc(input[i][j]);
                pTap2[i]->putPostInc(input[i][j]);
                pTap3[i]->putPostInc(input[i][j]);
                
                output[i][j] =  m_fFBgain*oTap1[i]->getPostInc() + pTap1[i]->getPostInc() \
                + m_fFBgain*oTap2[i]->getPostInc() + pTap2[i]->getPostInc() \
                + m_fFBgain*oTap3[i]->getPostInc() + pTap3[i]->getPostInc();
                
                output[i][j] /= 3;
                oTap1[i]->putPostInc(output[i][j]);
                oTap2[i]->putPostInc(output[i][j]);
                oTap3[i]->putPostInc(output[i][j]);
                
                output[i][j] += input[i][j];
            }
        }
    }
    else if (modeSelector == inversDelay)
    {
        float alfa = 0.8;
        for (int j = 0 ; j < iBlocksize; j++) {
            for (int i = 0 ; i < 2; i++) {
                if (i == 1) {
                    pTap1[i]->putPostInc(input[i][j]);
                    pTap2[i]->putPostInc(input[i][j]);
                    pTap3[i]->putPostInc(input[i][j]);
                    output[i][j] =  alfa * m_fFBgain*oTap1[i]->getPostInc() + pTap1[i]->getPostInc() + (1 - alfa) * m_fFBgain*oTap1[1]->getPostInc();
                    oTap1[i]->putPostInc(output[i][j]);
                    oTap2[i]->putPostInc(output[i][j]);
                    oTap3[i]->putPostInc(output[i][j]);
                    output[i][j] /= 2;
                    output[i][j] += input[i][j];
                    
                }
                else{
                    pTap1[i]->putPostInc(input[i][j]);
                    pTap2[i]->putPostInc(input[i][j]);
                    pTap3[i]->putPostInc(input[i][j]);
                    output[i][j] =  alfa * m_fFBgain*oTap1[i]->getPostInc() + pTap1[i]->getPostInc() + (1 - alfa) * m_fFBgain*oTap1[0] ->getPostInc();
                    oTap1[i]->putPostInc(output[i][j]);
                    oTap2[i]->putPostInc(output[i][j]);
                    oTap3[i]->putPostInc(output[i][j]);
                    output[i][j] /= 2;
                    output[i][j] += input[i][j];
                    
                    
                }
            }
        }
    }
    else{
        for (int i = 0 ; i < iNumChannel; i++) {
            for (int j = 0 ; j < iBlocksize; j++) {
                
                output[i][j] = input[i][j];
                
            }
        }
    }
}

void MultiTapDelay::reset()
{
    for (int i =0 ; i < iNumChannel; i++) {
        pTap1[i] -> resetInstance();
        pTap2[i] -> resetInstance();
        pTap3[i] -> resetInstance();
        oTap1[i] -> resetInstance();
        oTap2[i] -> resetInstance();
        oTap3[i] -> resetInstance();
        
    }
}
/*
void MultiTapDelay::processBypass(float **input, float **output, int iBlocksize)
{
    if (modeSelector == singleTap || modeSelector == singleTapwithReverb) {
        for (int i = 0 ; i < iNumChannel; i++) {
            for (int j = 0 ; j < iBlocksize; j++) {
                
                pTap1[i]->putPostInc(input[i][j]);
                pTap2[i]->putPostInc(input[i][j]);
                pTap3[i]->putPostInc(input[i][j]);
                output[i][j] =  m_fFBgain*oTap1[i]->getPostInc() + pTap1[i]->getPostInc();
                oTap1[i]->putPostInc(output[i][j]);
                oTap2[i]->putPostInc(output[i][j]);
                oTap3[i]->putPostInc(output[i][j]);
                output[i][j] = input[i][j];
            }
        }
    }
    else if(modeSelector == multiTap){
        for (int i = 0 ; i < iNumChannel; i++) {
            for (int j = 0 ; j < iBlocksize; j++) {
                pTap1[i]->putPostInc(input[i][j]);
                pTap2[i]->putPostInc(input[i][j]);
                pTap3[i]->putPostInc(input[i][j]);
                
                output[i][j] =  m_fFBgain*oTap1[i]->getPostInc() + pTap1[i]->getPostInc() \
                + m_fFBgain*oTap2[i]->getPostInc() + pTap2[i]->getPostInc() \
                + m_fFBgain*oTap3[i]->getPostInc() + pTap3[i]->getPostInc();
                
                oTap1[i]->putPostInc(output[i][j]);
                oTap2[i]->putPostInc(output[i][j]);
                oTap3[i]->putPostInc(output[i][j]);
                
                output[i][j] = input[i][j];
                
            }
        }
    }
    else if (modeSelector == inversDelay)
    {
        float alfa = 0.5;
        for (int j = 0 ; j < iBlocksize; j++) {
            for (int i = 0 ; i < 2; i++) {
                if (i == 1) {
                    pTap1[i]->putPostInc(input[i][j]);
                    pTap2[i]->putPostInc(input[i][j]);
                    pTap3[i]->putPostInc(input[i][j]);
                    output[i][j] =  alfa * m_fFBgain*oTap1[i]->getPostInc() + pTap1[i]->getPostInc() + (1 - alfa) * m_fFBgain*oTap1[1]->getPostInc();
                    oTap1[i]->putPostInc(output[i][j]);
                    oTap2[i]->putPostInc(output[i][j]);
                    oTap3[i]->putPostInc(output[i][j]);
                    output[i][j] += input[i][j];
                    output[i][j] /= 2;
                }
                else{
                    pTap1[i]->putPostInc(input[i][j]);
                    pTap2[i]->putPostInc(input[i][j]);
                    pTap3[i]->putPostInc(input[i][j]);
                    output[i][j] =  alfa * m_fFBgain*oTap1[i]->getPostInc() + pTap1[i]->getPostInc() + (1 - alfa) * m_fFBgain*oTap1[0]->getPostInc();
                    oTap1[i]->putPostInc(output[i][j]);
                    oTap2[i]->putPostInc(output[i][j]);
                    oTap3[i]->putPostInc(output[i][j]);
                    output[i][j] += input[i][j];
                    output[i][j] /= 2;

                }
            }
        }
    }
    else {
        for (int i = 0 ; i < iNumChannel; i++) {
            for (int j = 0 ; j < iBlocksize; j++) {
                
                output[i][j] = input[i][j];
                
            }
        }
    }
}
*/