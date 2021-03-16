#ifndef DEBUG_H_
#define DEBUG_H_
#include "igl_mouse.h"

void debug_print_pixels_beneath(igl_mouse_t mp);

void debug_print_mouse_meta(igl_mouse_t mp);

void debug_print_mouse_event(mouse_event_t evt);
#endif