# Just Ping-Pong Delay

This is simple Stereo [Delay Effect](https://en.m.wikipedia.org/wiki/Delay_(audio_effect)) plugin that alternates each delay repeat between the left and right channels to demonstrate one of possible ping-pong delay algorithms.

![image](https://user-images.githubusercontent.com/6858921/142690396-4f2484bc-35c3-406b-8652-deebe5cb1414.png)

## Parameters

**Time** - Controls time in ms between initial (dry) signal and repeated (wet) signal

**Feedback** - Controls the amount of the signal that is feed back into the input of your delay line to create repeatable echoes. More feedback results in more echos. 0% - only one repetition of the dry signal. 50% - every echo has twice less gain, than the previous one. 100% - endless echos

**Spatial** - Controls the balance between left/right repeats, making alternating between channels less or more distinctable

**Invert** - Changes the dominating channel (when **spatial** is > 0), from left to right

**Mix** - Controls the balance between dry and wet signal

