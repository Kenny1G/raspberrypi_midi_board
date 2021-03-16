/*
 * Author: Akshay Srivatsan (akshay01)
 * Date: March 7-23, 2018
 */
#ifndef GPUGL_H
#define GPUGL_H
#include <stdint.h>
#include "gpu.h"

enum gpugl_framebuffer_mode {
    GPUGL_SINGLEBUFFER=0,
    GPUGL_DOUBLEBUFFER
};

typedef struct gpugl_vertex {
    uint16_t x;
    uint16_t y;
    float r;
    float g;
    float b;
    float a;
} gpugl_vertex;

typedef enum gpugl_primitive_mode {
    GPUGL_PRIMITIVE_POINT = 0,
    GPUGL_PRIMITIVE_LINE,
    GPUGL_PRIMITIVE_LINE_LOOP,
    GPUGL_PRIMITIVE_LINE_STRIP,
    GPUGL_PRIMITIVE_TRIANGLE,
    GPUGL_PRIMITIVE_TRIANGLE_STRIP,
    GPUGL_PRIMITIVE_TRIANGLE_FAN
} gpugl_primitive_mode;

/**
 * Represents a shape for the GPU. `mode` must be set to one of the values in
 * `gpugl_primitive_mode`. Since this struct has a flexible array member, it
 * must be created on the heap. The function `gpugl_new_primitive` is provided
 * to do this.
 */
typedef struct gpugl_primitive {
    gpugl_primitive_mode    mode;
    uint16_t                length;
    gpugl_vertex            vertices[];
} gpugl_primitive;

int gpugl_character_width;
int gpugl_character_height;

/**
 * Initializes the GPU Graphics Library.
 * @param   width   the screen width to use
 * @param   height  the screen height to use
 * @param   mode    either GPUGL_DOUBLEBUFFER or GPUGL_SINGLEBUFFER
 */
void gpugl_init(unsigned width, unsigned height, unsigned mode);

/**
 * Begin a new frame.
 * Must be called at the beginning of every frame.
 */
void gpugl_begin();

/**
 * End the current frame and send to the GPU.
 * Must be called at the end of every frame.
 */
void gpugl_end();

/**
 * If the graphics library is double buffering, tells it to switch the front and
 * back buffers.
 */
void gpugl_swap_buffer();


/**
 * Constructs a new primitive object with the specified number of vertices.
 * @param   vertex_count    the number of vertices the primitive should have
 * @return                  a pointer to the new primitive
 */
gpugl_primitive *gpugl_new_primitive(gpugl_primitive_mode mode, int vertex_count);

/**
 * Adds a primitive to the current frame.
 * @param   p   the primitive to add
 */
void gpugl_add_primitive(gpugl_primitive *p);

/**
 * Frees the memory associated with a primitive.
 * @param   p   the primitive to free
 */
void gpugl_free_primitive(gpugl_primitive *p);

/**
 * Sets the data of a vertex of a primitive.
 * @param   p   the primitive
 * @param   i   the index of the vertex
 * @param   x   the x coordinate
 * @param   y   the y coordinate
 * @param   r   the r color channel
 * @param   g   the g color channel
 * @param   b   the b color channel
 * @param   a   the a channel
 */
void gpugl_set_primitive_vertex(gpugl_primitive *p, uint16_t i, uint16_t x, uint16_t y, float r, float g, float b, float a);

/**
 * Splits a 32-bit AARRGGBB color into red, green, blue, and alpha channels as floats.
 * @param   color   a 32-bit color stored as AARRGGBB
 * @param   r       a pointer to where to store the red channel
 * @param   g       a pointer to where to store the green channel
 * @param   b       a pointer to where to store the blue channel
 */
void gpugl_split_color(uint32_t color, float *r, float *g, float *b, float *a);

/**
 * Draws a character on the screen.
 * @param   ch      the character
 * @param   x       the x position
 * @param   y       the y position
 * @param   size    the size of the character (in multiples of its native bitmap size)
 * @param   r       the red color channel
 * @param   g       the green color channel
 * @param   b       the blue color channel
 * @param   a       the alpha channel
 */
