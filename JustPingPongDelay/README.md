# Just Ping-Pong Delay

This is simple Stereo [Delay Effect](https://en.m.wikipedia.org/wiki/Delay_(audio_effect)) plugin that alternates each delay repeat between the left and right channels to demonstrate one of possible ping-pong delay algorithms.

![image](https://user-images.githubusercontent.com/6858921/142690804-cf046268-3572-4fcb-96d6-870e3f0cf7db.png)

## Parameters

**Time** - Controls time in ms between initial (dry) signal and repeated (wet) signal

**Feedback** - Controls the amount of the signal that is feed back into the input of your delay line to create repeatable echoes. More feedback results in more echos. 0% - only one repetition of the dry signal. 50% - every echo has twice less gain, than the previous one. 100% - endless echos

**Spatial** - Controls the balance between left/right repeats, making alternating between channels less or more distinctable

**Invert** - Changes the dominating channel (when **spatial** is > 0), from left to right

**Mix** - Controls the balance between dry and wet signal

