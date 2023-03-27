#include "functions.h"
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
