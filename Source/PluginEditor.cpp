#include "PluginProcessor.h"
#include "MainEditorWindow.h"

#include "PluginEditor.h"

//==============================================================================
AlkamistMIDIDelayAudioProcessorEditor::AlkamistMIDIDelayAudioProcessorEditor (AlkamistMIDIDelayAudioProcessor& owner)
    : AudioProcessorEditor (owner),
      mParentProcessor (owner)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (104, 128);

    addAndMakeVisible (mMainEditorWindow = new MainEditorWindow (mParentProcessor));
}

AlkamistMIDIDelayAudioProcessorEditor::~AlkamistMIDIDelayAudioProcessorEditor()
{
    mMainEditorWindow = nullptr;
}

//==============================================================================
void AlkamistMIDIDelayAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void AlkamistMIDIDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
