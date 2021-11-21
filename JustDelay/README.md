# Just Delay

This is simple [Delay Effect](https://en.m.wikipedia.org/wiki/Delay_(audio_effect)) plugin to demonstrate basic stereo delay algorithm.

![image](https://user-images.githubusercontent.com/6858921/142690634-63763a7b-2a48-4716-832d-8b5329f9871e.png)

## Parameters

**Time** - Controls time in ms between initial (dry) signal and repeated (wet) signal

**Feedback** - Controls the amount of the signal that is feed back into the input of your delay to create repeatable echoes. More feedback results in more echos. 0% - only one repetition of the dry signal. 50% - every echo has twice less gain, than the previous one. 100% - endless echos. 

**Mix** - Controls the balance between dry and wet signal



## Graphical representation

![image](https://user-images.githubusercontent.com/6858921/142695687-46ae0e07-6c08-4726-812a-aac7242e9c76.png)
Input signal (IN) is passed into DELAY line, which is a temporary memory buffer, from which the signal is recalled at a later time. When delayed signal (wet) is mixed with the input signal (dry), it results in one repetition of the input signal. To generate more repetitions, some amount of the wet signal is feed back (fb) to the DELAY line. 

The differential equation of the delay line is 
```y(n)=x(n-D)+fb*y(n-D)```

Where\
***n*** is sample position\
***D*** is delay time parameter in samples\
***fb*** is feedback parameter from 0 to 1\
***y(n)*** is delay signal\
***x(n)*** is input signal\

So this equation can be read as\
```delay signal value = input value D samples back + feedback * delay value D samples back```

Not very precise and scientific, but time graph might look close to this:
![image](https://user-images.githubusercontent.com/6858921/142696931-4119d6d5-7d15-4374-a85b-b44fc12d7183.png)

## Algorithm highlight
### Circular buffer
Delay algorithm uses [circular buffer](https://en.m.wikipedia.org/wiki/Circular_buffer) data structure to temporary store data in delay buffer. The length of the buffer should be equal to max delay time in seconds * sample rate. In this implementation maximum delay time is 2 seconds, so buffer size is 2 * sample rate.

### Processing
> DISCLAIMER. \
This code is close to, but might not be the same, that you'll find in the repository, for the sake of easier explanation. 

For every input sample do the following:
1. Read input signal value
```
const float input = channelData[i];
```
2. Read delayed signal value from delay buffer X samples back. 
   - Take time from the "Time" control of the effect.
   - Convert time from milliseconds to seconds, by deviding value by 1000. 
   - Convert time from seconds to samples, by multiplying seconds to sample rate (which is basically samples per second).
```
float delay = delayBuffer[channel].read((*delayTimeMsParam / 1000) * sampleRate);
```
3. Create input for delay buffer and write.
   - Take percentage from the "Feedback" control of the effect.
   - Convert feedback percentage to the decimal (devide by 100).
   - Multiply feedback decimal to the delayed signal value to generate attenuated (or not if "Feedback" is 100%) feedback value. 
   - Sum input value (this will be our first "repetition" of the signal) with feedback value (this will be our follow-up "repetitions" of the signal) and write to the delay buffer.
```
delayBuffer[channel].write(input + (*feedbackParam / 100) * delay);
```
4. Write output mix
   - Take percentage from the "Mix" control of the effect.
   - Convert mix percentage to the decimal (devide by 100).
   - Adjust delayed signal (wet) gain by multiplying with mix decimal
   - Adjust input signal (dry) gain by multiplying with (1-mix decimal) (so dry signal will always take all the remaining space from wet signal) 
```
channelData[i] = (1 - (*mixParam / 100)) * input + (*mixParam / 100) * delay;
```
