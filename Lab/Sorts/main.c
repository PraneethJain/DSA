#include "sort.h"

int main()
{

    srand(time(NULL));

    clock_t start, end;
    double execution_time;

    int tc;
    scanf("%i", &tc);

    while (tc--)
    {
        int n;
        scanf("%d", &n);

        Data list[n];

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &list[i].a);
            scanf("%f", &list[i].b);
            scanf("%s", list[i].c);
        }
        start = clock();

        // qsort(list, n, sizeof(Data), comparator1);
        // SelectionSort(list, n);
        // InsertionSort(list,n);
        // BubbleSort(list,n);
        // MergeSort(list,0,n-1);
        // HeapSort(list,n);

        end = clock();

        execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Execution time for %d elements: %f\n", n, execution_time);

        // printf("\nSorted list:\n");
        // printList(list, n);
    }
}