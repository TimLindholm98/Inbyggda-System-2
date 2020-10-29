#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdbool.h>

#include "led.h"
#include "serial.h"
#include "timer.h"


void main(void){
	timer_init();
	LED_init();
	while(1){
		if(TIFR2 & (1<<OCF2A)){
			OCR0A = simple_ramp();
			TIFR2 |= ~(1<<OCF2A);
		}
	}
}
