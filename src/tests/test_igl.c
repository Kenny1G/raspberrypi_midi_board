#include "assert.h"
#include "igl.h"
#include "uart.h"
#include "pi.h"
#include "malloc.h"
#include "printf.h"
#include "timer.h"
extern void memory_report(void);

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
