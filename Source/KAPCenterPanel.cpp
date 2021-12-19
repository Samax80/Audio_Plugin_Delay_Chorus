/*
  ==============================================================================

    KAPCenterPanel.cpp
    Created: 9 Apr 2019 1:32:34pm
    Author:  j_samaca

  ==============================================================================
*/

#include "KAPCenterPanel.h"


KAPCenterPanel::KAPCenterPanel(Samax_pluginAudioProcessor* inProcessor)
	:KAPAPanelBase(inProcessor)
{
	setSize(CENTER_PANEL_WIDTH, CENTER_PANEL_HEIGHT);



	mMenuBar = new  KAPCenterPanelMenuBar(inProcessor);
	mMenuBar->setTopLeftPosition(0, 0);
	addAndMakeVisible(mMenuBar);

	mFxPanel = new  kKAPFxPAnel(inProcessor);
	mFxPanel->setTopLeftPosition(0,CENTER_PANEL_MENU_BAR_HEIGHT );
	addAndMakeVisible(mFxPanel);

	mMenuBar->addFxTypeComboBoxListener(mFxPanel);


}

KAPCenterPanel::~KAPCenterPanel()
{
	mMenuBar->RemoveFxTypeComboBoxListener(mFxPanel);
}
