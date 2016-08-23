#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

int main(void)
{
	DDRD |= (1 << PC0);

	while(1) {
		PORTC|=(1 << PC0)
		_delay_ms(10000);
		PORTC&=~(1 << PC0);
		_delay_ms(10000);
	}	

	return 0;
}
