/*
  ==============================================================================

	AudioState.h
	Created: 19 Jun 2026 10:21:45am
	Author:  SchoeDam

  ==============================================================================
*/

#pragma once


#include <atomic>

struct AudioState
{
	std::atomic<double> currentSampleRate{};


	// scope comp
	std::atomic<float> fftSmooth{};

	std::atomic<float> displaySmooth{};

	std::atomic<int> dbMin{ -100 };


	// spec comp




};