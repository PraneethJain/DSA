#ifndef __ARRAY
#define __ARRAY

extern int max_min_array_size;
extern int intersection_array_size;

int str_length(const char *string);

int *intersectionArray(int *Arr1, int *Arr2, int lenArr1, int lenArr2);
int countCharOccurences(const char *str, int length, char ch);
char findFirstNonRepeatingChar(const char *str, int length);
char *findLongestCommonPrefix(char **str, int numStr, int maxLen);
int *maxMin(int *Arr, int lenArr);

#endif
