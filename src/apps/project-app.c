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

#define NROWS 7 
#define NCOLS 11 
extern void memory_report(void);

void finish_loop(void) {
    while(1) {
        mouse_event_t evt = mouse_read_event();
        igl_update_mouse(evt);
        if (evt.action == MOUSE_BUTTON_PRESS && evt.middle) break;
    }
    igl_clean();
}

void setup_ui(void)
{
    int cell_width = ((gl_get_char_width() + 5) * 2);
    int cell_height = ((gl_get_char_height() + 5) * 2);
    unsigned int width =   cell_width * NCOLS;
    unsigned int height =   cell_height * NROWS;
    igl_init(width, height, NROWS, NCOLS, GL_BLACK,
            (gl_get_char_width() * 2), (gl_get_char_height() * 2));

    for (int y = 0; y < NROWS; ++y) {
        for (int x = 0; x < NCOLS; ++x) {
            igl_component_t*  i = igl_create_component("C#", x, y, IGL_BUTTON, 
                    (y % 3), gl_color(55, 0, 179));
        }
    }
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
