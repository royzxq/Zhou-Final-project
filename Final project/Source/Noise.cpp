//
//  Noise.cpp
//  FinalProject
//
//  Created by Xinquan Zhou on 2/15/14.
//  Copyright (c) 2014 Xinquan Zhou. All rights reserved.
//

#include "Noise.h"

void WhiteNoiseGen::generate(float ** noise,int numChannel, int len)
{
    float w = 1;
    float x1;
    float x2;
    float noize;
   
    for (int i = 0 ; i < len ; i++) {
        w = 1;
        while (w>=1) {
            x1 = ranf() * 2 - 1;
            x2 = ranf() * 2 - 1 ;
            w = x1 * x1 + x2 * x2;
        }
        w = (float) sqrt(-2 * log(w)/w);
        w *= x1;
        for (int j = 0 ; j < numChannel; j++)
        {
            noize += (w*sigma+mu);
            noize /= 10;
            noise[j][i] += noize;
        }
        
        
    }
}

void WavShaper::setRange(float range)
{
    inRange = range;
}

void WavShaper::process(float **input, float **output, int numChannel, int kBlocksize)
{
    
        for (int j = 0 ; j < numChannel; j++) {
            for (int i = 0 ; i < kBlocksize; i++) {
                output[j][i] = 2/(1+exp((-k)*input[j][i]/inRange)) - 1 ;
                output[j][i] *= inRange;
            }
            
        }
    
}