#ifndef STACK_H_
#define STACK_H_

#include <stdint.h>
#include <stdbool.h>

#define STACK_FULL        -2
#define STACK_EMPTY       -1
#define STACK_NOT_EMPTY   0
#define STACK_NOT_FULL    1

#define STACK_SIZE  128

int8_t stack_pop(void *item);
int8_t stack_push(void *item);
bool stack_empty(void);
bool stack_full(void);

#endif
