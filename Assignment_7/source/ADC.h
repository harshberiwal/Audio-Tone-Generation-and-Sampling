/*
 * Implementing an ADC audio input sampling software that checks for the audio frequency of the
 * different notes played on its ADC channel. THe channel is configurable and the whole code can be
 * changed with simple macros.
 *
 * Author: Harsh Beriwal, harsh.beriwal@colorado.edu
 *
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_7
 *
 * A part of ADC_init and ADC_input_conversion function were inspired and taken from Alex
 * Dean Github a link to which is given on
 * https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_6/Analog%20Demo/src/main.c
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include <MKL25Z4.H>
#include <stdio.h>
#include "fsl_debug_console.h"
#include "board.h"
#include "peripherals.h"
#include "timers.h"
#include "autocorrelate.h"

#define ADC_SAMPLING_RATE	96000

/* Initializes the ADC with alternate trigger of TPM1 according to 96Khz sampling Rate.
 *
 * Parameters:
 * None
 *
 * Returns:
 * None
 *
 */
void Init_ADC(void);

/* Starts the ADC conversion with alternate trigger of TPM1 according to 96Khz sampling Rate
 * and calculates min, max and avg samples and calls autocorrelate functions for the converted
 * raw samples to get a sine wave period.
 *
 * Parameters:
 * None
 *
 * Returns:
 * None
 *
 */
void audio_input_conversion();

/* Prints the information received from Audio_input_conversion functions so notify the user
 *
 * Parameters:
 * None
 *
 * Returns:
 * None
 *
 */
void print_audio_in_message();

#endif /* ADC_H_ */
