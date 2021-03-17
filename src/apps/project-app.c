#include "assert.h"
#include "igl.h"
#include "uart.h"
#include "pi.h"
#include "malloc.h"
#include "printf.h"
#include "timer.h"
#include "interrupts.h"
#include "gpio_interrupts.h"
#include "keyboard.h"
#include "instrument.h"

#define NROWS 6 
#define NCOLS 11
extern void memory_report(void);

static const char* NOTES[] = {"A", "A#", "B", "C", "C#", "D",
                       "D#", "E", "F", "F#", "G","G#"};
static const char* DURATIONS[] = {"WN", "HN", "QN", "EN"};

void finish_loop(void) {
    while(1) {
        mouse_event_t evt = mouse_read_event();
        igl_update_mouse(evt);
        if (evt.action == MOUSE_BUTTON_PRESS && evt.middle) break;
    }
    igl_clean();
}

void setup_note_buttons(void)
{
    int c = 0;
    int y_start = 0;
    int x_start = 3;
    int nrows = 3;
    int ncols = 4;
    /*Populate igl with note components*/
    for (int y = y_start; y < y_start + nrows; ++y) {
        for (int x = x_start; x < x_start + ncols; ++x) {
            /*
             * Auxiliary data to note commponent is 
             * the relative position of the notes
             */
            int * aux = malloc(sizeof(int) * 3);
            aux[0] = x - x_start;
            aux[1] = y - y_start;
            aux[2] = ncols;
            igl_component_t*  i = igl_create_component(NOTES[c++], x, y, 
                    IGL_BUTTON, IGL_CHAR, gl_color(55, 0, 179));
            igl_set_aux(i, aux);
            igl_set_onclick(i, instrument_note_onclick);
        }
    }

    igl_component_t*  pitch_up= igl_create_component("pitch_up", 7, 1, 
            IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(pitch_up, instrument_pitch_up_onclick);

    igl_set_next_rotation(180);
    igl_component_t*  pitch_down= igl_create_component("pitch_down", 7, 2, 
            IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(pitch_down, instrument_pitch_down_onclick);
}

void setup_time_buttons(void)
{
    int c = 0;
    int y_start = 0;
    int x_start = 0;
    int duration = 1;
    for (int y = y_start; y <= y_start + 1; ++y) {
        for (int x = x_start; x <= x_start + 1; ++x) {
            /*
             * Auxiliary to duration component is 
             * the time of play of the choord
             */
            int *aux = malloc(sizeof(int));
            aux[0] = duration;
            duration *= 2;
            igl_component_t*  i = igl_create_component(DURATIONS[c++], x, y, 
                    IGL_BUTTON, IGL_CHAR, gl_color(55, 0, 179));
            igl_set_aux(i, aux);
            igl_set_onclick(i, instrument_duration_onclick);
        }
    }
    igl_component_t* set_frame= igl_create_view_pane
        ("set_frame", 0, 2, 1, 2, gl_color(55,0, 179));
    igl_set_onclick(set_frame, instrument_set_frame_onclick);
}

void setup_music_frame(void)
{
    igl_component_t* prev_frame = igl_create_view_pane
        ("prev_frame", 2, 3, NCOLS - 4, 3, gl_color(55,0, 179));
    igl_component_t* curr_frame = igl_create_view_pane
        ("curr_frame", 2, 4, NCOLS - 4, 4, gl_color(55,0, 179));
    igl_component_t* next_frame = igl_create_view_pane
        ("next_frame", 2, 5, NCOLS - 4, 5, gl_color(55,0, 179));

    igl_component_t*  scroll_up= igl_create_component("scroll_up",
            NCOLS - 3, 4, IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(scroll_up, instrument_scroll_up_onclick);

    igl_set_next_rotation(180);
    igl_component_t*  scroll_down= igl_create_component("scroll_down",
            NCOLS - 3, 5, IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(scroll_down, instrument_scroll_down_onclick);

    igl_set_next_rotation(90);
    igl_component_t*  play_frame = igl_create_component("play_frame",
            NCOLS - 2, 4, IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(play_frame, instrument_play_frame_onclick);

    igl_set_next_rotation(90);
    igl_component_t*  play_all = igl_create_component("play_all",
            NCOLS - 1, 5, IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(play_all, instrument_play_all_onclick);
}
void setup_ui(void)
{
    int scale = 3;
    int cell_width = ((gl_get_char_width() + 5) * scale);
    int cell_height = ((gl_get_char_height() + 5) * scale);
    unsigned int width =   cell_width * NCOLS;
    unsigned int height =   cell_height * NROWS;
    igl_init(width, height, NROWS, NCOLS, GL_BLACK,
            (gl_get_char_width() * scale), (gl_get_char_height() * scale));
    setup_note_buttons();
    setup_time_buttons();
    setup_music_frame();

    finish_loop();
}
void main(void)
{
    interrupts_init();
    gpio_init();
    gpio_interrupts_init();
    timer_init();
    uart_init();
    interrupts_global_enable(); 
    mouse_init(KEYBOARD_CLOCK, KEYBOARD_DATA);

    instrument_init();
    setup_ui();

    memory_report();
    uart_putchar(EOT);
    pi_reboot();
}
