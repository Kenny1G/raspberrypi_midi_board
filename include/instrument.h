#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

/*
 * Functions and definitions for the sound parts of the user interface.
 * Includes defining a note struct with relevant info such as:
 * - note name
 * - time of play
 * - sine wave that defines the note
 * - pitch
 * Also includes function that plays the sequence of notes.
 * Reach goals: 
 * - include a function that accounts for chords
 * - implementing pitch
 *
 * Author: Rebecca Jia <rrjia@stanford.edu>
 * Date: Mar 16, 2021
 */

#include <stdint.h>

/*
 * Struct definition for a note configuration
 */
typedef struct {
    unsigned char note_name; //name of the note
    unsigned int note_duration; //time of play of the note (should be multiple of 4)
    const uint16_t waveform[]; //sine wave unique to the note
    unsigned int pitch; //specifies the pitch/octave of the note
} note_config_t;

/*
 * Receives a pointer to the beginning of an array of note 
 * configurations and plays the sequence of notes
 * 
 * @param note_sequence   a pointer to the beginning of an array of note configs
 * @param seq_len         length of note_sequence
*/
void play_notes(note_config_t *note_sequence, unsigned int seq_len);

#endif