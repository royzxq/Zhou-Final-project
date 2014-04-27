/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic startup code for a Juce application.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

const float defaultDelay = 0.1f;
const float defaultIntensity = 0.1f;
const float defaultReverb = 1.0f;
const bool defaultBypass = false;
const float defaultRrate = 0.2;
const bool defaultOld = false;
const short defaultMode = 0;
const float defaultRange = 1.0;

//==================================
//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
{
    delay_sec = defaultDelay;
    intensity = defaultIntensity;
    repeat_rate = defaultRrate;
    old = defaultOld;
    bypass = defaultBypass;
    HighShelving = false;
    LowShelving = false;
    ShelvingGain = 1.0;
    reverb_volumn = defaultReverb;
    InRange = defaultRange;
    CutoffHigh = 0.0;
    CutoffLow = 1.0;
    lastUIWidth = 700;
    lastUIHeight = 400;
    mode = defaultMode;
    myReverb = new Reverb();
   // fb_gain = 0.5;
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
    delete myReverb;
    myReverb = 0 ;
}

//==============================================================================
const String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int NewProjectAudioProcessor::getNumParameters()
{
    return numParam;
}

float NewProjectAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void NewProjectAudioProcessor::setParameter (int index, float newValue)
{
    switch (index) {
        case DelayParam:
            delay_sec = newValue;
            break;
        case ModeParam:
            mode = static_cast<int>(newValue);
            break;
        case IntensityParam:
            intensity = newValue;
            break;
        case RepeatParam:
            repeat_rate = newValue;
            break;
        case ReverbParam:
            reverb_volumn = newValue;
            break;
        case HighShelvingParam:
            HighShelving = !HighShelving;
            break;
        case LowShelvingParam:
            LowShelving = ! LowShelving;
            break;
        case CutoffHighParam:
            CutoffHigh = newValue;
            break;
        case CutoffLowParam:
            CutoffLow = newValue;
            break;
        case ShelvingGainParam:
            ShelvingGain = newValue;
            break;
        case oldParam:
            old = !old;
            break;
        case FBParam:
            fb_gain = newValue;
            break;
        case RangeParam:
            InRange = newValue;
            break;
        default:
            break;
    }
}

const String NewProjectAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String NewProjectAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String NewProjectAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String NewProjectAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool NewProjectAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool NewProjectAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool NewProjectAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 0;
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String NewProjectAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void NewProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    myMultiDelay = new MultiTapDelay(sampleRate,2);
    myHighShelving = new class HighShelving(CutoffHigh,ShelvingGain,2);
    myLowShelving = new class LowShelving(CutoffLow,ShelvingGain, 2);
    myNoise = new WhiteNoiseGen(0,0.007);
    myShaper = new WavShaper(4);
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    delete  myMultiDelay;
    delete myNoise;
    delete myShaper;
    delete myLowShelving;
    delete myHighShelving;
    LowShelving = 0;
    myHighShelving = 0;
    myMultiDelay = 0 ;
    myNoise = 0 ;
    myShaper = 0 ;
}

void NewProjectAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
    
        const int numSamples = buffer.getNumSamples();
        float ** input = buffer.getArrayOfChannels();
        const int numChannels = buffer.getNumChannels();
    
   
        if (mode == 3) {
            juce::Reverb::Parameters newParam;
            newParam.roomSize = reverb_volumn;
            newParam.damping = intensity;
            newParam.wetLevel = 1.0;
            newParam.dryLevel = 0.1;
            newParam.width = 0.5;
            newParam.freezeMode = 0.4;
            myReverb -> setParameters(newParam);
            myReverb -> processStereo(input[0], input[1], numSamples);

        }
        else if(mode<3){
            myMultiDelay -> setDelay(repeat_rate);
            myMultiDelay -> setFBgain(fb_gain);
            myMultiDelay -> setMode(mode);
            myMultiDelay -> process(input, input, numSamples);
        }
        else{
            myMultiDelay -> setDelay(repeat_rate);
            myMultiDelay -> setFBgain(fb_gain);
            myMultiDelay -> setMode(0);
            myMultiDelay -> process(input, input, numSamples);
            juce::Reverb::Parameters newParam;
            newParam.roomSize = reverb_volumn;
            newParam.damping = intensity;
            newParam.wetLevel = 1.0;
            newParam.dryLevel = 0.1;
            newParam.width = 0.5;
            newParam.freezeMode = 0.4;
            myReverb -> setParameters(newParam);
            myReverb -> processStereo(input[0], input[1], numSamples);
            
        }
        if (old) {
           myNoise -> generate(input, numChannels, numSamples);
        }
        
        myShaper -> setRange(InRange);
        
        myShaper -> process(input, input, numChannels, numSamples);
        if (HighShelving) {
            myHighShelving -> setCutoff(CutoffHigh);
            myHighShelving -> setGain(ShelvingGain);
            myHighShelving -> process(input, input, numSamples);
        }
        if (LowShelving)
        {
            myLowShelving -> setCutoff(CutoffLow);
            myLowShelving -> setGain(ShelvingGain);
            myLowShelving -> process(input, input, numSamples);
        }
        buffer.setDataToReferTo(input, numChannels, numSamples);
    
    
}
//void NewProjectAudioProcessor::processBlockBypassed(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
//{
//    const int numSamples = buffer.getNumSamples();
//    float ** input = buffer.getArrayOfChannels();
//    //const int numChannels = buffer.getNumChannels();
//    myMultiDelay -> setDelay(delay_sec);
//    myMultiDelay -> setFBgain(fb_gain);
//    myMultiDelay -> setMode(mode);
//    myMultiDelay -> processBypass(input, input, numSamples);
//    buffer.setDataToReferTo(input, 2, numSamples);
//}
//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
