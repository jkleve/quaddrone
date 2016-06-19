/*
 * led.h
 *
 * Created: 6/7/2016
 *  Author: Jesse
 */ 
#ifndef LED_H
# define LED_H

# include <avr/io.h>

# define INIT_LEDS (DDRA = (1 << PA3) | (1 << PA4) | (1 << PA5))

# define A_ON  (PORTA = 0b11110111)
# define A_OFF (PORTA = 0b11111111)

void blink_a( void ); /* BLUE   */
void blink_b( void ); /* ORANGE */
void triple_b( void );
void blink_c( void ); /* RED    */
void comms_init( void );

#endif
