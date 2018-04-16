# SparkFun RGB LED Music & Sound Visualizer
This repository holds the Arduino program featured in the SparkFun tutorial on creating a music visualizer with a strip of addressable RGB LEDs.

### Required Materials

The wish list for all these parts can be found [here.](http://sfe.io/w122818)

* [SparkFun RedBoard](https://www.sparkfun.com/products/12757) _(Any board with 3.3V and 5V pins will suffice.)_
* [LED RGB Strip - Addressable, Bare (1m)](https://www.sparkfun.com/products/12025)
* [SparkFun Sound Detector](https://www.sparkfun.com/products/12642)
* [Breadboard - Self-Adhesive (White)](https://www.sparkfun.com/products/12002)
* 3x [Momentary Pushbutton Switch - 12mm Square](https://www.sparkfun.com/products/9190)
* [Trimpot 10K with Knob](https://www.sparkfun.com/products/9806) _(or any analog potentiometer.)_
* [Resistor 330 Ohm 1/6th Watt PTH](https://www.sparkfun.com/products/8377) _(or any resistor between 300&ndash;500 &Omega;)_
* [Electrolytic Decoupling Capacitors - 1000uF/25V](https://www.sparkfun.com/products/8982)
* _(if needed)_ [Jumper Wires Standard 7" M/M Pack of 30](https://www.sparkfun.com/products/11026)


The resistor and capacitor are not required, but they will help prevent possible damage to the LEDs.

### Hookup
This project requires virtually no soldering! The few exceptions will probably be soldering some pins to the sound detector, and if you've cut a roll of addressable LEDs in the middle you'll have to solder some wires to the starting LED's pins. If you've never soldered before, I highly suggest taking a look at [this guide.](https://learn.sparkfun.com/tutorials/how-to-solder---through-hole-soldering)

Below is also a general chart for how the pin(s) on each component should be routed, and an accompanying diagram. But before you begin, here are some things to keep in mind:

* Be conscious of the orientation you think would allow the sound detector to take optimal readings for your intentions. Bending the pins to hold the sound detector perpendicular to the breadboard is a recommendable option.
* Electrolytic capacitors are polarity-sensitive, so how they are oriented is important. Make sure to place the side with a white stripe and a negative symbol into a negative current (ground) and the other into positive current.
* Resistors aren't polar, but it's good practice to be consistent with their orientation relative to the current.
* Trimpots are not polar either, however their middle pin is the analog output so don't power that directly.
* Pushbuttons are not polarity-sensitive and also do not need to be powered directly, just a ground connection will suffice.

The pins used in the diagram and the code are in parentheses. If you use a different pin, don't forget to change it in the code as well:

<table class="table table-striped table-hover table-bordered">
<tr><th>Sound Detector</th><th>Addressable LED strip</th><th>Trimpot</th><th>Pushbutton</th><th>1&nbsp;mF (1000&nbsp;&micro;F) Capacitor</th><th>300&ndash;500 &Omega; Resistor</th></tr>
<tr><td><center>Envelope&nbsp;&rarr;&nbsp;Analog&nbsp;(A0)</center></td><td><center>Digital/Analog&nbsp;(A5) &rarr;&nbsp;Resistor&nbsp;&rarr;&nbsp;DIN</center></td><td><center>5V&nbsp;&rarr;&nbsp;left or right pin</center></td><td><center>GND&nbsp;&rarr;&nbsp;Either side<td></center><center>Between ground and 5V</td></center><td><center>Between Digital/Analog (A5) and DIN on LED strip</center></td></tr>
<tr><td><center>3.3V&nbsp;&rarr;&nbsp;VCC</td></center><td><center>5V&nbsp;&rarr;&nbsp;5V</td></center><td><center>Middle&nbsp;pin&nbsp;&rarr;&nbsp;Analog&nbsp;(A1)</center></td><td><center>Other&nbsp;side&nbsp;&rarr;&nbsp;Digital (4, 5, 6)</center><td></td><td></td></tr>
<tr><td><center>GND&nbsp;&rarr;&nbsp;GND</center></td><td><center>GND&nbsp;&rarr;&nbsp;GND</td></center><td><center>Remaining left or right pin&nbsp;&rarr;&nbsp;GND</center></td><td></td><td></td><td></td></tr>
</table>


**Sound Detector Notes:** The microphone used is not a sophisticated, logarithmic sound receiver like your ear; it is only measuring compressional waves in the air. Consequently, the microphone is more likely to detect and/or prioritize lower-frequency sounds since they require more energy to propagate, and therefore oscillate the air more intensely. Also, a resistor can be placed in the "GAIN" slots to modify the gain. Standard gain should be sufficient for our purposes, but for more info check [here.](https://learn.sparkfun.com/tutorials/sound-detector-hookup-guide#configuration)

<center>**Diagram of a possible circuit:**
![diagram](http://i.imgur.com/Po12eSI.png)</center> 

### Compiling

Things to remember before you compile:

* If you didn't use a potentiometer, don't forget to remove all references to the variable `knob` in the code (ctrl+F will come in handy for that). Otherwise, the program will think you still have a potentiometer that is set to a very low value (i.e. everything will be very dim).
* If you didn't use buttons, change the initialization `bool shuffle = false;` to `bool shuffle = true;`. The code should compile and run properly, but for good practice you should remove all blocks the code says to delete since they reference the `BUTTON` constants.
