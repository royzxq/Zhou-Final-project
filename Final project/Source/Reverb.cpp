/*
  ==============================================================================

    Reverb.cpp
    Created: 28 Apr 2014 9:46:49pm
    Author:  XinquanZhou

  ==============================================================================
*/

#include "Reverb.h"


void Reverb::setDecay(float delay)
{
    m_Decay = delay;
    myTank -> setDecay(m_Decay);
}

void Reverb::setSwitch(bool sw)
{
    m_Switch = sw;
    myTank -> InputChannel(m_Switch);
}

void Reverb::setRemix(float remix)
{
    m_Remix = remix;
    myTank -> setRatio(m_Remix);
}

void Reverb::process(float **input, float **output, int NumChannel, int NumSample)
{
    if(NumChannel != 2)
    {
        for(int i = 0 ; i < NumChannel ; i ++)
        {
            for (int j= 0 ; j < NumSample; j++) {
                output[i][j]= input[i][j];
            }
        }
    }
    else {
        float tmpL, tmpR;
        for (int j = 0 ; j < NumSample; j++) {
            for (int i = 0; i < NumChannel; i++) {
                if (i == 0 ) {
                    tmpL = myDiffusionL->process(input[i][j]);
                    
                }
                else
                    tmpR = myDiffusionR->process(input[i][j]);
            }
            myTank -> process(input[0][j], input[1][j], tmpL, tmpR, output[0][j], output[1][j]);
        }
    }
}