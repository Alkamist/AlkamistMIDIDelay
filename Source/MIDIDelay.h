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

    inline void setDelayTime (std::vector<float> inputDelayTime) { mDelayTime = inputDelayTime; };

private:

    std::vector<float> mDelayTime;

    double mSampleRate;
    int mBlockSize;

};

#endif  // MIDIDELAY_H_INCLUDED
