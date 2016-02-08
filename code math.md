### The mathematics of the code are explained here for those of you who are curious or want clarification. Some of this is mentioned in the code itself, but without visual aid.

---
### How Loud is Loud?
This problem has a simple solution in this project, but it's still a problem nonetheless.

Adjusting the visuals to correspond with volume level is the most straightforward and accurate way to make the two feel "synchronized." But there is an issue if we want the visualizer to be versatile.

Not every sound environment will have the same range of loudness. Some will want to use it by their computer (like when I did most of my testing), others still will want to have it near their surround-sound system, others may even lug it to a concert. These are all radically different scenarios.

The way to approach this is to adjust what the program thinks is the "loudest" sound. So initially you'd have the program keep track of what the loudest sound it's detected and proportionally adjust everything else accordingly. But there's one one issue with this model (that's easily fixed).

Consider the following graph:

**Volume Readings + Values of Loudest Noise Encountered<sub>(red)</sub>**
![vols+mvol](http://i.imgur.com/9I54tbY.png)

Notice how the song gets quieter near the end, and consequently no new maximum volumes are being detected. While this would appropriately adjust the visual-intensity for the remainder of this song, the following sounds may not fit into this range of loudness. Not to mention if you bump the visualizer or some other stray, excessively loud sound is detected then it would permanently diminish the intensity of the visuals until the program was reset.
 
A simple solution to this: just lower the max volume periodically. Not once every cycle of course, but occasionally so the visualizer restricts its range to an appropriate level every so often.

How I've implemented this in the program is to average the loudest volume level with the current volume level of a cycle where `gradient` is modulated. So if you were on `Rainbow()` mode, then `maxVol` will be averaged with whatever `volume` is at when `gradient` is greater than or equal to `1530` (`Rainbow()`'s loop threshold). This is an decently arbitrary check that occurs periodically, and it adjusts the `maxVol` appropriately enough (i.e. not just setting it to 0, but also allowing it to slowly reduce over time if the sound environment has gotten quieter.)

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

### Fading
Fading is done through exponential decay of each color in each pixel. The `fade()` function simply multiplies each R, G, and B value of each pixel by a number less than 1 (i.e. dividing it by a number greater than 1). Since it's multiplying each pass, the lights decrease by an amount that is relative to the current light value. Here's a graphical example where we take a light value that starts at max brightness (255) and we decay it by 0.95 each pass (i.e. 255&times;0.95^x where x is the number of times `fade()` is called with the same decimal):

