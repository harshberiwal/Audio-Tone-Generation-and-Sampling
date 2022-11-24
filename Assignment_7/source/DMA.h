/*
 * Using the DIrect memory Access (DMA) in cycle stealing mode to copy two bytes of data from the
 * pre-computer sample_buffer to the DACDAT register.
 *
 * Author: Harsh Beriwal, harsh.beriwal@colorado.edu
 *
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_7
 *
 * THE Init_DMA_for playback, Start_DMA and DMA0_IRQhandler functions were taken for Alexander Dean
 * Github folder a link to which is given below.
 * https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_9/DMA_Examples/Source
 */

#ifndef DMA_H
#define DMA_H

/*
 * Initializes DMA to work in cycle stealing mode at 48Mhz Frequency.
 * The DMA is called every time the TPM0 counter overflows using the DMA_Enable_mask in
 * TPM0 Init.
 *
 * Paramters:
 * 	None
 *
 * Returns:
 *  None
 */
void Init_DMA_For_Playback();

/*
 * Begins DMA transfer with a source address and the total byte count in cycle
 * stealing mode. When all the bytes are transferred, a DMA interrupt is
 * generated.
 *
 * Parameters:
 * 	None
 *
 * Returns:
 *  None
 */
void Start_DMA_Playback();

/*
 * Returns the total numbers of cycles that has elapsed for each tone.
 * This helps us in checking the time a particular tone is running for
 * using TPM0.
 *
 * Parameters:
 * 	None
 *
 * Returns:
 *  The number of cycles that has been generated.
 */
uint8_t cycle_check();

/*
 * Resets the total numbers of cycles that has elapsed for each tone to zero
 *
 * Parameters:
 * 	None
 *
 * Returns:
 *  None.
 */
void reset_current_cycle();

/*
 * Updates the source address and the byte count for the DMA to process.
 * We use this when we switch tones.
 *
 * Parameters:
 * 	None
 *
 * Returns:
 *  The number of cycles that has been generated.
 */
void update_DMA_source(uint16_t * source, uint32_t count);
#endif
