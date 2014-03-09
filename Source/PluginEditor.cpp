/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor* ownerFilter)
: AudioProcessorEditor (ownerFilter),title("","Space Echo"),FBLabel("","FeedBack Gain:"),intensityLabel("","Intensity:"),RrateLabel("","Repeat Rate:"),ReverbLabel("","Reverb Volumn:"),ModeLabel("","Mode Selector:"),Bypass(false),Old(false)
{
    // This is where our plugin's editor size is set.
    addAndMakeVisible(FBGainSlider);
    FBGainSlider.setSliderStyle(Slider::LinearBar);
    FBGainSlider.addListener(this);
    FBGainSlider.setRange(0.0, 2.0,0.1);
    
    addAndMakeVisible(intensitySlider);
    intensitySlider.setSliderStyle(Slider::LinearBar);
    intensitySlider.addListener(this);
    intensitySlider.setRange(0.0, 2.0,0.1);
    
    addAndMakeVisible(RrateSlider);
    RrateSlider.setSliderStyle(Slider::LinearBar);
    RrateSlider.addListener(this);
    RrateSlider.setRange(0.0, 2.0,0.1);
    
    addAndMakeVisible(ReverbSlider);
    ReverbSlider.setSliderStyle(Slider::LinearBar);
    ReverbSlider.addListener(this);
    ReverbSlider.setRange(0.0, 2.0,0.1);
    
    addAndMakeVisible(ModeSlider);
    ModeSlider.setSliderStyle(Slider::Rotary);
    ModeSlider.addListener(this);
    ModeSlider.setRange(0.0,4.0,1.0);
    
    
    addAndMakeVisible(BypassButton);
    BypassButton.setButtonText("ByPass");
    BypassButton.addListener(this);
    
    addAndMakeVisible(OldButton);
    OldButton.setButtonText("Old");
    OldButton.addListener(this);
    
    addAndMakeVisible(title);
    title.setColour(Label::textColourId, Colours::blue);
    title.setFont(Font(17.0f));
    
    addAndMakeVisible(resizer = new ResizableCornerComponent(this,&resizeLimits));
    
    resizeLimits.setSizeLimits(200, 200, 1000, 400);
    
    setSize(700, 400);
    
    startTimer(50);
    
    FBLabel.attachToComponent(&FBGainSlider, true);
    intensityLabel.attachToComponent(&intensitySlider, true);
    ModeLabel.attachToComponent(&ModeSlider, true);
    ReverbLabel.attachToComponent(&ReverbSlider, true);
    RrateLabel.attachToComponent(&RrateSlider, true);
    
    
    
    //BypassButton.setClickingTogglesState(true);
    //OldButton.setClickingTogglesState(true);
    
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

void NewProjectAudioProcessorEditor::buttonClicked(Button * button)
{
    if (button == &BypassButton) {
        Bypass = !Bypass;
    }
    if (button == &OldButton) {
        Old = !Old;
    }

}

void NewProjectAudioProcessorEditor::timerCallback()
{
    NewProjectAudioProcessor * ourProcessor = getProcessor();
    
    FBGainSlider.setValue(ourProcessor->fb_gain,sendNotificationSync);
    RrateSlider.setValue(ourProcessor->repeat_rate,sendNotificationSync);
    ModeSlider.setValue(ourProcessor->mode,sendNotificationSync);
    
}

void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &FBGainSlider) {
        getProcessor() -> setParameterNotifyingHost(NewProjectAudioProcessor::FBParam, (float)FBGainSlider.getValue());
    }
    else if (slider == &intensitySlider){
        getProcessor() -> setParameterNotifyingHost(NewProjectAudioProcessor::IntensityParam, (float)intensitySlider.getValue());
    }
    else if(slider == &RrateSlider)
    {
        getProcessor() -> setParameterNotifyingHost(NewProjectAudioProcessor::RepeatParam, (float)RrateSlider.getValue());
    }
    else if(slider == & ReverbSlider)
    {
        getProcessor() -> setParameterNotifyingHost(NewProjectAudioProcessor::ReverbParam, (float)ReverbSlider.getValue());
    }
    else if(slider == & ModeSlider){
        getProcessor() -> setParameterNotifyingHost(NewProjectAudioProcessor::ModeParam, (int)ModeSlider.getValue());
    }
}
//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    
    g.fillAll (Colours::white);

}

void NewProjectAudioProcessorEditor::resized()
{
    title.setBounds(10, 10, 100, 30);
    intensitySlider.setBounds(200, 60, 100, 30);
    RrateSlider.setBounds(200, 100, 100, 30);
    ReverbSlider.setBounds(200, 150, 100, 30);
    FBGainSlider.setBounds(200, 200, 100, 30);
    BypassButton.setBounds(200, 300, 60, 40);
    OldButton.setBounds(200, 350, 40, 40);
    ModeSlider.setBounds(500, 300, 100, 40);
    resizer -> setBounds(getWidth() - 16 , getHeight() - 16 , 16, 16);
    
}

