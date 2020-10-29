#include <avr/io.h>

#include <stdbool.h>
#include "timer.h"


void timer_init() {
	OCR0A = 155;
	TCCR0A |= (1 << WGM01); // enable ctc mode
  TCCR0B |= (1 << CS02) | (1 << CS00);  //Set prescaler
}
