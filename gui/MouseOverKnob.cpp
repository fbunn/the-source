/*
  ==============================================================================

    MouseOverKnob.cpp
    Created: 4 Nov 2015 9:54:43pm
    Author:  Nhat

  ==============================================================================
*/

#include "MouseOverKnob.h"

//==============================================================================
// contructer & destructer
MouseOverKnob::MouseOverKnob(const String& name): Slider(name)
{
    addAndMakeVisible(knobLabel = new Label("new label", TRANS(name)));
    knobLabel->setFont(Font(15.00f, Font::plain));
    knobLabel->setJustificationType(Justification::centred);
    knobLabel->setEditable(false, false, false);
    knobLabel->setColour(TextEditor::textColourId, Colours::black);
    knobLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    knobLabel->attachToComponent(this, false);
    knobLabel->addComponentListener(this);

    initTextBox();
}

MouseOverKnob::~MouseOverKnob()
{
    knobLabel = nullptr;
}
//==============================================================================

void MouseOverKnob::initTextBox()
{
    if (knobLabel->isVisible()) {
        setTextBoxStyle(MouseOverKnob::NoTextBox, false, this->getTextBoxWidth(), this->getTextBoxHeight());
    } else {
        setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

void MouseOverKnob::setName  (const String& newName) {
    knobLabel->setText(newName, NotificationType::dontSendNotification);
}


/**
* If mouse enters slider then replace label with textbox.
*/
void MouseOverKnob::mouseEnter(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        knobLabel->setVisible(false);
        setTextBoxStyle(MouseOverKnob::TextBoxBelow, false, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

/**
* If mouse exits slider then replace textbox with label.
*/
void MouseOverKnob::mouseExit(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        knobLabel->setVisible(true);
        setTextBoxStyle(MouseOverKnob::NoTextBox, true, this->getTextBoxWidth(), this->getTextBoxHeight());
    }
}

/**
* If slider is double clicked then values can be edited manually.
*/
void MouseOverKnob::mouseDoubleClick(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        showTextBox();
    }
}

/**
* Only drag on slider, not on label.
*/
void MouseOverKnob::mouseDrag(const MouseEvent &e)
{
    if (e.eventComponent == this)
    {
        Slider::mouseDrag(e);
    }
}

/**
* Overwrite resize(), so that slider size is independent of textbox visibility.
*/
void MouseOverKnob::resized()
{
    if (!this->isMouseOver())
    {
        this->setSize(knobWidth, knobHeight - this->getTextBoxHeight());
    }
    else
    {
        this->setSize(knobWidth, knobHeight);
    }

    Slider::resized();
}

/*
* Needed to save bounds of slider.
*/
void MouseOverKnob::setBounds(int x, int y, int width, int height)
{
    knobWidth = width;
    knobHeight = height;
    Slider::setBounds(x, y, width, height);
}

/**
* Always set label below slider.
*/
void MouseOverKnob::componentMovedOrResized(Component &component, bool wasMoved, bool wasResized)
{
    knobLabel->setSize(labelWidth, this->getTextBoxHeight());
    knobLabel->setTopLeftPosition(this->getX() + (knobWidth- labelWidth)/2, this->getY() + this->getHeight());

    ComponentListener::componentMovedOrResized(component, wasMoved, wasResized);
}