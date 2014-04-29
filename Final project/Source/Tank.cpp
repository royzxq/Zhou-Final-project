/*
  ==============================================================================

    Tank.cpp
    Created: 28 Apr 2014 12:32:31am
    Author:  XinquanZhou

  ==============================================================================
*/

#include "Tank.h"



void Tank::setTankBlock(float gain ,float LPC, float delaysec1, float delaysec2, float samplerate, int num)
{
    if (num == 1) {
        myTankBlock1 = new TankBlock(gain,LPC,delaysec1,delaysec2,samplerate);
    }
    if (num == 2) {
        myTankBlock2 = new TankBlock(gain,LPC,delaysec1,delaysec2,samplerate);

    }
    if (num == 3) {
        myTankBlock3 = new TankBlock(gain,LPC,delaysec1,delaysec2,samplerate);

    }
    if (num == 4) {
        myTankBlock4 = new TankBlock(gain,LPC,delaysec1,delaysec2,samplerate);

    }
}
void Tank::setDelay(float delay_sam1, float delay_sam2, int num)
{
    if (num == 1) {
        myTankBlock1 -> setAPDelay(delay_sam1, delay_sam2);
    }
    if (num == 2) {
        myTankBlock2 -> setAPDelay(delay_sam1, delay_sam2);
        
    }
    if (num == 3) {
        myTankBlock3 -> setAPDelay(delay_sam1, delay_sam2);
    }
    if (num == 4) {
        myTankBlock4 -> setAPDelay(delay_sam1, delay_sam2);
        
    }
}
void Tank::InputChannel(bool flag)
{
    Input = flag    ;
}

void Tank::OutputChannel(bool flag)
{
    Output = flag;
}

void Tank::setDecay(float decay)
{
    m_Decay = decay;
}
void Tank::setRatio(float ratio)
{
    m_Ratio = ratio;
}
void Tank::process(float leftDry, float rightDry, float left, float right, float &output_left, float &output_right)
{

    myTankBlock1->process(0.6*left+m_Decay*output4,output1,output1_star);
    if (Input) {
        myTankBlock2->process(0.6*left+m_Decay*output1,output2,output2_star);
    }
    else
        myTankBlock2->process(0.6*right+m_Decay*output1,output2,output2_star);
    if (Input) {
        myTankBlock3->process(-0.6*left+m_Decay*output2,output3,output3_star);
    }
    else
        myTankBlock3->process(-0.6*right+m_Decay*output2,output3,output3_star);
    
    myTankBlock4 -> process(0.6*right+m_Decay*output3,output4,output4_star);
    output_left = leftDry * m_Ratio + (1-m_Ratio)*(0.55/2 * output1 + 0.55/2*output2_star + 0.55 /2 * output3 + 0.55 /2 * output4_star);
    output_left /= 2;
    output_right = rightDry *m_Ratio - (1-m_Ratio)*(0.44/2 * output1_star + 0.33/2 * output2 + 0.33/2 * output3_star + 0.44/2 * output4);
    output_right /= 2;
}
