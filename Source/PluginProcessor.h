#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MIDIDelay.h"

class FloatParameter;

//==============================================================================
/**
*/
class AlkamistMIDIDelayAudioProcessor  : public AudioProcessor
{
public:

    //==============================================================================
    AlkamistMIDIDelayAudioProcessor();
    ~AlkamistMIDIDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override                                                 { return true; };

    //==============================================================================
    const String getName() const override                                           { return JucePlugin_Name; }

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override                                                   { return 1; }
    int getCurrentProgram() override                                                { return 0; }
    void setCurrentProgram (int /*index*/) override                                 {}
    const String getProgramName (int /*index*/) override                            { return "Default"; }
    void changeProgramName (int /*index*/, const String& /*newName*/) override      {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================

    void reset (double inputSampleRate, int inputBlockSize);

    FloatParameter* delayParameter;

private:

    void bufferParameters();
    void sendParameterBuffers();
    void clearParameterChanges();

    MIDIDelay mMIDIDelay;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlkamistMIDIDelayAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
