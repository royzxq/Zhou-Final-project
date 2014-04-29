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
#include "RingBuffer.h"
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

class LowShelving{
public:
    LowShelving(float cutoff, float G, int iChannel):m_Wc(cutoff),m_G(G), m_iChannel(iChannel){
        V0 = powf(10, m_G/20);
        H0 = V0 -1 ;
        if (m_G >=0 ) {
            m_C = (tanf(M_PI*m_Wc/2)-1)/(tanf(M_PI*m_Wc)+1);

        }
        else
            m_C = (tanf(M_PI*m_Wc/2)-V0)/(tanf(M_PI*m_Wc)+V0);

        m_Xh = new float[m_iChannel];
        memset(m_Xh,0.0,sizeof(float)*m_iChannel);
    }
    virtual ~LowShelving(){
        delete [] m_Xh;
        m_Xh = 0 ;
    }
    void setGain(float G);
    void setCutoff(float cutoff);
    virtual void  process(float ** input, float ** output , int NumSamples);

protected:
    float m_Wc;
    float m_G;
    float V0, H0;
    int m_iChannel;
    float m_C;
    float *m_Xh;
};

class HighShelving : public LowShelving{
public:
    HighShelving(float cutoff, float G, int iChannel):LowShelving(cutoff,G,iChannel){};
    ~HighShelving(){
        delete [] m_Xh;
        m_Xh = 0 ;
    }
    void  process(float ** input, float ** output , int NumSamples);
};

class DelayClass
{
public:
    DelayClass(float delay_sec, float samplerate):m_delaySec(delay_sec),m_sampleRate(samplerate){
        m_delaySam = m_delaySec*m_sampleRate;
        m_Buffer = new CRingBuffer<float>(m_delaySam);
        m_Buffer -> resetInstance();
    }
    ~DelayClass(){
        delete m_Buffer;
        m_Buffer = 0;
    }
    float process(float input);
private:
    float m_delaySec;
    float m_delaySam;
    float m_sampleRate;
    CRingBuffer<float> * m_Buffer;
    
};

#endif /* defined(__FinalProject__Filter__) */
