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

#include "ADC.h"

#define MAX_INTEGER				65535
#define ADC_POS 				(20)
#define SIZE 					1024
#define ADC_CHANNEL 			23
#define TPM1_TRIGGER 			9
#define ALTERNATE_TRIGGER_ON	1

uint16_t ADC_period =0, ADC_min =65535, ADC_max= 0, ADC_avg =0, ADC_count =0;

void Init_ADC(void) {
	//gate clock of ADC0 module
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	//16 bit single-ended conversion, bus clock input, divide bus by 4
	ADC0->CFG1 = ADC_CFG1_MODE(3);
	ADC0->CFG2 =0;
	ADC0->SC2 = ADC_SC2_ADTRG(1);
	//set ADC channel input as DAC output
	ADC0->SC1[0] |= ADC_SC1_ADCH(ADC_CHANNEL);
	//Selecting Alternate Trigger with TPM1
	SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN(ALTERNATE_TRIGGER_ON) | SIM_SOPT7_ADC0TRGSEL(TPM1_TRIGGER);
}

void audio_input_conversion() {
	uint32_t ADC_sum =0;
	uint16_t ADC_Raw[SIZE];
	ADC_count =0;
	ADC_min =MAX_INTEGER;
	ADC_max =0;
	ADC_avg =0;
	Start_TPM1();                          //Starting TPM1 for ADC conversion
	//***********************TAKING all the RAW samples from the ADC channel*************************
	for(int i =0; i<SIZE; i++) {
		ADC0->SC1[0] = ADC_CHANNEL; // start conversion on channel 0
		while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
		ADC_Raw[i] = ADC0->R[0];     //Read Result
		ADC0->SC1[0] &= ~ADC_SC1_COCO_MASK;
	}
	Stop_TPM1();
	//************************CALCULATING MIN SAMPLE, MAX SAMPLE AND AVERAGE*************************
	while(ADC_count<SIZE){
		if(ADC_Raw[ADC_count]>ADC_max)
			ADC_max = ADC_Raw[ADC_count];
		else if(ADC_Raw[ADC_count]< ADC_min)
			ADC_min = ADC_Raw[ADC_count];
		ADC_sum +=ADC_Raw[ADC_count];
		ADC_count++;
	}
	ADC_avg = ADC_sum/SIZE;
	//***********************AUTOCORRELATE FUNCTION RETURNS THE DETECTED PERIOD**********************
	ADC_period = autocorrelate_detect_period(ADC_Raw, SIZE, kAC_16bps_unsigned);
}

void print_audio_in_message() {
	printf("min=%d max=%d avg=%d period=%d samples frequency=%d\n\r",
				ADC_min, ADC_max, ADC_avg,ADC_period,(ADC_SAMPLING_RATE/ADC_period));
}



