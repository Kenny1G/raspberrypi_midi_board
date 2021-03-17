#include "igl_component.h"
#include "malloc.h"
#include "strings.h"
#include "timer.h"
#include "printf.h"

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
            gl_draw_triangle(x + w/2, y, x, y + h, x + w, y + h, c);
            break;
    }
}

