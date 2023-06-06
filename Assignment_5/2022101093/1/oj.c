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

void swap(int *x, int *y);

typedef struct node
{
  int val;
  struct node *next;
} node;

node *init_node(Arena *a, int val);

typedef struct graph
{
  size_t num_vertices;
  node **list;
} graph;

graph *init_graph(Arena *a, size_t num_vertices);
void insert_edge(Arena *a, graph *g, int v1, int v2);

typedef struct heap
{
  size_t capacity;
  int *arr;
  size_t length;
} heap;

heap *init_heap(Arena *a, size_t capacity);
void sift_up(heap *h, size_t idx);
void sift_down(heap *h, size_t idx);
void insert(heap *h, int x);
int top(heap *h);
int pop(heap *h);
bool is_empty(heap *h);
__attribute__((unused)) void print(heap *h);

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

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

node *init_node(Arena *a, int val)
{
  node *n = (node *)a->arena_alloc(a, sizeof(node));
  n->val = val;
  n->next = NULL;

  return n;
}

graph *init_graph(Arena *a, size_t num_vertices)
{
  graph *g = (graph *)a->arena_alloc(a, sizeof(graph));
  g->num_vertices = num_vertices;
  g->list = (node **)a->arena_alloc(a, sizeof(node *) * (g->num_vertices + 1));
  for (size_t i = 1; i <= num_vertices; ++i)
    g->list[i] = NULL;

  return g;
}

void insert_edge(Arena *a, graph *g, int v1, int v2)
{
  node *temp = g->list[v1];
  g->list[v1] = init_node(a, v2);
  g->list[v1]->next = temp;

  temp = g->list[v2];
  g->list[v2] = init_node(a, v1);
  g->list[v2]->next = temp;
}

heap *init_heap(Arena *a, size_t capacity)
{
  heap *h = (heap *)a->arena_alloc(a, sizeof(heap));

  h->capacity = capacity;
  h->length = 0;
  h->arr = (int *)a->arena_alloc(a, sizeof(int) * (h->capacity + 1));

  return h;
}

void sift_up(heap *h, size_t idx)
{
  size_t cur = idx;
  while (cur != 1 && h->arr[cur] < h->arr[cur / 2])
  {
    swap(&h->arr[cur], &h->arr[cur / 2]);
    cur /= 2;
  }
}

void sift_down(heap *h, size_t idx)
{
  size_t cur = idx;
  size_t next_idx;
  while (2 * cur <= h->length)
  {
    if (2 * cur + 1 <= h->length)
      next_idx = h->arr[2 * cur] < h->arr[2 * cur + 1] ? 2 * cur : 2 * cur + 1;
    else
      next_idx = 2 * cur;

    if (h->arr[cur] > h->arr[next_idx])
      swap(&h->arr[cur], &h->arr[next_idx]);
    else
      break;

    cur = next_idx;
  }
}

void insert(heap *h, int x)
{
  h->arr[++h->length] = x;
  sift_up(h, h->length);
}

int top(heap *h)
{
  return h->arr[1];
}

int pop(heap *h)
{
  int to_return = h->arr[1];

  h->arr[1] = h->arr[h->length--];
  sift_down(h, 1);

  return to_return;
}

bool is_empty(heap *h)
{
  return h->length == 0;
}

__attribute__((unused)) void print(heap *h)
{
  for (int i = 1; i <= h->length; ++i)
    printf("%i ", h->arr[i]);
  printf("\n");
}

int main()
{
  const size_t buffer_length = 1024 * 1024 * 16;
  unsigned char buffer[buffer_length];
  Arena a = {0};
  arena_init(&a, buffer, buffer_length);

  size_t n, m;
  scanf("%zu %zu", &n, &m);

  graph *g = init_graph(&a, n);
  int x, y;
  for (size_t i = 0; i < m; ++i)
  {
    scanf("%i %i", &x, &y);
    insert_edge(&a, g, x, y);
  }

  bool seen[n + 1];
  for (size_t i = 1; i <= n; ++i)
    seen[i] = false;

  heap *h = init_heap(&a, n);
  insert(h, 1);
  seen[1] = true;
  while (!is_empty(h))
  {
    int cur = pop(h);
    printf("%i ", cur);

    node *neighbour = g->list[cur];
    while (neighbour != NULL)
    {
      if (!seen[neighbour->val])
      {
        seen[neighbour->val] = true;
        insert(h, neighbour->val);
      }
      neighbour = neighbour->next;
    }
  }
  printf("\n");

  a.arena_free(&a);
  return 0;
}
