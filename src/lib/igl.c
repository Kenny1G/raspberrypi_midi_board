#include "igl.h"
#include "malloc.h"

const int padding = 1;
static igl_config_t igl;

int igl_init(unsigned int res_width, unsigned int res_height,
        unsigned int row, unsigned int col, color_t background,
        unsigned int c_width, unsigned int c_height) 
{
    igl.row = row;
    igl.col = col;
    igl.c_height = c_height;
    igl.c_width = c_width;
    gl_init(res_width, res_height, GL_DOUBLEBUFFER);
    igl.background = background;
    gl_clear(background);

    igl.mp = malloc(sizeof(igl_mouse_t));
    igl.grid = malloc(sizeof(igl_component_t) * row * col);

    return 0;
}

igl_config_t* igl_get_config(void)
{
    return &igl; 
}

int igl_update_mouse(mouse_event_t evt)
{
    return 0; 
}

igl_component_t*  igl_create_component(int x, int y, 
        unsigned int width, unsigned int height,
        igl_cmpn_type_t type, color_t color)
{
    return 0; 
}

int igl_set_onclick(igl_component_t* component, onclick_fn_t fn)
{
    return 0; 
}

unsigned int igl_get_res_width(void)
{
    return gl_get_width(); 
}

unsigned int igl_get_res_height(void)
{
    return gl_get_height(); 
}

unsigned int igl_get_c_width(void)
{
    return igl.c_width; 
}

unsigned int igl_get_c_height(void)
{
    return igl.c_height; 
}

unsigned int igl_get_row(void)
{
    return igl.row; 
}

unsigned int igl_get_col(void)
{
    return igl.col; 
}
