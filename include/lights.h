#ifndef LIGHTS_H_
#define LIGHTS_H_

#include "gpio.h"

// Set pins to output and then to low before doing anything with them
void lights_init(void);

// Set one light for a specific key
void piano_lights(int key);

// clear all the lights by setting all pins to low
void clear_lights(void);

#endif
