#include "circular_deque.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  Queue head = (Queue)malloc(sizeof(node));
  head->next = head;
  head->prev = head;
  head->val = 0;

  int T;
  scanf("%i", &T);
  char s[64];
  for (int i = 0; i < T; ++i)
  {
    scanf("%s", s);
    char oper = s[4];
    if (oper == '1')
    {
      int n;
      scanf("%i", &n);
      Push(head, n);
    }
    else if (oper == '2')
    {
      printf("%i\n", Pop(head));
    }
    else if (oper == '3')
    {
      int n;
      scanf("%i", &n);
      Inject(head, n);
    }
    else if (oper == '4')
    {
      printf("%i\n", popRear(head));
    }
    else if (oper == '5')
    {
      Print(head);
    }
    else if (oper == '6')
    {
      PrintReverse(head);
    }
    else if (oper == '7')
    {
      int n;
      scanf("%i", &n);
      printf("%i\n", findElem(head, n));
    }
    else if (oper == '8')
    {
      int n;
      scanf("%i", &n);
      removeKElems(head, n);
    }
    else
    {
      printf("Invalid Operation!\n");
    }
  }
  
  return 0;
}