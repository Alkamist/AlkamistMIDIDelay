#ifndef FLOATPARAMETER_H_INCLUDED
#define FLOATPARAMETER_H_INCLUDED

#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"
#include "LinearlySmoothedDouble.h"

class FloatParameter : public AudioProcessorParameter
{
public:

    FloatParameter (float defaultParameterValue,
                    float minimumParameterValue,
                    float maximumParameterValue,
                    const String& parameterName,
                    const String& parameterLabel,
                    double inputSampleRate,
                    int inputBlockSize);

    void bufferParameter();
    void reset (double inputSampleRate, int inputBlockSize);

    inline bool parameterChangedThisBlock()                                 { return mParameterChangedThisBlock; };
    void clearParameterChange();

    inline bool parameterNeedsToSendFlatBuffer()                            { return mParameterNeedsToSendFlatBuffer; };
    inline void setFlagForSendingFlatBuffer (bool input)                    { mParameterNeedsToSendFlatBuffer = input; };

    inline float getMinimum() const                                         { return mMinimumValue; };
    inline float getMaximum() const                                         { return mMaximumValue; };
    float getUnNormalizedUnSmoothedValue();
    std::vector<float> getUnNormalizedSmoothedBuffer();
    std::vector<float> getNormalizedSmoothedBuffer();
    void setNormalizedValue (float nonNormalizedValue);

    inline float getDefaultValue() const override                           { return mDefaultValue; };
    inline String getLabel() const override                                 { return mLabel; };
    inline float getValueForText (const String& inputString) const override { return inputString.getFloatValue(); };
    inline float getValue() const override                                  { return mUnSmoothedParameterValue; };
    String getName (int maximumStringLength) const override;
    String getText(float inputValue, int) const override;
    void setValue (float newValue) override;

private:

    std::vector<float> mParameterBuffer;

    float mUnSmoothedParameterValue;
    float mDefaultValue;
    float mMinimumValue;
    float mMaximumValue;
    String mName;
    String mLabel;

    double mSampleRate;
    int mBlockSize;
    bool mParameterChangedThisBlock;
    bool mParameterWasReset;
    bool mParameterNeedsToSendFlatBuffer;

    LinearlySmoothedDouble mLinearlySmoothedDouble;
    NormalisableRange<float> mNormalizableRange;

};

#endif  // FLOATPARAMETER_H_INCLUDED
