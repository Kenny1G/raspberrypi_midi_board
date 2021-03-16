#ifndef IGL_MOUSE_H_
#define IGL_MOUSE_H_

#include "gl.h"
#include "mouse.h"


typedef struct {
    unsigned int pointer_size;
    int x;
    int y;
    color_t* pixels_beneath;
    color_t cursor_color;
    unsigned int res_width;
    unsigned int res_height;
} igl_mouse_t;

void igl_mouse_init(unsigned int res_width, unsigned int res_height,
        unsigned int pointer_size, color_t cursor_color);
/*
 * Clears cursor moves cursor based on `evt` 
 * and redraws mouse 
 *
 * @param evt       mouse event that triggered redraw
 */
void igl_mouse_update(mouse_event_t evt);
void igl_mouse_clean(void);
int igl_mouse_get_x(void);
int igl_mouse_get_y(void);
#endif
