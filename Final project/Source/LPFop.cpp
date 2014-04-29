//
//  LPFop.cpp
//  MyProject
//
//  Created by Raja Raman on 4/26/14.
//
//

#include "LPFop.h"



LPFop::LPFop() : bwGain(0),prevSample(0){}
LPFop::~LPFop(){}

void LPFop::initInstances()
{
    prevSample = 0;
}

void LPFop::setGain(float gain)
{
    bwGain = gain;
}

float LPFop::process(float input)
{
    float output;
    output = (1-bwGain)*input + bwGain * prevSample;
    prevSample = output;
    return output;
}

