
#include <Visualizer.h>

#define LED_PIN 4
#define STRAND_LEDS 60
#define AUDIO_PIN A0

Visualizer visualizer = Visualizer(LED_PIN, STRAND_LEDS, AUDIO_PIN);

void setup() {
 
  Serial.begin(9600); //Sets data rate for serial data transmission.

  visualizer.setWaitMillis(30);  
  visualizer.setLightLevel(0.9);
  visualizer.setShuffle(false);
  visualizer.setVisualMode(0);
  visualizer.start();
}

void loop() {
  
  visualizer.oncePerLoop();
}