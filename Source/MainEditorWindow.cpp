/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
#include "FloatParameter.h"
//[/Headers]

#include "MainEditorWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainEditorWindow::MainEditorWindow (AlkamistMIDIDelayAudioProcessor& inputProcessor)
    : mParentProcessor (&inputProcessor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (delaySlider = new Slider ("Delay Slider"));
    delaySlider->setRange (0, 10, 0.01);
    delaySlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delaySlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    delaySlider->setColour (Slider::thumbColourId, Colour (0xff909090));
    delaySlider->setColour (Slider::trackColourId, Colour (0x7fdddddd));
    delaySlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fdddddd));
    delaySlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66dddddd));
    delaySlider->setColour (Slider::textBoxTextColourId, Colour (0xffdddddd));
    delaySlider->setColour (Slider::textBoxBackgroundColourId, Colour (0xff4a4a4a));
    delaySlider->setColour (Slider::textBoxHighlightColourId, Colour (0x40e4e4e4));
    delaySlider->addListener (this);

    addAndMakeVisible (delayLabel = new Label ("Delay Label",
                                               TRANS("Delay (ms)")));
    delayLabel->setFont (Font (15.00f, Font::plain));
    delayLabel->setJustificationType (Justification::centred);
    delayLabel->setEditable (false, false, false);
    delayLabel->setColour (Label::textColourId, Colour (0xffdddddd));
    delayLabel->setColour (TextEditor::textColourId, Colours::black);
    delayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    setAllSliderRanges();
    //[/UserPreSize]

    setSize (240, 128);


    //[Constructor] You can add your own custom stuff here..

    delaySlider->setVelocityModeParameters(0.45, 1, 0.05, true);
    delaySlider->setDoubleClickReturnValue(true, 0.0);

    updateAllSliderValues();

    startTimerHz(60);

    //[/Constructor]
}

MainEditorWindow::~MainEditorWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    delaySlider = nullptr;
    delayLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainEditorWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323232));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainEditorWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    delaySlider->setBounds (64, 40, 104, 88);
    delayLabel->setBounds (72, 0, 88, 40);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainEditorWindow::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    setNormalizedValueFromSlider (sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == delaySlider)
    {
        //[UserSliderCode_delaySlider] -- add your slider handling code here..
        //[/UserSliderCode_delaySlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainEditorWindow::setSliderRange (Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider(slider))
    {
        double dittoInterval = slider->getInterval();

        slider->setRange (parameter->getMinimum(), parameter->getMaximum(), dittoInterval);
    }
}

void MainEditorWindow::setAllSliderRanges()
{
    setSliderRange (delaySlider);
}

void MainEditorWindow::setNormalizedValueFromSlider(Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider(slider))
    {
        parameter->setNormalizedValue ((float) slider->getValue());
    }
}

void MainEditorWindow::updateSliderValue(Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider(slider))
    {
        float unNormalizedParameterValue = parameter->getUnNormalizedUnSmoothedValue();

        slider->setValue (unNormalizedParameterValue);
    }
}

void MainEditorWindow::updateAllSliderValues()
{
    updateSliderValue (delaySlider);
}

void MainEditorWindow::timerCallback()
{
    updateAllSliderValues();
}

void MainEditorWindow::sliderDragStarted (Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider (slider))
    {
        parameter->beginChangeGesture();
    }
}

void MainEditorWindow::sliderDragEnded (Slider* slider)
{
    if (FloatParameter* parameter = getParameterFromSlider (slider))
    {
        parameter->endChangeGesture();
    }
}

FloatParameter* MainEditorWindow::getParameterFromSlider (const Slider* slider) const
{
    if (slider == delaySlider)
        return mParentProcessor->delayParameter;

    return nullptr;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainEditorWindow" componentName=""
                 parentClasses="public Component, public Timer" constructorParams="AlkamistMIDIDelayAudioProcessor&amp; inputProcessor"
                 variableInitialisers="mParentProcessor (&amp;inputProcessor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="240" initialHeight="128">
  <BACKGROUND backgroundColour="ff323232"/>
  <SLIDER name="Delay Slider" id="bd046531e78c1c7" memberName="delaySlider"
          virtualName="" explicitFocusOrder="0" pos="64 40 104 88" thumbcol="ff909090"
          trackcol="7fdddddd" rotarysliderfill="7fdddddd" rotaryslideroutline="66dddddd"
          textboxtext="ffdddddd" textboxbkgd="ff4a4a4a" textboxhighlight="40e4e4e4"
          min="0" max="10" int="0.01" style="RotaryVerticalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Delay Label" id="bd41beb649728737" memberName="delayLabel"
         virtualName="" explicitFocusOrder="0" pos="72 0 88 40" textCol="ffdddddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Delay (ms)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
