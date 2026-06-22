/*
  ==============================================================================

    UIComponent.h
    Created: 19 Jun 2026 10:20:31am
    Author:  SchoeDam

  ==============================================================================
*/

#pragma once
#include "AudioState.h"


class UIComponent : public juce::Component
{
public:
	UIComponent(AudioState& state) :audioState(state)
	{

		levelSlider.reset(new juce::Slider("level"));
		addAndMakeVisible(levelSlider.get());
		levelSlider->setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		levelSlider->setRange(0.0f, 1.0f);
		levelSlider->setBounds(0, labelHeight, elementWidth, elementHeight);
		levelSlider->setValue(0.1f);
		levelSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
		levelSlider->onValueChange = [this] {audioState.level.store(static_cast<float>(levelSlider->getValue()));};

		addAndMakeVisible(&lblFreq);
		lblFreq.setBounds(0, 0, elementWidth, labelHeight);
		lblFreq.setText("Freq", juce::NotificationType::dontSendNotification);
		lblFreq.setJustificationType(juce::Justification::centred);



		freqSlider.reset(new juce::Slider("freq"));
		addAndMakeVisible(freqSlider.get());
		freqSlider->setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		freqSlider->setRange(20.0f, 20000.0f);
		freqSlider->setBounds(100, labelHeight, elementWidth, elementHeight);
		freqSlider->setValue(500.0f);
		freqSlider->setSkewFactorFromMidPoint(500.0f);
		freqSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
		freqSlider->setTextValueSuffix(" Hz");
		freqSlider->onValueChange = [this] {audioState.freq.store(static_cast<double>(freqSlider->getValue()));};

	}

	~UIComponent()
	{
		levelSlider = nullptr;
		freqSlider = nullptr;
	}

	void resize() {}

	std::unique_ptr<juce::Slider> levelSlider;
	std::unique_ptr<juce::Slider> freqSlider;

	juce::Label lblFreq;

private:

	int labelHeight = 25;

	int elementWidth = 100;
	int elementHeight = 500;

	AudioState& audioState;
};
