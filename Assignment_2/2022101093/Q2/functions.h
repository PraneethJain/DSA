#ifndef __CIRCULAR_DEQUE_H
#define __CIRCULAR_DEQUE_H

typedef struct node
{
  int val;
  struct node *next;
  struct node *prev;
} node;

typedef struct node *Queue;

void Push(Queue head, int val);
int Pop(Queue head);
void Inject(Queue head, int val);
int popRear(Queue head);
void Print(Queue head);
void PrintReverse(Queue head);
int findElem(Queue head, int pos);
void removeKElems(Queue head, int k);

#endif

