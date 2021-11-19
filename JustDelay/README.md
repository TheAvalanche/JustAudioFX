# Just Delay

![image](https://user-images.githubusercontent.com/6858921/142690634-63763a7b-2a48-4716-832d-8b5329f9871e.png)

## Parameters

**Time** - Time in ms between dry and delayed signal

**Feedback** - Attenuation to delayed signal of delayed signal. 🤷‍♂️ 50% will result, that every delayed sound is twice quiter, then previous one. 100% will result endless delay. 0% will result in only one repetition of dry signal

**Mix** - Mix between dry and wet signal in %

## Block Diagram

![image](https://user-images.githubusercontent.com/6858921/142695687-46ae0e07-6c08-4726-812a-aac7242e9c76.png)


## Time Diagram

![image](https://user-images.githubusercontent.com/6858921/142696931-4119d6d5-7d15-4374-a85b-b44fc12d7183.png)

## Algorithm highlight
1. Read input signal

```
const float input = channelData[i];
```
2. Read signal from delay buffer X sample back. 
  1. To convert time from milliseconds to seconds, devide value by 1000. 
  2. To convert time from seconds to samples, multiply seconds to sample rate.
```
float delay = delayBuffer[channel].read(*delayTimeMsParam * sampleRate / 1000);
```
3. Create input for delay line and write to buffer
```
delayBuffer[channel].write(input + (*feedbackParam / 100) * delay);
```
4. Write output mix
```
channelData[i] = (1 - (*mixParam / 100)) * input + (*mixParam / 100) * delay;
```
