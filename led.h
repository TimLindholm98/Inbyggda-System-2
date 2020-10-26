#ifndef _LED_H_
#define _LED_H_

enum COLORS {
  RED,
  MAGENTA,
  BLUE,
  CYAN,
  GREEN,
  YELLOW
};

extern enum COLORS colors;

void LED_init(void);
void turn_on_LED(enum COLORS color);

#endif // _LED_H_
