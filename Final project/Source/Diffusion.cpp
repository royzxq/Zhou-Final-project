 /*
  ==============================================================================

    Diffusion.cpp
    Created: 28 Apr 2014 9:39:34pm
    Author:  XinquanZhou

  ==============================================================================
*/

#include "Diffusion.h"


void DiffusionLine::setParamerets(float LPFgain, float APF1gain, float APF2gain, float APF3gain, float APF4gain ){
    LPbw->setGain(LPFgain);
    AP1->setAPFgain(APF1gain);
    AP2->setAPFgain(APF2gain);
    AP3->setAPFgain(APF3gain);
    AP4->setAPFgain(APF4gain);
}

float DiffusionLine::process(float input)
{
    
    float output = myDelay->process(input);
    output = LPbw->process(output);
    output =AP1->process(output);
    return AP2->process(output);
    
}
