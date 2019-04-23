#include "hsh.h"

#define ASCII 97
#define NOT_PRIME 0
#define IS_PRIME 1
#define NOT_IN_DIC 0
#define IN_DIC 1
#define INSUFFICIENT 0
#define ENOUGH_SPACE 1
#define PROBE 2

int hash(char *v, int size);
int remaining_space(dic *s);
dic* dic_resized(dic* s);
void rehash(char **tempo, dic* s, char* v);
int prime_number(int size);



/*=========================
Creates an empty dictionary
===========================*/
dic* dic_init(int size)
{
   dic* dict;
   int i;
   int array_size = 11;

   /*Creates space for the dic structure*/
   dict = (dic*)calloc(1, sizeof(dic));
   if(dict == NULL) {
      printf("Dictionary structure not created\n");
   }

   /*Creates space for an array of char pointers*/
   dict->data = (char**)calloc(array_size, sizeof(char*));
   if(dict->data == NULL) {
      printf("Empty char pointer array not created\n");
   }

   /*creates space for the words to be inserted*/
   for (i=0; i< array_size; i++) {
      dict->data[i] = (char*)calloc(size, sizeof(char));
      if(dict->data[i] == NULL) {
         printf("Empty word array not created\n");
      }
   }

   /*assigning values to the remaining variables in the dic struct*/
   dict->size_array = array_size;
   dict->word_size = size;
   dict->num_words= 0;

   return dict;
}

/*========================================================
CHECKING THE WORD DOES NOT ALREADY EXIST IN THE Dictionary
==========================================================*/
bool dic_isin(dic* s, char* v)
{
   int index, i;

   index = hash(v, s->size_array);

   for(i=0; i< s->size_array; i++) {
      if (s->data[index][0] == '\0') {
         return NOT_IN_DIC;
      }
      else if (strcmp(s->data[index], v)==0) {
         return IN_DIC;
      }
      else {
         if (index < s->size_array-2) {
            index += PROBE;
         }
         else {
            index= 0;
         }
      }
   }
   return NOT_IN_DIC;
}

/*==================================
Adds one element into the dictionary
====================================*/
void dic_insert(dic* s, char* v)
{
   int index, word_len;

   index = hash(v, s->size_array);

   /*checks a word is not already at that index*/
   while (s->data[index][0] != '\0') {
      if (index < s->size_array-2) {
         index += PROBE;
      }
      else {
         index= 0;
      }
   }

   /*adjust size of space made for our string*/
   word_len=(strlen(v));
   s->data[index] = (char*)realloc(s->data[index], word_len+1);
   if(s->data[index] == NULL) {
      printf("Word array not created\n");
   }

   /*inserts the word*/
   strcpy(s->data[index], v);
   s->num_words++;

   /*checks enough space is remaining in dict for future
   insertions.If not, the dict is resized.*/
   if (remaining_space(s)==INSUFFICIENT) {
      s = dic_resized(s);
   }
}

/*===============
HASH FUNCTION
=================*/
int hash(char *v, int size)
{
   int value_of_letter, hash_key;
   unsigned long power_value, sum_letters=0;
   int i=0;

   while (tolower(*v)!='\0') {
      value_of_letter = *v - ASCII;
      power_value = pow(26, i);
      sum_letters = sum_letters + value_of_letter*power_value;
      i++;
      v++;
   }
   hash_key= sum_letters % size;

   return hash_key;
}

/*==============================================
CHECKS THE AMOUNT OF SPACE REMAINING IN THE DICT
================================================*/
int remaining_space(dic *s)
{
   int empty_spaces;

   empty_spaces = s->size_array - s->num_words;

   if (empty_spaces < s->size_array/2) {
      return INSUFFICIENT;
   }
   return ENOUGH_SPACE;
}


/*=========================
Creates a bigger dictionary
===========================*/
dic* dic_resized(dic* s)
{
   int i, new_size, previous_size;
   char **tempo;

   previous_size = s->size_array;
   new_size= (s->size_array)*2;

   if (prime_number(new_size)==NOT_PRIME) {
      new_size++;
   }
   s->size_array = new_size;

   /*Creating space in memory for the pointer to a char pointer*/
   tempo = (char**)calloc(new_size, sizeof(char*));
   if(tempo == NULL) {
      printf("Pointer array not created\n");
   }

   /*creating space for words before inserting them*/
   for (i=0; i<new_size; i++) {
      tempo[i] = (char*)calloc(s->word_size, sizeof(char));
      if(tempo[i] == NULL) {
         printf("Word array not created\n");
      }
   }

   /*rehashing words to save in the new temporary dictionary*/
   for(i=0; i<previous_size; i++) {
      rehash(tempo, s, s->data[i]);
      free(s->data[i]);
   }
   free(s->data);
   s->data = tempo;

   return s;
}

/*=========================
REHASHING AND REINSERTION:(
==========================*/
void rehash(char** tempo, dic* s, char* v)
{
   int index, word_len;

   index = hash(v, s->size_array);

   /*loop to ensure we are not inserting a
   word where there is already one*/
   while (tempo[index][0] != '\0') {
      if (index < s->size_array) {
         index += 2; /*probing linearly 2 by 2*/
      }
      if (index >= s->size_array) {
         index= 0;
      }
   }
   /*reallocating space for the word so it is exactely the same
   size as the word to save some memory*/
   word_len=(strlen(v));
   tempo[index] = (char*)realloc(tempo[index], word_len+1);
   if(tempo[index] == NULL) {
      printf("Word array not created\n");
   }
   strcpy(tempo[index], v);
}



/*=========================================
FUNCTION TO CHECK WHETHER A NUMBER IS PRIME
===========================================*/
int prime_number(int size)
{
   int i;

   for(i=2; i<size; i++) {
     if (size % i == 0) {
       return NOT_PRIME;
     }
   }
   return IS_PRIME;
}


/**************Functions to clear memory****************/
/*=============================================
Clears all space used, and sets pointer to NULL
==============================================*/
void dic_free(dic** s)
{
   dic* free_dic = *s;
   int i;

   for (i=0; i<free_dic->size_array; i++) {
      free(free_dic->data[i]);
   }
   free(free_dic->data);
   free(free_dic);
}
