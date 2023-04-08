#ifndef __DEQUE_H
#define __DEQUE_H
#include "bst.h"

typedef struct deq_node
{
  node *n;
  struct deq_node *next;
  struct deq_node *prev;
  int length;
} deq_node;

typedef deq_node *deq;

void push(deq head, node *n);
void push_start(deq head, node *n);
node *pop(deq head);
node *pop_rear(deq head);
void print(deq head);
void print_reverse(deq head);
int is_empty(deq head);

#endif