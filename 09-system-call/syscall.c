/* Skelix by Xiaoming Mo (skelixos@gmail.com)
 * Licence: GPLv2 */
#include <isr.h>
#include <syscall.h>

void (*sys_call_table[VALID_SYSCALL])(void) = {sys_print};

