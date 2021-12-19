/*
  ==============================================================================

    KAPCenterPanelMenuBar.cpp
    Created: 9 Apr 2019 1:32:55pm
    Author:  j_samaca

  ==============================================================================
*/

#include "KAPCenterPanelMenuBar.h"
#include "KAPParameters.h"


KAPCenterPanelMenuBar::KAPCenterPanelMenuBar(Samax_pluginAudioProcessor* inProcessor)
	:KAPAPanelBase(inProcessor)

  {

	setSize(CENTER_PANEL_MENU_BAR_WIDTH,
		CENTER_PANEL_MENU_BAR_HEIGHT);
	const int width = 85;

	mFxTypeComboBox =
	new KAPParameterComboBox(mProcessor->parameters, 
		KAPParameterID[kParameter_DelayType]);

	auto value = (int)mProcessor->getParameter(kParameter_DelayType);//test

	mFxTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight());
	mFxTypeComboBox->addItem("DELAY", 1);
	mFxTypeComboBox->addItem("CHORUS",2);
	mFxTypeComboBox->setSelectedItemIndex((int)mProcessor->getParameter(kParameter_DelayType),
																   juce::dontSendNotification);

	addAndMakeVisible(mFxTypeComboBox);
  }

KAPCenterPanelMenuBar::~KAPCenterPanelMenuBar()
{


}

void KAPCenterPanelMenuBar::addFxTypeComboBoxListener(juce::ComboBox::Listener *inListener)
{
	mFxTypeComboBox->addListener(inListener);
}

void KAPCenterPanelMenuBar::RemoveFxTypeComboBoxListener(juce::ComboBox::Listener *inListener)
{
	mFxTypeComboBox->removeListener(inListener);
}
