/*
  ==============================================================================

    KAPPanelBase.cpp
    Created: 9 Apr 2019 1:31:23pm
    Author:  j_samaca

  ==============================================================================
*/

#include "KAPPanelBase.h"
#include "KAPInterfaceDefines.h"

KAPAPanelBase::KAPAPanelBase(Samax_pluginAudioProcessor* inProcessor)
	:mProcessor(inProcessor)
  {

  }

KAPAPanelBase::~KAPAPanelBase()
{

}



void KAPAPanelBase::mouseEnter(const juce::MouseEvent & event)
{

	repaint();

}

void KAPAPanelBase::mouseExit(const juce::MouseEvent & event)
{
	repaint();

}

void KAPAPanelBase::paint(juce::Graphics & g)
{

	if (isMouseOver(true)) {
		
		const Colour hovercolour =
			Colour(juce::Colours::whitesmoke).withAlpha(0.03f);


		g.setColour(hovercolour); //paint when mouse is over!!!
		g.fillAll();

	} 
	 

}