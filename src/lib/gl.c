/*
 * Author: Akshay Srivatsan (akshay01)
 * Date: March 7-23, 2018
 *
 * This file is a wrapper around the GPU Graphics Library, designed to swap all
 * the raw framebuffer manipulation for GPU commands.
 */
#include "gl.h"
#include "gpugl.h"
#include "font.h"
#include "strings.h"
#include "assert.h"
#include <stdbool.h>

#define GL_DEPTH_BYTES  4

/**
 * Initializes the graphics library and the underlying framebuffer.
 * @param   width   the width of the graphical interface
 * @param   height  the height of the graphical interface
 * @param   mode    either GL_DOUBLEBUFFER or GL_SINGLEBUFFER
 */
void gl_init(unsigned int width, unsigned int height, gl_mode_t mode)
{
    assert(mode == GL_DOUBLEBUFFER);
    // the swap_buffer command actually sends data to the gpu, so it is necessary
    if (mode == GL_DOUBLEBUFFER) {
        gpugl_init(width, height, GPUGL_DOUBLEBUFFER);
    } else if (mode == GL_SINGLEBUFFER) {
        gpugl_init(width, height, GPUGL_SINGLEBUFFER);
    } else {
        // Unknown mode.
        return;
    }
    gpugl_begin();
}

/**
 * Tells the GPU to switch the front and back buffers (reveals the current image).
 */
void gl_swap_buffer(void)
{
    gpugl_end();
    gpugl_swap_buffer();
    gpugl_begin();
}

/**
 * Gets the current width of the screen.
 * @return  the width of the screen in pixels
 */
unsigned int gl_get_width(void) 
{
    return gpugl_width;
}

/**
 * Gets the current height of the screen.
 * @return  the height of the screen in pixels
 */
unsigned int gl_get_height(void)
{
    return gpugl_height;
}

/**
 * Assembles a color from red, green, and blue parameters. Assumes an alpha of
 * 0xff.
 * @param   r   the amount of red
 * @param   g   the amount of green
 * @param   b   the amount of blue
 * @return      the color specified
 */
color_t gl_color(unsigned char r, unsigned char g, unsigned char b)
{
    return (0xff << 24) | (r << 16) | (g << 8) | (b << 0);
}

/**
 * Clears the graphics with the specified color.
 * @param   c   the color to reset the graphics to
 */
void gl_clear(color_t c)
{
    float r;
    float g;
    float b;
    float a;
    gpugl_split_color(c, &r, &g, &b, &a);
    gpugl_primitive *p = gpugl_new_primitive(GPUGL_PRIMITIVE_TRIANGLE_STRIP, 4);
    gpugl_set_primitive_vertex(p, 0, 0, 0, r, g, b, a);
    gpugl_set_primitive_vertex(p, 1, gpugl_width, 0, r, g, b, a);
    gpugl_set_primitive_vertex(p, 2, 0, gpugl_height, r, g, b, a);
    gpugl_set_primitive_vertex(p, 3, gpugl_width, gpugl_height, r, g, b, a);
    gpugl_add_primitive(p);
    gpugl_free_primitive(p);
}

/**
 * Sets a specific pixel's color. Ignores the request if the pixel is out of
 * bounds.
 * @param   x   the x coordinate of the pixel
 * @param   y   the y coordinate of the pixel
 * @param   c   the color to set the pixel to
 */
void gl_draw_pixel(unsigned int x, unsigned int y, color_t c)
{
    float r;
    float g;
    float b;
    float a;
    gpugl_split_color(c, &r, &g, &b, &a);
    gpugl_primitive *p = gpugl_new_primitive(GPUGL_PRIMITIVE_POINT, 1);
    gpugl_set_primitive_vertex(p, 0, x, y, r, g, b, a);
    gpugl_add_primitive(p);
    gpugl_free_primitive(p);
}

/**
 * Gets the color of a specific pixel.
 * @param   x   the x coordinate of the pixel
 * @param   y   the y coordinate of the pixel
 * @return      the color of the pixel
 */
color_t gl_read_pixel(unsigned int x, unsigned int y)
{
    if (x < 0 || y < 0 || x >= fb_get_width() || y >= fb_get_height()) return 0;
    color_t *buf = (color_t *)fb_get_draw_buffer();
    int i = y*fb_get_pitch()/GL_DEPTH_BYTES + x;
    return buf[i];
}

