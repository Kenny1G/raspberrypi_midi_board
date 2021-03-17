#ifndef SOUND_H_
#define SOUND_H_

#include <stdmath>
/*
 * Functions for a bare metal Raspberry Pi 
 * that handles tones and sounds of output
 * Author: Rebecca Jia and Omar Ramos <ramos16@stanford.edu> 
 * Date: Mar 16, 2021
 */

/*
* Creates and allocates the space for a sin wave at a given frequency for a duration in seconds
* @param freq	      frequency of the note wanted in Hz
* @param duration     duration in seconds for the frequency
* @return             returns a pointer to an array with discrete sin values
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
