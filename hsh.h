#ifndef _HASHH_
#define _HASHH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

struct dic {
  char **data;
  int size_array;
  int num_words;
  int word_size;
};
typedef struct dic dic;

dic* dic_init(int size);
bool dic_isin(dic* s, char* v);
void dic_free(dic** s);
void dic_insert(dic* s, char* v);

#endif
