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
    igl_config_t* cfg = igl_get_config();
    free(cfg->grid);
    free(cfg->mp);

    igl_init(1920, 1080, 15,7, GL_CYAN, 10, 10);
    assert(igl_get_res_width() == 800);
    assert(igl_get_res_height() == 600);
    assert(igl_get_c_width() == 40);
    assert(igl_get_c_height() == 90);
    assert(igl_get_row() == 2);
    assert(igl_get_col() == 5);
    cfg = igl_get_config();
    free(cfg->grid);
    free(cfg->mp);
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

    printf("Completed main() in test_igl.c\n");
    memory_report();
    uart_putchar(EOT);
    pi_reboot();
}
