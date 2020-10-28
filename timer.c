#include <avr/io.h>

#include <stdbool.h>
#include "timer.h"


void timer_init() {
  //TIMSK0 |= (1 << OCIE0A); // sätter på interrupts för  TIMER0_COMPA
  TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);    // Fast PWM-mode
  TCCR0B |= (1 << CS00) | (1 << CS01);  //Set prescaler

  OCR2A = 249; //COMPARE_MATCH_REGISTER
  //TIMSK0 = (1 << OCIE0A);
  TCCR2A |= (1 << WGM21); // enable ctc mode
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  //Set prescaler

  /*TIMSK0 |= (1 << OCIE0A); // sätter på interrupts för  TIMER0_COMPA
  TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
  TCCR0B |= (1 << CS00) | (1 << CS01) /*| (1 << WGM02)*/;  //Set prescaler*/
}

uint8_t simple_ramp(){
  static bool ramp_up = true;
  static int pwm_value = 0;

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
  return pwm_value;
}
