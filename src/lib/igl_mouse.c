#include "igl_mouse.h"
#include "malloc.h"
#include "strings.h"
#include "printf.h"
#include "fb.h"
#include "debug.h"

static igl_mouse_t mp;

/* Private Functions*/

/*
 * This function saves content beneath cursor in 
 * pixels_beneath buffer and redraws cursor 
 */
static void draw_mouse(void);
/*
 * Clears cursor from screen using pixels_beneath buffer
 */
static void clear_mouse(void);


void igl_mouse_init(unsigned int res_width, unsigned int res_height,
        unsigned int pointer_size, color_t cursor_color)
{
    /*Initialize mouse*/
    mp.x = res_width / 2;
    mp.y = res_height / 2;
    mp.pointer_size = pointer_size;
    mp.res_width = res_width;
    mp.res_height = res_height;
    mp.pixels_beneath =
      malloc(sizeof(color_t) * pointer_size * pointer_size);
    mp.cursor_color = cursor_color;
}

static void draw_mouse()
{
    unsigned int per_row = fb_get_pitch()/fb_get_depth();
    unsigned int (*im)[per_row] = fb_get_draw_buffer();

    int iRet = mp.pointer_size;
    for (int y = 0; y < iRet; ++y) {
        for (int x = 0; x < iRet; ++x)
            mp.pixels_beneath[(y * iRet) + x] = im[mp.y + y][mp.x + x];
    }

    gl_draw_rect(mp.x, mp.y, iRet, iRet, mp.cursor_color);
}

static void clear_mouse(void)
{
    /*Clear current cursor*/
    int iRet = mp.pointer_size;
    unsigned int per_row = fb_get_pitch()/fb_get_depth();
    unsigned int (*im)[per_row] = fb_get_draw_buffer();

    for (int y = 0; y < iRet; ++y) {
        for (int x = 0; x < iRet; ++x) {
            color_t pix = mp.pixels_beneath[(y * iRet) + x];
            im[mp.y + y][mp.x + x] = pix;
        }
    }
}

void igl_mouse_clean(void)
{
    free(mp.pixels_beneath);
}


void igl_mouse_update(mouse_event_t evt)
{
  int iRet = mp.pointer_size;
  clear_mouse();

  /*Move pointer*/
  mp.x += evt.dx;
  mp.y += -evt.dy;
  int max_width = mp.res_width - iRet;
  int max_height = mp.res_height - iRet;

  /*Clip pointer to bounds*/
  mp.x = (mp.x < 0) ? 0 : (mp.x >= max_width) ? max_width : mp.x;
  mp.y = (mp.y < 0) ? 0 : (mp.y >= max_height) ? max_height : mp.y;

  draw_mouse();
}
