#include "igl.h"
#include "malloc.h"
#include "strings.h"

const int padding = 1;
static igl_config_t cfg;

void igl_init(unsigned int res_width, unsigned int res_height,
        unsigned int row, unsigned int col, color_t background,
        unsigned int c_width, unsigned int c_height) 
{
    /*TODO(kenny): add in an error check that ensures row x col components of size c_width x c_height can fit in res_width x res_height*/
    cfg.row = row;
    cfg.col = col;
    cfg.c_height = c_height;
    cfg.c_width = c_width;
    /*must be single buffer because rate we draw to the screen*/
    gl_init(res_width, res_height, GL_SINGLEBUFFER);
    cfg.background = background;
    gl_clear(background);
    gl_swap_buffer();
    gl_clear(background);


    igl_mouse_init(gl_get_width(), gl_get_height(), 12, GL_BLACK);
    /*Initialize grid*/
    cfg.grid = malloc(sizeof(igl_component_t) * row * col);
    memset(cfg.grid, 0, sizeof(igl_component_t) * row * col);
}


int igl_update_mouse(mouse_event_t evt)
{
    igl_mouse_update(evt);
    return 0;
}

void igl_clean(void)
{
    free(cfg.grid);
    igl_mouse_clean();
}

igl_config_t *igl_get_config(void) { return &cfg; }

igl_component_t*  igl_create_component(int x, int y, 
        unsigned int width, unsigned int height,
        igl_cmpn_type_t type, color_t color) { return 0; }

int igl_set_onclick(igl_component_t* component, onclick_fn_t fn) { return 0; }

unsigned int igl_get_res_width(void) { return gl_get_width(); }

unsigned int igl_get_res_height(void) { return gl_get_height(); }

unsigned int igl_get_c_width(void) { return cfg.c_width; }

unsigned int igl_get_c_height(void) { return cfg.c_height; }

unsigned int igl_get_row(void) { return cfg.row; }

unsigned int igl_get_col(void) { return cfg.col; }
