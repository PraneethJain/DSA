#ifndef __POINTERS
#define __POINTERS

extern int unique_elements_count;

void swap(char *x, char *y);
void reverseString(char *str, int length);
int *uniqueElements(int *arr, int length);
char *compressString(char *str, int length);
int **transpose(int **matrix, int NumRow, int NumCol);
int ceil_log_10(int x);
char *int_to_str(int x);

#endif