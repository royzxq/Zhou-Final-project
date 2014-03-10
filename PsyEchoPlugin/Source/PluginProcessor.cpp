/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioProcessor* JUCE_CALLTYPE createPluginFilter();

//==================================
//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor() : delayBuffer(2,2000)
{
    delay_sec = 0.1f;
    intensity = 0.1f;
    repeat_rate = 0.2;
    old = true;
    bypass = false;
    reverb_volume = 1.0f;
    
    lastUIWidth = 800;
    lastUIHeight = 400;
    
    lastPosInfo.resetToDefault();
    delayPosition = 0;
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================

int NewProjectAudioProcessor::getNumParameters()
{
    return numParam;
}

float NewProjectAudioProcessor::getParameter (int index)
{
    switch (index)
    {
        case DelayParam:        return delay_sec;
            break;
        case ModeParam:         return (float)mode;
            break;
        case IntensityParam:    return intensity;
            break;
        case RepeatParam:       return repeat_rate;
            break;
        case ReverbParam:       return reverb_volume;
            break;
        case oldParam:
        {
            if (old == true)
                return 1.0f;
            else
                return 0.0f;
        }
            break;
        case bypassParam:
        {
            if (old == true)
                return 1.0f;
            else
                return 0.0f;
        }
            break;
        case FBParam:           return fb_gain;
            
        default: return 0.0f;
    }
}

void NewProjectAudioProcessor::setParameter (int index, float newValue)
{
    switch (index)
    {
        case DelayParam:
            delay_sec = newValue;
            break;
        
        case ModeParam:
            mode = newValue;
            break;
            
        case IntensityParam:
        intensity = newValue;
        
        case RepeatParam:
        repeat_rate = newValue;
        
        case ReverbParam:
        reverb_volume = newValue;
        
        case bypassParam:
            if (newValue==1)
            {
                bypass = true;
            }
            else bypass = false;
            break;
        
        case oldParam:
            if (newValue==1)
            {
                old = true;
            }
            else old = false;
            break;
        
        case FBParam:
            fb_gain = newValue;
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

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    myMultiDelay = new CmultiTAPdelay(sampleRate,2);
    delayBuffer.clear();
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    delete  myMultiDelay;
}

void NewProjectAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
    if (!bypass)
    {
        const int numSamples = buffer.getNumSamples();
        float **input = buffer.getArrayOfChannels();
        const int numChannels = buffer.getNumChannels();

        myMultiDelay -> setDelay(delay_sec);
        myMultiDelay -> setMode(mode);
        myMultiDelay -> process(input, input, numSamples);
        buffer.setDataToReferTo(input, numChannels, numSamples);
    }
    else
    {
        processBlockBypassed(buffer, midiMessages);
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}
void NewProjectAudioProcessor::processBlockBypassed(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
    float **input = buffer.getArrayOfChannels();
    const int numChannels = buffer.getNumChannels();
    myMultiDelay->processBypass(input, input, numSamples);
    buffer.setDataToReferTo(input, numChannels, numSamples);
}
//==============================================================================

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
