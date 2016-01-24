The mathematics of the code are explained here for those of you who are curious or want clarification. Some of this is mentioned in the code itself, but without visual aid.
---

Having brightness correspond to loudness is an obvious enough feature, however its implementation was a bit of a design choice. Initially, I started with straight proportionality:
<center>![linear proportionality](http://i.imgur.com/bAM95uO.gif) &nbsp;&nbsp;&nbsp;&nbsp;in the code as: `(volume / maxVol) * 255`</center>

I found this method to be a little underwhelming, so I tried a more exponential approach to make lower ratios darker and higher ratios brighter:

<center>![exponential](http://imgur.com/sqhPcq8.gif)&nbsp;&nbsp;&nbsp;&nbsp;in the code as: `pow(256, volume / maxVol) - 1`</center>

This seemed a little too extreme, so the code currently uses a squared proportion:

<center>![proportion^2](http://imgur.com/3amI46q.gif)&nbsp;&nbsp;&nbsp;&nbsp;in the code as: `pow(volume / maxVol, 2.0) * 255`</center>

This was used because it is a balance between the linear and exponential approaches, as can be seen graphically:

<center>![bright graph](http://imgur.com/DPynqok.gif)</center>

I encourage you to to try all methods to see which one you find to be the most pleasing. One other alternative is to raise the volume ratio to the power of 1.5 to get a slightly more linear output.
