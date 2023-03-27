#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void push(stack *pile, char c)
{
  pile->s[pile->top++] = c;
}

char pop(stack *pile)
{
  return pile->s[--pile->top];
}

char peek(const stack *pile)
{
  return pile->s[pile->top - 1];
}

int is_empty(const stack *pile)
{
  return pile->top == 0;
}
