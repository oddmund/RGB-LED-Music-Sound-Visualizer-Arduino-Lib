#### The mathematics of the code are explained here for those of you who are curious or want clarification. Some of this is mentioned in the code itself, but without visual aid.
&nbsp;

---
### How Loud is Loud?
This problem has a simple solution in this project, but it's still a problem nonetheless.

Adjusting the visuals to correspond with volume level is the most straightforward and accurate way to make the two feel "synchronized." But there is an issue if we want the visualizer to be versatile.

Not every sound environment will have the same range of loudness. Some will want to use it by their computer (like when I did most of my testing), some will want to have it near their surround-sound system, others may even lug it to a concert. These are all radically different scenarios.

The way to approach this is to adjust what the program thinks is the "loudest" sound. So initially you'd have the program keep track of what the loudest sound it's detected and proportionally adjust everything else accordingly. But there's one one issue with this model (that's easily fixed).

Consider the following graph:

**Volume Readings + Values of Loudest Noise Encountered<sub>(red)</sub>**
![vols+mvol](http://i.imgur.com/9I54tbY.png)

Notice how the song gets quieter near the end, and consequently no new maximum volumes are being detected. While this would appropriately adjust the visual-intensity for the remainder of this song, the following sounds may not fit into this range of loudness. Not to mention if you bump the visualizer or some other stray, excessively loud sound is detected then it would permanently diminish the intensity of the visuals until the program was reset.

A simple solution to this: just lower the max volume periodically. Not once every cycle of course, but occasionally so the visualizer restricts its range to an appropriate level every so often.

How I've implemented this in the program is to average the loudest volume level with the current volume level of a cycle where `gradient` is modulated. So if you were on `Rainbow()` mode, then `maxVol` will be averaged with whatever `volume` is at when `gradient` is greater than or equal to `1530` (`Rainbow()`'s loop threshold). This is an arbitrary enough check that occurs periodically enough, and it adjusted the `maxVol` appropriately enough (i.e. not setting it to 0, but also allowing it to slowly reduce over time if the sound environment has gotten quieter.)

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
### "Average"
This program uses what is called "sequenced averages." The difference between them and a regular average is that rather than averaging all available values at once, the averages between a current value and the last computed average are computed in a sequence (this sequence influences the final result). 

**Examples:**

True average of the list of integers from 0&ndash;10 inclusive:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![true avg](http://i.imgur.com/mTfEUwg.gif)

Sequenced average in numerical order:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![sequenced avg](http://i.imgur.com/sLXRbIf.gif)

_Interestingly&mdash;although useless&mdash;if the sequence is in numerical order it follows this formula:_
![seq numerical](http://i.imgur.com/NyLx6lo.gif)

&nbsp;

Rarely will you get an ordered sequence from the sound detector, and that's where the importance of this model becomes evident:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![seq arb](http://i.imgur.com/3sMsmzr.gif)

In this sequence, there is an trend toward lower inputs (i.e. volume readings, so in the program this would reflect a decreasing noise level). The sequenced average properly reflects this trend, whereas if we did a proper mathematical average it would still read as 5. The difference here is a little too nuanced to be of importance, so I'll demonstrate with some actual data:

<table>
<tr><td> All values were read out simultaneously during the same song. Some quiet was left at the end to demonstrate the difference between true and sequenced averages.</td></tr>
<tr><th> Volume Readings, Straight from Sound Detector </th></tr>
<tr><td><img src="http://i.imgur.com/PXKdeAa.png" alt="vols"></td></tr>
<tr><th> Volume Readings + Sequenced Average of Volumes<sub>(orange)</sub> </th></tr>
<tr><td><img src="http://i.imgur.com/njBWWgb.png" alt="vol+sa"></td></tr>
<tr><th> Volume Readings + True Average of Volumes<sub>(green)</sub> </th></tr>
<tr><td><img src="http://i.imgur.com/ltuQTL4.png" alt="vol+av"></td></tr>
<tr><th> Sequenced Average of Volumes<sub>(orange)</sub> + True Average of Volumes<sub>(green)</sub> </th></tr>
<tr><td><img src="http://i.imgur.com/68cjnTl.png" alt="av+sa"></td></tr>
</table>

It's pretty evident which method is more responsive to the sound level. The most notable failure of the true average is when the song ends and it's silent. If we relied on the true average to to tell us what was going on in the environment, we'd still think it was plenty noisy, whereas the sequenced average reflects the silence almost immediately&mdash;which is the point.

The reason the true average fails is because of the culmination of data. It is an average after all, so after a long time reading values even large fluctuations in volume have little impact. This problem would only exaggerate the longer you left the visualizer on, which is obviously not in our best interest since we want to be able to leave the visualizer unattended.

Case in point, the sequenced average is the objectively superior method to get an "average" idea of the sound level (unless you like vapid, unresponsive visualization.)

---



