/*
 * Implementing an DAC audio Output sampling software that creates sine waveform for each tone.
 *
 * Author: Alexander Dean
 * Modified By: Harsh Beriwal, harsh.beriwal@colorado.edu
 *
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_7
 *
 * THE DAC_init was taken for Alexander Dean Github folder a link to which is given below.
 * https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_9/DMA_Examples/Source
 */

#include "DAC.h"

#define DAC_POS (30)

void Init_DAC(void) {
	// Init DAC output
	SIM->SCGC6 |= (1UL << SIM_SCGC6_DAC0_SHIFT);
	SIM->SCGC5 |= (1UL << SIM_SCGC5_PORTE_SHIFT);
	PORTE->PCR[DAC_POS] &= ~(PORT_PCR_MUX(7));		// Select analog
	// Disable buffer mode
	DAC0->C1 = 0;
	DAC0->C2 = 0;
	// Enable DAC, select VDDA as reference voltage
	DAC0->C0 = (1 << DAC_C0_DACEN_SHIFT) |
							(1 << DAC_C0_DACRFS_SHIFT);
}
