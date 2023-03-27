#ifndef __STACK_H
#define __STACK_H

typedef struct stack
{
  char s[1024];
  int top;
} stack;

void push(stack *pile,char c);
char pop(stack *pile);
char peek(const stack *pile);
int is_empty(const stack *pile);

#endif