void gpugl_draw_char(char ch, int x, int y, float size, float r, float g, float b, float a);

/**
 * Draws a string on the screen.
 * @param   string  the string
 * @param   x       the x position
 * @param   y       the y position
 * @param   scale   the size of the character (in multiples of its native bitmap size)
 * @param   r       the red color channel
 * @param   g       the green color channel
 * @param   b       the blue color channel
 * @param   a       the alpha channel
 */
void gpugl_draw_string(char *string, int x, int y, float scale, float r, float g, float b, float a);

/**
 * Draws a string on the screen, centered horizontally.
 * @param   string  the string
 * @param   y       the y position
 * @param   scale   the size of the character (in multiples of its native bitmap size)
 * @param   r       the red color channel
 * @param   g       the green color channel
 * @param   b       the blue color channel
 * @param   a       the alpha channel
 */
void gpugl_draw_centered_text(char *string, int y, float scale, float r, float g, float b, float a);

/**
 * Renders an image on the screen.
 * @param   x               the x coordinate of the top left
 * @param   y               the y coordinate of the top left
 * @param   width           the width to draw the image
 * @param   height          the height to draw the image
 * @param   image_width     the native width of the image (power of 2 preferred; the GPU sometimes glitches with other sizes)
 * @param   image_height    the native height of the image
 * @param   image           the image data
 * @param   a               the opacity of the image
 */
void gpugl_render_image_advanced(int x, int y, int width, int height, int image_width, int image_height, const void *image, float a);

/**
 * Renders an image on the screen, using its native height and width and opacity.
 * @param   x       the x coordinate of the top left
 * @param   y       the y coordinate of the top left
 * @param   width   the native width of the image
 * @param   height  the native height of the image
 * @param   image   the image data
 */
void gpugl_render_image(int x, int y, int width, int height, const void *image);

/**
 * The following methods and variables are only for use by other parts of the
 * GPU Graphics Library. They should not be used by client code.
 */

#define GPUGL_MEMORY_BLOCK_SIZE     0x100000
#define GPUGL_TILE_SIZE             64
#define GPUGL_FB_DEPTH              4
#define GPUGL_VERTEX_SIZE_WORDS     7
#define GPUGL_IMAGE_VERTEX_WORDS    6
#define GPUGL_FONT_VERTEX_WORDS     9

struct gpugl_memory_block gpugl_binning;
struct gpugl_memory_block gpugl_shader_record;
struct gpugl_memory_block gpugl_vertex_data;
struct gpugl_memory_block gpugl_vertex_list;
struct gpugl_memory_block gpugl_default_shader;
struct gpugl_memory_block gpugl_default_shader_uniforms;
struct gpugl_memory_block gpugl_font_shader;
struct gpugl_memory_block gpugl_font_shader_uniforms;
struct gpugl_memory_block gpugl_font_vertex_data;
struct gpugl_memory_block gpugl_font_image;
struct gpugl_memory_block gpugl_image_shader;
struct gpugl_memory_block gpugl_image_shader_uniforms;
struct gpugl_memory_block gpugl_image_vertex_data;
struct gpugl_memory_block gpugl_rendering;
struct gpugl_memory_block gpugl_tile_allocation;
struct gpugl_memory_block gpugl_tile_state_data;

// These add various data types into the specified GPU buffers, changing the
// offset in the memory block struct.
void gpugl_add_b(struct gpugl_memory_block *block, uint8_t data);
void gpugl_add_s(struct gpugl_memory_block *block, uint16_t data);
void gpugl_add_w(struct gpugl_memory_block *block, uint32_t data);
void gpugl_add_f(struct gpugl_memory_block *block, float data);
void gpugl_double_buffer_size(struct gpugl_memory_block *current);

struct gpugl_memory_block {
    gpu_mem_handle handle;
    char *buffer;
    unsigned size;
    unsigned offset;
};

unsigned gpugl_width;
unsigned gpugl_height;

void gpugl_poke(unsigned address, unsigned value);
unsigned gpugl_peek(unsigned address);

#endif
