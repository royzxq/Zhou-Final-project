//
//  Filter.h
//  FinalProject
//
//  Created by Xinquan Zhou on 2/15/14.
//  Copyright (c) 2014 Xinquan Zhou. All rights reserved.
//

#ifndef __FinalProject__Filter__
#define __FinalProject__Filter__

#include <iostream>
#include<cmath>
#include "/Users/xinquanzhou/Desktop/backup/ProjectTemplate/SharedSources/incl/RingBuffer.h"
class FilterBase{
public:
// the init parameters with maximum order 5
    FilterBase(float nor_Freq, int order, int ChannelNum):normalizeFreq(nor_Freq),NumChannel(ChannelNum)
    {
        Input_Buffer = new CRingBuffer<float>*[NumChannel];
        Output_Buffer = new CRingBuffer<float>*[NumChannel];
        a = new float *[NumChannel];
        b = new float *[NumChannel];
        for (int i = 0 ; i < NumChannel; i++) {
            Input_Buffer[i] = new CRingBuffer<float>(5);
            Output_Buffer[i] = new CRingBuffer<float>(5);
            a[i] = new float [order+1];
            b[i] = new float [order+1];
        }
        
        

        
    }
    virtual ~FilterBase()
    {
        for (int i = 0; i < NumChannel ; i++) {
            delete Input_Buffer[i];
            delete Output_Buffer[i];
            delete [] a[i];
            delete [] b[i];
        }
        delete Input_Buffer;
        delete Output_Buffer;
        delete a;
        delete b;
    }
    virtual void process(float ** input, float ** output, int kBlocksize) = 0;
    virtual void setQ(float q) = 0 ;
protected:
    // the common parameters of a filter: normalized cutoff freq; the ringbuffer for
    // input and output ; the coefficients of filter b,a
    float normalizeFreq;
    CRingBuffer<float> **Input_Buffer=0;
    CRingBuffer<float> **Output_Buffer=0;
    int NumChannel;
    float ** a;
    float ** b;
    float Q;
};

class LPF_Butter:public FilterBase{
public:
    LPF_Butter(float norFreq, int order, int ChannelNum):FilterBase(norFreq,order,ChannelNum){}
    ~LPF_Butter(){}
    void process(float ** input, float ** output, int kBlocksize) override;
private:
    void CalculateCoeffiects();
};

class HPF_Butter:public FilterBase{
public:
    HPF_Butter(float norFreq, int order, int ChannelNum):FilterBase(norFreq,order,ChannelNum){}
    ~HPF_Butter(){}
    void process(float ** input, float ** output, int kBlocksize) override;
private:
    void CalculateCoeffiects();
};


// warm the wav by some transformation
class WavShaper{
public:
    WavShaper(float newK):k(newK){}
    void process(float * input, float * output, int kBlocksize)
    {
        for (int i = 0 ; i < kBlocksize; i++) {
            output[i] = (1/atan(k))*atan(k*input[i]);
        }
    }
private:
    float k;
};

#endif /* defined(__FinalProject__Filter__) */
