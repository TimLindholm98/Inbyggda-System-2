#include <avr/io.h>
#include "led.h"

void LED_init() {
	// ...
  //DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);
  DDRD |= (1 << DDD6);

}

void toogle_LED(enum COLORS color){
  switch(color){
    case RED:
      PORTB ^= (1 << PB3);
      break;
    case BLUE:
      PORTB ^= (1 << PB2);
      break;
    case GREEN:
      PORTB ^= (1 << PB1);
      break;
    case MAGENTA:
      PORTB ^= (1 << PB3) | (1 << PB2);
      break;
    case CYAN:
      PORTB ^= (1 << PB2) | (1 << PB1);
      break;
    case YELLOW:
      PORTB ^= (1 << PB1)| (1 << PB3);
      break;
  }
}
