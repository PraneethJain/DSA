#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define STRLEN 20

typedef struct Data
{
    int a;
    float b;
    char c[STRLEN];
} Data;
typedef Data *DataPtr;

int comparator1(const void *a, const void *b);
void printList(DataPtr list, int size);

void SelectionSort(Data a[], int n);
void InsertionSort(Data a[], int n);
void BubbleSort(Data a[], int n);
void MergeSort(Data a[], int l, int r);

typedef struct heap
{
  size_t capacity;
  Data *arr;
  size_t length;
} heap;

heap *init_heap(size_t capacity);
void sift_up(heap *h, size_t idx);
void sift_down(heap *h, size_t idx);
void insert(heap *h, Data x);
Data pop(heap *h);
bool is_empty(heap *h);

void HeapSort(Data a[], int n);

#endif