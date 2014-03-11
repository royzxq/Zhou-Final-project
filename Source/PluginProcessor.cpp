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
const bool defaultOld = true;
const short defaultMode = 0;


//==================================
//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
{
    delay_sec = defaultDelay;
    intensity = defaultIntensity;
    repeat_rate = defaultRrate;
    old = defaultOld;
    bypass = defaultBypass;
    reverb_volumn = defaultReverb;
    lastUIWidth = 800;
    lastUIHeight = 400;
    mode = defaultMode;
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
    
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
        case bypassParam:
            // bypass = !bypass;
            if (newValue==1) {
                bypass = true;
            }
            else bypass = false;
            break;
        case oldParam:
            // old = !old;
            if (newValue==1) {
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
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    delete  myMultiDelay;
}

void NewProjectAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
//    float ** input = buffer.getArrayOfChannels();
//    const int numSamples = buffer.getNumSamples();
//    const int numChannels = buffer.getNumChannels();
//    for (int i =0 ; i < numSamples; i++) {
//                   for (int j = 0 ; j < numChannels ; j++) {
//                        float f = input[j][i];
//                        if(f!=0){
//                            int a = 0 ;
//                        }
//                    }
//                }
//    buffer.setDataToReferTo(input, 2, numSamples);
//
    if (!bypass) {
        const int numSamples = buffer.getNumSamples();
         float ** input = buffer.getArrayOfChannels();
         const int numChannels = buffer.getNumChannels();
     
         myMultiDelay -> setDelay(delay_sec);
         myMultiDelay -> setMode(mode);
         myMultiDelay -> process(input, input, numSamples);
        
         buffer.setDataToReferTo(input, 2, numSamples);
     }
     else {
         juce::AudioProcessor::processBlockBypassed(buffer, midiMessages);
     }

// In case we have more outputs than inputs, we'll clear any output
// channels that didn't contain input data, (because these aren't
// guaranteed to be empty - they may contain garbage).
//    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
//    {
//        buffer.clear (i, 0, buffer.getNumSamples());
//    }

}
void NewProjectAudioProcessor::processBlockBypassed(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
    float ** input = buffer.getArrayOfChannels();
    const int numChannels = buffer.getNumChannels();
    myMultiDelay -> setDelay(delay_sec);
    myMultiDelay -> setMode(mode);
    myMultiDelay->processBypass(input, input, numSamples);
    buffer.setDataToReferTo(input, 2, numSamples);
}
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
