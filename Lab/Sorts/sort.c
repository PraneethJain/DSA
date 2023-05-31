#include "sort.h"
#define ll long long

ll times_swapped = 0;
void swap(Data *a, Data *b)
{
  Data temp = *a;
  *a = *b;
  *b = temp;
  ++times_swapped;
}

ll times_compared = 0;
int comparator1(const void *a, const void *b)
{
  DataPtr da = (DataPtr)a;
  DataPtr db = (DataPtr)b;
  ++times_compared;
  return strcmp(da->c, db->c) < 0;
}

void printList(DataPtr list, int size)
{
  for (int i = 0; i < size; i++)
    printf("%d, %f, %s\n", list[i].a, list[i].b, list[i].c);
}

// Sorting Algorithms

void InsertionSort(Data a[], int n)
{
  times_compared = 0;
  times_swapped = 0;
  for (size_t i = 1; i < n; ++i)
    for (size_t j = i; j > 0; --j)
      if (comparator1(&a[j], &a[j - 1]))
        swap(&a[j], &a[j - 1]);
      else
        break;

  printf("Compared %lli times\n", times_compared);
  printf("Swapped %lli times\n", times_swapped);
}

void BubbleSort(Data a[], int n)
{
  times_compared = 0;
  times_swapped = 0;
  for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < n - 1; ++j)
      if (comparator1(&a[j], &a[j + 1]))
        swap(&a[j], &a[j + 1]);
  printf("Compared %lli times\n", times_compared);
  printf("Swapped %lli times\n", times_swapped);
}

void SelectionSort(Data a[], int n)
{
  times_compared = 0;
  times_swapped = 0;
  for (size_t i = 0; i < n; ++i)
  {
    size_t min_idx = i;
    for (size_t j = i; j < n; ++j)
      if (comparator1(&a[j], &a[min_idx]))
        min_idx = j;
    swap(&a[i], &a[min_idx]);
  }
  printf("Compared %lli times\n", times_compared);
  printf("Swapped %lli times\n", times_swapped);
}

void MergeSort(Data a[], int l, int r)
{
  if (l >= r)
    return;

  int mid = (l + r) / 2;
  MergeSort(a, l, mid);
  MergeSort(a, mid + 1, r);

  size_t idx_1 = l;
  size_t idx_2 = mid + 1;
  Data sorted[r + 1];
  size_t sorted_idx = l;
  while (idx_1 <= mid && idx_2 <= r)
  {
    if (comparator1(&a[idx_1], &a[idx_2]))
      sorted[sorted_idx++] = a[idx_1++];
    else
      sorted[sorted_idx++] = a[idx_2++];
  }
  if (idx_1 > mid)
    for (size_t i = idx_2; i <= r; ++i)
      sorted[sorted_idx++] = a[i];
  else
    for (size_t i = idx_1; i <= mid; ++i)
      sorted[sorted_idx++] = a[i];

  for (size_t i = l; i <= r; ++i)
    a[i] = sorted[i];
}

heap *init_heap(size_t capacity)
{
  heap *h = (heap *)malloc(sizeof(heap));

  h->capacity = capacity;
  h->length = 0;
  h->arr = (Data *)malloc(sizeof(Data) * (capacity + 1));

  return h;
}

void sift_up(heap *h, size_t idx)
{
  size_t cur = idx;
  while (cur != 1 && comparator1(&h->arr[cur], &h->arr[cur / 2]))
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
      next_idx = comparator1(&h->arr[2 * cur], &h->arr[2 * cur + 1]) ? 2 * cur : 2 * cur + 1;
    else
      next_idx = 2 * cur;

    if (comparator1(&h->arr[next_idx], &h->arr[cur]))
      swap(&h->arr[cur], &h->arr[next_idx]);
    else
      break;

    cur = next_idx;
  }
}

void insert(heap *h, Data x)
{
  h->arr[++h->length] = x;
  sift_up(h, h->length);
}

Data pop(heap *h)
{
  Data to_return = h->arr[1];

  h->arr[1] = h->arr[h->length--];
  sift_down(h, 1);

  return to_return;
}

bool is_empty(heap *h)
{
  return h->length == 0;
}

void HeapSort(Data a[], int n)
{
  heap *h = init_heap(2 * n);
  for (size_t i = 0; i < n; ++i)
    insert(h, a[i]);

  size_t count = 0;
  while (!is_empty(h))
    a[count++] = pop(h);

  free(h->arr);
  free(h);
}
