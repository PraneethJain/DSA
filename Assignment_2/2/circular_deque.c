#include "circular_deque.h"
#include <stdio.h>
#include <stdlib.h>

void Push(Queue head, int val)
{
  node *new = (node *)malloc(sizeof(node));
  new->val = val;
  
  node *old_last = head->prev;
  head->prev = new;
  new->next = head;
  new->prev = old_last;
  old_last->next = new;
}

int Pop(Queue head)
{
  if (head->next == head)
    return -1;

  node *old_first = head->next;
  head->next = old_first->next;
  old_first->next->prev = head;
  int val = old_first->val;
  free(old_first);
  return val;
}

void Inject(Queue head, int val)
{
  node *new = (node *)malloc(sizeof(node));
  new->val = val;
  node *old_first = head->next;
  new->prev = head;
  new->next = old_first;
  old_first->prev = new;
  head->next = new;
}

int popRear(Queue head)
{
  if (head->next == head)
    return -1;

  node *old_last = head->prev;
  old_last->prev->next = head;
  head->prev = old_last->prev;
  int val = old_last->val;
  free(old_last);
  return val;
}

void Print(Queue head)
{
  node *cur = head->next;
  while (cur != head)
  {
    printf("%i ", cur->val);
    cur = cur->next;
  }
  printf("\n");
}

void PrintReverse(Queue head)
{
  node *cur = head->prev;
  while (cur != head)
  {
    printf("%i ", cur->val);
    cur = cur->prev;
  }
  printf("\n");
}

int findElem(Queue head, int pos)
{
  int cur_pos = 1;
  node *cur = head->next;
  while (cur != head)
  {
    if (cur_pos == pos)
      return cur->val;

    cur = cur->next;
    cur_pos++;
  }

  return -1;
}

void removeKElems(Queue head, int k)
{
  node *cur = head->next;
  node *temp;
  for (int i = 0; i < k; ++i)
  {
    temp = cur->next;
    printf("%i ", cur->val);
    free(cur);
    cur = temp;
  }
  printf("\n");
  head->next = temp;
  temp->prev = head;
}
