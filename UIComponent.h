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

		sld_dbMin.reset(new juce::Slider("slider_dbMin"));
		addAndMakeVisible(sld_dbMin.get());
		sld_dbMin->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
		sld_dbMin->setRange(-100, 0, 1);
		sld_dbMin->setTextValueSuffix(" dB");
		sld_dbMin->setValue(-100);
		sld_dbMin->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, elementWidth, labelHeight);
		sld_dbMin->onValueChange = [this] {audioState.dbMin.store(static_cast<float>(sld_dbMin->getValue()));};
		sld_dbMin->setBounds(0, labelHeight, elementWidth, elementHeight);
		sld_dbMin->setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::lime);

		lbl_dbMin.reset(new juce::Label("label_dbMin"));
		addAndMakeVisible(lbl_dbMin.get());
		lbl_dbMin->setText("dbMin", juce::NotificationType::dontSendNotification);
		lbl_dbMin->setColour(juce::Label::outlineColourId, juce::Colours::lime);
		lbl_dbMin->setJustificationType(juce::Justification::centred);
		lbl_dbMin->attachToComponent(sld_dbMin.get(), false);





	}

	~UIComponent()
	{
		sld_dbMin, lbl_dbMin = nullptr;

	}

	void resize() {}

	std::unique_ptr<juce::Slider> sld_dbMin;
	std::unique_ptr<juce::Label> lbl_dbMin;


private:

	int labelHeight = 20;

	int elementWidth = 60;
	int elementHeight = 60;

	AudioState& audioState;
};
