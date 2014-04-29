//
//  APdelay.cpp
//  MyProject
//
//  Created by Raja Raman
//
//

#include "APdelay.h"

APdelay::~APdelay()
{
    delete m_pDelay;
}

void APdelay::initInstances(float delayLengthSam)
{
    m_pDelay = new CRingBuffer<float>(delayLengthSam);
    resetInstance();

}

void APdelay::setAPFgain(float gain)
{
    APFgain = gain;
}

void APdelay::resetInstance()
{
    m_pDelay->resetInstance();
    APFgain = 0.f;
    nodeOutD = 0;
    nodeInD = 0;
}

float APdelay::process(float input)
{
    float output;
    nodeOutD = m_pDelay->getPostInc();
    nodeInD = input + APFgain * nodeOutD;
    m_pDelay->putPostInc(nodeInD);
    output = -APFgain*nodeInD + nodeOutD;
    return output;
}
