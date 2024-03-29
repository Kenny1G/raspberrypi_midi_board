#ifndef IGL_H_
#define IGL_H_
/*
 * Functions for a bare metal Raspberry Pi interactive graphics library
 * that creates buttons, view panes, and handles mouse clicks. Builds
 * on the baremetal graphics library gl.[ch] for framebuffer
 * access and configuration; trying to use both igl and gl
 * simultaneously is discouraged... Basically budget QT
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
    igl_component_t** grid; //pointer to 2d array of components
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
 * Creates a component at grid locations x, y
 *
 * components start as just viewable (unclickable, unhighlightable, etc.)
 *
 * @param name      name of component
 * @param x         grid x location of component
 * @param y         grid y location of component
 * @param type      component type
 * @param shape     component shape 
 * @param color     color of component
 * @returns         pointer to the component, NULL if unsuccessful
 */
igl_component_t*  igl_create_component(const char* name, int x, int y,
        igl_component_type_t type, igl_component_shape_t shape,
        color_t color);

/*
 * Creates a view pane component that goes from grid location
 * `start_x`, `start_y` to grid location `end_x`, `end_y`
 *
 * Returns 0 if viewpane will overlap with another component
 *
 * @param name      name of component
 * @param start_x   starting x location of component
 * @param start_y   starting y location of component
 * @param end_x     ending x location of component
 * @param end_y     ending y location of component
 * @param color     color of component
 * @returns         pointer to the component, NULL if unsuccessful
 */
igl_component_t* igl_create_view_pane(const char* name, int start_x, int start_y,
        int end_x, int end_y, color_t color);

/*
 * Sets `component` to be clickable and registers fn
 * as its on click function
 * 
 * @param component     component to set to clickable
 * @param fn            function to be called when component is clicked
 */
void igl_set_onclick(igl_component_t* component, onclick_fn_t fn);

/*
 * Adds aux_data to `component`. aux_data must be malloced as
 * igl_clean frees it if it is not 0.
 *
 * @param component     component to add aux_data to
 * @param fn            auxiliary data
 */
void igl_set_aux(igl_component_t* component, void* aux_data);

/* 
 * Sets the rotation of the next created component
 * Only useful with components of shape IGL_TRIA
 *
 * @param rotation      rotation of next created component
 */
void igl_set_next_rotation(int rotation);

/* 
 * Sets the buffer from which the viewpane of `component` will
 * update its content
 *
 * @param component         component who's viewpane will get buffer
 * @param buffer            buffer to attatch to component
 */
void igl_set_viewpane_buffer(igl_component_t* component,
        char** buffer, int bufsize);

/*
 * Calculates the starting x and y locations for the framebuffer from the
 * x and y index on the grid of components
 *
 * @param grid_x        grid x index of component
 * @param grid_y        grid y index of component
 * @param start_x       pointer to variable to store starting x coord
 * @param start_y       pointer to variable to store starting y coord
 */
void igl_get_start(int grid_x, int grid_y, int *start_x, int *start_y);
/* Getters for igl dimensions */
unsigned int igl_get_res_width(void);
unsigned int igl_get_res_height(void);
unsigned int igl_get_c_width(void);
unsigned int igl_get_c_height(void);
unsigned int igl_get_row(void);
unsigned int igl_get_col(void);
#endif //igl.h
