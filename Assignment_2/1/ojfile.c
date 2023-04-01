#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
  char s[10024];
  int top;
} stack;

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
  pile->top = 0;

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
  pile->top = 0;

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
      break;
    }
  }

  return palindrome;
}

int main()
{
  int T;
  scanf("%i", &T);

  char *string = (char *)malloc(sizeof(char) * 10024);
  for (int i = 0; i < T; ++i)
  {
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