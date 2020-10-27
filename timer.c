#include <avr/io.h>

#include "timer.h"

void timer_init() {
  TIMSK0 |= (1 << OCIE0A); // sätter på interrupts för  TIMER0_COMPA
  TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
  TCCR0B |= (1 << CS00) | (1 << CS01) /*| (1 << WGM02)*/;  //Set prescaler
}
