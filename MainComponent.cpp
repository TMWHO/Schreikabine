#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	setAudioChannels(2, 0);  // we want a couple of input channels but no outputs
	setSize(1280, 1024);

	addAndMakeVisible(&ScopeComponent);
	addAndMakeVisible(&SpecComponent);
	addAndMakeVisible(&uiComponent);
}

MainComponent::~MainComponent()
{
	shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{

}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	if (bufferToFill.buffer->getNumChannels() > 0)
	{
		auto* channelData = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);

		for (auto i = 0; i < bufferToFill.numSamples; ++i)
		{
			ScopeComponent.pushNextSampleIntoFifo(channelData[i]);
			SpecComponent.pushNextSampleIntoFifo(channelData[i]);
		}

	}

}

void MainComponent::releaseResources()
{

}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);


}

void MainComponent::resized()
{

	juce::Rectangle<int> boundsScope(0, 0, getWidth() / 2, getHeight() / 2);
	juce::Rectangle<int> boundsSpec(0, getHeight() / 2, getWidth() / 2, getHeight() / 2);
	juce::Rectangle<int> boundsUi(getWidth() / 2, 0, getWidth() / 2, getHeight() / 2);



	ScopeComponent.setBounds(boundsScope);
	SpecComponent.setBounds(boundsSpec);
	uiComponent.setBounds(boundsUi);
}
