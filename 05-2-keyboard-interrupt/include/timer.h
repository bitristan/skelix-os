/* Skelix by Xiaoming Mo (skelixos@gmail.com)
 * Licence: GPLv2 */
#ifndef TIMER_H
#define TIMER_H

void timer_install(int);
void dotimer(void);

extern volatile unsigned int timer_ticks;

#endif
