#include "printf.h"
#include "strings.h"
#include "uart.h"
#include "instrument.h"

#include "timer.h"
#include "gpio.h"

//taken from lecture/CS 107E Winter 2020 class code
#include "pwm.h"
#include "tone.h"
#include "pitch.h"

//written with the help of referencing melody.c from lecture (the gitHub path is cs107e.github.io/lectures/Sensors/code/sound/melody/melody.c)
void play_notes(note_config_t *note_sequence, unsigned int seq_len) 
{
    timer_init();

    gpio_init();
    gpio_set_function( 40, GPIO_FUNC_ALT0 ); // PWM0
    gpio_set_function( 45, GPIO_FUNC_ALT0 ); // PWM1
    gpio_set_function( 18, GPIO_FUNC_ALT5 ); // PWM0

    pwm_init();
    pwm_set_clock( F_AUDIO );

    //play the sequence of notes
    for (unsigned int curr_note = 0; curr_note < seq_len; curr_note++) {
        //save the type of the current note (quarter note, eighth note, etc)
        unsigned int this_note_type = *note_sequence -> note_len;

        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int note_dur = 1000/this_note_type;



        //TO-DO: DELETE THIS STUFF BECAUSE MIGHT NOT WORK
        // //the beginning of the string that we will concatenate onto for the note/pitch
        // //size is 8, because for example "NOTE_C4" has 7 chars, and the last index holds the null terminator
        // unsigned char beginning[8] = "NOTE_";

        // //we will append onto specific_note in order to get the full string that represents the note/pitch identity
        // char *specific_note = beginning;
        
        //TO-DO: FIGURE A WAY TO INDEX INTO AN ARRAY OF THE NOTE PITCHES AND THEN PASS IN THAT VALUE INTO tone() BELOW
        tone();




        timer_delay_ms(note_dur);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = note_dur * 0.30;
        tone(0); // 0 turns off sound
        timer_delay_ms(pauseBetweenNotes);
    }
    
}

void main(void) 
{
    uart_init();
    printf("Hello, world!\n");
    uart_putchar(EOT);
}