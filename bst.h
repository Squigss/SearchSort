#ifndef _BSTH_
#define _BSTH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct dic {
  char *word;
  struct dic *left;
  struct dic *right;
};
typedef struct dic dic;

/*enum bool {not_in_dictionary, in_dictionary};
typedef enum bool bool;*/

dic* dic_init(int size);
bool dic_isin(dic* s, char* v);
void dic_insert(dic* s, char* v);
void dic_free(dic** s);

#endif
