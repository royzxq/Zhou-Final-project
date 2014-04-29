//
//  ShelvingBPF.cpp
//  MyProject
//
//  Created by Raja Raman on 4/27/14.
//
//

#include "ShelvingBPF.h"
#define _USE_MATH_DEFINES
#include <cmath>

ShelvingBPF::ShelvingBPF() : LPcutOff(0), HPcutOff(0), sampleRate(0)
{
    m_pLPFShelf.m_f_a0 = 0;
    m_pLPFShelf.m_f_a1 = 0;
    m_pLPFShelf.m_f_a2 = 0;
    m_pLPFShelf.m_f_b1 = 0;
    m_pLPFShelf.m_f_b2 = 0;
    
    m_pHPFShelf.m_f_a0 = 0;
    m_pHPFShelf.m_f_a1 = 0;
    m_pHPFShelf.m_f_a2 = 0;
    m_pHPFShelf.m_f_b1 = 0;
    m_pHPFShelf.m_f_b2 = 0;
    
    m_pLPFShelf.flushDelays();
    m_pHPFShelf.flushDelays();
}

ShelvingBPF::~ShelvingBPF() {}

void ShelvingBPF::initSampleRate(float fSampleRate)
{
    sampleRate = fSampleRate;
}

void ShelvingBPF::calculatecoeffLPFShelf(float gaindB)
{
    float freqcutoffLPF = 300.0;
	float thetac = 2*M_PI*freqcutoffLPF/sampleRate;
	float mu = pow(10.0,(gain/20.0));
	float beta = 4/(1+mu);
	float delta = beta*tan(thetac/2.0);
	float gamma = (1-delta)/(1+delta);
	float a0lpf =( 1-gamma)/2;
	float a1lpf = (1-gamma)/2;
	float a2lpf = 0.0;
	float b1lpf = -gamma;
	float b2lpf = 0.0;
    LPcutOff = mu - 1.0;
    
    m_pLPFShelf.m_f_a0 = a0lpf;
	m_pLPFShelf.m_f_a1 = a1lpf;
	m_pLPFShelf.m_f_a2 = a2lpf;
	m_pLPFShelf.m_f_b1 = b1lpf;
	m_pLPFShelf.m_f_b2 = b2lpf;
}

void ShelvingBPF::calculatecoeffHPFShelf(float gaindB)
{
    float freqCutoffHPF = 3000.0;
	float thetac = 2*M_PI*freqCutoffHPF/sampleRate;
	float mu = pow(10.0,(gain/20.0));
	float beta = (1+mu)/4;
	float delta = beta*tan(thetac/2.0);
	float gamma = (1-delta)/(1+delta);
	float a0hpf =( 1+gamma)/2;
	float a1hpf = -((1+gamma)/2);
	float a2hpf = 0.0;
	float b1hpf = -gamma;
	float b2hpf = 0.0;
    HPcutOff = mu - 1.0;
    
    
    m_pHPFShelf.m_f_a0 = a0hpf;
	m_pHPFShelf.m_f_a1 = a1hpf;
	m_pHPFShelf.m_f_a2 = a2hpf;
	m_pHPFShelf.m_f_b1 = b1hpf;
	m_pHPFShelf.m_f_b2 = b2hpf;
}

void ShelvingBPF::process(float input, float output)
{
    float temp = (HPcutOff*m_pLPFShelf.doBiQuad(input)) + input;
    output = (LPcutOff*m_pLPFShelf.doBiQuad(temp)) + temp;
}










