/*
  ==============================================================================

    KAPCenterPanel.h
    Created: 9 Apr 2019 1:32:34pm
    Author:  j_samaca

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

#include "KAPCenterPanelMenuBar.h"
#include "KAPFxPanel.h"


class KAPCenterPanel
	:public KAPAPanelBase

{
public:
	KAPCenterPanel(Samax_pluginAudioProcessor* inprocessor);

	~KAPCenterPanel();


private:

	juce::ScopedPointer<KAPCenterPanelMenuBar> mMenuBar;

	juce::ScopedPointer<kKAPFxPAnel> mFxPanel;

};


