#include "printf.h"
#include "strings.h"
#include "uart.h"
#include "instrument.h"
#include "malloc.h"

#include "timer.h"
#include "gpio.h"

//taken from lecture/CS 107E Winter 2020 class code
#include "pwm.h"
#include "tone.h"
#include "pitch.h"

#define MAX_LENGTH 100

/* Grid of all notes that correspond to components grid*/
static note_t notes[12];
static instrument_config_t cfg;
/*Populates the notes grid with all the musical notes*/
static void populate_notes(void);
static int last_on_note_index = -1;

void instrument_init(void)
{
    /*Initialize space for shell*/
    populate_notes();
    /*piece is an array of choords of max length*/
    cfg.piece = malloc(MAX_LENGTH * sizeof(choord_t*));
    memset(cfg.piece, 0, MAX_LENGTH * sizeof(choord_t*));

    cfg.piece_pitch = malloc(MAX_LENGTH * sizeof(choord_pitch_t*));
    memset(cfg.piece_pitch, 0, MAX_LENGTH * sizeof(choord_pitch_t*));

    cfg.lens = malloc(MAX_LENGTH * sizeof(int));
    memset(cfg.lens, 0, MAX_LENGTH * sizeof(int));

    cfg.current_frame = -1;
    next_frame();
}

static void populate_notes(void)
{
    const char* NOTES[] = {"A", "A#", "B", "C", "C#", "D",
                           "D#", "E", "F", "F#", "G","G#"};
    int base_feqs[12] = {NOTE_A1, NOTE_AS1, NOTE_B0, NOTE_C1, NOTE_CS1,
        NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1};

    for (int i = 0; i < 12; ++i) {
        notes[i].name = NOTES[i];
        notes[i].base_freq = base_feqs[i];
    }
}

instrument_config_t *instrument_get_config(void) { return &cfg; }

void next_frame(void)
{
    cfg.frame_labels[cfg.current_frame] = "F";
    /*12 ints to hold the on state and pitch of each note in a choord*/
    int sz = sizeof(int) * 12;
    cfg.piece[++cfg.current_frame] = malloc(sz);
    memset(cfg.piece[cfg.current_frame], 0, sz);

    cfg.piece_pitch[cfg.current_frame] = malloc(sz);
    for(int i = 0; i < 12; ++i)
        cfg.piece_pitch[cfg.current_frame][i] = 4;
}

/* On click buttons*/
void instrument_note_onclick(igl_component_t *cmpn)
{
    int x = ((int*)cmpn->aux_data)[0];
    int y = ((int*)cmpn->aux_data)[1];
    int ncols = ((int*)cmpn->aux_data)[2];
    int index = (y * ncols) + x;
    /*Toggle the note in the choord*/
    int is_on = cfg.piece[cfg.current_frame][index]; 
    is_on ^= 1;

    /*
     * Set note as last set to on
     * If note is set to off, reset it's pitch to 4
     */
    if (is_on)
        last_on_note_index = index;
    else {
        last_on_note_index = -1;
        cfg.piece_pitch[cfg.current_frame][index] = 4;
    }

    printf("x:%d, y:%d, note work?: %d\n", x, y, is_on);
    cfg.piece[cfg.current_frame][index] = is_on;
}

void instrument_pitch_change_onclick(igl_component_t *cmpn)
{
    int change = *(int*)cmpn->aux_data;
    if (last_on_note_index != -1) {
        int iRet = cfg.piece_pitch[cfg.current_frame][last_on_note_index];
        iRet += change;
        /*Cap pitch at 1 and 8*/
        if (iRet < 1 || iRet > 8)
            return;
        printf("change: %d, index:%d, pitch:%d\n",
                change, last_on_note_index, iRet); 
        cfg.piece_pitch[cfg.current_frame][last_on_note_index] = iRet;
    }
}

void instrument_duration_onclick(igl_component_t *cmpn)
{
    int duration = *((int*)cmpn->aux_data);
    /*Set frames duration*/
    cfg.lens[cfg.current_frame] = duration;
    printf("duration work?: %d\n",
        cfg.lens[cfg.current_frame]);
}

void instrument_set_frame_onclick(igl_component_t *cmpn) {}

void instrument_frame_onclick(igl_component_t *cmpn){}
void instrument_scroll_up_onclick(igl_component_t *cmpn){}
void instrument_scroll_down_onclick(igl_component_t *cmpn){}
void instrument_play_frame_onclick(igl_component_t *cmpn){}
void instrument_play_all_onclick(igl_component_t *cmpn){}

/*
//written with the help of referencing melody.c from lecture (the gitHub path is cs107e.github.io/lectures/Sensors/code/sound/melody/melody.c)
void play_notes(note_t *note_sequence, unsigned int seq_len) 
{
    timer_init();

    gpio_init();
    gpio_set_function( 40, GPIO_FUNC_ALT0 ); // PWM0
    gpio_set_function( 45, GPIO_FUNC_ALT0 ); // PWM1
    gpio_set_function( 18, GPIO_FUNC_ALT5 ); // PWM0

    pwm_init();
    pwm_set_clock( F_AUDIO );

    //play the sequence of notes
    for (unsigned int curr_note = 0; curr_note < seq_len; curr_note++) {
        //save the type of the current note (quarter note, eighth note, etc)
        unsigned int this_note_type = *note_sequence -> note_len;

        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int note_dur = 1000/this_note_type;



        //TO-DO: DELETE THIS STUFF BECAUSE MIGHT NOT WORK
        // //the beginning of the string that we will concatenate onto for the note/pitch
        // //size is 8, because for example "NOTE_C4" has 7 chars, and the last index holds the null terminator
        // unsigned char beginning[8] = "NOTE_";

        // //we will append onto specific_note in order to get the full string that represents the note/pitch identity
        // char *specific_note = beginning;
        
        //TO-DO: FIGURE A WAY TO INDEX INTO AN ARRAY OF THE NOTE PITCHES AND THEN PASS IN THAT VALUE INTO tone() BELOW
        tone();




        timer_delay_ms(note_dur);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = note_dur * 0.30;
        tone(0); // 0 turns off sound
        timer_delay_ms(pauseBetweenNotes);
    }
    
}
*/
