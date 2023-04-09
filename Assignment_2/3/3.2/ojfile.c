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

void level_order(tree T)
{

  if (T == NULL)
    return;

  deq head = (deq)malloc(sizeof(deq_node));
  head->n = NULL;
  head->next = head;
  head->prev = head;
  head->length = 0;

  push(head, T);
  node *cur = NULL;
  while (!is_empty(head))
  {
    cur = pop(head);
    printf("%i ", cur->val);
    if (cur->left)
      push(head, cur->left);
    if (cur->right)
      push(head, cur->right);
  }
  printf("\n");
}

int pre_index = 0;
tree get_tree(int *inorder, int *preorder, int start, int end)
{

  if (start > end)
    return NULL;

  tree T = create_node(preorder[pre_index]);

  int cur = -1;
  for (int i = start; i <= end; ++i)
  {
    if (inorder[i] == preorder[pre_index])
    {
      cur = i;
      break;
    }
  }
  ++pre_index;
  T->left = get_tree(inorder, preorder, start, cur - 1);
  T->right = get_tree(inorder, preorder, cur + 1, end);

  return T;
}

int main()
{
  int T;
  scanf("%i", &T);
  for (int i = 0; i < T; ++i)
  {
    int N;
    scanf("%i", &N);
    int inorder[N];
    int preorder[N];
    for (int j = 0; j < N; ++j)
      scanf("%i", &inorder[j]);

    for (int j = 0; j < N; ++j)
      scanf("%i", &preorder[j]);

    tree t = get_tree(inorder, preorder, 0, N - 1);

    level_order(t);
  }

  return 0;
}
