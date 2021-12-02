# Just Ping-Pong Delay

This is simple Stereo [Delay Effect](https://en.m.wikipedia.org/wiki/Delay_(audio_effect)) plugin that alternates each delay repeat between the left and right channels to demonstrate one of possible ping-pong delay algorithms.

![image](https://user-images.githubusercontent.com/6858921/142690396-4f2484bc-35c3-406b-8652-deebe5cb1414.png)

## Parameters

**Time** - Controls time in ms between initial (dry) signal and repeated (wet) signal

**Feedback** - Controls the amount of the signal that is feed back into the input of your delay line to create repeatable echoes. More feedback results in more echos. 0% - only one repetition of the dry signal. 50% - every echo has twice less gain, than the previous one. 100% - endless echos

**Spatial** - Controls the balance between left/right repeats, making alternating between channels less or more distinctable

**Invert** - Changes the dominating channel (when **spatial** is > 0), from left to right

**Mix** - Controls the balance between dry and wet signal

## Graphical representation

Before reading further, make sure, that you are familiar with [mono/stereo delay algorithm](../JustDelay), as we are not going to cover it here.

<img src="https://user-images.githubusercontent.com/6858921/144234489-5708c2dc-8b63-4f02-9ae7-dee73bbcd1b7.png" width="600px">

In general, processing is the same, as in stereo delay, with the only difference, that feedback is sent to the opposite channel. Thus, repetitions of the signal will bounce from one channel to another. But there is one problem.

**Problem:**

If stereo signal has similar data in left and right channel, ping-pong effect might not be very audible. It will be very close to stereo delay, as similar signals will alternate between left and right channel.

**Solution:**

Introduce **Spatial** parameter, which will reduce one channel's gain, before it is sent to delay line. Thus one channel signal's repetitions will be louder, than other one's, while alternating between channels, and it will make ping-pong effect more distinctable. By default we will reduce right channel's gain, thus giving more priority to the left channel. To give priority to the right channel, check the **Invert** parameter.

## Algorithm highlights

The biggest part of the logic is taken from [mono/stereo delay algorithm](../JustDelay), so we will cover only differences here.

Intorduce **spatial** coefficient for every channel, to reduce channel's gain before sending to delay line. By default, left channel will not be adjusted (`spatialLeft = 1`), and right channel can be reduced up to 100% (`spatialRight = 0`), by the **spatial** parameter. If `invertSide` is true, right channel will not be adjusted (`spatialRight = 1`), and left channel can be reduced up to 100% (`spatialLeft = 0`).
```
auto invertSide = *invertSideParam > 0.5f;
auto spatialLeft = invertSide ? (1 - (*spatialParam / 100)) : 1;
auto spatialRight = invertSide ? 1 : (1 - (*spatialParam / 100));
```

When writing delay sample into the circular buffer for later recall, adjust left or right channel's input, based on the the **spatial** coefficient, that we have calculated earlier. Put right channel's feedback data to the left channel's delay buffer. And put left channel's feedback data to the right channel's delay buffer.
```
delayBuffer[LEFT_CHANNEL_IDX].write(inputL * spatialLeft + (*feedbackParam / 100) * delayR);
delayBuffer[RIGHT_CHANNEL_IDX].write(inputR * spatialRight + (*feedbackParam / 100) * delayL);
```
