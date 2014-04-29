/*
  ==============================================================================

    try.cpp
    Created: 28 Apr 2014 9:08:18pm
    Author:  XinquanZhou

  ==============================================================================
*/

#include "try.h"
void TankBlock::setAPDelay(float delay1_sec, float delay2_sec)
{
    myAP1->initInstances(delay1_sec*m_SampleRate);
    myAP2->initInstances(delay2_sec*m_SampleRate);
    
}

void  TankBlock::process(float input, float &output1, float &output2)
{
    float tmp;
    tmp = myAP1 -> process(input);
    tmp = myAP2 -> process(tmp);
    tmp = myLP -> process(tmp);
    tmp = myDelay1 -> process(tmp);
    output1 = tmp;
    output2 = myDelay2 -> process(tmp);
}