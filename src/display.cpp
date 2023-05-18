#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display.hpp"


#define SDA_PIN             0x06
#define SCL_PIN             0x07

#define DISPLAY_WIDTH       128
#define DISPLAY_HEIGHT      64
#define DISPLAY_RST         -1
#define DISPLAY_TEXT_SIZE   1


OledDisplay::OledDisplay()
{
    // TODO
}


/**
 * Destructor
*/
OledDisplay::~OledDisplay()
{
    delete this->_wire;
}


/**
 * Function to setup the display
 * 
*/
void OledDisplay::initDisplay()
{
    this->_wire = new TwoWire(SDA_PIN, SCL_PIN);
    this->_display = Adafruit_SSD1306(DISPLAY_WIDTH, DISPLAY_HEIGHT, this->_wire, DISPLAY_RST);

    if(!this->_display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;) Serial.println("Display doesn't work"); // Don't proceed, loop forever
    } 

    delay(2000);
    this->_display.clearDisplay();

    this->_display.setTextSize(DISPLAY_TEXT_SIZE);
    this->_display.setTextColor(WHITE);
    this->_display.setCursor(0, 10);
}


/**
 * 
*/
void OledDisplay::writeStringToDisplay(String const &text)
{
    this->_display.println(text);
    this->_display.display();
}


/**
 * Method to write icons to display
 * 
*/
// void OledDisplay::writeIcontoDisplay()
// {

// }