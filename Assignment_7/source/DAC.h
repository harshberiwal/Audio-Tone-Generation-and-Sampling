/*
 * Implementing an DAC audio Output sampling software that creates sine waveform for each tone.
 *
 * Author: Harsh Beriwal, harsh.beriwal@colorado.edu
 *
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_7
 *
 * THE DAC_init function was taken for Alexander Dean Github folder a link to which is given below.
 * https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_9/DMA_Examples/Source
 */

#ifndef DAC_H_
#define DAC_H_

#include <MKL25Z4.H>
#include <stdio.h>
#include "fsl_debug_console.h"

/* Initializes the DAC conversion at PTE30 of the KL25Z.
 *
 * Parameters:
 * None
 *
 * Returns:
 * None
 */
void Init_DAC(void);

#endif /* DAC_H_ */
