#include "stack.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int T;
  scanf("%i", &T);

  for (int i = 0; i < T; ++i)
  {
    char string[1024];
    scanf("%s", string);
    stack *pile = (stack *)malloc(sizeof(stack));
    int length = string_length(string);

    int is_balanced = 1;
    for (int i = 0; i < length; ++i)
    {
      switch (string[i])
      {
        case '(':
        case '[':
        case '{':
          push(pile, string[i]);
          break;
        case ')':
        case ']':
        case '}':
          is_balanced = (!is_empty(pile)) && (pop(pile) == match(string[i]));
          break;
        default:
          break;
      }
      if (!is_balanced)
      {
        break;
      }
    }
    if (is_empty(pile) && is_balanced)
    {
      printf("Balanced\n");
    }
    else
    {
      printf("-1\n");
    }
  }

  
  return 0;
}
