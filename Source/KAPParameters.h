/*
  ==============================================================================

    KAPParameters.h
    Created: 10 Apr 2019 6:22:01pm
    Author:  samax

  ==============================================================================
*/

#pragma once

enum KAPParameter
{
	kParameter_InputGain =0,
	kParameter_DelayTime,
	kParameter_DelayFeedback,
	kParameter_DelayWetDry,
	kParameter_DelayType,//chorus or delay 
	kParameter_OutputGain,
	kParameter_ModulationRate,
	kParameter_ModulationDepth,
	kParameter_TotalNumParameters,
};

static juce::String KAPParameterID[kParameter_TotalNumParameters] =
{
	"InputGain",
	"Time",
	"Feedback",
	"WetDry",
	"Type",
	"OutputGain",
	"ModulationRate",
	"ModulationDepth",

};

static juce::String KAPParameterLabel[kParameter_TotalNumParameters] =
{
	"Input Gain",
	"Time",
	"Feedback",
	"Wet Dry",
	"Type",
	"Output Gain",
	"Modulation Rate",
	"Modulation Depth",

};

static float  KAPParameterDefaultValue[kParameter_TotalNumParameters] =
{
	0.1f,
	0.2f,
	0.3f,
	0.4f,
	1.0f,
	0.6f,
	0.7f,
	0.8f,

};