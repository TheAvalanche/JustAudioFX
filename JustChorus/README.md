# Just Flanger

This is a simple [Chorus Effect](https://en.wikipedia.org/wiki/Chorus_(audio_effect)) plugin to demonstrate basic chorus algorithm.

![image](https://user-images.githubusercontent.com/6858921/183247557-22625d50-ebfe-4bd5-b6a8-b395f5995b0e.png)

## Parameters

**Rate** - Controls the frequency of LFO, that modulates the delay time

**Depth** - Controls the amplitude of Lfo, that modulates the delay time

**Mix** - Controls the balance between dry and wet signals. You can also get [Vibrato Effect](https://en.wikipedia.org/wiki/Vibrato) by setting *Mix* to 100%


## Algorithm highlights

To better understand how chorus effect works, refer to [Flanger Effect algorithm](https://github.com/TheAvalanche/JustAudioFX/tree/main/JustFlanger) first. 
The only difference from flanger is that in chorus delay time is usually bigger (~10ms to ~30ms). And bipolar LFO modulation is used.
