#include "deque.h"
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void push(deq head, node *n)
{
  deq_node *new = (deq_node *)malloc(sizeof(node));
  new->n = n;

  deq_node *old_last = head->prev;
  head->prev = new;
  new->next = head;
  new->prev = old_last;
  old_last->next = new;
  head->length++;
}

void push_start(deq head, node *n)
{
  deq_node *new = (deq_node *)malloc(sizeof(deq_node));
  new->n = n;
  deq_node *old_first = head->next;
  new->prev = head;
  new->next = old_first;
  old_first->prev = new;
  head->next = new;
  head->length++;
}

node *pop(deq head)
{
  deq_node *old_first = head->next;
  head->next = old_first->next;
  old_first->next->prev = head;
  node *n = old_first->n;
  head->length--;
  return n;
}

node *pop_rear(deq head)
{

  deq_node *old_last = head->prev;
  old_last->prev->next = head;
  head->prev = old_last->prev;
  node *n = old_last->n;
  head->length--;
  return n;
}

void print(deq head)
{
  if (head->next == head)
  {
    printf("-1");
  }
  else
  {
    deq cur = head->next;
    while (cur != head)
    {
      printf("%i ", cur->n->val);
      cur = cur->next;
    }
  }
  printf("\n");
}

void print_reverse(deq head)
{
  if (head->prev == head)
  {
    printf("-1");
  }
  else
  {
    deq cur = head->prev;
    while (cur != head)
    {
      printf("%i ", cur->n->val);
      cur = cur->prev;
    }
  }
  printf("\n");
}

int is_empty(deq head)
{
  return (head->length == 0);
}