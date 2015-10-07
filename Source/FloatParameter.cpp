#include <algorithm>

#include "FloatParameter.h"

FloatParameter::FloatParameter (float defaultParameterValue,
                                float minimumParameterValue,
                                float maximumParameterValue,
                                const String& parameterName,
                                const String& parameterLabel,
                                double inputSampleRate,
                                int inputBlockSize)
    : mUnSmoothedParameterValue (defaultParameterValue),
      mDefaultValue (defaultParameterValue),
      mMinimumValue (minimumParameterValue),
      mMaximumValue (maximumParameterValue),
      mName (parameterName),
      mLabel (parameterLabel),
      mNormalizableRange (mMinimumValue, mMaximumValue),
      mLinearlySmoothedDouble (defaultParameterValue),
      mParameterChangedThisBlock (false),
      mParameterWasReset (false),
      mParameterNeedsToSendFlatBuffer (false),
      mSampleRate (inputSampleRate),
      mBlockSize (inputBlockSize)
{
    reset (inputSampleRate, inputBlockSize);
}

float FloatParameter::getUnNormalizedUnSmoothedValue()
{
    float unNormalizedValue = mNormalizableRange.convertFrom0to1 (mUnSmoothedParameterValue);
    return unNormalizedValue;
}

std::vector<float> FloatParameter::getUnNormalizedSmoothedBuffer()
{
    std::vector<float> unNormalizedBuffer (mParameterBuffer.size());

    for (int index = 0; index < mParameterBuffer.size(); ++index)
    {
        float currentValue = mParameterBuffer[index];
        float unNormalizedValue = mNormalizableRange.convertFrom0to1 (currentValue);
        unNormalizedBuffer[index] = unNormalizedValue;
    }

    return unNormalizedBuffer;
}

std::vector<float> FloatParameter::getNormalizedSmoothedBuffer()
{
    return mParameterBuffer;
}

void FloatParameter::setNormalizedValue (float nonNormalizedValue)
{
    float newValue = mNormalizableRange.convertTo0to1 (nonNormalizedValue);
    newValue = std::min (newValue, 1.0f);
    newValue = std::max (newValue, 0.0f);
    setValueNotifyingHost (newValue);
}

void FloatParameter::clearParameterChange()                                      
{ 
    if (mParameterNeedsToSendFlatBuffer)
    {
        mParameterNeedsToSendFlatBuffer = false;
    }

    if (mParameterChangedThisBlock)
    {
        for (int index = 0; index < mBlockSize; ++index)
        {
            mParameterBuffer[index] = mUnSmoothedParameterValue;
        }

        mParameterNeedsToSendFlatBuffer = true;
    }

    mParameterChangedThisBlock = false; 
};

void FloatParameter::bufferParameter()
{
    if (mParameterChangedThisBlock)
    {
        for (int index = 0; index < mBlockSize; ++index)
        {
            mLinearlySmoothedDouble.processPerSample();
            mParameterBuffer[index] = ((float) mLinearlySmoothedDouble.getCurrentValue());
        }
    }

    if (mParameterWasReset)
    {
        for (int index = 0; index < mBlockSize; ++index)
        {
            mParameterBuffer[index] = mUnSmoothedParameterValue;
        }

        mParameterWasReset = false;
    }
}

void FloatParameter::reset (double inputSampleRate, int inputBlockSize)
{
    mSampleRate = inputSampleRate;
    mBlockSize = inputBlockSize;

    mParameterBuffer.resize (mBlockSize);

    // Linear Parameter Ramp
    double smoothingTimeInSeconds = ((double) mBlockSize) / mSampleRate;
    mLinearlySmoothedDouble.reset (mSampleRate, smoothingTimeInSeconds);

    mParameterWasReset = true;
}

// Overridden Functions:

String FloatParameter::getName (int maximumStringLength) const    
{ 
    int numberOfCharactersToDrop = mName.length() - maximumStringLength;

    return mName.dropLastCharacters (numberOfCharactersToDrop); 
};

String FloatParameter::getText(float inputValue, int) const
{
    float unNormalizedValue = mNormalizableRange.convertFrom0to1 (inputValue);
    String outputString (unNormalizedValue);
    return outputString;
}

void FloatParameter::setValue (float inputValue)
{
    mUnSmoothedParameterValue = inputValue;
    mLinearlySmoothedDouble.setTargetValue (mUnSmoothedParameterValue);
    mParameterChangedThisBlock = true;
}