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

#include "timers.h"
#include "MKL25Z4.h"

#define MODE_LPTPM_INC	1

void Init_TPM0(int period)
{
	//turn on clock to TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM1_MASK;
	//set clock source for tpm as 48 Mhz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	// disable TPM
	TPM0->SC = 0;
	//load the counter and mod
	TPM0->CNT = TPM1->CNT = 0;
	TPM0->MOD = TPM_MOD_MOD(period-1);			  //Given the DAC dampling Rate
	TPM0->SC = (TPM_SC_DMA_MASK | TPM_SC_PS(0));  //Triggers DMA in cycle stealing
}

void Init_TPM1(int period){
	SIM ->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	TPM1->SC = 0;
	TPM1->CNT = 0;
	TPM1->MOD = TPM_MOD_MOD(period -1);			//Given the ADC sampling rate
	TPM1->SC =  TPM_SC_PS(0);  					// No prescaler
}

void Start_TPM0(void) {
	// Enable counter
	TPM0->SC |= TPM_SC_CMOD(1);
}

void Start_TPM1(void) {
	TPM1->SC |= TPM_SC_CMOD(1);
}

void Stop_TPM1(void) {
	TPM1->SC &= ~TPM_SC_CMOD(1);
}


