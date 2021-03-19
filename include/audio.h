#ifndef AUDIO_H_
#define AUDIO_H_

/*Modified version of Pat's audio code that can output choords*/

#include <stdint.h>

void audio_init(void);

void audio_write_u8(const uint8_t* waveforms[256], int num_waveforms,
        unsigned int* dphase);
#endif
