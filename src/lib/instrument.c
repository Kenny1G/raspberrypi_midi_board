#include "instrument.h"
#include "printf.h"
#include "strings.h"
#include "uart.h"
#include "malloc.h"
#include "debug.h"

#include "timer.h"
#include "gpio.h"

//taken from lecture/CS 107E Winter 2020 class code
#include "pwm.h"
#include "tone.h"
#include "pitch.h"
#include "igl.h"


/* Grid of all notes that correspond to components grid*/
static note_t notes[12];
static instrument_config_t cfg;
/*Populates the notes grid with all the musical notes*/
static void populate_notes(void);
static int last_on_note_index = -1;
const int MAX_INSTRUMENT_FRAMES = 100;

static const char* NOTES[] = {"A", "A#", "B", "C", "C#", "D",
                       "D#", "E", "F", "F#", "G","G#"};

void instrument_init(void)
{
    /*Initialize pwm */
    gpio_set_function( 40, GPIO_FUNC_ALT0 ); // PWM0
    gpio_set_function( 45, GPIO_FUNC_ALT0 ); // PWM1
    gpio_set_function( 18, GPIO_FUNC_ALT5 );

    pwm_init();
    pwm_set_clock( F_AUDIO );

    /*Initialize space for shell*/
    populate_notes();
    /*piece is an array of choords of max length*/
    cfg.piece = malloc(MAX_INSTRUMENT_FRAMES * sizeof(choord_t*));
    memset(cfg.piece, 0, MAX_INSTRUMENT_FRAMES * sizeof(choord_t*));

    cfg.piece_pitch = malloc(MAX_INSTRUMENT_FRAMES * sizeof(choord_pitch_t*));
    memset(cfg.piece_pitch, 0, MAX_INSTRUMENT_FRAMES * sizeof(choord_pitch_t*));

    cfg.lens = malloc(MAX_INSTRUMENT_FRAMES * sizeof(int));
    for (int i = 0; i < MAX_INSTRUMENT_FRAMES; ++i) {
        cfg.lens[i] = 1;
    }

    cfg.frame_labels  = malloc(MAX_INSTRUMENT_FRAMES * sizeof(char*));
    memset(cfg.frame_labels, 0, MAX_INSTRUMENT_FRAMES * sizeof(char*));

    cfg.current_frame = -1;
    next_frame();

}

void instrument_clean()
{
    int i = cfg.current_frame;
    while (i >= 0) {
        free(cfg.piece_pitch[i]);
        free(cfg.frame_labels[i]);
        free(cfg.piece[i--]);
    }
    free(cfg.piece);
    free(cfg.piece_pitch);
    free(cfg.frame_labels);
    free(cfg.lens);
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
    /*12 ints to hold the on state and pitch of each note in a choord*/
    int sz = sizeof(int) * 12;
    cfg.piece[++cfg.current_frame] = malloc(sz);
    memset(cfg.piece[cfg.current_frame], 0, sz);

    cfg.piece_pitch[cfg.current_frame] = malloc(sz);
    for(int i = 0; i < 12; ++i)
        cfg.piece_pitch[cfg.current_frame][i] = 4;

    cfg.frame_labels[cfg.current_frame] = malloc(3);
    memset(cfg.frame_labels[cfg.current_frame], 0, 3);
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
    if (is_on) {
        cfg.frame_labels[cfg.current_frame][0] = notes[index].name[0];
        cfg.frame_labels[cfg.current_frame][1] = notes[index].name[1];
        last_on_note_index = index;
        igl_mouse_set_x(0);
        igl_mouse_set_y(0);

        igl_component_t dummy = {cmpn->name, cmpn->x, cmpn->y, cmpn->width,
            cmpn->height, cmpn->alt_color, IGL_CHAR, 0, 0, cmpn->color};
        igl_component_draw(&dummy);
        debug_print_component_meta(cmpn);

    }
    else {
        last_on_note_index = -1;
        cfg.piece_pitch[cfg.current_frame][index] = 4;
    }

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
        cfg.piece_pitch[cfg.current_frame][last_on_note_index] = iRet;
    }
}

void instrument_duration_onclick(igl_component_t *cmpn)
{
    int duration = *((int*)cmpn->aux_data);
    /*Set frames duration*/
    cfg.lens[cfg.current_frame] = duration;
}

static void reset_notes_view(void)
{
    int c = 0;
    for (int y = 0; y < 3; ++y) {
        for (int x = 3; x < 7; ++x) {
            int start_x, start_y;
            igl_get_start(x, y, &start_x, &start_y);
            color_t purp = gl_color(55, 0, 179);
            igl_component_t dummy = {NOTES[c++], start_x, start_y, igl_get_c_width(), igl_get_c_height(), purp, IGL_CHAR, 0, 0, ~purp};
            igl_component_draw(&dummy);
        }
    }
}
void instrument_set_frame_onclick(igl_component_t *cmpn) 
{
    next_frame();
    igl_component_update_viewpane(cmpn->aux_data);
    reset_notes_view();
}

void instrument_frame_onclick(igl_component_t *cmpn){}

void instrument_scroll_up_onclick(igl_component_t *cmpn)
{
    igl_viewpane_t *vp = (igl_viewpane_t*)cmpn->aux_data;
    debug_print_viewpane_meta(vp);
    vp->start_y = (vp->start_y == 0)?  vp->start_y : vp->start_y - 1 ;
    igl_component_update_viewpane(vp);
}

void instrument_scroll_down_onclick(igl_component_t *cmpn)
{
    igl_viewpane_t *vp = (igl_viewpane_t*)cmpn->aux_data;
    debug_print_viewpane_meta(vp);
    vp->start_y = (vp->start_y == 10)? vp->start_y : vp->start_y + 1 ;
    igl_component_update_viewpane(vp);
}
void instrument_play_frame_onclick(igl_component_t *cmpn){}

static void play_piece(unsigned int* tones)
{ 
    for (int i = 0; i < cfg.current_frame; ++i) {
        if (tones[i] != 0)
            tone(tones[i]);
        timer_delay_ms(1000 / cfg.lens[i]);
    }
    tone(0);
    free(tones);
}

void instrument_play_all_onclick(igl_component_t *cmpn)
{
    unsigned int* tones = malloc(sizeof(int) * cfg.current_frame);
    memset(tones, 0, sizeof(int) * cfg.current_frame);
    for (int frame = 0; frame < cfg.current_frame; ++frame) {
        /* Since we are only playing one tone we just find a tone
         * that's on and add it to the play queue*/
        for (int i = 0; i < 12; ++i) {
            int is_on = cfg.piece[frame][i];
            note_t note = notes[i];
            int pitch = cfg.piece_pitch[frame][i];
            if (is_on) {
                tones[frame] = note.base_freq * pitch;
            }
        }
    }
    play_piece(tones);
}

