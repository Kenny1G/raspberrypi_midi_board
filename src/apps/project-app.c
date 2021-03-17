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

#define NROWS 5 
#define NCOLS 10
extern void memory_report(void);
const char* NOTES[] = {"A", "A#", "B", "C", "C#", "D",
                       "D#", "E", "F", "F#", "G","G#"};

const char* DURATIONS[] = {"WN", "HN", "QN", "EN"};

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
    for (int y = y_start; y <= y_start + 2; ++y) {
        for (int x = x_start; x <= x_start + 3; ++x) {
            igl_component_t*  i = igl_create_component(NOTES[c++], x, y, 
                    IGL_BUTTON, IGL_CHAR, gl_color(55, 0, 179));
        }
    }
}

void setup_time_buttons(void)
{
    int c = 0;
    int y_start = 0;
    int x_start = 0;
    for (int y = y_start; y <= y_start + 1; ++y) {
        for (int x = x_start; x <= x_start + 1; ++x) {
            igl_component_t*  i = igl_create_component(DURATIONS[c++], x, y, 
                    IGL_BUTTON, IGL_CHAR, gl_color(55, 0, 179));
        }
    }
}

void setup_ui(void)
{
    int cell_width = ((gl_get_char_width() + 5) * 2);
    int cell_height = ((gl_get_char_height() + 5) * 2);
    unsigned int width =   cell_width * NCOLS;
    unsigned int height =   cell_height * NROWS;
    igl_init(width, height, NROWS, NCOLS, GL_BLACK,
            (gl_get_char_width() * 2), (gl_get_char_height() * 2));
    setup_note_buttons();
    setup_time_buttons();

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

    setup_ui();

    memory_report();
    uart_putchar(EOT);
    pi_reboot();
}
