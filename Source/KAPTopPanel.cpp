/*
  ==============================================================================

    KAPTopPanel.cpp
    Created: 9 Apr 2019 1:36:02pm
    Author:  j_samaca

  ==============================================================================
*/

#include "KAPTopPanel.h"

KAPTopPanel::KAPTopPanel(Samax_pluginAudioProcessor* inProcessor)
	:KAPAPanelBase(inProcessor)
	
  {
	setSize(TOP_PANEL_WIDTH,
		TOP_PANEL_HEIGHT);

	int button_x = 15;
	int button_y = 10;
	int button_w = 55;
	int button_h = 25;

	mNewPreset = new juce::TextButton();
	mNewPreset->setButtonText("NEW");
	mNewPreset->setBounds(button_x, button_y, button_w,button_h );
	mNewPreset->addListener(this);
	addAndMakeVisible(mNewPreset);
	button_x = button_x + button_w;

	mSavePreset = new juce::TextButton();
	mSavePreset->setButtonText("SAVE");
	mSavePreset->setBounds(button_x, button_y, button_w, button_h);
	mSavePreset->addListener(this);
	addAndMakeVisible(mSavePreset);
	button_x = button_x + button_w;

	mSaveAspreset = new juce::TextButton();
	mSaveAspreset->setButtonText("SAVE AS");
	mSaveAspreset->setBounds(button_x, button_y, button_w, button_h);
	mSaveAspreset->addListener(this);
	addAndMakeVisible(mSaveAspreset);
	button_x = button_x + button_w;

	const int comboBox_w = 200;
	const int comboBox_X = TOP_PANEL_WIDTH * 0.5 - comboBox_w * 0.5;

	mPresetDisplay = new juce::ComboBox();
	mPresetDisplay->setBounds(comboBox_X, button_y, comboBox_w, button_h);
	mPresetDisplay->addListener(this);
	addAndMakeVisible(mPresetDisplay);

	updatePresetComboBox();


  }

KAPTopPanel::~KAPTopPanel()
{

}

void KAPTopPanel::paint(juce::Graphics & g)
{
	KAPAPanelBase::paint(g);

	g.setColour(KAPColour_1);
	g.setFont(font_2);

	const int label_w = 220;


	g.drawFittedText("Samax Audio Plugin", TOP_PANEL_WIDTH- label_w, 0, label_w, getWidth()-10, getHeight(), juce::Justification::centredRight, 1);

}

void KAPTopPanel::buttonClicked(juce::Button * b)
{
	KAPPresetManager*presetManager = mProcessor->getPresetManager();

	if (b == mNewPreset) {

		presetManager->createNewPreset();

		updatePresetComboBox();
	}

	else if (b == mSavePreset){

	   presetManager->SavePreset();
		
	}
	else if (b == mSaveAspreset){

		displaySaveAsPopup();

	}

}

void KAPTopPanel::comboBoxChanged(juce::ComboBox * comboBoxThatHasChanged)
{
	if (comboBoxThatHasChanged == mPresetDisplay) {
		
		KAPPresetManager* presetManager = mProcessor->getPresetManager();

		const int index = mPresetDisplay->getSelectedItemIndex();

		presetManager->loadPreset(index);
	}

}



void KAPTopPanel::displaySaveAsPopup()
{
	KAPPresetManager* presetManager = mProcessor->getPresetManager();

	juce::String currentPresetName = presetManager->getCurrentPresetName();

	juce::AlertWindow window("Save As", "Please enter a name for your preset", juce::AlertWindow::NoIcon);

	window.centreAroundComponent(this, getWidth(), getHeight());
	window.addTextEditor("presetName", currentPresetName, "preset name:");
	window.addButton("Confirm", 1);
	window.addButton("Cancel", 0);

	if (window.runModalLoop()) {
		juce::String presetName = window.getTextEditor("presetName")->getText();
		presetManager->saveAsPreset(presetName);

		updatePresetComboBox();
	}

}

void KAPTopPanel::updatePresetComboBox()
{
	KAPPresetManager* presetManager = mProcessor->getPresetManager();
	juce::String presetName = presetManager->getCurrentPresetName();

	mPresetDisplay->clear(juce::dontSendNotification);


	

	const int numPresets = presetManager->getNumberOfPresets();
		

	for (int i = 0; i < numPresets; i++) {

		mPresetDisplay->addItem(presetManager->getPresetName(i), (i + 1));
	}
	mPresetDisplay->setText(presetManager->getCurrentPresetName());

}
