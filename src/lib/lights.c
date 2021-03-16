#include "gpio.h"

static const unsigned int pianopins[13] = {4, 17, 27, 22, 10, 9, 11, 5, 6, 26, 21, 20, 16};

// Init for lights setting up gpio pins as outputs and setting them low
void lights_init(void) {
    gpio_init();
    for int (i = 0; i < sizeof(pianopins); i++) {
    	gpio_set_output(pianopins[i]);
	gpio_write(i, 0);
    }
}

// turn on a certain note
// NEED TO ENUMERATE DEPENDING ON REST OF IMPLEMENTATION!!
void piano_lights(int key) {
    gpio_write(key, 1);
}

// Turns all the lights off
void clear_lights(void) {
    for (int i = 0; i < sizeof(pianopins); i++)
    	gpio_write(pianopins[i], 0);
}
