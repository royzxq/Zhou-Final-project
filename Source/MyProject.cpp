/*
  ==============================================================================

    MyProject.cpp
    Created: 8 Mar 2014 12:37:05pm
    Author:  Xinquan Zhou

  ==============================================================================
*/

#include "MyProject.h"
const float MultiTapDelay::MAX_DELAY = 0.5;

void MultiTapDelay::setDelay(float newDelay1_sec)
{
    delay1_sec = newDelay1_sec;
    delay1_sample = delay1_sec * sample_rate;
    delay2_sample = delay1_sample * ratio1;
    delay3_sample = delay1_sample * ratio2;
}

void MultiTapDelay::setMode(int idx)
{
    modeSelector = static_cast<mode>(idx);
    
}

void MultiTapDelay::process(float **input, float **output, int iBlocksize)
{
    if (modeSelector == singleTap) {
        for (int i = 0 ; i < iNumChannel; i++) {
            for (int j = 0 ; j < iBlocksize; j++) {
                pTap1[i]->putPostInc(input[i][j]);
                pTap2[i]->putPostInc(input[i][j]);
                pTap3[i]->putPostInc(input[i][j]);
                output[i][j] = pTap1[i]->get(delay1_sample);
                //output[i][j] += input[i][j];
            }
        }
    }
    else if(modeSelector == multiTap){
        for (int i = 0 ; i < iNumChannel; i++) {
            for (int j = 0 ; j < iBlocksize; j++) {
                pTap1[i]->putPostInc(input[i][j]);
                pTap2[i]->putPostInc(input[i][j]);
                pTap3[i]->putPostInc(input[i][j]);
                output[i][j] = pTap1[i]->get(delay1_sample) + pTap2[i]->get(delay2_sample) + pTap3[i]->get(delay3_sample);
                output[i][j] /= 3;
                //output[i][j] += input[i][j];

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
    }
}
void MultiTapDelay::processBypass(float **input, float **output, int iBlocksize){
    if (modeSelector == 1) {
        for (int i = 0 ; i < iNumChannel; i++) {
            for (int j = 0 ; j < iBlocksize; j++) {
                pTap1[i]->putPostInc(input[i][j]);
                pTap2[i]->putPostInc(input[i][j]);
                pTap3[i]->putPostInc(input[i][j]);
                
                output[i][j] = input[i][j];
            }
        }
    }
    else if(modeSelector == 2){
        for (int i = 0 ; i < iNumChannel; i++) {
            for (int j = 0 ; j < iBlocksize; j++) {
                pTap1[i]->putPostInc(input[i][j]);
                pTap2[i]->putPostInc(input[i][j]);
                pTap3[i]->putPostInc(input[i][j]);
                output[i][j] = pTap1[i]->get(delay1_sample) + pTap2[i]->get(delay2_sample) + pTap3[i]->get(delay3_sample);
               
                output[i][j] = input[i][j];
                
            }
        }
    }
}