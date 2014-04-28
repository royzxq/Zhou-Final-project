//
//  APdelay.cpp
//  MyProject
//
//  Created by Raja Raman
//
//

#include "APdelay.h"

APdelay::APdelay() : m_pDelay(0), APFgain(0), nodeOutD(0), nodeInD(0) {}
APdelay::~APdelay()
{
    delete m_pDelay;
}

void APdelay::initInstances(int delayLengthSamples)
{
    resetInstance();
    m_pDelay = new CRingBuffer<float>(delayLengthSamples);
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

void APdelay::process(float input, float output)
{
    nodeOutD = m_pDelay->getPostInc();
    nodeInD = input + APFgain * nodeInD;
    m_pDelay->putPostInc(nodeInD);
    output = -APFgain*nodeInD + nodeOutD;
}
