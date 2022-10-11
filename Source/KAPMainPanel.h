/*
  ==============================================================================

    KAPMainPanel.h
    Created: 9 Apr 2019 1:32:07pm
    Author:  j_samaca

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"
#include "KAPGainPanel.h"
#include"KAPCenterPanel.h"
#include "KAPTopPanel.h"


class   KAPMainPanel
	:public KAPAPanelBase

{


public:
	KAPMainPanel(Samax_pluginAudioProcessor* inProcessor);

	~KAPMainPanel();



private:
	
	std::unique_ptr < KAPTopPanel> mTopPanel;
	std::unique_ptr< KAPGainPanel> mInputGainPanel;
	std::unique_ptr< KAPGainPanel> mOutputGainPanel;
	std::unique_ptr< KAPCenterPanel> mCenterPanel;

};