#ifndef IGL_COMPONENT_H_
#define IGL_COMPONENT_H_

#include <stdbool.h>
#include "gl.h"

typedef enum {IGL_BUTTON, IGL_VIEW_PANE, IGL_TEXT_FIELD} igl_component_type_t;
typedef enum {IGL_RECT, IGL_TRIA, IGL_CHAR} igl_component_shape_t;

typedef struct igl_component igl_component_t;
/*Typedef for type of function used as an onclick event handler*/
typedef void (*onclick_fn_t)(igl_component_t*);

struct  igl_component{
    /*Necessary attributes*/
    const char *name;
    int x;
    int y;
    unsigned int width;
    unsigned int height;
    color_t color;
    igl_component_shape_t shape;
    igl_component_type_t type;

    /*Unnecessary attributes*/
    onclick_fn_t fn;
    color_t alt_color;
    bool highlight;
    bool hover;
};

/*
 * Initializes a new igl component and returns a pointer to it
 *
 * @param name:     name of the component/string that'll be drawn if type char
 * @param x:        x coord of component
 * @param y:        y coord of component
 * @param width:    width of component
 * @param height:   height of component
 * @param type:     type of component (button, pane or text field)
 * @param shape:    shape of component (rectangle, triangle or characters)
 * @param color:    color of component
 * @return          pointer to new component or NULL if failed to create
 */ 
igl_component_t *igl_component_new(const char* name, int x, int y,
        unsigned int width, unsigned int height,
        igl_component_type_t type, igl_component_shape_t shape,
        color_t color);

/*
 * Draws `component` to the framebuffer based on it's current state
 */
void igl_component_draw(igl_component_t* component);
#endif