/*
 * functions.c
 *
 * Created: 8/16/2015 1:43:14 AM
 *  Author: Jesse
 */ 

#include <util/delay.h>
#include <avr/io.h>


//SET_OUTPUT(DDRB, MOTOR1); /* set PB5 as output */
	//SET_OUTPUT(DDRB, MOTOR2); /* set PB6 as output */
	//DDRA = (1<<PA3) | (1<<PA4) | (1<<PA5); /* initialize ABC lights */
	
	//lights_fast(); /* indicate ABC lights initialized */
	
	/* configure pwm */
	//Fast PWM Mode Fpwm = F_cpu / (N * (End + 1))
	//TCCR1B = (2 << CS10); /* 0b001: no prescaling  0b010: prescaling 8 *
	//					   * 0b011: 64  0b100: 256  0b101: 1024        */
	//ICR1 = 5999;
	//TCCR1A = (1 << COM1B1);				   /* non-inverting mode */
	//TCCR1A |= (1 << WGM11);				   /* enable fast PWM */
//	TCCR1B |= (1 << WGM12) | (1 << WGM13); /* enable fast PWM */
//	OCR1B = 2000;	
	//TIMSK1 = (1 << TOIE1); /* Set timer/counter overflow interrupt enable */
	
/*
void motors_low()
{
	OUTPUT_LOW(PORTB, MOTOR1);
	OUTPUT_LOW(PORTB, MOTOR2);
	OUTPUT_LOW(PORTE, MOTOR3);
	OUTPUT_LOW(PORTE, MOTOR4);
}

void motors_high()
{
	OUTPUT_HIGH(PORTB, MOTOR1);
	OUTPUT_HIGH(PORTB, MOTOR2);
	OUTPUT_HIGH(PORTE, MOTOR3);
	OUTPUT_HIGH(PORTE, MOTOR4);
}*/

void lights_fast()
{
	PORTA = 0b11011111;
	PORTA = 0b11101111;
	PORTA = 0b11110111;
	PORTA = 0xFF;
	return;
}

void lights_slow()
{
	PORTA = 0b11011111;
	_delay_ms(500);
	PORTA = 0b11101111;
	_delay_ms(500);
	PORTA = 0b11110111;
	_delay_ms(500);
	PORTA = 0xFF;
	return;
}