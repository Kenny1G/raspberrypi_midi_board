#include "debug.h"
#include "printf.h"
#include "malloc.h"
#include "strings.h"

void debug_print_pixels_beneath(igl_mouse_t mp) {
    int iRet = mp.pointer_size;
    for (int y = 0; y < iRet; ++y) {
        for (int x = 0; x < iRet; ++x)
            printf("%x ", mp.pixels_beneath[(y* iRet) + x]);
        printf("\n");
    }
}

void debug_print_mouse_meta(igl_mouse_t mp)
{
    printf("mouse at: x: %d, y: %d \n", mp.x, mp.y);
}

void debug_print_mouse_event(mouse_event_t evt) {
    char* action = malloc(8);
    memset(action, 0, 8);
    strlcat(action, 
            (evt.action == MOUSE_BUTTON_PRESS)? "Press" :
            (evt.action == MOUSE_BUTTON_RELEASE)? "Release":
            (evt.action == MOUSE_DRAGGED)? "Dragged": "Moved", 8);

    printf("action: %s, dx: %d, dy: %d, "
           "x_overflow: %d, y_overflow: %d, "
           "left: %d, middle: %d, right: %d\n",
           action, evt.dx, evt.dy, evt.x_overflow,
           evt.y_overflow, evt.left, evt.middle, evt.right );
    free(action);
}
