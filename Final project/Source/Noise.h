//
//  Noise.h
//  FinalProject
//
//  Created by Xinquan Zhou on 2/15/14.
//  Copyright (c) 2014 Xinquan Zhou. All rights reserved.
//

#ifndef __FinalProject__Noise__
#define __FinalProject__Noise__

#include <iostream>
#include <time.h>
#include <cmath>
#include <stdlib.h>



inline float ranf(){
    //srand(0);
    return (float)(rand())/(float)(RAND_MAX);
}

class WhiteNoiseGen
{
public:
    WhiteNoiseGen(float m, float s):mu(m),sigma(s){}
    ~WhiteNoiseGen(){}
    void generate(float ** noise, int numChannel, int len);
    
private:
    float mu;
    float sigma;
    bool pass = false;
};

class WavShaper{
public:
    WavShaper(float newK):k(newK),inRange(1){}
    ~WavShaper() {}
    void process(float ** input, float ** output, int numChannel, int kBlocksize);
    void setRange(float range);
    
private:
    float k;
    float inRange;
};

#endif /* defined(__FinalProject__Noise__) */
