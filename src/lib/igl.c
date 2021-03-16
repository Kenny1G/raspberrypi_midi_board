#include "igl.h"
#include "malloc.h"
#include "strings.h"
#include "printf.h"
#include "debug.h"

//#define DOUBLEBUFF
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
    /*must be single buffer because of rate we draw to the screen*/
#ifdef DOUBLEBUFF
    gl_init(res_width, res_height, GL_DOUBLEBUFFER);
#else
    gl_init(res_width, res_height, GL_SINGLEBUFFER);
#endif
    cfg.background = background;
    gl_clear(background);
#ifdef DOUBLEBUFF
    gl_swap_buffer();
    gl_clear(background);
#endif


    igl_mouse_init(gl_get_width(), gl_get_height(), 12, GL_BLACK);
    /*Initialize grid*/
    cfg.grid = malloc(sizeof(void*) * row * col);
    memset(cfg.grid, 0, sizeof(void*) * row * col);
}

int igl_update_mouse(mouse_event_t evt)
{
    if (evt.dx != 0|| evt.dy != 0) 
        igl_mouse_update(evt);
    /* A component is clicked if the user releases a mouse button on it*/
    if (evt.action == MOUSE_BUTTON_RELEASE) {
        //unsigned int grid_x = igl_mouse_get_x() % (gl_get_width() / cfg.col);
        //unsigned int grid_y = igl_mouse_get_y() % (gl_get_height() / cfg.row);
        //printf("grid_x: %d, grid_y: %d",grid_x, grid_y);
        //igl_component_t *comp = cfg.grid[(grid_y * cfg.col) + grid_x];
        //if (comp->fn != 0)
        //    comp->fn(comp); 
    }
    return 0;
}

void igl_clean(void)
{
    free(cfg.grid);
    for (int y = 0; y < cfg.row; ++y) {
        for (int x = 0; x < cfg.col; ++x) {
            if (cfg.grid[(y * cfg.col) + x] != 0)
                free(cfg.grid[(y * cfg.col) + x]);
        }
    }

    igl_mouse_clean();
}

igl_config_t *igl_get_config(void) { return &cfg; }

igl_component_t*  igl_create_component(const char* name, int x, int y,
        igl_component_type_t type, igl_component_shape_t shape,
        color_t color)
{ 
    /*Calculate x and y of the component*/
    unsigned int cell_width = gl_get_width() / cfg.col;
    unsigned int cell_height = gl_get_height() / cfg.row;
    unsigned int x_offset = (cell_width - cfg.c_width)/2;
    unsigned int y_offset = (cell_height - cfg.c_height)/2;
    int start_x = (x * cell_width) + x_offset;
    int start_y = (y * cell_height) + y_offset;

    igl_component_t* pRet = igl_component_new(name, start_x, start_y, 
            cfg.c_width, cfg.c_height, type, shape, color);
    cfg.grid[(y * cfg.col) + x] = pRet;

    igl_component_draw(pRet);
    return 0; 
}

void igl_set_onclick(igl_component_t* component, onclick_fn_t fn) 
{
    component->fn = fn;
}

unsigned int igl_get_res_width(void) { return gl_get_width(); }

unsigned int igl_get_res_height(void) { return gl_get_height(); }

unsigned int igl_get_c_width(void) { return cfg.c_width; }

unsigned int igl_get_c_height(void) { return cfg.c_height; }

unsigned int igl_get_row(void) { return cfg.row; }

unsigned int igl_get_col(void) { return cfg.col; }
