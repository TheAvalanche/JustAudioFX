# Just Delay

This is simple [Delay Effect](https://en.m.wikipedia.org/wiki/Delay_(audio_effect)) plugin to demonstrate basic delay algorithm.

![image](https://user-images.githubusercontent.com/6858921/142690634-63763a7b-2a48-4716-832d-8b5329f9871e.png)

## Parameters

**Time** - Controls time in ms between initial (dry) signal and repeated (wet) signal

**Feedback** - Controls the amount of the signal that is feed back into the input of your delay to create repeatable echoes. More feedback results in more echos. 0% - only one repetition of the dry signal. 50% - every echo has twice less gain, than the previous one. 100% - endless echos. 

**Mix** - Controls the balance between dry and wet signal



## Graphical representation

<img src="https://user-images.githubusercontent.com/6858921/142695687-46ae0e07-6c08-4726-812a-aac7242e9c76.png" width="600px">

Input signal (IN) is passed into DELAY line, which is a temporary memory buffer, from which the signal is recalled at a later time. When delayed signal (WET) is mixed with the input signal (DRY), it results in one repetition of the input signal. To generate more repetitions, some amount of the wet signal is feed back (fb) to the DELAY line. 

The differential equation of the delay line is \
```y(n)=x(n-D)+fb*y(n-D)```

Where\
***n*** is sample position\
***D*** is delay time parameter in samples\
***fb*** is feedback parameter from 0 to 1\
***y(n)*** is delay signal\
***x(n)*** is input signal

So this equation can be read as\
```delay signal value = input value D samples back + feedback * delay value D samples back```

Not very precise and scientific, but time graph might look close to this:

<img src="https://user-images.githubusercontent.com/6858921/142696931-4119d6d5-7d15-4374-a85b-b44fc12d7183.png" width="500px">

## Algorithm highlight

### Circular buffer
Delay algorithm uses [circular buffer](https://en.m.wikipedia.org/wiki/Circular_buffer) data structure to temporary store data for the delay line. 
The length of the buffer should be greater or equal to `max delay time in seconds * sample rate`.

Under the hood, circular buffer is a simple array. \
When we write data into our circular buffer, we start from index 0 and increment the index after each write. When index gets equal to array length, we set it back to 0 and start again. Thus, we never exceed the array length. \
When we read data from our circular buffer, we calculate read index as `write index - D samples` (delay time parameter in samples). As result of this calculation can be negative, we add additonal check to treat negative result as offset from the end of array.

In the repository you will find 2 versions of circular buffers. [Non optimized](./Source/CircularBuffer.cpp) and [Optimized](./Source/CircularBufferOptimized.cpp). 
Non optimized is the simpliest possible implementation of circular buffer. 
Optimized is using mask for shifting index if it exceeds array boundaries, as described in [Will C. Pirkle book](https://www.amazon.com/Designing-Audio-Effect-Plugins-C/dp/1138591939).

For every channel we should have a separate circular buffer instance.

---

### Processing
> DISCLAIMER. \
This code is close to, but might not be the same, that you'll find in the repository.

For every input sample in every channel we do the following:

1. Read input sample value (dry signal)
```
float input = channelData[channel];
```

2. Read delay sample value from the circular buffer `D` samples back (wet signal)
   - To calculate `D`, take value from the "Time" control of the plugin and convert it to samples. To convert miliseconds to samples, first convert miliseconds to seconds (divide by 1000) and then multiply with current sample rate
```
float delay = delayBuffer[channel].read((*delayTimeMsParam / 1000) * sampleRate);
```

3. Write delay sample into the circular buffer for later recall
   - As per formula, we should write `input + fb * delay` into the buffer
   - To calculate `fb`, take value from the "Feedback" control of the plugin and convert it to decimal (divide by 100)
   - `input` will generate the first repetition of the signal later and `fb * delay` will generate more repetitions after the first one
```
delayBuffer[channel].write(input + (*feedbackParam / 100) * delay);
```

4. Mix `input` sample and `delay` sample to generate output sample value
   - "Mix" control the fraction of wet signal (`delay`) in the output. So if "Mix" control is set to 40%, it will result in `0.6 * input + 0.4 * delay`
```
channelData[channel] = (1 - (*mixParam / 100)) * input + (*mixParam / 100) * delay;
```
