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
           
            noise[j][i] += (w*sigma+mu);
        }
        
        
    }
}