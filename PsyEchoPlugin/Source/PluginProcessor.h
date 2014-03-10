/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "multiTAPdelay.h"

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
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    void processBlockBypassed(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    //==============================================================================
    bool hasEditor() const override                           { return true;}
    AudioProcessorEditor* createEditor() override;

    //==============================================================================
    const String getName() const override                      { return JucePlugin_Name;}

    int getNumParameters() override;

    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override {return 0;}
    int getCurrentProgram() override {return 0;}
    void setCurrentProgram (int /*index*/) override {}
    const String getProgramName (int /*index*/ ) override {return String::empty;}
    void changeProgramName (int /*index*/, const String& /*newName*/) override {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    enum Param
    {
        DelayParam = 0,
        ModeParam,
        IntensityParam,
        RepeatParam,
        ReverbParam,
        oldParam,
        bypassParam,
        FBParam,
        
        numParam

    };
    
    float delay_sec,
    intensity,
    repeat_rate,
    reverb_volume,
    fb_gain;
    
    bool bypass,
    old;
    
    int mode;
    
    AudioPlayHead::CurrentPositionInfo lastPosInfo;
    int lastUIWidth,lastUIHeight;
    
private:
    //==============================================================================
    CmultiTAPdelay *myMultiDelay;
    
    AudioSampleBuffer delayBuffer;
    int delayPosition;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
