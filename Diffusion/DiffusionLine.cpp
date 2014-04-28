//
//  DiffusionLine.cpp
//  MyProject
//
//  Created by Raja Raman on 4/27/14.
//
//

#include "DiffusionLine.h"

DiffusionLine::DiffusionLine() : preDelay(0),LPinput(0),AP1input(0), AP2input(0) {};

void DiffusionLine::initInstance(float preDelay_Samples, float APF1delay, float APF2delay)
{
    preDelay = new CRingBuffer<float>(preDelay_Samples);
    preDelay->resetInstance();
    
    AP1.initInstances(APF1delay);
    AP2.initInstances(APF2delay);
}

void DiffusionLine::setParamerets(float LPFgain, float APF1gain, float APF2gain)
{
    LPbw.setGain(LPFgain);
    AP1.setAPFgain(APF1gain);
    AP2.setAPFgain(APF2gain);
}

float DiffusionLine::process(float input)
{
    
    float LPinput = preDelay->getPostInc();
    AP1input = LPbw.process(LPinput);
    AP2input =AP1.process(AP1input);
    return AP2.process(AP2input);
    
}

