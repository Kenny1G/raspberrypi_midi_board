#include "malloc.h"
#include <math.h>

#define PI 3.13149265
#define SPS 256

int* tonesinwave(unsigned int freq, unsigned int duration) {
    int samples = duration * SPS;
    int* wave = malloc(sizeof(int)*samples);
    for (int i = 0; i < samples; i++) {
    	wave[i] = (int) sin(2.0 * PI * i * freq / SPS);
    }
    return wave;
}

int* superposition(int* firsttone, int* secondtone, int aWeight, int bWeight) {
    int* newwave = malloc(sizeof(firsttone));
    for (int i = 0; i < sizeof(firsttone); i++) {
    	newwave[i] = (aWeight*firsttone[i]) + (aWeight*secondtone[i]);
    }
    free(firsttone);
    free(secondtone);
    return newwave;
}

int* toneswithharmonics(unsigned int freq, unsigned int duration) {
    int* tone = tonesinwave(freq, duration);
    int* lowertone = tonesinwave(freq/2, duration);
    int* uppertone = tonesinwave(freq*2, duration);
    int* harmonics = superposition(lowertone, uppertone, 50, 50);
    free(lowertone);
    free(uppertone);
    int* combined = superposition(tone, harmonics, 60, 40);
    free(tone);
    return combined;
}


