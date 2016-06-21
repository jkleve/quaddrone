/*
 * led.h
 *
 * Created: 6/7/2016
 *  Author: Jesse
 */ 
#ifndef LED_H
# define LED_H

# include <avr/io.h>

# define LED_BLINK_DELAY 50


# define INIT_LEDS (DDRA |= (1 << DDA3) | (1 << DDA4) | (1 << DDA5))

# define BLUE   PA5
# define ORANGE PA4
# define RED    PA3

# define A_ON  (PORTA |= (1 << PA5)) /* BLUE   */
# define B_ON  (PORTA |= (1 << PA4)) /* ORANGE */
# define C_ON  (PORTA |= (1 << PA3)) /* RED    */
# define A_OFF (PORTA &= ~(1 << PA5))
# define B_OFF (PORTA &= ~(1 << PA4))
# define C_OFF (PORTA &= ~(1 << PA3))

# define LED_ON(x)  (PORTA |= (1 << x))
# define LED_OFF(x) (PORTA &= ~(1 << x))
# define BLINK(x) { \
          LED_ON(x);\
          _delay_ms(LED_BLINK_DELAY);\
          LED_OFF(x);\
         }

void blink_a( void ); /* BLUE   */
void blink_b( void ); /* ORANGE */
void triple_b( void );
void blink_c( void ); /* RED    */
void comms_init( void );

#endif
