#include <stdio.h>
#include <stdlib.h>

#ifndef __BST_H
#define __BST_H

typedef struct node
{
  int val;
  struct node *left;
  struct node *right;
} node;

typedef node *tree;

node *create_node(int val);
node *insert(tree T, int val);
node *make_tree(int n, int *values, int index);

void pre_order(tree T);
void zig_zag_order(tree T);

#endif

#ifndef __DEQUE_H
#define __DEQUE_H

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
void free_deq(deq head);

#endif

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
  free(old_first);
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

void free_deq(deq head)
{
  deq cur = head->next;
  while (cur != head)
  {
    deq temp = cur->next;
    free(cur);
    cur = temp;
  }
  free(head);
}

node *create_node(int val)
{
  node *new = (node *)malloc(sizeof(node));
  new->left = NULL;
  new->right = NULL;
  new->val = val;

  return new;
}

node *insert(tree T, int val)
{
  if (T == NULL)
    return create_node(val);

  if (val < T->val)
  {
    T->left = insert(T->left, val);
  }
  else if (val > T->val)
  {
    T->right = insert(T->right, val);
  }

  return T;
}

node *make_tree(int n, int *values, int index)
{

  if (index >= n)
    return NULL;

  tree T = create_node(values[index]);
  T->left = make_tree(n, values, 2 * index + 1);
  T->right = make_tree(n, values, 2 * index + 2);

  return T;
}

void pre_order(tree T)
{
  if (T == NULL)
    return;

  printf("%i ", T->val);
  pre_order(T->left);
  pre_order(T->right);
}

void zig_zag_order(tree T)
{
  if (T == NULL)
    return;

  deq head = (deq)malloc(sizeof(deq_node));
  head->n = NULL;
  head->next = head;
  head->prev = head;
  head->length = 0;

  int flag = 0;
  node *cur;
  push(head, T);
  while (!is_empty(head))
  {
    int len = head->length;
    int to_print[len];
    for (int i = 0; i < len; ++i)
    {
      cur = pop(head);
      to_print[i] = cur->val;

      if (cur->right != NULL)
        push(head, cur->right);
      if (cur->left != NULL)
        push(head, cur->left);
    }

    if (flag)
      for (int j = 0; j < len; ++j)
        printf("%i ", to_print[j]);
    else
      for (int j = len - 1; j >= 0; --j)
        printf("%i ", to_print[j]);

    flag = !flag;
  }
  printf("\n");
  free_deq(head);
}

void free_tree(tree T)
{
  if (T == NULL)
      return;

  free_tree(T->left);
  free_tree(T->right);
  free(T);
}

int main()
{
  int T;
  scanf("%i", &T);
  for (int i = 0; i < T; ++i)
  {
    int N;
    scanf("%i", &N);
    int values[N];
    for (int j = 0; j < N; ++j)
      scanf("%i", &values[j]);

    tree t = make_tree(N, values, 0);
    zig_zag_order(t);
    free_tree(t);
  }

  return 0;
}
