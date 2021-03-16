#ifndef IGL_MOUSE_H_
#define IGL_MOUSE_H_

#include "gl.h"
#include "mouse.h"


typedef struct {
    unsigned int pointer_size;
    int x;
    int y;
    color_t* pixels_beneath;

} igl_mouse_t;

void igl_mouse_init(unsigned int res_width, unsigned int res_height,
        unsigned int pointer_size, color_t cursor_color);
int igl_update_mouse(mouse_event_t evt);
#endif
