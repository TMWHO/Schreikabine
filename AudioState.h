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
    std::atomic<float> level{ 0.1f };
    std::atomic<double> freq{ 500.0f };

};