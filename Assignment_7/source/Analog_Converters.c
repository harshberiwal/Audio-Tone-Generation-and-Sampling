/*
 * Creating a Software using DAC to generate 4 different Audio tones of varying frequencies
 * each for 1 sec. The cycle continues and the ADC is configured to confirm if the frequencies
 * that we are getting is correct.
 *
 * Author: Harsh Beriwal, harsh.beriwal@colorado.edu
 *
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_7
 *
 * No Leveraged Code in this file.
 */


#include <MKL25Z4.H>
#include <math.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fp_trig.h"
#include "timers.h"
#include "DMA.h"
#include "ADC.h"
#include "DAC.h"

#define CLOCKVALUE 			48000000
#define DAC_SAMPLING_RATE 	48000
#define SIZE 				1024
#define TPM1_PERIOD 		(CLOCKVALUE/ADC_SAMPLING_RATE)
#define TPM0_PERIOD			(CLOCKVALUE/DAC_SAMPLING_RATE)
#define A4_FREQ 			440
#define D5_FREQ				587
#define E5_FREQ 			659
#define A5_FREQ				880
#define NUM_TONES			4

uint8_t num_of_period =0, cmp_count =0;
void tone_to_samples();

//************************CREATING AN ENUM FOR EACH TONE**********************************
typedef enum tones{
	A4,
	D5,
	E5,
	A5
}tones_t;

//***********************PRE_COMPUTER BUFFER FOR EACH NOTE********************************
uint16_t sample_buffer[NUM_TONES][SIZE];


//**************************A MEMORY TABLE FOR EACH NOTE**********************************
typedef struct tones_table{
	tones_t tone_name;
	uint16_t frequency;
	uint16_t total_samples;
	uint16_t period;
	uint16_t total_num_period;
}tones_table_t;

//**************************INITIALIZATION FOR EACH TONE**********************************
tones_table_t tones_table_chart[] = {
		{A4, A4_FREQ, 0, 0, 0},
		{D5, D5_FREQ, 0, 0, 0},
		{E5, E5_FREQ, 0, 0, 0},
		{A5, A5_FREQ, 0, 0, 0},
};

int num_tones = sizeof(tones_table_chart)/sizeof(tones_table_t);
uint16_t current_cycle=0, count =0;

/*A function that calculates the samples from the different tones and provides its period,
 * the samples, and the buffer size
 *
 * Parameters:
 * None
 *
 * Returns:
 * None
 *
 */
void tone_to_samples() {
	for(int i=0; i<num_tones; i++) {
		tones_table_chart[i].period = DAC_SAMPLING_RATE/(tones_table_chart[i].frequency);  //period per cycle
		num_of_period = SIZE/(tones_table_chart[i].period);
		tones_table_chart[i].total_samples = (num_of_period*tones_table_chart[i].period);  //buffer size
		tones_table_chart[i].total_num_period =
				(DAC_SAMPLING_RATE/tones_table_chart[i].total_samples);					   //req periods for 1 sec
		for(int j =0; j<tones_table_chart[i].total_samples;j++) {
			sample_buffer[i][j] = (fp_sin((TWO_PI*j)/(tones_table_chart[i].period))		   //Filling Buffers
					+ TRIG_SCALE_FACTOR);
		}
	}
}
/*--------------------------------------------------------------------------------------
  MAIN function
 *--------------------------------------------------------------------------------------*/
int main (void) {
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	    /* Init FSL debug console. */
	    BOARD_InitDebugConsole();
	#endif
	//*********************INITIALIZING THE DAC FOR AUDIO********************************
	Init_DAC();
	//*********************INITIALIZING THE ADC FOR AUDIO-IN*****************************
	Init_ADC();
	//******************INITIALIZING THE DMA FOR DATA TRANSFER***************************
	Init_DMA_For_Playback();
	//******************INITIALIZING THE TPM0 FOR DMA TRIGGER****************************
	Init_TPM0(TPM0_PERIOD);
	//******************INITIALIZING THE TPM1 FOR ADC TRIGGER****************************
	Init_TPM1(TPM1_PERIOD);
	//********************CREATING DAC SAMPLES FOR THE TONES*****************************
	tone_to_samples();
	Start_TPM0();
	update_DMA_source(&sample_buffer[0][0], (tones_table_chart[0].total_samples));
	//****************STARTING DMA TRANSFER WITH AUDIO OUT TURNED ON*********************
	Start_DMA_Playback();
	//*********************STARTING ADC TRIGGER FOR SAMPLING*****************************
	audio_input_conversion();
	__enable_irq();
	while(1){
		//****************GETTING CURRENT TIME ELAPSED IN THE TONE***********************
		current_cycle = cycle_check();
		//**********************IF TIME ELAPSED IS 1 SEC SWITCH**************************
		if(current_cycle >= tones_table_chart[count].total_num_period){
			reset_current_cycle();				//Reset Time Elapsed
			count++;
			if(count == NUM_TONES)				//After last tones, repeat cycle
				count = 0;
			//*************SWITCHING THE SOURCE ADDRESS WITH ANOTHER TONE****************
			update_DMA_source(&sample_buffer[count][0], tones_table_chart[count].total_samples);
			Start_DMA_Playback();  				//Starting DMA transfer with TPM0
			if(count ==0)
				cmp_count = NUM_TONES-1;		//During first tone, print audio in for last tone
			else
				cmp_count = count-1;
			printf("Generated %d samples at %d Hz; computed Period = %d\n\r",
						tones_table_chart[cmp_count].total_samples,
						tones_table_chart[cmp_count].frequency,
						tones_table_chart[cmp_count].period);
			print_audio_in_message();  			//printing ADC message
			audio_input_conversion(); 			//Taking Value for the next conversion
		}
	}
}

