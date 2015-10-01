#ifndef LINEARLYSMOOTHEDDOUBLE_H_INCLUDED
#define LINEARLYSMOOTHEDDOUBLE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class LinearlySmoothedDouble
{
public:

    LinearlySmoothedDouble(double defaultValue);

    void reset (double sampleRate, double fadeLengthSeconds);
    void processPerSample();

    // Getters
    inline double getCurrentValue() const { return mCurrentValue; };

    // Setters
    void setTargetValue (double newValue);

private:

    mutable double mCurrentValue;
    mutable double mTarget;
    mutable double mStep;
    mutable int mCountdown;
    mutable int mStepsToTarget;

    JUCE_DECLARE_NON_COPYABLE (LinearlySmoothedDouble)

};

#endif  // LINEARLYSMOOTHEDDOUBLE_H_INCLUDED
