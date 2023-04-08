#include "bst.h"
#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

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
      {
        push(head, cur->right);
      }
      if (cur->left != NULL)
      {
        push(head, cur->left);
      }
    }

    if (flag)
    {
      for (int j = 0; j < len; ++j)
      {
        printf("%i ", to_print[j]);
      }
    }
    else
    {
      for (int j = len - 1; j >= 0; --j)
      {
        printf("%i ", to_print[j]);
      }
    }
    flag = !flag;
  }
}
