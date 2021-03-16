#include "igl_mouse.h"
#include "malloc.h"

static igl_mouse_t mp;

void igl_mouse_init(unsigned int res_width, unsigned int res_height,
        unsigned int pointer_size, color_t cursor_color)
{
    /*Initialize mouse*/
    mp.x = res_width / 2;
    mp.y = res_height / 2;
    mp.pointer_size = pointer_size;
    mp.pixels_beneath =
      malloc(sizeof(color_t) * pointer_size * pointer_size);
    cursor_color = GL_BLACK;
    gl_draw_rect(mp.x, mp.y, pointer_size, pointer_size, cursor_color);
}

void igl_mouse_clean(void)
{
    free(mp.pixels_beneath);
}

static void redraw_mouse(mouse_event_t evt)
{
}

int igl_mouse_update(mouse_event_t evt)
{
    if (evt.action == MOUSE_DRAGGED || evt.action == MOUSE_MOVED)
    { redraw_mouse(evt); }
    return 0;
}
