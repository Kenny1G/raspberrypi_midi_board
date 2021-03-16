#ifndef IGL_H_
#define IGL_H_
/*
 * Functions for a bare metal Raspberry Pi interactive graphics library
 * that creates buttons, view panes, and handles mouse clicks. Builds
 * on the baremetal graphics library gl.[ch] for framebuffer
 * access and configuration; trying to use both igl and gl
 * simultaneously is discouraged. Basically budget QT
 *
 * Author: Kenny Oseleononmen Jr. <kenny1g@stanford.edu>
 * Date: Mar 15 2021
 */

#include "mouse.h"
#include "igl_mouse.h"
#include "igl_component.h"

typedef struct {
    unsigned int row; //num of rows in representational grid
    unsigned int col; //num of columns in representational grid
    unsigned int c_width; //width of each component
    unsigned int c_height;//height of each component
    igl_mouse_t* mp; //mouse pointer
    igl_component_t* grid; //pointer to 2d array of components
    color_t background;
    color_t cursor_color;
} igl_config_t;

/*
 * Initialize interactive graphic library. calculates the
 * required resolution to house a row by col grid
 * minimum resolution is 800 x 600
 *
 * @param res_width  width of resolution
 * @param res_height height of resolution
 * @param row        number of rows of the grid
 * @param col        number of columns of the grid
 * @param background background color
 * @param c_width    width of each component grid
 * @param c_height   height of each component grid
 * @return     0 if successful non-zero otherwise
 */
void igl_init(unsigned int res_width, unsigned int res_height,
        unsigned int row, unsigned int col, color_t background,
        unsigned int c_width, unsigned int c_height);

/*
 * Updates the component grid and user module based on
 * mouse event `evt`
 *
 * @param evt   mouse event
 * @return      0 if successful non-zero otherwise
 */
int igl_update_mouse(mouse_event_t evt);

/*
 * Frees all memory igl malloced
 *
 * Mostly used for testing purposes
 */
void igl_clean(void);

/*
 * Returns config
 *
 * @return      igl_config_t created in init
 */
igl_config_t* igl_get_config(void);

/*
 * Creates a component that spans width rows and
 * height columns at grid locations x, y
 *
 * components start as just viewable (unclickable, unhighlightable, etc.)
 *
 * @param x         grid x location of component
 * @param y         grid y location of component
 * @param width     num of columns component spans
 * @param height    num of rows component spans
 * @param type      component type
 * @param color     color of component
 * @returns         pointer to the component, NULL if unsuccessful
 */
igl_component_t*  igl_create_component(int x, int y, 
        unsigned int width, unsigned int height,
        igl_cmpn_type_t type, igl_cmpn_shape_t shape, color_t color);

/*
 * Sets `component` to be clickable and registers fn
 * as its on click function
 * 
 * @param component     component to set to clickable
 * @param fn            function to be called when component is clicked
 * @return              0 if successful non-zero otherwise
 */
int igl_set_onclick(igl_component_t* component, onclick_fn_t fn);

/* Getters for igl dimensions */
unsigned int igl_get_res_width(void);
unsigned int igl_get_res_height(void);
unsigned int igl_get_c_width(void);
unsigned int igl_get_c_height(void);
unsigned int igl_get_row(void);
unsigned int igl_get_col(void);
#endif //igl.h
