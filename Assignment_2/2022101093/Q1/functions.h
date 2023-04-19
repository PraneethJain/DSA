#ifndef __STACK_H
#define __STACK_H

typedef struct stack
{
  char s[10024];
  int top;
} stack;

void push(stack *pile, char c);
char pop(stack *pile);
char peek(const stack *pile);
int is_empty(const stack *pile);

int string_length(char *s);
char match(char c);
int is_balanced(char *string, int length);
int is_palindrome(char *string, int length);

#endif