<center>![exp decay](http://i.imgur.com/8OSB4cz.png)</center>  

Technically this function never reaches zero, but the strip has its cutoff (values < 0.5 are 0), and this is where the fade function simply iterates to the next pixel if one is completely off.

We can gauge how long it will take to snuff out a light completely by simply solving for x when the function equals 0.49, and knowing that each pass of loop is at least 30 ms (because of the delay call) we can get a lower-end estimate for how long it will take to completely fade out a pixel. Here's this written out for `fade()` called with `0.95` and `0.99` for an R, G, or B value of 255:

<center>![decay 0.95](http://i.imgur.com/Lzodfqd.png)</center>

So you can see that a fade coefficient of 0.95 would take about 3.5 seconds to completely fade out a full light, assuming extra operations done during the loop are of negligible time.

Doing the same math with 0.99 yields:

<center>![fade 0.99](http://i.imgur.com/WPW5wtx.png)</center>

Even a difference of a few _hundredths_ has exaggerated the magnitude of the effect, more than squaring it! A linear approach can also be taken by merely subtracting the same number from each light each pass (i.e. 255-Y&times;x where Y is the number you're subtracting each pass).

A graphical comparison that would fade out at the same time:

<center>![expo & linear](http://i.imgur.com/edPA7oN.png)</center>

Currently `fade()` uses the exponential function since it more accurately models how fire burns out, and I think that caters to a more natural-looking aesthetic, but simply changing `split(col, j) * damper;` to `split(col, j) - damper;` would make it linear if this is something you want to try. 

Different fading is necessary for different modes (e.g. `Traffic()` needs a relatively low fade so the strip doesn't get washed out and you can still see the individual dots, but `Snake()` needs a long fade to make the trail more distinct). This was a design choice for each visual as well, so play around with the numbers to see what you find satisfying. 

---
### "Bumps"
The Sound Detector is certainly an impressive instrument, but unfortunately we still have to "coax" the information we may want from the stream of data. Since this project lacks a spectrum analyzer (one of which you can find and read about [here](https://www.sparkfun.com/products/10468)) the best we can do is use volume intensity and oscillations in volume which may or may not correspond to a beat. This isn't necessarily a disadvantage, as we can still get some very satisfying responsiveness in the visuals.

Of all the sections, this one probably required the most refinement and testing, but I feel I've developed a decently responsive method that isn't _too_ responsive (i.e. reacting to every little twitch in the audio, but the big bursts). Since it's been developed to be a versatile for various ranges of music it isn't perfect, but it still manages to impress me sometimes with its beat detection. This section will be updated as more accurately responsive methods are developed and tested.

The basics of "bumps" is that they are a _relatively_ large, _positive_ change in volume (i.e. current volume - last volume > 0, where at least the current volume is not noise). The easiest way to think about this is a bass drum beat, where you have quick and hard changes in volume very regularly. While bumps were initially intended to follow the beat, by nature of the data they tend to follow other patterns of a song as well, which isn't necessarily a bad thing. Because of this drift toward other patterns in the sound, it becomes a little harder to talk about bumps, but there namesake is decent enough: just "bumps" in volume regardless of what the actual sound is.

As mentioned, bumps were intended to model the bass drum or the "beat" of a given song, so that intent is still the focus; any deviating responsiveness that occurs is just an added bonus. As such, the current implementation uses a similar sequenced average discussed in the **"Averaging"** section, but instead for an average positive change in volume instead of just volume. Consider the following table:

<center>![bumps](http://i.imgur.com/yZ3yErL.png)</center>

A positive change in volume was read out every time it occurred (so this does not show decreases in volume). So, how do we decide which of these bumps are worthy enough to represent the beat? Well, the answer is  convoluted. 

There are two main ways to approach this problem I've found, and that's whether the threshold for a "bump" is a constant or dynamic. Both methods have their pros and cons, but I've opted for the dynamic method which utilizes a sequenced average of bumps. How the average of bumps is coded as: `if (volume - last > 0) avgBump = (avgBump + (volume - last)) / 2.0;`

Essentially, every positive change in volume is averaged in. Here is the value of the average bump level (in red) of the bumps above: 
<center>![bumps+abump](http://i.imgur.com/HmE58O7.png)</center>

Hopefully you'll agree that this model for determining what is the "average" bump is pretty good at staying in the middle of the extremes. Now all that's left is what our criteria is for a proper "bump". Currently in the code is this segment: `bump = (volume - last > avgBump * .9);`

The result of whether the current bump is larger than the average bump is stored in the Boolean `bump`. The .9 is there to slightly lower the average bump so the programs declaration of what a bump is or isn't is more generous. This is the optimal result I found through testing, but feel free to play around with it. Using this logic, what bumps were classified as `true` (i.e. larger than the roughly average bump) are represented by the dark blue dots:

![true bump](http://i.imgur.com/yfpMWRV.png)

This method generates appropriate, but conservative amounts of, bumps. And they seem to occur sort of regularly so they tend to follow the beat (especially since lower frequency noises associated with bass are more likely to register as louder volumes) 

Here are where "bumps" are triggered if our condition is simply a volume difference of at least 10 (`volume - last > 10`) represented by violet dots:

![threshold bump](http://i.imgur.com/EAd4gi1.png)

The difference may be hard to see at first glance, but there is a much less regular appearance of bumps. Here's an overlay of the two, where the red dots are the threshold-based bump triggers, and the blue are the average-bump based triggers:

![both](http://i.imgur.com/IwBfNb8.png)

The threshold-based eliminates quieter "noise" bumps, however they create louder noise bumps. The average-based method has some quiet noise bumps, but these are proportionally allowed, in louder environments they eliminate those quieter bumps, while preventing the formation of louder noise bumps. 

The average-based method is useful when it comes to long tones, like a key being held for a while. To our ear, there are no "bumps" of any sort in this kind of sound, but the volume differences trigger bumps in the program. They are very obvious with the threshold based method, but the average-based method tends to mitigate too much responsiveness during these types of sounds, so it was ultimately the method that was implemented in the code.

---

### Pulse() & PalettePulse()

The only unique aspect of this visualization that hasn't already been discussed is the math that determines how it spreads from the center of the strand.
in the code we have:

    int start = LED_HALF - (LED_HALF * (volume / maxVol));
    int finish = LED_HALF + (LED_HALF * (volume / maxVol)) + strand.numPixels() % 2;`

These calculations determine where to start the "pulse" and where to end it, based on intensity of volume. An easy way to think about why this works is dividing the strip into two halves, and treating each halve like its own proportional rectangular "health bar" (for lack of a better term). For example, if we just treated the entire strand as a health bar (where all the lights being on represented 100% health), then we we'd just multiply the end point by the volume ratio to know when to end it (e.g. a ratio of .5 would only light up half of the lights from the beginning). However, this creates more of a "tower" rather than a pulse (this is initially how this mode started), but the pulse is a bit more horizontal-friendly in my opinion. 

To get the pulse, we just split the LED strand in half and treat each half as its own bar. However we need to flip the side of the strand that is closer to the beginning LED so that it's a pulse and not just 2 bars, hence why we subtract the proportional length ( `(LED_HALF * (volume / maxVol))` ) from the maximum length (`LED_HALF`). For the other half, we have to make sure its bar starts at the middle of the strand, which is why its proportional length is added to `LED_HALF`. The modulus of the strand over 2 is added to account for odd quantities of LEDs.

The dimming effect as the pixels get closer to the edge the pulse is done by using a sine function with a period that is adjusted to the span of the pulse (i.e. `finish - start`):

`float damp = sin((i - start) * PI / float(finish - start));`

`i` is the iterating variable of the for loop, so it will retrieve the changing values from the sine function. Since we don't want any negative dimness, we simply use one crest of the sine wave (half its period). This is a simple way of executing this since the sine function will give regular values between 0 and 1. You could also achieve this effect with a piece-wise function or absolute-value function, such as the following:

<center>![pyramid](http://i.imgur.com/aGvCGwB.png)</center>

This may seem a little convoluted as first glance, but the math works: If you have a pulse which takes up the entire strand (i.e. `start = 0` & `finish = 36` (for my strand)), then you end up with:

<center>![18pyramid](http://i.imgur.com/LBs2Soj.png)</center>

Which may make a little more sense as to why it works, but here's a graph to drive home the point:

<center>![sinpyra](http://i.imgur.com/TMYDQRI.png)</center> 

This is the linear approach to the dimming affect, where as the sine-wave is an exponential approach. There isn't a noticeable difference in computational effort either way, the sine method was used simply because sine-waves are typically more familiar than absolute-value cusps. I also found the smooth change in brightness from the sine wave to be more aesthetically pleasing than the linear dimming, but as always feel free to try either method and see what works best for you.

The last feature that's a little subtle is that each pass, it checks if the current lights (after fading) are still brighter than the ones you're about to overwrite them with. The purpose of this is that I found the original mode to blink too often, and the fade effect is a waste of computing power if you're just going to overwrite the faded lights with new lights. This gives them an opportunity to fade a little bit if the song goes into a small quiet spell, and makes the experience a little more fluent.

There are two main ways to ask for the "brightness" of a particular pixel. The best way would be using vectors, and treat each color (R, G, and B) as axes. If you don't know what vectors are, they are basically a line to a point. Normally a coordinate like (x,y) would be a point, using vectors this represents a line drawn from the origin (0,0) to the point (x,y). In two dimensions, if you want the length of this vector you simply use the Pythagorean Theorem: `sqrt(x^2 + y^2)`. Similarly for a 3D vector (which is what we're pretending to make with the three color values), the length (or "magnitude") of the vector is: `sqrt(x^2 + y^2 + z^2)`. So if we treat the brightness of the 3 different colors as spacial lengths (i.e. `sqrt(R^2 + G^2 + B^2)`), the "longer" magnitude vectors would be "brighter" by contrast.

However this isn't the method that is used. Since the colors we're comparing brightness are "similar" so to speak (they will be near each other in the gradient), you can simply take an average of the three colors and have that value represent the brightness (e.g. and RGB value of `255, 128, 0` would be  127.7). This is simply to conserve a little bit of computational effort since you're avoiding squaring, adding, and rooting, and simply just adding and dividing. 

This averaging check is currently done during the `for` loop in Pulse(). It was not isolated as its own helper function since currently no other visualization needs to make use of it. If necessary, it will be abstracted into its own function in the future.

---

### Traffic()

Not much to talk about here. The trail effect is created by `fade()`. The position of each dot of color is stored in an array. The array is the same length as the number of pixels in your strand (since that is the maximum amount of dots your strand can display). It recycles slots in the array, and the parity of its position determines whether if goes left or right. The process by which slots are recycled is a little convoluted, but in essence it scans over the array until it finds an empty slot to put the next dot in.

---

### Snake()

Also not much to math going on here. This mode is essentially just `Traffic()` with one dot, but with more going on. Notably: the dot iterates in one direction (left or right) until a `bump` is experienced (i.e. `bump = true`). I found that the speed of iteration without any throttling (even after the 30ms delay) was inconsistent with slower tempo songs, so a little bit of modulation was imposed. Essentially it utilizes the average amount of time between bumps to determine a tempo of sorts, and if it's slower it will only iterate every modulus of `gradient`. I'm still ironing out what average times correspond well with what iteration speeds, so for the time being I won't put any hard numbers here.

---

### PaletteDance()

This function has some complexities, but nothing that hasn't been covered above. It uses the proportional color fitting seen in `PalettePulse()`, as well as the sine brightness dimming. The only difference is shifting these two functions to correspond with a position on the strip. The brightness shifts by simply performing a mathematical shift on on the sine function (e.g. sin(x + c) ). Since it's the absolute value of sine, the brightness simply loops over. Here's a graphical demonstration of the concept:

<center>![sine shift](http://i.imgur.com/PKmTWdA.png)</center>

Here the sine function is shifted by 10 to make the effect obvious, but that could be any arbitrary quantity. Luckily the inherent behavior of the sine function causes it to loop the brightness effect appropriately around the strand. This shifting is also executed with the color palette sizing, so it appears as if the "hump" of color is one continuous object that is moving across the strand.

---

### Glitter()

This one was the simplest to make in my experience. Essentially just uses the palette sizing seen above, and slowly gradients through it to create a background for the sparkles. Since the sparkles should stand out, each color is divided by a constant to dim it. Sparkles are created every bump and are given a random position and relative sound level brightness. Since the gradient progresses over each pixel, the sparkle is immediately overwritten to create a glimmer effect. 

---

### Paintball()

My personal favorite of all the modes. Follows the same random position logic as `Glitter()`, but instead of sparkles on a background, they are dots of color that get averaged out across the the strand. This bleeding effect is position oriented (i.e. it treats the passed position as the "center" of color blending, and averages the colors together from there). One pass of `bleed()` doesn't do much, but since it ideally takes a few cycles between each `bump`, `bleed()` can work its magic a couple of times and slowly blend the colors together. On a true `bump`, more bright dots of color are added and get bled together, so it can create some very beautiful color-scapes. 

`bleed()` works specifically by check to the left and right of the center point. It then checks to the left and right of those points, and then uses the average of those 3 pixel's colors to overwrite the currently checked pixel's color. This can be confusing since there's a lot of lefts and rights here, so for example, if our center point is `18`, then it would go to position `19`, average together the colors of `18`, `19`, and `20` and overwrite `19` with that average color. Then it would go to position `17`, average the colors of `16`, `17`, and `18` and overwrite `17`. It will continue to do this until it reaches the ends of the strand. 

With the way `Paintball()` works, the center point would have just been given a pure color from the specific `palette()`, so the points immediately to the left and right will be approximately half of that color, and so on. `bleed()` tends to generate its own fading effect, but as a fail-safe `fade()` is called if a bump hasn't been detected in a while.  

---

