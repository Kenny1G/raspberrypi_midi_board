#ifndef IGL_COMPONENT_H_
#define IGL_COMPONENT_H_

#include <stdbool.h>
#include "gl.h"

typedef enum {IGL_BUTTON, IGL_VIEW_PANE, IGL_TEXT_FIELD} igl_cmpn_type_t;
typedef enum {IGL_BTN_RECT, IGL_BTN_TRIA, IGL_BTN_CHAR} igl_cmpn_shape_t;

/*Typedef for type of function used as an onclick event handler*/
typedef int (*onclick_fn_t)(void);
typedef struct {
    const char *name;
    igl_cmpn_type_t type;
    int x;
    int y;
    unsigned int width;
    unsigned int height;
    igl_cmpn_shape_t shape;
    onclick_fn_t fn;
    bool highlight;
    bool hover;
    color_t alt_color;
} igl_component_t;

igl_component_t *igl_component_new();
#endif
