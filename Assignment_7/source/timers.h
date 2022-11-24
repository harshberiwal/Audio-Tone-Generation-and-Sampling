/*
 * Using the TPM0 and TPM1 timers to control the DMA transfer from source to DACDAT register and
 * ADC alternate trigger.
 *
 * Author: Harsh Beriwal, harsh.beriwal@colorado.edu
 *
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_7
 *
 * No leveraged code in this file.
 */

#ifndef TIMERS_H
#define TIMERS_H
#include "MKL25Z4.h"

/*
 * Initializes the Timer0 to make the DMA work in cycle stealing mode at 48khz DAC Frequency.
 * The DMA is called every time the TPM0 counter overflows using the DMA_Enable_mask in
 * TPM0 Init.
 *
 * Parameters:
 * 	None
 *
 * Returns:
 *  None
 */
void Init_TPM0(int period);

/*
 * Initializes the Timer1 to make the ADC trigger according to the 96khz ADC Frequency.
 *
 * Parameters:
 * 	None
 *
 * Returns:
 *  None
 */
void Init_TPM1(int period);

/*
 * Starts the TPM0 counter basically starting DMA transfer
 *
 * Parameters:
 * 	None
 *
 * Returns:
 *  None
 */
void Start_TPM0(void);

/*
 * Starts the TPM1 counter basically starting ADC sampling.
 *
 * Parameters:
 * 	None
 *
 * Returns:
 *  None
 */
void Start_TPM1(void);

/*
 * Stops the TPM1 counter basically stopping ADC sampling.
 *
 * Parameters:
 * 	None
 *
 * Returns:
 *  None
 */
void Stop_TPM1(void);

#endif
