#include "functions.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int string_length(char *s)
{
  int res = 0;
  while (s[res] != '\0')
  {
    res++;
  }

  return res;
}

char match(char c)
{
  switch (c)
  {
  case ')':
    return '(';
  case ']':
    return '[';
  case '}':
    return '{';
  }
  return -1;
}

int is_balanced(char *string, int length)
{
  stack *pile = (stack *)malloc(sizeof(stack));

  int balanced = 1;
  int exists = 0;
  for (int i = 0; i < length; ++i)
  {
    switch (string[i])
    {
    case '(':
    case '[':
    case '{':
      exists = 1;
      push(pile, string[i]);
      break;
    case ')':
    case ']':
    case '}':
      balanced = !is_empty(pile) && (pop(pile) == match(string[i]));
      break;
    default:
      break;
    }
    if (!balanced)
    {
      break;
    }
  }

  return is_empty(pile) && balanced && exists;
}

int is_palindrome(char *string, int length)
{
  if (length == 0 || length == 1)
    return 1;

  stack *pile = (stack *)malloc(sizeof(stack));

  int palindrome = 1;
  int middle = length / 2;
  int cur;
  for (cur = 0; cur < middle; ++cur)
  {
    push(pile, string[cur]);
  }
  if (length % 2)
    ++cur;

  for (; cur < length; ++cur)
  {
    if (pop(pile) != string[cur])
    {
      palindrome = 0;
    }
    break;
  }

  return palindrome;
}