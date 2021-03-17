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
#include "igl_component.h"

/*
 * Struct definition for a note configuration
 */
typedef struct {
    unsigned char note_name; //name of the note
    unsigned char sharp_state; //'S' for a sharp note, 'N' for a normal note
    const uint16_t *waveform; //sine wave unique to the note
    unsigned int pitch; //specifies the pitch/octave of the note
} note_t;

typedef int* choord_t; //A choord is a grid of bools that correspond to notes grid

typedef struct {
    choord_t* piece; //Array of choords that make up the musical piece
    unsigned int* lens; //Array of time of play of each choord(should be multiple of 4)
    int current_frame;
} instrument_config_t;

/*
 * Initializes an instrument. mallocs the arrays to hold the choords
 * of the pieces and their length and populates the notes grid
 */
void instrument_init(void);

/*
 * Allocates space for the next frame and updates
 * cfg.current_frame
 */
void next_frame(void);

/*
 * Onclick function for when a note component is clicked
 *
 * @param cmpn      note component that is clicked
 */
void instrument_note_onclick(igl_component_t *cmpn);

/*
 * Onclick function for when a duration component is clicked
 *
 * @param cmpn      duration commponent that is clicked
 */
void instrument_duration_onclick(igl_component_t *cmpn);

void instrument_pitch_up_onclick(igl_component_t *cmpn);
void instrument_pitch_down_onclick(igl_component_t *cmpn);
void instrument_set_frame_onclick(igl_component_t *cmpn);
void instrument_frame_onclick(igl_component_t *cmpn);
void instrument_scroll_up_onclick(igl_component_t *cmpn);
void instrument_scroll_down_onclick(igl_component_t *cmpn);
void instrument_play_frame_onclick(igl_component_t *cmpn);
void instrument_play_all_onclick(igl_component_t *cmpn);

/*
 * Receives a pointer to the beginning of an array of note 
 * configurations and plays the sequence of notes
 * 
 * @param note_sequence   a pointer to the beginning of an array of note configs
 * @param seq_len         length of note_sequence
*/
void play_notes(note_t *note_sequence, unsigned int seq_len);

#endif
