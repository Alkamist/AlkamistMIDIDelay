#ifndef MIDIDELAY_H_INCLUDED
#define MIDIDELAY_H_INCLUDED

#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"

class MIDIDelay
{
public:

    MIDIDelay();

    void reset (double inputSampleRate, int inputBlockSize);
    void processMIDIBuffer (MidiBuffer& inputMIDIBuffer);

    void setDelayTimeInms (std::vector<float> inputDelayTime);

private:

    std::vector<float> mDelayTime;

    double mSampleRate;
    int mBlockSize;

    std::vector<MidiMessage> mDelayedMIDIBuffer;
    MidiBuffer mReplacementBuffer;

};

#endif  // MIDIDELAY_H_INCLUDED
