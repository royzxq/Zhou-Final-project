//
//  Filter.cpp
//  FinalProject
//
//  Created by Xinquan Zhou on 2/15/14.
//  Copyright (c) 2014 Xinquan Zhou. All rights reserved.
//

#include "Filter.h"


void LowPass::setCutoff(float cutoff)
{
    m_Wc = cutoff;
    m_C = (tanf(M_PI*m_Wc/2)-1)/(tanf(M_PI*m_Wc)+1);
}
void LowPass::process(float **input, float **output, int NumSamples)
{
    for (int i = 0 ; i < m_iChannel; i++) {
        for (int j = 0 ; j < NumSamples; j++) {
            float xh_new = input[i][j] - m_C*m_Xh[i];
            float ap_y = m_C * xh_new + m_Xh[i];
            m_Xh[i] = xh_new;
            output[i][j] = 0.5 * (input[i][j] + ap_y);
        }
    }
}

void HighPass::process(float **input, float **output, int NumSamples)
{
    for (int i = 0 ; i < m_iChannel; i++) {
        for (int j = 0 ; j < NumSamples; j++) {
            float xh_new = input[i][j] - m_C*m_Xh[i];
            float ap_y = m_C * xh_new + m_Xh[i];
            m_Xh[i] = xh_new;
            output[i][j] = 0.5 * (input[i][j] - ap_y);
        }
    }
}

void LowShelving::setGain(float G)
{
    m_G = G;
    V0 = powf(10, m_G/20);
    H0 = V0 -1 ;
}
void LowShelving::setCutoff(float cutoff)
{
    m_Wc = cutoff;
    if (m_G >=0 ) {
        m_C = (tanf(M_PI*m_Wc/2)-1)/(tanf(M_PI*m_Wc)+1);
        
    }
    else
        m_C = (tanf(M_PI*m_Wc/2)-V0)/(tanf(M_PI*m_Wc)+V0);
}

void LowShelving::process(float **input, float **output, int NumSamples)
{
    for (int i = 0 ; i < m_iChannel; i++) {
        for (int j = 0 ; j < NumSamples; j++) {
            float xh_new = input[i][j] - m_C*m_Xh[i];
            float ap_y = m_C * xh_new + m_Xh[i];
            m_Xh[i] = xh_new;
            output[i][j] = 0.5 * H0 * (input[i][j] + ap_y) + input[i][j];
        }
    }
}

void HighShelving::process(float **input, float **output, int NumSamples)
{
    for (int i = 0 ; i < m_iChannel; i++) {
        for (int j = 0 ; j < NumSamples; j++) {
            float xh_new = input[i][j] - m_C*m_Xh[i];
            float ap_y = m_C * xh_new + m_Xh[i];
            m_Xh[i] = xh_new;
            output[i][j] = 0.5 * H0 * (input[i][j] - ap_y) + input[i][j];
        }
    }
}