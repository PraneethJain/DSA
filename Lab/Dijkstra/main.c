#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int min(int x, int y)
{
  return x < y ? x : y;
}

typedef struct node
{
  int val;
  int weight;
  struct node *next;
} node;

node *init_node(int val, int weight)
{
  node *n = (node *)malloc(sizeof(node));
  n->val = val;
  n->weight = weight;
  n->next = NULL;

  return n;
}

typedef struct graph
{
  size_t n;
  node **list;
} graph;

graph *init_graph(size_t n)
{
  graph *g = (graph *)malloc(sizeof(graph));
  g->n = n;
  g->list = (node **)malloc(sizeof(node *) * (g->n + 1));
  for (size_t i = 1; i <= n; ++i)
    g->list[i] = NULL;

  return g;
}

void insert_edge(graph *g, int x, int y, int weight)
{
  node *temp = g->list[x];
  g->list[x] = init_node(y, weight);
  g->list[x]->next = temp;
}

void print_graph(graph *g)
{
  for (size_t i = 1; i <= g->n; ++i)
  {
    node *cur = g->list[i];
    printf("%zu: ", i);
    while (cur != NULL)
    {
      printf("%i %i\t", cur->val, cur->weight);
      cur = cur->next;
    }
    printf("\n");
  }
}

void free_ll(node *n)
{
  if (n == NULL)
    return;

  free_ll(n->next);
  free(n);
}

void free_graph(graph *g)
{
  for (size_t i = 1; i <= g->n; ++i)
  {
    free_ll(g->list[i]);
  }
  free(g->list);
  free(g);
}

int main()
{
  printf("Number of vertices: ");
  size_t n;
  scanf("%zu", &n);
  graph *g = init_graph(n);
  printf("Number of edges: ");
  size_t e;
  scanf("%zu", &e);

  int a, b, w;
  for (size_t i = 0; i < e; ++i)
  {
    scanf("%i %i %i", &a, &b, &w);
    insert_edge(g, a, b, w);
  }

  print_graph(g);

  bool known[n + 1];
  int cost[n + 1];
  int prev[n + 1];
  for (size_t i = 1; i <= n; ++i)
  {
    known[i] = false;
    cost[i] = INT_MAX;
    prev[i] = -1;
  }

  printf("Node to start from: ");
  int start;
  scanf("%i", &start);
  cost[start] = 0;
  while (1)
  {
    int min_cost_vertex = -1;
    int min_cost = INT_MAX;
    for (size_t i = 1; i <= n; ++i)
    {
      if (!known[i] && cost[i] < min_cost)
      {
        min_cost = cost[i];
        min_cost_vertex = i;
      }
    }

    if (min_cost_vertex == -1)
      break;

    known[min_cost_vertex] = true;

    node *n = g->list[min_cost_vertex];
    while (n != NULL)
    {
      if (min_cost + n->weight < cost[n->val])
      {
        cost[n->val] = min_cost + n->weight;
        prev[n->val] = min_cost_vertex;
      }
      n = n->next;
    }
  }

  for (size_t i = 1; i <= n; ++i)
    printf("%i ", cost[i]);
  printf("\n");

  for (size_t i = 1; i <= n; ++i)
    printf("%i ", prev[i]);
  printf("\n");

  free_graph(g);

  return 0;
}
