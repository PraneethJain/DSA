#include <stdbool.h>
#include <stdio.h>

typedef struct Arena
{
  unsigned char *buffer;
  size_t buffer_length;
  size_t offset;
  void *(*arena_alloc)(struct Arena *a, size_t size);
  void (*arena_free)(struct Arena *a);
} Arena;

void arena_init(Arena *a, unsigned char *buffer, size_t buffer_length);
void *arena_alloc(Arena *a, size_t size);
void arena_free(Arena *a);

void arena_init(Arena *a, unsigned char *buffer, size_t buffer_length)
{
  a->buffer = buffer;
  a->buffer_length = buffer_length;
  a->offset = 0;
  a->arena_alloc = arena_alloc;
  a->arena_free = arena_free;
}

void *arena_alloc(Arena *a, size_t size)
{
  if (a->offset + size >= a->buffer_length)
    return NULL;

  void *allocated = (void *)(a->buffer + a->offset);
  a->offset += size;
  return allocated;
}

void arena_free(Arena *a)
{
  a->offset = 0;
}

typedef struct node
{
  int val;
  struct node *next;
  struct node *prev;
} node;

typedef struct node *deque;

deque init_deque(Arena *a);
void push_back(Arena *a, deque head, int val);
int pop_front(deque head);
void push_front(Arena *a, deque head, int val);
int pop_back(deque head);
void print(deque head);
bool is_empty(deque head);

deque init_deque(Arena *a)
{
  deque q = (deque)a->arena_alloc(a, sizeof(node));
  q->next = q;
  q->prev = q;

  return q;
}

void push_back(Arena *a, deque head, int val)
{
  node *new = (node *)a->arena_alloc(a, sizeof(node));
  new->val = val;

  node *old_last = head->prev;
  head->prev = new;
  new->next = head;
  new->prev = old_last;
  old_last->next = new;
}

int pop_front(deque head)
{
  node *old_first = head->next;
  head->next = old_first->next;
  old_first->next->prev = head;
  int val = old_first->val;
  return val;
}

void push_front(Arena *a, deque head, int val)
{
  node *new = (node *)a->arena_alloc(a, sizeof(node));
  new->val = val;
  node *old_first = head->next;
  new->prev = head;
  new->next = old_first;
  old_first->prev = new;
  head->next = new;
}

int pop_back(deque head)
{
  node *old_last = head->prev;
  old_last->prev->next = head;
  head->prev = old_last->prev;
  int val = old_last->val;
  return val;
}

void Print(deque head)
{
  node *cur = head->next;

  while (cur != head)
  {
    printf("%i ", cur->val);
    cur = cur->next;
  }

  printf("\n");
}

bool is_empty(deque head)
{
  return head->next == head;
}

int main()
{

  return 0;
}