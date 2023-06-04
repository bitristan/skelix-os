/* Skelix by Xiaoming Mo (skelixos@gmail.com)
 * Licence: GPLv2 */
#ifndef ISR_H
#define ISR_H

void default_isr(void);

#define VALID_ISR	(32+1)

extern void (*isr[(VALID_ISR)<<1])(void);

#endif
