#ifndef SOUND_H_
#define SOUND_H_
/*
 * Functions for a bare metal Raspberry Pi 
 * that handles tones and sounds of output
 * Author: Rebecca Jia and Omar Ramos <rrjia@stanford.edu> 
 * Date: Mar 16, 2021
 */

/**********************************************************
 * TO-DO Omar: ADD DETAILS TO DESCRIPTIONS BELOW WHERE 
 * NECESSARY
**********************************************************/

/*
* TO-DO OMAR: Function description
*/
int* tonesinwave(unsigned int freq, unsigned int duration);

/*
* Superpositions the two tones
*
* @param firsttone    pointer to the start of first tone
* @param secondtone   pointer to the start of second tone
* @param aWeight      weight given to each value of first tone
* @param bWeight      weight given to each value of second tone
* @return             returns a pointer to the new wave
*/
int* superposition(int* firsttone, int* secondtone, int aWeight, int bWeight);

/*
* Creates tones with harmonics
* @ param freq        frequency
* @ param duration    duration
* @ return            pointer to combined superposition of tone and harmonics
*/
int* toneswithharmonics(unsigned int freq, unsigned int duration);

#endif //sound.h