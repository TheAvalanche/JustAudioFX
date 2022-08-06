# Just Flanger

This is a simple [Flanger Effect](https://en.wikipedia.org/wiki/Flanging) plugin to demonstrate basic flanger algorithm.

![image](https://user-images.githubusercontent.com/6858921/182820804-eca79b51-5a1a-4053-a5be-3ecfb18d0c6c.png)

## Parameters

**Rate** - Controls the frequency of LFO, that modulates the delay time

**Depth** - Controls the amplitude of Lfo, that modulates the delay time

**Feedback** - Controls the amount of the signal that is fed back into the input of your delay line to create repeatable echoes. More feedback results in more echoes. 0% - only one repetition of the dry signal. 50% - every echo has twice less gain, than the previous one. 100% - endless echoes

**Mix** - Controls the balance between dry and wet signals. You can also get [Vibrato Effect](https://en.wikipedia.org/wiki/Vibrato) by setting *Mix* to 100%



## Graphical representation

<img src="https://user-images.githubusercontent.com/6858921/183245065-e7f82a68-c95b-43a0-a032-9688a2cf6c27.png" width="600px">

To better understand how flanger effect works, refer to [Delay Effect algorithm](https://github.com/TheAvalanche/JustAudioFX/tree/main/JustDelay) first. 

The only difference from the delay effect is that in flanger `delay time` changes over time. Delay time is controlled (modulated) by LFO and usually is from 1ms to 7ms.

## Algorithm highlights

### LFO and modulation
LFO algorithm uses [Low Frequency Oscillator, or LFO](https://en.wikipedia.org/wiki/Low-frequency_oscillation) to modulate the delay time.

LFO is usually sine/saw/triangle wave of low frequency, usually below 20Hz and with amplitude either from -1 to +1 (bipolar), or from 0 to +1 (unipolar). 
This wave can modulate (change over time) any parameter. 
You can define any minimum and maximum value of the parameter and with LFO modulation this parameter will change from min (LFO = 0) to max (LFO = 1) over time in repeatable way.
Formula for modulated value in our case will be
```
modulatedValue = lfoValue * (maxValue - minValue) + minValue;
```

In this repository you will find LFO abstract class and SineLFO, TriangleLFO and SawLFO as implementations. However, for flanger we will us TriangleLFO only. 
To generate LFO signal, we will use moduloCounter, which will increase from 0 to 1 in a steps, set by oscilator frequency ("Rate" control). Thus we get unipolar saw signal. We will use this signal to tranform to sine or triangle. 
We will not cover the math part here, please, refer to the code for more details.

---

### Processing
> DISCLAIMER. \
This code might not be exactly the same, that you'll find in the repository.

To better understand how flanger effect works, refer to [Delay Effect algorithm](https://github.com/TheAvalanche/JustAudioFX/tree/main/JustDelay) first. Here the only difference is in delay time calculation.

1. Read current LFO value and multiply by "Depth" control in percentage.
```
double lfoValue = lfo->getUnipolarValue() * (*depthParam / 100);
```
2. Calculate delay time by modulating value between 1ms and 10ms with current LFO value (see modulation formula in LFO section).
```
double delayParam = modulate(lfoValue, FLANGER_MIN_DELAY_TIME_MS, FLANGER_MAX_DELAY_TIME_MS);
```
