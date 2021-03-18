#include "igl_component.h"
#include "malloc.h"
#include "strings.h"
#include "timer.h"
#include "printf.h"
#include "debug.h"

igl_component_t *igl_component_new(const char* name, int x, int y,
        unsigned int width, unsigned int height,
        igl_component_type_t type, igl_component_shape_t shape,
        color_t color)
{
    igl_component_t *cmp = malloc(sizeof(igl_component_t));
    memset(cmp, 0, sizeof(igl_component_t));
    cmp->name = name;
    cmp->x = x;
    cmp->y = y;
    cmp->width = width;
    cmp->height= height;
    cmp->type = type;
    cmp->shape = shape;
    cmp->color = color;
    cmp->rotation = 0;
    return cmp;
}

void igl_component_draw(igl_component_t* component)
{
    unsigned int w = component->width;
    unsigned int h = component->height;
    unsigned int x = component->x;
    unsigned int y = component->y;
    color_t c = component->color;
    color_t alt_c = (component->alt_color)? component->alt_color : ~c;
    unsigned int num_can_take = w / gl_get_char_width();
    unsigned int char_offset = ((num_can_take - strlen(component->name))/2) 
        * gl_get_char_width();

    switch(component->shape) {
        case IGL_RECT:
            gl_draw_rect(x, y, w, h, c);
            break;
        case IGL_CHAR:
            gl_draw_rect(x, y, w, h, c);
            gl_draw_string(x + char_offset, y + h/2, component->name, alt_c);
            break;
        case IGL_TRIA:
            if (component->rotation == 0) {
                gl_draw_triangle(x + w/2, y, x, y + h, x + w, y + h, c);
            }
            else if (component->rotation == 90) {
                gl_draw_triangle(x, y, x, y + h, x + w, y + h/2, c);
            }
            else if (component->rotation == -90) {
                gl_draw_triangle(x + w, y, x, y + h/2, x + w, y + h, c);
            }
            else if (component->rotation == 180) {
                gl_draw_triangle(x + w/2, y + h, x, y, x + w, y, c);
            }
            break;
    }
}

void igl_component_new_viewpane(igl_component_t *component,
        int end_x, int end_y, int nrows, int ncols) 
{
    igl_viewpane_t * viewpane = malloc(sizeof(igl_viewpane_t));
    component->aux_data = viewpane;
    viewpane->component = component;
    viewpane->nrows = nrows;
    viewpane->ncols = ncols;
    printf("viewpane cols: %d rows: %d\n",ncols, nrows);
    component->type = IGL_VIEW_PANE;
    unsigned int width = (end_x - component->x) + component->width;
    unsigned int height = (end_y - component->y) + component->height;

    igl_component_t dummy = {"", component->x, component->y,
        width, height, component->color, IGL_RECT};
    igl_component_draw(&dummy);

}

void igl_component_draw_on_pane(igl_component_t* component, 
        const char* label)
{ 
    igl_viewpane_t *vp = (igl_viewpane_t*)component->aux_data;
    unsigned int width = component->width * vp->ncols;
    unsigned int height = component->height * vp->nrows;
    igl_component_t dummy = {label, component->x, component->y,
        width, height, component->color, IGL_CHAR, 0, 0, component->alt_color};
    debug_print_component_meta(dummy);

    igl_component_draw(&dummy);
}
