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
    void* aux_data;
    int rotation;
};

/*A viewpane is a component spread across multiple rows and columns*/
typedef struct {
    igl_component_t *component;
    int nrows;
    int ncols;
}igl_viewpane_t;

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
 * Creates and draws a new viewpane that goes from the components x and y
 * to end_x and y
 *
 * @param component         component to create viewpane from
 * @param end_x             end x coordinate of view pane
 * @param end_y             end y coordinate of view pane       
 */
void igl_component_new_viewpane(igl_component_t *component, int end_x, int end_y);

/*
 * Draws `component` to the framebuffer based on it's current state
 */
void igl_component_draw(igl_component_t* component);

#endif
