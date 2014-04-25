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
#include <cmath>
//#include "RingBuffer.h"
//class FilterBase{
//public:
//// the init parameters with maximum order 5
//    FilterBase(float nor_Freq, int order, int ChannelNum):normalizeFreq(nor_Freq),NumChannel(ChannelNum)
//    {
//        Input_Buffer = new CRingBuffer<float>*[NumChannel];
//        Output_Buffer = new CRingBuffer<float>*[NumChannel];
//        a = new float *[NumChannel];
//        b = new float *[NumChannel];
//        for (int i = 0 ; i < NumChannel; i++) {
//            Input_Buffer[i] = new CRingBuffer<float>(5);
//            Output_Buffer[i] = new CRingBuffer<float>(5);
//            a[i] = new float [order+1];
//            b[i] = new float [order+1];
//        }
//        
//        
//
//        
//    }
//    virtual ~FilterBase()
//    {
//        for (int i = 0; i < NumChannel ; i++) {
//            delete Input_Buffer[i];
//            delete Output_Buffer[i];
//            delete [] a[i];
//            delete [] b[i];
//        }
//        delete Input_Buffer;
//        delete Output_Buffer;
//        delete a;
//        delete b;
//    }
//    virtual void process(float ** input, float ** output, int kBlocksize) = 0;
//    virtual void setQ(float q) = 0 ;
//protected:
//    // the common parameters of a filter: normalized cutoff freq; the ringbuffer for
//    // input and output ; the coefficients of filter b,a
//    float normalizeFreq;
//    CRingBuffer<float> **Input_Buffer=0;
//    CRingBuffer<float> **Output_Buffer=0;
//    int NumChannel;
//    float ** a;
//    float ** b;
//    float Q;
//};

class LowPass{
public:
    LowPass(float cutoff, int iChannel):m_Wc(cutoff),m_iChannel(iChannel){
        m_C = (tanf(M_PI*m_Wc/2)-1)/(tanf(M_PI*m_Wc)+1);
        m_Xh = new float[m_iChannel];
        memset(m_Xh,0.0,sizeof(float)*m_iChannel);
    }
    virtual ~LowPass(){
        delete [] m_Xh;
        m_Xh = 0 ;
    }
    void    setCutoff(float cutoff);
    virtual void  process(float ** input, float ** output , int NumSamples);
protected:
    float m_Wc;
    int m_iChannel;
    float m_C;
    float *m_Xh;
};

class HighPass: public LowPass{
public:
    HighPass( float cutoff, int iChannel):LowPass(cutoff,  iChannel){};
    ~HighPass(){
        delete [] m_Xh;
        m_Xh = 0 ;
    }
    void process(float ** input, float ** output , int NumSamples);
};





#endif /* defined(__FinalProject__Filter__) */
