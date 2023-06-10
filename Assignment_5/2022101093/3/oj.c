#include <limits.h>
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
  int x;
  int y;
  struct node *next;
  struct node *prev;
} node;

typedef struct node *deque;

deque init_deque(Arena *a);
void push_back(Arena *a, deque head, int x, int y);
void pop_front(deque head, int *x, int *y);
void push_front(Arena *a, deque head, int x, int y);
bool is_empty(deque head);

deque init_deque(Arena *a)
{
  deque q = (deque)a->arena_alloc(a, sizeof(node));
  q->next = q;
  q->prev = q;

  return q;
}

void push_back(Arena *a, deque head, int x, int y)
{
  node *new = (node *)a->arena_alloc(a, sizeof(node));
  new->x = x;
  new->y = y;

  node *old_last = head->prev;
  head->prev = new;
  new->next = head;
  new->prev = old_last;
  old_last->next = new;
}

void pop_front(deque head, int *x, int *y)
{
  node *old_first = head->next;
  head->next = old_first->next;
  old_first->next->prev = head;

  *x = old_first->x;
  *y = old_first->y;
}

void push_front(Arena *a, deque head, int x, int y)
{
  node *new = (node *)a->arena_alloc(a, sizeof(node));
  new->x = x;
  new->y = y;
  node *old_first = head->next;
  new->prev = head;
  new->next = old_first;
  old_first->prev = new;
  head->next = new;
}

bool is_empty(deque head)
{
  return head->next == head;
}

int main()
{
  const size_t buffer_length = 1024 * 1024;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  int T;
  scanf("%i", &T);
  for (int t = 0; t < T; ++t)
  {
    size_t n, m;
    scanf("%zu %zu", &n, &m);
    short grid[n][m];

    deque q = init_deque(&a);

    a.arena_free(&a);
  }

  return 0;
}
