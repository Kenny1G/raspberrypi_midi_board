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

void debug_print_igl_grid(igl_config_t cfg) 
{
    for (int y = 0; y < cfg.row; ++y) {
        for (int x = 0; x < cfg.col; ++x) {
            int index = (y * cfg.col) + x;
            igl_component_t *cmpn = cfg.grid[index];
            if (cmpn != 0)
                printf("%s ",cfg.grid[index]->name);
            else
                printf("NA ");
        }
        printf("\n");
    }
}

void debug_print_component_meta(igl_component_t *c)
{
    if (c == 0) {
        printf("NA\n");
        return;
    }
    igl_component_t comp = *c;
    printf("\nname: %s, x:%d y:%d, width:%d, height:%d, color:%x, shape:%d, "
            "type:%d, fn:%x, alt_color:%x, highlight:%d, hover:%d, aux_data:%x, "
            "rotation:%d\n", 
            comp.name,
            comp.x,
            comp.y,
            comp.width,
            comp.height,
            comp.color,
            comp.shape,
            comp.type,
            (unsigned int)comp.fn,
            comp.alt_color,
            comp.highlight,
            comp.hover,
            (unsigned int)comp.aux_data,
            comp.rotation);
}
void debug_print_viewpane_meta(igl_viewpane_t *vp)
{
    if (vp == 0) {
        printf("NA\n");
        return;
    }
    igl_viewpane_t comp = *vp;
    printf("\ncomponent: %x, nrows: %d, ncols: %d, buffer: %s, bufsize: %d, start_y: %d, padding_x: %d, padding_y: %d\n",
    (unsigned int) comp.component,
    comp.nrows,
    comp.ncols,
    *comp.buffer,
    comp.bufsize,
    comp.start_y, //row of buffer to start displaying from
    comp.padding_x,
    comp.padding_y);
}
