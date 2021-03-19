#include "igl.h"
#include "malloc.h"
#include "strings.h"
#include "printf.h"
#include "debug.h"
#include "timer.h"

static igl_config_t cfg;
static bool left_pressed;
static int nextRotation;


void igl_init(unsigned int res_width, unsigned int res_height,
        unsigned int row, unsigned int col, color_t background,
        unsigned int c_width, unsigned int c_height)
{
    /* 
     * TODO(kenny): add in an error check that ensures 
     * row x col components of size c_width x c_height 
     * can fit in res_width x res_height
     */
    cfg.row = row;
    cfg.col = col;
    cfg.c_height = c_height;
    cfg.c_width = c_width;
    /*must be single buffer because of rate we draw to the screen*/
    gl_init(res_width, res_height, GL_SINGLEBUFFER);

    cfg.background = background;
    gl_clear(background);

    igl_mouse_init(gl_get_width(), gl_get_height(), 7, GL_RED);
    /*Initialize grid*/
    cfg.grid = malloc(sizeof(void*) * row * col);
    memset(cfg.grid, 0, sizeof(void*) * row * col);
}

int igl_update_mouse(mouse_event_t evt)
{
    if (evt.dx != 0|| evt.dy != 0) 
        igl_mouse_update(evt);
    if (evt.action == MOUSE_BUTTON_PRESS && evt.left == 1)
        left_pressed = true;
    /* A component is clicked if the user releases a mouse button on it*/
    if (evt.action == MOUSE_BUTTON_RELEASE && left_pressed) {
        unsigned int grid_x = igl_mouse_get_x() / (gl_get_width() / cfg.col);
        unsigned int grid_y = igl_mouse_get_y() / (gl_get_height() / cfg.row);
        igl_component_t *comp = cfg.grid[(grid_y * cfg.col) + grid_x];
        if (comp != 0 && comp->fn != 0) {
            comp->fn(comp); 
        }
        left_pressed = false;
    }
    return 0;
}

void igl_clean(void)
{
    for (int y = 0; y < cfg.row; ++y) {
        for (int x = 0; x < cfg.col; ++x) {
            igl_component_t *comp = cfg.grid[(y * cfg.col) + x];
            if (comp->aux_data != 0) {
                free(comp->aux_data);
                comp->aux_data = 0;
            }
            if (comp != 0 && comp->name != 0) {
                free(comp);
                comp->name = 0;
            }
        }
    }
    free(cfg.grid);
    cfg.grid = 0;

    igl_mouse_clean();
}

igl_config_t *igl_get_config(void) { return &cfg; }

void igl_get_start(int grid_x, int grid_y, int *start_x, int *start_y) {
    /*Calculate x and y of the component*/
    unsigned int cell_width = gl_get_width() / cfg.col;
    unsigned int cell_height = gl_get_height() / cfg.row;
    unsigned int x_offset = (cell_width - cfg.c_width)/2;
    unsigned int y_offset = (cell_height - cfg.c_height)/2;
    *start_x = (grid_x * cell_width) + x_offset;
    *start_y = (grid_y * cell_height) + y_offset;
}

igl_component_t*  igl_create_component(const char* name, int x, int y,
        igl_component_type_t type, igl_component_shape_t shape,
        color_t color)
{ 
    int start_x;
    int start_y;
    igl_get_start(x, y, &start_x, &start_y);
    if (cfg.grid[(y * cfg.col) + x] == 0) {
        igl_component_t* pRet = igl_component_new(name, start_x, start_y, 
                cfg.c_width, cfg.c_height, type, shape, color);
        cfg.grid[(y * cfg.col) + x] = pRet;

        pRet->rotation = nextRotation;
        nextRotation = 0;
        igl_component_draw(pRet);
        return pRet; 
    }
    return NULL;
}

igl_component_t* igl_create_view_pane(const char* name, int start_x, int start_y,
                                      int end_x, int end_y, color_t color)
{
    int s_x, s_y, e_x, e_y;
    igl_get_start(start_x, start_y, &s_x, &s_y);
    igl_get_start(end_x, end_y, &e_x, &e_y);
    int ncols = end_x -start_x +1;
    int nrows = end_y -start_y +1;

    if (cfg.grid[(start_y * cfg.col) + start_x] == 0) {
        igl_component_t* pRet = igl_component_new(name, s_x, s_y, 
                cfg.c_width, cfg.c_height, IGL_VIEW_PANE, IGL_RECT, color);
        igl_component_new_viewpane(pRet, e_x, e_y, nrows, ncols);
        for (int y = start_y; y <= end_y; ++y) {
            for (int x = start_x; x <= end_x; ++x) {
                if (cfg.grid[(y * cfg.col) + x] == 0)
                    cfg.grid[(y * cfg.col) + x] = pRet;
                else {
                    free(pRet);
                    return 0;
                }
            }
        }
       return pRet; 
    }
    return 0;
}

void igl_set_aux(igl_component_t* component, void* aux_data)
{
    component->aux_data = aux_data;
}

void igl_set_onclick(igl_component_t* component, onclick_fn_t fn) 
{
    component->fn = fn;
}

void igl_set_next_rotation(int rotation)
{
    nextRotation = rotation;
}

void igl_set_viewpane_buffer(igl_component_t* component,
        char** buffer, int bufsize)
{
    igl_viewpane_t* vp = (igl_viewpane_t*)component->aux_data;
    vp->buffer = buffer;
    vp->bufsize = bufsize;
}

unsigned int igl_get_res_width(void) { return gl_get_width(); }

unsigned int igl_get_res_height(void) { return gl_get_height(); }

unsigned int igl_get_c_width(void) { return cfg.c_width; }

unsigned int igl_get_c_height(void) { return cfg.c_height; }

unsigned int igl_get_row(void) { return cfg.row; }

unsigned int igl_get_col(void) { return cfg.col; }
