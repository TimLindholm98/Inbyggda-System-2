#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"

//enum COLORS colors = RED;

static volatile int indexing = 0;

void main(void){
	uart_init();
	timer_init();
	LED_init();
	sei();
	while (1) {
		if(indexing == 10){
			toogle_LED(MAGENTA);
			indexing = 0;
		}
	}
}

ISR(TIMER0_COMPA_vect){
	//printf_P(PSTR("Hello there\n"));
	indexing++;
}
