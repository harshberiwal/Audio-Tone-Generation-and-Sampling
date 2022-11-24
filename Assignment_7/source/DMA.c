/*
 * Using the DIrect memory Access (DMA) in cycle stealing mode to copy two bytes of data from the
 * pre-computer sample_buffer to the DACDAT register.
 *
 * Author: Harsh Beriwal, harsh.beriwal@colorado.edu
 *
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_7
 *
 * THE Init_DMA_for playback, Start_DMA and DMA0_IRQhandler function was taken for Alexander Dean
 * Github folder a link to which is given below.
 * https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_9/DMA_Examples/Source
 */

#include <stdint.h>
#include <MKL25Z4.h>
#include "timers.h"

#define ARR_SIZE (256)
uint32_t s[ARR_SIZE], d[ARR_SIZE];

uint16_t * Reload_DMA_Source=0;
uint32_t Reload_DMA_Byte_Count=0;
uint32_t DMA_Playback_Count=0;
uint8_t total_cycles =0;


void Init_DMA_For_Playback(uint16_t * source, uint32_t count) {
	// Save reload information
	// Timer stop
	//
	// Gate clocks to DMA and DMAMUX
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	// Disable DMA channel to allow configuration
	DMAMUX0->CHCFG[0] = 0;

	// Generate DMA interrupt when done
	// Increment source, transfer words (16 bits)
	// Enable peripheral request
	DMA0->DMA[0].DCR = DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK |
											DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) |
											DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK;
	// Configure NVIC for DMA ISR
	NVIC_SetPriority(DMA0_IRQn, 2);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	// Enable DMA MUX channel with TPM0 overflow as trigger
	DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_SOURCE(54);
}

void Start_DMA_Playback() {
	// initialize source and destination pointers
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) Reload_DMA_Source);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));
	// byte count
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(Reload_DMA_Byte_Count*2);
	// clear done flag
	DMA0->DMA[0].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;
	// set enable flag
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}

void update_DMA_source(uint16_t * source, uint32_t count){
	Reload_DMA_Source =source;
	Reload_DMA_Byte_Count =count;
}

uint8_t cycle_check(){
	return total_cycles;
}

void reset_current_cycle(){
	total_cycles =0;
}

void DMA0_IRQHandler(void) {
	// Clear done flag
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
	// Start the next DMA playback cycle
	Start_DMA_Playback();
	//Increments this counter to check for the time elapsed
	total_cycles++;
}
