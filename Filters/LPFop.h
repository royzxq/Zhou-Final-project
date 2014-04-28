//
//  LPFop.h
//  MyProject
//
//  Created by Raja Raman on 4/26/14.
//
//

#ifndef __MyProject__LPFop__
#define __MyProject__LPFop__

class LPFop
{
public:
    LPFop();
    ~LPFop();
    
    void setGain(float gain);
    void initInstances();
    void process(float input, float output);
    
protected:
    float bwGain;
    float prevSample;
};


#endif /* defined(__MyProject__LPFop__) */
