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

void pop_back(deque head, int *x, int *y)
{
  node *old_last = head->prev;
  old_last->prev->next = head;
  head->prev = old_last->prev;

  *x = old_last->x;
  *y = old_last->y;
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

  size_t n, m, r;
  scanf("%zu %zu %zu", &n, &m, &r);
  int seen[n * m];
  for (size_t i = 0; i < n * m; ++i)
    seen[i] = -1;

  int arr[r];
  int x, y;
  for (size_t i = 0; i < r; ++i)
  {
    scanf("%i %i", &x, &y);
    --x;
    --y;
    arr[i] = m * x + y;
    seen[m * x + y] = 0;
  }

  int res = 0;
  for (size_t i = 0; i < r; ++i)
  {
    if (seen[arr[i]])
      continue;

    x = arr[i] / m;
    y = arr[i] % m;
    deque q = init_deque(&a);
    push_front(&a, q, x, y);
    seen[arr[i]] = 1;
    int cur = 0;
    while (!is_empty(q))
    {
      pop_front(q, &x, &y);
      int neighbours[4][2] = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
      for (size_t j = 0; j < 4; ++j)
      {
        if (neighbours[j][0] >= 0 && neighbours[j][0] < n && neighbours[j][1] >= 0 && neighbours[j][1] < m)
        {
          int x1 = neighbours[j][0];
          int y1 = neighbours[j][1];
          cur += seen[m * x1 + y1] != -1;
          if (seen[m * x1 + y1] == 0)
          {
            push_front(&a, q, neighbours[j][0], neighbours[j][1]);
            seen[m * neighbours[j][0] + neighbours[j][1]] = 1;
          }
        }
      }
    }
    if (cur > res)
      res = cur;
  }

  printf("%i\n", res);

  a.arena_free(&a);

  return 0;
}
