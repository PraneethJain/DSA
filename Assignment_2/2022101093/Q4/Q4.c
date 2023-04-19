#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define int long long

typedef struct node
{
  int val;
  struct node *left;
  struct node *right;
  int min;
  int max;
} node;

typedef node *tree;

typedef struct deq_node
{
  node *n;
  struct deq_node *next;
  struct deq_node *prev;
  int length;
} deq_node;

typedef deq_node *deq;

void push(deq head, node *n)
{
  deq_node *new = (deq_node *)malloc(sizeof(deq_node));
  new->n = n;

  deq_node *old_last = head->prev;
  head->prev = new;
  new->next = head;
  new->prev = old_last;
  old_last->next = new;
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

node *create_range_node(int val, int min, int max)
{
  node *n = (node *)malloc(sizeof(node));
  n->val = val;
  n->min = min;
  n->max = max;
  n->left = NULL;
  n->right = NULL;

  return n;
}

tree ListToBST(int *arr, int n)
{
  if (n == 0)
    return NULL;

  deq head = (deq)malloc(sizeof(deq_node));
  head->n = NULL;
  head->next = head;
  head->prev = head;
  head->length = 0;

  tree r = create_range_node(arr[0], INT_MIN, INT_MAX);
  push(head, r);

  int i = 1;
  while (i < n)
  {
    node *cur = pop(head);
    if (cur->val > arr[i] && cur->min < arr[i])
    {
      node *t = create_range_node(arr[i], cur->min, cur->val);
      push(head, t);
      cur->left = t;
      ++i;
    }

    if (cur->val < arr[i] && cur->max > arr[i])
    {
      node *t = create_range_node(arr[i], cur->val, cur->max);
      push(head, t);
      cur->right = t;
      ++i;
    }
  }
  free_deq(head);
  return r;
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
    printf("%lli ", cur->val);
    if (cur->left)
      push(head, cur->left);
    if (cur->right)
      push(head, cur->right);
  }
  printf("\n");
}

int cur = 0;
int maximum_sale = 0;
void ModifyBST(tree T)
{
  if (T == NULL)
    return;

  ModifyBST(T->left);
  cur += T->val;
  T->val = cur;
  maximum_sale += cur;
  ModifyBST(T->right);
}

void free_tree(tree T)
{
  if (T == NULL)
    return;

  free_tree(T->left);
  free_tree(T->right);
  free(T);
}

__int32_t main()
{
  int N;
  scanf("%lli", &N);
  int arr[N];
  for (int i = 0; i < N; ++i)
    scanf("%lli", &arr[i]);

  tree T = ListToBST(arr, N);
  ModifyBST(T);
  level_order(T);
  printf("%lli\n", maximum_sale);

  free_tree(T);

  return 0;
}
