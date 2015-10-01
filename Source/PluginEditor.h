#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AlkamistMIDIDelayAudioProcessor;
class MainEditorWindow;

class AlkamistMIDIDelayAudioProcessorEditor  : public AudioProcessorEditor
{
public:

    AlkamistMIDIDelayAudioProcessorEditor (AlkamistMIDIDelayAudioProcessor& owner);
    ~AlkamistMIDIDelayAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:

    AlkamistMIDIDelayAudioProcessor& mParentProcessor;

    ScopedPointer<MainEditorWindow> mMainEditorWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlkamistMIDIDelayAudioProcessorEditor)

};


#endif  // PLUGINEDITOR_H_INCLUDED