#include "igl.h"

int igl_init(unsigned int res_width, unsigned int res_height,
        unsigned int row, unsigned int col, color_t background,
        unsigned int c_width, unsigned int c_height) 
{
    return 0;
}

igl_config_t* igl_get_config(void)
{
    return 0; 
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
    return 0; 
}
unsigned int igl_get_res_height(void)
{
    return 0; 
}
unsigned int igl_get_c_width(void)
{
    return 0; 
}
unsigned int igl_get_c_height(void)
{
    return 0; 
}
unsigned int igl_get_row(void)
{
    return 0; 
}
unsigned int igl_get_col(void)
{
    return 0; 
}
