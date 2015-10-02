#include "MIDIDelay.h"

MIDIDelay::MIDIDelay()
{

}

void MIDIDelay::processMIDIBuffer (MidiBuffer& inputMIDIBuffer)
{
    MidiBuffer::Iterator inputMIDIBufferIterator (inputMIDIBuffer);

    MidiMessage currentMidiMessage;
    int midiMessageSamplePosition = 0;

    if (! inputMIDIBuffer.isEmpty())
    {
        inputMIDIBufferIterator.getNextEvent (currentMidiMessage, midiMessageSamplePosition);
        bool midiBufferIsNotEmpty = true;

        for (int sampleIndex = 0; sampleIndex < mBlockSize; ++sampleIndex)
        {
            // Go through every MIDI message this sample.
            while (sampleIndex == midiMessageSamplePosition
                && midiBufferIsNotEmpty)
            {
                double delayedSamplePosition = midiMessageSamplePosition + mDelayTime[sampleIndex];
                MidiMessage delayedMIDIMessage (currentMidiMessage, delayedSamplePosition);

                mDelayedMIDIBuffer.push_back (delayedMIDIMessage);

                midiBufferIsNotEmpty = inputMIDIBufferIterator.getNextEvent (currentMidiMessage, midiMessageSamplePosition);
            }
        }
    }

    if (! mDelayedMIDIBuffer.empty())
    {
        for (int index = 0; index < mDelayedMIDIBuffer.size(); ++index)
        {
            if (mDelayedMIDIBuffer[index].getTimeStamp() < mBlockSize)
            {
                mReplacementBuffer.addEvent (mDelayedMIDIBuffer[index],
                                             int (mDelayedMIDIBuffer[index].getTimeStamp()));

                mDelayedMIDIBuffer.erase (mDelayedMIDIBuffer.begin() + index);
                --index;
            }
            else if (mDelayedMIDIBuffer[index].getTimeStamp() >= mBlockSize)
            {
                double newTimeStamp = mDelayedMIDIBuffer[index].getTimeStamp() - mBlockSize;
                mDelayedMIDIBuffer[index].setTimeStamp (newTimeStamp);
            }
        }
    }

    inputMIDIBuffer.swapWith (mReplacementBuffer);
    mReplacementBuffer.clear();
}
void MIDIDelay::reset (double inputSampleRate, int inputBlockSize)
{
    mSampleRate = inputSampleRate;
    mBlockSize = inputBlockSize;
}

void MIDIDelay::setDelayTimeInms (std::vector<float> inputDelayTime) 
{
    mDelayTime = inputDelayTime;

    for (int index = 0; index < mDelayTime.size(); ++index)
    {
        mDelayTime[index] = mDelayTime[index] * mSampleRate / 1000.0;
    }
}