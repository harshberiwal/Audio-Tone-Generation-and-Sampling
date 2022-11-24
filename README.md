# PES_Assignment_7
Frequency_tone_generation and configuring ADC to read the same tone frequency

Creating a Software using 12-bit DAC to generate 4 different Audio tones of varying frequencies
each for 1 sec. The cycle continues and the 16-bit ADC is configured to confirm if the frequencies
that we are getting is correct. Four different musical tones are generated as required.  

1)A4- 440 Hz 2)D5- 587 Hz 3)E5- 660 Hz 4)A5- 880 Hz

Author: Harsh Beriwal, harsh.beriwal@colorado.edu

IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
Github Link: https://github.com/harshberiwal/PES_Assignment_7

Following files are present in the project: 

1) ADC.c - Implementing an ADC audio input sampling software that checks for the audio frequency of the
 different notes played on its ADC channel. The channel is configurable and the whole code can be
 changed with simple macros.
 
2) DMA.c - Using the DIrect memory Access (DMA) in cycle stealing mode to copy two bytes of data from the
pre-computer sample_buffer to the DACDAT register.

3) Analog_Converters.c -  Created a Finite State Machine that can be easily scaled for more tones. 
Currently, the software uses DAC to generate 4 different Audio tones of varying frequencies
each for 1 sec.

Below are the most important functions created in the Project. 

void Tone_to_samples() - A function that calculates the samples from the different tones and provides its period,
the samples, and the buffer size. The functions uses integer math to get the different DAC samples with 
the corresponding period and Queue Size. 

void audio_input_conversion() -  Starts the ADC conversion with alternate trigger of TPM1 according to 96Khz sampling Rate
and calculates min, max and avg samples and calls autocorrelate functions for the converted
raw samples to get a sine wave period

void Start_DMA_Playback() - Begins DMA transfer with a source address and the total byte count in cycle
stealing mode. When all the bytes are transferred, a DMA interrupt is generated.

uint8_t cycle_check() -  Returns the total numbers of cycles that has elapsed for each tone. 
This helps us in checking the time a particular tone is running and using TPM0.

Challenges overcomed: 

The biggest issue was seen while observing the generated Analog waveform on the oscilloscope. A tearing was observed between 
the transitions from one tone to another. To avoid this, I used the DMA interrupt by using TPM and checking the number of cycles
that it needs to output to reach 1 sec. Using that count, I am reaching the 1 sec tone requirement. However, there is small error of 
1-1.5 percent in the total tone period as it coming to be around 985ms to 990ms. 

However, there is no tearing between two different tone when transitioning. It looks very smooth and can be checked using the 
screenshots in the main branch in a different subfolder.  


 
 
