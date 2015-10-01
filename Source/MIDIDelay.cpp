#include "MIDIDelay.h"

MIDIDelay::MIDIDelay()
{

}

void MIDIDelay::processMIDIBuffer (MidiBuffer& inputMIDIBuffer)
{

}

void MIDIDelay::reset (double inputSampleRate, int inputBlockSize)
{
    mSampleRate = inputSampleRate;
    mBlockSize = inputBlockSize;
}