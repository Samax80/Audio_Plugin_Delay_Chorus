/*
  ==============================================================================

    KAPLookAndFeel.h
    Created: 25 Apr 2019 10:37:31am
    Author:  j_samaca

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "KAPInterfaceDefines.h"


class KAPLookAndFeel
	:public juce::LookAndFeel_V4
{
public:
	KAPLookAndFeel()
	{

		//store image assets
		mSliderImage = juce::ImageCache::getFromMemory(BinaryData::kadenze_knob_png, BinaryData::kadenze_knob_pngSize);//



		using ComboBox = juce::ComboBox;
		//comboBox Colours
		setColour(ComboBox::backgroundColourId,KAPColour_3);
		setColour(ComboBox::outlineColourId,KAPColour_2);
		setColour(ComboBox::arrowColourId,KAPColour_1);
		setColour(ComboBox::textColourId,KAPColour_1);

		using TextButton = juce::TextButton;
		//button text colours 
		setColour(TextButton::buttonColourId,KAPColour_1);
		setColour(TextButton::textColourOnId, KAPColour_1);
		setColour(TextButton::textColourOffId, KAPColour_1);
	}
	virtual ~KAPLookAndFeel()
	{

		
	}

	/**buttons */
	Font getTextButtonFont(juce::TextButton&, int buttonHeight) override

	{
		return font_1;
	}

	void drawButtonBackground(juce::Graphics& g,juce:: Button& button, const Colour& backgroundColour,
		                      bool isMouseOverButton, bool isButtonDown) override
	{
	 
		Colour fillColour;

		if (isButtonDown) {

			fillColour = KAPColour_6;
		}
		else if (isMouseOverButton) {
			fillColour = KAPColour_3;
		}
		else  {
			fillColour = KAPColour_5;
		}

		const float cornerSize = 6.0f;
		const juce::Rectangle<float> bounds =button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

		g.setColour(fillColour);

		g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
		
	}

	/* *comboBoxes */
	Font getLabelFont(juce::Label& label) override
	{
	
		return font_1;
	}
	void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
						   bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
						   const juce::String& text, const juce::String& shortcutKeyText,
						   const juce::Drawable* icon, const Colour* textColour) override
	{
		juce::Rectangle<int> r(area);

		Colour fillColour = isHighlighted ? KAPColour_5: KAPColour_4;

		g.setColour(fillColour);
		g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight()-1);
		
		Colour myTextColour = isTicked ? KAPColour_7 : KAPColour_1;
		g.setColour(myTextColour);
		g.setFont(font_1);

		r.setLeft(10);
		r.setY(1);
		g.drawFittedText(text, r, juce::Justification::left, 1);
		
	}

	void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
		int buttonX, int buttonY, int buttonW, int buttonH,
		juce::ComboBox& box) override
	{
		const float cornerSize = 3.0f;
		const juce::Rectangle<int>boxbounds(0, 0, width, height);

		g.setColour(KAPColour_3);
		g.fillRoundedRectangle(boxbounds.toFloat(), cornerSize);

		juce::Rectangle<int>arrow(width - 30, 0, 20, height);

		juce::Path path;

		path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
		path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0);
		path.lineTo(arrow.toFloat().getRight()-3.0f, arrow.toFloat().getCentreY() - 2.0);

		Colour arrowColour = box.findColour(juce::ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
		g.setColour(arrowColour);
		g.strokePath(path, juce::PathStrokeType(2.0f));


	}

	/**Sliders */


	void drawRotarySlider(juce::Graphics& g , int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle,
		float rotaryEndAngle, juce::Slider& slider) override
	{

		const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth();
		const  int frameIndex = (int)std::ceil(sliderPosProportional*(numFrames - 1));
		
		const float radius = juce::jmin(width*0.5, height*0.5);
		const float centreX = x + width * 0.5f;//position where the slider is 
		const float centreY = y + width * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;

		g.drawImage(mSliderImage,
					rx,
					ry,
					2 * radius,
					2 * radius,
					0,
					frameIndex*mSliderImage.getWidth(),
					mSliderImage.getWidth(), mSliderImage.getWidth());



	}

	

private:

	juce::Image mSliderImage;
};