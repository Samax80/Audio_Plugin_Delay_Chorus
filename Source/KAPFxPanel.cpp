/*
  ==============================================================================

    KAPFxPanel.cpp
    Created: 9 Apr 2019 1:34:43pm
    Author:  j_samaca

  ==============================================================================
*/

#include "KAPFxPanel.h"
#include "KAPParameters.h"
#include "KAPHelperFunctions.h"
#include "PluginProcessor.h"



kKAPFxPAnel::kKAPFxPAnel(Samax_pluginAudioProcessor* inProcessor)
	:KAPAPanelBase(inProcessor)
	//,
	//mStyle(kKAPFxPAnelStyle_Delay)
	
{
	setSize(FX_PANEL_WIDTH,
			FX_PANEL_HEIGHT);
	
	const int currentStyle = (int)mProcessor->getParameter(kParameter_DelayType);
	setFxPanelStyle((KAPFxPanelStyle)currentStyle);
	//setFxPanelStyle(kKAPFxPAnelStyle_Delay);
	//setFxPanelStyle(kKAPFxPAnelStyle_Chorus);

	
}

kKAPFxPAnel::~kKAPFxPAnel()
{
}


void kKAPFxPAnel::paint(juce::Graphics & g)
{
	KAPAPanelBase::paint(g);
	
	juce::String label;


	switch (mStyle)
	{
	case(kKAPFxPAnelStyle_Delay):
	{
	 // g.drawFittedText("DELAY ff", 0, 0, getWidth(), getHeight() *0.45, juce::Justification::centred, 1);To be removed

	  label = "DELAY";

	} break;

	case(kKAPFxPAnelStyle_Chorus):
	{
		label ="CHORUS";
	  }break;

	case(kKAPFxPAnelStyle_TotalNumStyles):
    	{  
		jassertfalse;
	    }
	}

	

	g.setColour(KAPColour_5);
	g.setFont(font_3);

	g.drawText(label, 0, 0, getWidth(), 80, juce::Justification::centred);




	//paint Labels
	for (int i = 0; i < mSliders.size(); i++){
		paintComponentLabel(g, mSliders[i]);
	}
}
 




void kKAPFxPAnel::setFxPanelStyle(KAPFxPanelStyle inStyle)
{
	mStyle = inStyle;
	
	mSliders.clear();
	const int slider_size = 56;
	int x = 130;
	int y = getHeight()*0.5 - (slider_size*0.5);

	switch (mStyle)
	{
	case(kKAPFxPAnelStyle_Delay):
	{
		
		KAPParameterSlider* time =
		new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayTime], KAPParameterLabel[kParameter_DelayTime]);
		time->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(time);
		mSliders.add(time);
		x = x + (slider_size * 2);

		KAPParameterSlider* feedback =
		new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayFeedback], KAPParameterLabel[kParameter_DelayFeedback]);
		feedback->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(feedback);
		mSliders.add(feedback);
		x = x + (slider_size * 2);

		KAPParameterSlider* wetdry =
		new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayWetDry], KAPParameterLabel[kParameter_DelayWetDry]);
		wetdry->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(wetdry);
		mSliders.add(wetdry);
		x = x + (slider_size * 2);


	} break;

	case(kKAPFxPAnelStyle_Chorus):
	{
		KAPParameterSlider* rate =
		new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_ModulationRate], KAPParameterLabel[kParameter_ModulationRate]);
		rate->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(rate);
		mSliders.add(rate);
		x = x + (slider_size * 2);

		KAPParameterSlider* depth =
		new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_ModulationDepth], KAPParameterLabel[kParameter_ModulationDepth]);
		depth->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(depth);
		mSliders.add(depth);
		x = x + (slider_size * 2);

		KAPParameterSlider* wetdry =
		new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayWetDry], KAPParameterLabel[kParameter_DelayWetDry]);
		wetdry->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(wetdry);
		mSliders.add(wetdry);
		x = x + (slider_size * 2);


	}break;

	default:

	case (kKAPFxPAnelStyle_TotalNumStyles):

	{
		//This Should'nt happen!		
		jassertfalse;

	}break;

	}
	repaint();
}

void kKAPFxPAnel::comboBoxChanged(juce::ComboBox * comboBOxThatHasChanged)
{
	KAPFxPanelStyle style=(KAPFxPanelStyle) comboBOxThatHasChanged->getSelectedItemIndex();
	setFxPanelStyle(style);
}


