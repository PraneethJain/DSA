#include <stdio.h>
#include <stdlib.h>

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
  return val;
}

void Print(Queue head)
{
  node *cur = head->next;
  if (cur == head)
  {
    printf("-1");
  }
  else
  {
    while (cur != head)
    {
      printf("%i ", cur->val);
      cur = cur->next;
    }
  }
  printf("\n");
}

void PrintReverse(Queue head)
{
  node *cur = head->prev;
  if (cur == head)
  {
    printf("-1");
  }
  else
  {
    while (cur != head)
    {
      printf("%i ", cur->val);
      cur = cur->prev;
    }
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
  for (int i = 0; i < k; ++i)
    Pop(head);
}

int main()
{
  Queue head = (Queue)malloc(sizeof(node));
  head->next = head;
  head->prev = head;
  head->val = 0;

  int T;
  scanf("%i", &T);
  char *s = (char *)malloc(sizeof(char) * 64);
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
  }

  return 0;
}