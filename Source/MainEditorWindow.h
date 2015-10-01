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

#ifndef __JUCE_HEADER_3FD6B791BA8A3E30__
#define __JUCE_HEADER_3FD6B791BA8A3E30__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"

class AlkamistMIDIDelayAudioProcessor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainEditorWindow  : public Component,
                          public Timer,
                          public SliderListener
{
public:
    //==============================================================================
    MainEditorWindow (AlkamistMIDIDelayAudioProcessor& inputProcessor);
    ~MainEditorWindow();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void sliderDragStarted  (Slider* slider) override;
    void sliderDragEnded    (Slider* slider) override;
    void timerCallback() override;
    void updateSliderValue (Slider* slider);
    void updateAllSliderValues();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AlkamistMIDIDelayAudioProcessor* mParentProcessor;
    FloatParameter* getParameterFromSlider (const Slider*) const;
    void setNormalizedValueFromSlider(Slider* slider);
    void setSliderRange (Slider* slider);
    void setAllSliderRanges();
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> delaySlider;
    ScopedPointer<Label> delayLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainEditorWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_3FD6B791BA8A3E30__
