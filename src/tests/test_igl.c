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
extern void memory_report(void);

void finish_loop(void) {
    while(1) {
        mouse_event_t evt = mouse_read_event();
        igl_update_mouse(evt);
        if (evt.action == MOUSE_BUTTON_PRESS && evt.middle) break;
    }
    igl_clean();
}
void test_gl_init(void)
{
    igl_init(800, 600, 2,5, GL_BLUE, 40, 90);
    assert(igl_get_res_width() == 800);
    assert(igl_get_res_height() == 600);
    assert(igl_get_c_width() == 40);
    assert(igl_get_c_height() == 90);
    assert(igl_get_row() == 2);
    assert(igl_get_col() == 5);
    igl_clean();
    timer_delay(1);

    igl_init(1920, 1080, 15,7, GL_CYAN, 10, 10);
    assert(igl_get_res_width() == 1920);
    assert(igl_get_res_height() == 1080);
    assert(igl_get_c_width() == 10);
    assert(igl_get_c_height() == 10);
    assert(igl_get_row() == 15);
    assert(igl_get_col() == 7);
    finish_loop();
}

void test_igl_update_mouse(void)
{
    /*Test mouse leaves complex framebuffer undisturbed*/
    printf("Testing mouse leaves complex framebuffer undisturbed\n");
    printf("Press middle mouse to stop\n");
    igl_init(1920, 1080, 10, 10, GL_CYAN, 10, 10);
    gl_draw_triangle(100, 40, 40, 300, 700, 300, GL_RED); 
    gl_draw_line(0, 0, 799, 599, GL_CAYENNE);
    gl_draw_line(799, 0, 0, 599,GL_CAYENNE);
    gl_swap_buffer();
    gl_draw_triangle(100, 40, 40, 300, 700, 300, GL_RED); 
    gl_draw_line(0, 0, 799, 599, GL_CAYENNE);
    gl_draw_line(799, 0, 0, 599,GL_CAYENNE);
    finish_loop();
}

void onclick(igl_component_t* component) {
    printf("Clicked button at x:%d y:%d\n", component->x, component->y);
}
void test_igl_component(void)
{
    int row = 3;
    int col = 3;
    igl_init(800, 600, row , col, GL_RED, 200, 150);
    color_t color = GL_BLACK;
    for (int y = 0; y < row; ++y) {
        for (int x = 0; x < col; ++x) {
            igl_component_t*  i = igl_create_component("C#", x, y, IGL_BUTTON, 
                    (y % 3), color);
            igl_set_onclick(i, onclick);
        }
    }
    finish_loop();
}

void main(void)
{
    uart_init();
    timer_init();
    interrupts_init();
    gpio_init();
    gpio_interrupts_init();
    uart_init();
    interrupts_global_enable(); 
    mouse_init(KEYBOARD_CLOCK, KEYBOARD_DATA);
    printf("Executing main() in test_igl.c\n");

    //test_gl_init();
    //test_igl_update_mouse();
    test_igl_component();

    printf("Completed main() in test_igl.c\n");
    memory_report();
    uart_putchar(EOT);
    pi_reboot();
}
