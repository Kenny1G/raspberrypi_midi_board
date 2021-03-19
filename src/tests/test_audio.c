#include "uart.h"
#include "timer.h"
#include "printf.h"
#include "pi.h"
#include "malloc.h"

extern void memory_report(void);
void main(void)
{
    uart_init();
    timer_init();
    uart_init();
    printf("Executing main() in test_audio.c\n");


    printf("Completed main() in test_audio.c\n");
    memory_report();
    uart_putchar(EOT);
    pi_reboot();
}
