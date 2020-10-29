#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdbool.h>

#include "led.h"
#include "serial.h"
#include "timer.h"

static volatile int pwm_value = 0;
static volatile bool ramp_up = true;

void main(void){
	timer_init();
	LED_init();
	//sei();
	while(1){
		if(ramp_up){
			pwm_value++;
			if(pwm_value == 255){
				ramp_up = false;
			}
		}
		else{
			pwm_value--;
      if(pwm_value <= 0){
				ramp_up = true;
			}
		}
		_delay_ms(10);
		OCR0A = pwm_value;
	}
}


ISR(TIMER0_COMPA_vect){			//Ramping LED uncomment sei(); for interrupts
	if(ramp_up){
		pwm_value++;
		if(pwm_value >= 255){
			ramp_up = false;
		}
	}
	else{
		pwm_value--;
		if(pwm_value <= 0){
			ramp_up = true;
		}
	}
	OCR0A = pwm_value;
}
