#ifndef __POINTERS
#define __POINTERS

extern int unique_elements_count;

int str_length(const char *string);

void reverseString(char *str, int length);
int *uniqueElements(int *arr, int length);
char *compressString(char *str, int length);
int **transpose(int **matrix, int NumRow, int NumCol);

#endif