/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic startup code for a Juce application.
 
 ==============================================================================
 */

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MyProject.h"
#include "Noise.h"
#include "Filter.h"

#define REVERB

#ifdef REVERB
#include "Reverb.h"
#else
#include "juce_Reverb.h"
#endif

//class LowPass;
//==============================================================================
/**
 */
class NewProjectAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor();
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
   
    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;
    
    //==============================================================================
    const String getName() const;
    
    int getNumParameters();
    
    float getParameter (int index);
    void setParameter (int index, float newValue);
    
    const String getParameterName (int index);
    const String getParameterText (int index);
    
    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;
    
    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;
    
    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);
    
    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    
    enum Param{
        DelayParam = 0 ,
        ModeParam,
        IntensityParam,
        RepeatParam,
        ReverbParam,
        oldParam,
        HighShelvingParam,
        LowShelvingParam,
        CutoffHighParam,
        CutoffLowParam,
        ShelvingGainParam,
        FBParam,
        RangeParam,
        numParam
        
    };
    
    float delay_sec;
    float intensity;
    float repeat_rate;
    float reverb_volumn;
    float fb_gain;
    float InRange;
    float CutoffLow;
    float CutoffHigh;
    bool bypass;
    bool old;
    bool HighShelving;
    bool LowShelving;
    float ShelvingGain;
    int mode;
    
    int lastUIWidth,lastUIHeight;
private:
    //==============================================================================
    MultiTapDelay * myMultiDelay;
    WhiteNoiseGen * myNoise;
    WavShaper   * myShaper;
#ifdef REVERB
    myReverb * myReverb;
#else
    Reverb * myReverb;
#endif
    class LowShelving *myLowShelving;
    class HighShelving * myHighShelving;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
