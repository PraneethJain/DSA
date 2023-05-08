#ifndef __HEAP_H
#define __HEAP_H

#include <stdio.h>

typedef struct heap
{
  size_t capacity;
  int *arr;
  size_t length;
} heap;

#endif
