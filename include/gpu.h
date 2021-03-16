/*
 * Author: Akshay Srivatsan (akshay01)
 * Date: March 7-23, 2018
 */
#ifndef GPU_H
#define GPU_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t gpu_mem_handle;

/**
 * Initializes the GPU, setting up the framebuffer and sending a message to the
 * VideoCore processor to turn it on.
 * 
 * @param   width   the requested width of the framebuffer
 * @param   height  the requested height of the framebuffer
 * 
 * The framebuffer should not be directly manipulated by any other library after this call.
 */
void gpu_init(unsigned int width, unsigned int height);

/**
 * Requests a memory allocation from the GPU's memory allocator. This memory is
 * not yet usable, and needs to be locked by the CPU. This function always
 * requests 4k-aligned, zeroed out, coherent memory that is marked for CPU use
 * (i.e., the memory is probably going to be locked for a long time).
 * @param   bytes   the number of bytes to allocate
 * @return          a number which the GPU uses to identify this memory
 *                  allocation, zero if the memory could not be allocated
 */
gpu_mem_handle gpu_mem_alloc(size_t bytes);

/**
 * Requests that the GPU lock the memory associated with a specific allocation so the CPU can use it freely.
 * @param   handle  the handle representing the memory allocation
 * @return          a GPU bus address: this address of the allocated memory in the GPU's memory space
 */
char *gpu_mem_lock(unsigned handle);

/**
 * Allows the GPU to take control of the memory, allowing the memory allocator to move it as necessary. The contents of the memory will be preserved.
 * @param   handle  the handle representing the memory allocation
 * @return          true if the request was successful, false otherwise
 */
bool gpu_mem_unlock(unsigned handle);

/**
 * Marks the memory as free, allowing the GPU to reuse it.
 * @param   handle  the handle representing the memory allocation
 * @return          true if the request was successful, false otherwise
 */
bool gpu_mem_free(unsigned handle);


#endif
