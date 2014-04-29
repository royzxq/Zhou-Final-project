/*
  ==============================================================================

    Tank.h
    Created: 28 Apr 2014 12:32:22am
    Author:  XinquanZhou

  ==============================================================================
*/

#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED

#include "try.h"
//#include "TankBlock.h"

class Tank{
public:
    Tank():Input(true),Output(false),m_Ratio(0.5), m_Decay(0.5), output1(0),output1_star(0),output2(0),output2_star(0),output3(0),output3_star(0),output4(0),output4_star(0){};
    ~Tank(){};
    
    void setTankBlock(float gain1, float LPC, float delaysec1, float delaysec2, float samplerate, int num);
    void setDelay(float delay_sam1,float delay_sam2, int num);
    void InputChannel(bool flag);
    void OutputChannel(bool flag);
    void setDecay(float decay);
    void setRatio(float ratio);
    void process(float leftDry, float rightDry, float left, float right, float & output_left, float & output_right);
private:
    bool Input;
    bool Output;
    float m_Ratio;
    float m_Decay;
    float output1, output1_star;
    float output2, output2_star;
    float output3, output3_star;
    float output4, output4_star;
    
    TankBlock * myTankBlock1, * myTankBlock2, * myTankBlock3, * myTankBlock4;
};


#endif  // TANK_H_INCLUDED
