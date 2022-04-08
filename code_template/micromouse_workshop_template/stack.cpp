#include "stack.h"

static void *items[STACK_SIZE];
int32_t top = -1;

int8_t stack_pop(void *item)
{
  int8_t status = STACK_EMPTY;
  
  if(!stack_empty())
  {
    item = items[top];
    top--;
    status = STACK_NOT_EMPTY;
  }

  return status;
}

int8_t stack_push(void *item)
{
  int8_t status = STACK_FULL;
  
  if(!stack_full())
  {
    top++;
    items[top] = item;
    status = STACK_NOT_FULL;
  }

  return status;
}

bool stack_empty(void)
{
  return (top == -1) ? true : false; 
}

bool stack_full(void)
{
  return (top == STACK_SIZE) ? true : false;
}
