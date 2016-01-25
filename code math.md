### The mathematics of the code are explained here for those of you who are curious or want clarification. Some of this is mentioned in the code itself, but without visual aid.

---
### Loudness and Brightness

Having brightness correspond to volume is an obvious enough feature, however its implementation was a bit of a design choice. Initially, I started with straight proportionality:
 ![linear proportionality](http://i.imgur.com/bAM95uO.gif) &nbsp;&nbsp;&nbsp;&nbsp;in the code as: `(volume / maxVol) * 255` 

I found this method to be a little underwhelming, so I tried a more exponential approach to make lower ratios darker and higher ratios brighter:

 ![exponential](http://imgur.com/sqhPcq8.gif)&nbsp;&nbsp;&nbsp;&nbsp;in the code as: `pow(256, volume / maxVol) - 1` 

This seemed a little too extreme, so the code currently uses a squared proportion:

 ![proportion^2](http://imgur.com/3amI46q.gif)&nbsp;&nbsp;&nbsp;&nbsp;in the code as: `pow(volume / maxVol, 2.0) * 255` 

This was used because it is a balance between the linear and exponential approaches, as can be seen graphically:

 ![bright graph](http://imgur.com/DPynqok.gif) 

I encourage you to to try all methods to see which one you find to be the most pleasing. One other alternative is to raise the volume ratio to the power of 1.5 to get a slightly more linear output.

---
### "Averaging"
This program uses what is called "sequenced averages." The difference between them and a regular average is that rather than averaging all available values at once, the averages between a current value and the last computed average are computed in a sequence (this sequence influences the final result). 

**Examples:**

True average of the list of integers from 0&ndash;10 inclusive:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![true avg](http://i.imgur.com/mTfEUwg.gif)

Sequenced average in numerical order:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![sequenced avg](http://i.imgur.com/sLXRbIf.gif)

_Interestingly&mdash;although useless&mdash;if the sequence is in numerical order it follows this formula:_
![seq numerical](http://i.imgur.com/NyLx6lo.gif)

&nbsp;

Rarely will you get an ordered sequence from the sound detector, and that's where the importance of this model becomes evident:![seq arb](http://i.imgur.com/3sMsmzr.gif)

In this sequence, there is an trend toward lower inputs (i.e. volume readings, so in the program this would reflect a decreasing noise level). The sequenced average properly reflects this trend, whereas if we did a proper mathematical average it would still read as 5. The difference here is a little too nuanced to be of importance, so I'll demonstrate with some actual data:

<table>
<tr><td> All values were read out simultaneously during the same song. Some quiet was left at the end to demonstrate the difference between true and sequenced averages.</td></tr>
<tr><th> Volume Readings, Straight from Sound Detector </th></tr>
<tr><td><img src="http://i.imgur.com/SOczWME.png" alt="vols"></td></tr>
<tr><th> Volume Readings + Sequenced Average of Volumes<sub>(orange)</sub> </th></tr>
<tr><td><img src="http://i.imgur.com/W7Ae3GM.png" alt="vol+sa"></td></tr>
<tr><th> Volume Readings + True Average of Volumes<sub>(green)</sub> </th></tr>
<tr><td><img src="http://i.imgur.com/6ZqfvHw.png" alt="vol+av"></td></tr>
<tr><th> Sequenced Average of Volumes<sub>(orange)</sub> + True Average of Volumes<sub>(green)</sub> </th></tr>
<tr><td><img src="http://i.imgur.com/tlKwwFt.png" alt="av+sa"></td></tr>
</table>

It's pretty evident which method is more responsive to the sound level. The most notable failure of the true average is when the song ends and it's silent. If we relied on the true average to to tell us what was going on in the environment, we'd still think it was plenty noisy, whereas the sequenced average reflects the silence almost immediately&mdash;which is the point.

The reason the true average fails is because of the culmination of data. It is an average after all, so after a long time reading values even large fluctuations in volume have little impact. This problem would only exaggerate the longer you left the visualizer on, which is obviously not in our best interest since we want to be able to leave the visualizer unattended.

Case in point, the sequenced average is the objectively superior method to get an "average" idea of the sound level (unless you like vapid, unresponsive visualization.)

---



