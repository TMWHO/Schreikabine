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
    std::atomic<int> dbMin{ -100 };


    //std::atomic<double> freq{ 500.0f };

};