#include "assert.h"
#include "igl.h"
#include "uart.h"
#include "pi.h"
#include "malloc.h"
#include "printf.h"
#include "timer.h"
extern void memory_report(void);

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
    igl_clean();
}

void test_gl_update_mouse(void)
{
    /*Test mouse leaves complex framebuffer undisturbed*/
}
void main(void)
{
    uart_init();
    timer_init();
    printf("Executing main() in test_igl.c\n");

    /*TODO(kenny): tests R' Us*/
    test_gl_init();

    printf("Completed main() in test_igl.c\n");
    memory_report();
    uart_putchar(EOT);
    pi_reboot();
}