/**
 * Draws a rectangle on the screen.
 * @param   x   the x coordinate of the top left of the rectangle
 * @param   y   the y coordinate of the top right of the rectangle
 * @param   w   the width of the rectangle
 * @param   h   the height of the rectangle
 * @param   c   the color to draw the rectangle in
 */
void gl_draw_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, color_t c)
{
    float r;
    float g;
    float b;
    float a;
    gpugl_split_color(c, &r, &g, &b, &a);
    gpugl_primitive *p = gpugl_new_primitive(GPUGL_PRIMITIVE_TRIANGLE_STRIP, 4);
    gpugl_set_primitive_vertex(p, 0, x, y, r, g, b, a);
    gpugl_set_primitive_vertex(p, 1, x+w, y, r, g, b, a);
    gpugl_set_primitive_vertex(p, 2, x, y+h, r, g, b, a);
    gpugl_set_primitive_vertex(p, 3, x+w, y+h, r, g, b, a);
    gpugl_add_primitive(p);
    gpugl_free_primitive(p);
}

/**
 * Draws the specified character on the screen.
 * @param   x   the x coordinate of the top left
 * @param   y   the y coordinate of the top left
 * @param   ch  the character to draw
 * @param   c   the color to draw in
 */
void gl_draw_char(unsigned int x, unsigned int y, char ch, color_t c)
{
    float r;
    float g;
    float b;
    float a;
    gpugl_split_color(c, &r, &g, &b, &a);
    gpugl_draw_char(ch, x, y, 1.0, r, g, b, a);
}

/**
 * Draws a string.
 * @param   x   the x coordinate of the top left
 * @param   y   the y coordinate of the top left
 * @param   str the string to draw
 * @param   c   the color to draw in
 */
void gl_draw_string(unsigned int x, unsigned int y, const char* str, color_t c)
{
    static bool initialized = false;
    static unsigned int width;
    if (!initialized) {
        width = font_get_glyph_width();
        initialized = true;
    }
    int l = strlen(str);
    for (int i = 0; i < l; i++) {
        gl_draw_char(x + i*width, y, str[i], c);
    }
}

/**
 * Gets the height of a character.
 * @return  the height of a character
 */
unsigned int gl_get_char_height(void)
{
    return fb_get_height()/font_get_glyph_height();
}

/**
 * Gets the width of a character.
 * @return  the width of a character
 */
unsigned int gl_get_char_width(void)
{
    return fb_get_width()/font_get_glyph_width();
}

/**
 * Draws an anti-aliased line.
 * @param   x1  the x coordinate of one end of the line
 * @param   y1  the y coordinate of one end of the line
 * @param   x2  the x coordinate of the other end of the line
 * @param   y2  the y coordinate of the other end of the line
 * @param   c   the color of the line
 */
void gl_draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, color_t c)
{
    float r;
    float g;
    float b;
    float a;
    gpugl_split_color(c, &r, &g, &b, &a);
    gpugl_primitive *p = gpugl_new_primitive(GPUGL_PRIMITIVE_LINE, 2);
    gpugl_set_primitive_vertex(p, 0, x1, y1, r, g, b, a);
    gpugl_set_primitive_vertex(p, 1, x2, y2, r, g, b, a);
    gpugl_add_primitive(p);
    gpugl_free_primitive(p);
}

/**
 * Draws and fills a triangle.
 * @param   x1  the x coordinate of the 1st vertex of the triangle
 * @param   y1  the y coordinate of the 1st vertex of the triangle
 * @param   x1  the x coordinate of the 2nd vertex of the triangle
 * @param   y1  the y coordinate of the 2nd vertex of the triangle
 * @param   x1  the x coordinate of the 3rd vertex of the triangle
 * @param   y1  the y coordinate of the 3rd vertex of the triangle
 * @param   c   the color of the triangle
 *
 * Warning: this function is slow
 */
void gl_draw_triangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, color_t c)
{
    float r;
    float g;
    float b;
    float a;
    gpugl_split_color(c, &r, &g, &b, &a);
    gpugl_primitive *p = gpugl_new_primitive(GPUGL_PRIMITIVE_TRIANGLE, 3);
    gpugl_set_primitive_vertex(p, 0, x1, y1, r, g, b, a);
    gpugl_set_primitive_vertex(p, 1, x2, y2, r, g, b, a);
    gpugl_set_primitive_vertex(p, 2, x3, y3, r, g, b, a);
    gpugl_add_primitive(p);
    gpugl_free_primitive(p);
}
