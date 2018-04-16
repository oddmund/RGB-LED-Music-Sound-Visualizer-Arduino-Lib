# RGB LED Music & Sound Visualizer Library

This repository holds an Arduino Library to make it easier to include most of the visualizer from the
[SparkFun Addressable RGB LED Sound and Music Visualizer Tutorial Arduino Code](https://github.com/bartlettmic/SparkFun-RGB-LED-Music-Sound-Visualizer-Arduino-Code)
by Michael Bartlett, without adding a lot of code in the sketch itself.

There is an example sketch called simple-viz to show how it works.

## PLEASE NOTE 

* Only one instance of Visualizer is currently possible because of the use of static global variables for state.
* The Traffic() visual has not been tested. To try to use it, you will need to modify the library header file  
  and `#define VISUALIZER_TRAFFIC_LED_TOTAL` there.
 
