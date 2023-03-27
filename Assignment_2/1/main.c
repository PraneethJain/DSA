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
    int length = string_length(string);
    int balanced = is_balanced(string, length);
    int palindrome = is_palindrome(string, length);
    if (balanced && palindrome)
    {
      printf("Balanced and Palindromic");
    }
    else if (balanced)
    {
      printf("Balanced");
    }
    else if (palindrome)
    {
      printf("Palindromic");
    }
    else
    {
      printf("-1");
    }
    printf("\n");
  }

  return 0;
}
