#include "PluginEditor.h"
#include "FloatParameter.h"
#include "PluginProcessor.h"

//const int PDC_DELAY_TIME = 1024;

//==============================================================================
AlkamistMIDIDelayAudioProcessor::AlkamistMIDIDelayAudioProcessor()
{
    double sampleRate = getSampleRate();
    int samplesPerBlock = getBlockSize();

    addParameter (delayParameter  = new FloatParameter (0.0f, 0.0f, 100.0f, "Delay", "ms", sampleRate, samplesPerBlock));

    reset();

    //mMIDIHumanizer.setMaximumDelayTime (PDC_DELAY_TIME);

    //setLatencySamples (PDC_DELAY_TIME);
}

AlkamistMIDIDelayAudioProcessor::~AlkamistMIDIDelayAudioProcessor()
{
}

//==============================================================================
const String AlkamistMIDIDelayAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String AlkamistMIDIDelayAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool AlkamistMIDIDelayAudioProcessor::isInputChannelStereoPair (int /*index*/) const
{
    return true;
}

bool AlkamistMIDIDelayAudioProcessor::isOutputChannelStereoPair (int /*index*/) const
{
    return true;
}

bool AlkamistMIDIDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AlkamistMIDIDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AlkamistMIDIDelayAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double AlkamistMIDIDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//==============================================================================
void AlkamistMIDIDelayAudioProcessor::prepareToPlay (double /*sampleRate*/, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    reset();
}

void AlkamistMIDIDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void AlkamistMIDIDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    bufferParameters();
    sendParameterBuffers();

    mMIDIDelay.processMIDIBuffer (midiMessages);

    /*for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float temporaryGain = mMIDIDelay.mDelayTime[sample] / 100.0f;
            channelData[sample] = temporaryGain;
        }
    }*/

    clearParameterChanges();

    for (int index = getNumInputChannels(); index < getNumOutputChannels(); ++index)
        buffer.clear (index, 0, buffer.getNumSamples());
}

//==============================================================================
AudioProcessorEditor* AlkamistMIDIDelayAudioProcessor::createEditor()
{
    return new AlkamistMIDIDelayAudioProcessorEditor (*this);
}

//==============================================================================
void AlkamistMIDIDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    // Create an outer XML element..
    XmlElement xmlRoot ("ALKAMISTMIDIDELAYSETTINGS");
    XmlElement* xmlPointer;

    // Document our parameter values in XML child elements.
    xmlPointer = xmlRoot.createNewChildElement ("delayParameter");
    xmlPointer->addTextElement (String (delayParameter->getUnNormalizedUnSmoothedValue()));

    // Use this helper function to stuff it into the binary blob and return it.
    copyXmlToBinary (xmlRoot, destData);
}

void AlkamistMIDIDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    ScopedPointer<XmlElement> xmlPluginState (getXmlFromBinary (data, sizeInBytes));

    if (xmlPluginState != nullptr)
    {
        forEachXmlChildElement (*xmlPluginState, xmlChildPointer)
        {
            if(xmlChildPointer->hasTagName("delayParameter"))
            {
                String text = xmlChildPointer->getAllSubText();
                delayParameter->setNormalizedValue (text.getFloatValue());
            }
        }
    }
}

//==============================================================================

void AlkamistMIDIDelayAudioProcessor::bufferParameters()
{
    delayParameter->bufferParameter();
}

void AlkamistMIDIDelayAudioProcessor::sendParameterBuffers()
{
    if (delayParameter->parameterChangedThisBlock())
    {
        mMIDIDelay.setDelayTime (delayParameter->getUnNormalizedSmoothedBuffer());

        delayParameter->setFlagForSendingFlatBuffer (true);
    }
    if (delayParameter->parameterNeedsToSendFlatBuffer())
    {
        mMIDIDelay.setDelayTime (delayParameter->getUnNormalizedSmoothedBuffer());

        delayParameter->setFlagForSendingFlatBuffer (false);
    }
}

void AlkamistMIDIDelayAudioProcessor::clearParameterChanges()
{
    delayParameter->clearParameterChange();
}

void AlkamistMIDIDelayAudioProcessor::reset()
{
    double sampleRate = getSampleRate();
    int samplesPerBlock = getBlockSize();

    mMIDIDelay.reset (sampleRate, samplesPerBlock);

    // Parameters
    delayParameter->reset (sampleRate, samplesPerBlock);
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AlkamistMIDIDelayAudioProcessor();
}




