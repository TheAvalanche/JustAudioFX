# Just Delay

## ![Delay Effect]()

![image](https://user-images.githubusercontent.com/6858921/142690634-63763a7b-2a48-4716-832d-8b5329f9871e.png)

## Parameters

**Time** - Time in ms between dry and delayed signal

**Feedback** - Attenuation to delayed signal of delayed signal. 🤷‍♂️ 50% will result, that every delayed sound will have twice less gain, then previous one. 100% will result endless delay. 0% will result in only one repetition of the dry signal

**Mix** - Mix between dry and wet signal in %



## Block Diagram

![image](https://user-images.githubusercontent.com/6858921/142695687-46ae0e07-6c08-4726-812a-aac7242e9c76.png)


## Time Diagram

![image](https://user-images.githubusercontent.com/6858921/142696931-4119d6d5-7d15-4374-a85b-b44fc12d7183.png)

## Algorithm highlight
### Circular buffer

### Circular buffer
> DISCLAIMER. \
This code might not be the same, that you'll find in the repository, for the sake of easier explanation. 

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
