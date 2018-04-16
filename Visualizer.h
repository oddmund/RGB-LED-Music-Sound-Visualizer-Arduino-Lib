/*
 * Visualizer.h - Library version of visualization code for Arduino, Sparkfun Sound Detector and Adafruit NeoPixels strand.
 *
 * by: Oddmund Møgedal 
 * date: 2018-04-15
 * license: Creative Commons Attribution-ShareAlike 4.0 (CC BY-SA 4.0)
 * Do whatever you'd like with this code, use it for any purpose.
 * Please attribute and keep this license.
 *
 * Library based on https://github.com/bartlettmic/SparkFun-RGB-LED-Music-Sound-Visualizer-Arduino-Code 
 *
 * SparkFun Addressable RGB LED Sound and Music Visualizer Tutorial Arduino Code
 * by: Michael Bartlett
 * SparkFun Electronics
 * date: 2/7/16
 * license: Creative Commons Attribution-ShareAlike 4.0 (CC BY-SA 4.0)
 * Do whatever you'd like with this code, use it for any purpose.
 * Please attribute and keep this license.
 *  
 *  NOTE: 
 *  Only one instance of Visualizer is currently possible because of the use of static global variables for state.
 *  
 *  UNTESTED:
 *  To use the Traffic() visual, define VISUALIZER_TRAFFIC_LED_TOTAL in this header file to the same as 
 *  your pixelStrandPixels to allocate extra memory.
 *  e.g 
 *  #define VISUALIZER_TRAFFIC_LED_TOTAL 32
 *  in this header file.
 *
 */

#ifndef Visualizer_h
#define Visualizer_h

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

//Libraries
#include <Adafruit_NeoPixel.h>  //Library to simplify interacting with the LED strand
#ifdef __AVR__
#include <avr/power.h>   //Includes the library for power reduction registers if your chip supports them. 
#endif                   //More info: http://www.nongnu.org/avr-libc/user-manual/group__avr__power.htlm

class Visualizer
{
  public:
    Visualizer(int pixelStrandPin, int pixelStrandPixels, int audioEnvelopePin);
    void start();
    void clearPixels();
    void oncePerLoop();
    void lightsOut();
    int getWaitMillis();
    void setWaitMillis(int waitMillis);
    float getLightLevel();
    void setLightLevel(float lightLevel);
    uint8_t getVisualMode();
    void setVisualMode(uint8_t visualMode);
    bool getShuffle();  
    void setShuffle(bool shuffleBool);  
};

#endif

