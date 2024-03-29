/* Skelix by Xiaoming Mo (skelixos@gmail.com)
 * Licence: GPLv2 */
#ifndef SYSCALL_H
#define SYSCALL_H

#define VALID_SYSCALL 1

extern void (*system_call_table[VALID_SYSCALL])(void);

#endif
