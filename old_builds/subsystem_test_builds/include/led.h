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


# define INIT_LEDS {\
          (DDRA |= (1 << DDA3) | (1 << DDA4) | (1 << DDA5)); \
          (PORTA = 0xFF); \
         }

# define BLUE   0x08
# define ORANGE 0x10
# define RED    0x20

# define LED_ON(x)  (PORTA &= ~(x))
# define LED_OFF(x) (PORTA |= (x))
# define BLINK(x) { \
          LED_ON(x);\
          _delay_ms(LED_BLINK_DELAY);\
          LED_OFF(x);\
         }

#endif
