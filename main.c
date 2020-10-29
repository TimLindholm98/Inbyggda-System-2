#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdbool.h>

#include "led.h"
#include "serial.h"
#include "timer.h"

static volatile int indexing = 0;

void main(void){
	timer_init();
	LED_init();

	while(1){
		if(TIFR0 & (1<<OCF0A)){
			indexing++;
	    TIFR0 |= ~(1 << OCF0A);
		}
		if(indexing == 10){
			toggle_LED(MAGENTA);
			indexing = 0;
		}
	}
}
