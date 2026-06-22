/*
  ==============================================================================

	ScopeComponent.h
	Created: 19 Jun 2026 9:38:18am
	Author:  SchoeDam

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ScopeComponent : public juce::Component, private juce::Timer
{
public:
	ScopeComponent() : forwardFFT(fftOrder), window(fftSize, juce::dsp::WindowingFunction<float>::hann)
	{
		juce::zeromem(fifo, sizeof(fifo));
		juce::zeromem(fftData, sizeof(fftData));
		juce::zeromem(scopeData, sizeof(scopeData));

		setOpaque(true);
		startTimerHz(60);
	}

	void pushNextSampleIntoFifo(float sample) noexcept
	{
		if (fifoIndex == fftSize)
		{
			if (!nextFFTBlockReady)
			{
				juce::zeromem(fftData, sizeof(fftData));
				memcpy(fftData, fifo, sizeof(fifo));
				nextFFTBlockReady = true;
			}

			fifoIndex = 0;
		}
		fifo[fifoIndex++] = sample;
	}

	void paint(juce::Graphics& g) override
	{
		g.fillAll(juce::Colours::black);

		g.setColour(juce::Colours::lime);

		auto bounds = getLocalBounds().toFloat();

		juce::Path spectrumPath;

		spectrumPath.startNewSubPath(0.0f, bounds.getBottom());

		for (int i = 1; i < scopeSize; ++i)
		{
			auto x = juce::jmap<float>(
				(float)i,
				0.0f,
				(float)scopeSize - 1,
				0.0f,
				bounds.getWidth());

			auto y = juce::jmap<float>(
				scopeData[i],
				0.0f,
				1.0f,
				bounds.getBottom(),
				bounds.getY());

			spectrumPath.lineTo(x, y);
		}

		g.strokePath(spectrumPath, juce::PathStrokeType(2.0f));
	}

private:
	static constexpr int fftOrder = 11;
	static constexpr int fftSize = 1 << fftOrder;
	static constexpr int scopeSize = 512;

	juce::dsp::FFT forwardFFT;
	juce::dsp::WindowingFunction<float> window;

	float fifo[fftSize];
	float fftData[2 * fftSize];
	float scopeData[scopeSize];

	int fifoIndex = 0;
	bool nextFFTBlockReady = false;

	void timerCallback() override
	{
		if (nextFFTBlockReady)
		{
			drawNextFrameOfSpectrum();
			nextFFTBlockReady = false;
			repaint();
		}
	}

	void drawNextFrameOfSpectrum()
	{
		window.multiplyWithWindowingTable(fftData, fftSize);

		forwardFFT.performFrequencyOnlyForwardTransform(fftData);

		auto mindB = -100.0f;
		auto maxdB = 0.0f;

		for (int i = 0; i < scopeSize; ++i)
		{
			auto skewedProportionX =
				1.0f - std::exp(std::log(1.0f - (float)i / (float)scopeSize) * 0.2f);

			auto fftDataIndex = juce::jlimit(
				0,
				fftSize / 2,
				(int)(skewedProportionX * fftSize * 0.5f));

			auto level = juce::jmap(
				juce::jlimit(
					mindB,
					maxdB,
					juce::Decibels::gainToDecibels(fftData[fftDataIndex])
					- juce::Decibels::gainToDecibels((float)fftSize)),
				mindB,
				maxdB,
				0.0f,
				1.0f);

			scopeData[i] = level;
		}
	}

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScopeComponent)
};