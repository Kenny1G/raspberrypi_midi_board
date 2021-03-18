/* Driver Program*/
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
#include "debug.h"

#define NROWS 6 
#define NCOLS 11
extern const int MAX_INSTRUMENT_FRAMES;
extern void memory_report(void);

static const char* NOTES[] = {"A", "A#", "B", "C", "C#", "D",
                       "D#", "E", "F", "F#", "G","G#"};
static const char* DURATIONS[] = {"WN", "HN", "QN", "EN"};
static instrument_config_t *instrument_config;

void finish_loop(void) {
    while(1) {
        mouse_event_t evt = mouse_read_event();
        igl_update_mouse(evt);
        if (evt.action == MOUSE_BUTTON_PRESS && evt.middle) break;
    }
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

    /*Buttons to increase and decrease pitch of notes*/
    igl_component_t*  pitch_up= igl_create_component("pitch_up", 7, 1, 
            IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(pitch_up, instrument_pitch_change_onclick);
    int *up = malloc(sizeof(int));
    up[0] = 1;
    igl_set_aux(pitch_up, up);

    igl_set_next_rotation(180);
    igl_component_t*  pitch_down= igl_create_component("pitch_down", 7, 2, 
            IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(pitch_down, instrument_pitch_change_onclick);
    int *down = malloc(sizeof(int));
    down[0] = -1;
    igl_set_aux(pitch_down, down);
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
}

void setup_music_frame(void)
{
    igl_component_t* frame = igl_create_view_pane
        ("frame", 0, 3, NCOLS - 2, 5, gl_color(55,0, 179));
    igl_set_viewpane_buffer(frame, instrument_config->frame_labels,
            MAX_INSTRUMENT_FRAMES);
    if (frame == 0)
        printf("Error creating frame \n");

    /* Button used for saving a frame is initially a viewpane becuase 
     * we want it to span two columns cause that looks prettier*/
    igl_component_t* set_frame= igl_create_view_pane
        ("set_frame", 0, 2, 1, 2, gl_color(55,0, 179));
    igl_set_onclick(set_frame, instrument_set_frame_onclick);
    igl_component_draw_on_pane(set_frame, "FRAME");
    /*
     * Because this button is a viewpane, it's aux_data
     * initially points to a view pane we free that and
     * it to frame so when it's clicked it can update the frame
     * when it is clicked
     */
    printf("frame aux: %x\n",(unsigned int)set_frame->aux_data);
    free(set_frame->aux_data);
    igl_set_aux(set_frame, frame);


    igl_component_t*  scroll_up= igl_create_component("scroll_up",
            NCOLS - 1, 4, IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(scroll_up, instrument_scroll_up_onclick);

    igl_set_next_rotation(180);
    igl_component_t*  scroll_down= igl_create_component("scroll_down",
            NCOLS - 1, 5, IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(scroll_down, instrument_scroll_down_onclick);
}

void setup_play(void)
{
    igl_set_next_rotation(90);
    igl_component_t*  play_frame = igl_create_component("play_frame",
            NCOLS - 4, 0, IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
    igl_set_onclick(play_frame, instrument_play_frame_onclick);

    igl_set_next_rotation(90);
    igl_component_t*  play_all = igl_create_component("play_all",
            NCOLS - 1, 3, IGL_BUTTON, IGL_TRIA, gl_color(55, 0, 179));
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
    setup_play();

    finish_loop();
    igl_clean();
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
    instrument_config = instrument_get_config();
    setup_ui();
    instrument_clean();

    memory_report();
    uart_putchar(EOT);
    pi_reboot();
}
