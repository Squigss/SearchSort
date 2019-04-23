#include "bst.h"

#define NOT_IN_DIC 0
#define IN_DIC 1

/*=========================
CREATES AN EMPTY DICTIONARY
===========================*/
dic* dic_init(int size)
{
   dic* empty_dic;

   empty_dic = (dic*)calloc(1, sizeof(dic));
   if(empty_dic == NULL) {
      printf("Dictionary structure not created\n");
   }

   empty_dic->word = (char*)calloc(size+1, sizeof(char));
   if(empty_dic->word == NULL) {
      printf("Dictionary structure not created\n");
   }

   /*assign the pointers*/
   empty_dic->left = NULL;
   empty_dic->right = NULL;

   return empty_dic;
}


/*============================
INSERTING A NODE INTO THE TREE
==============================*/
void dic_insert(dic* s, char* v)
{
   dic* new_node;
   int size_string;

   size_string = strlen(v);

   if(s->word == NULL) {
      strcpy(s->word, v);
   }

   /*Left insertion of word*/
   if(0 < strcmp(s->word, v)) {
      if(s->left == NULL) {
         new_node= dic_init(size_string);
         strcpy(new_node->word, v);
         s->left = new_node;
      }
      else {
         dic_insert(s->left, v);
      }
   }

   /*Right insertion of word*/
   else {
      if (s->right == NULL) {
         new_node= dic_init(size_string);
         strcpy(new_node->word, v);
         s->right = new_node;
      }
      else {
         dic_insert(s->right, v);
      }
   }
}

/*====================================================
CHECKING WHETHER THE WORD IS ALREADY IN THE DICTIONARY
======================================================*/
bool dic_isin(dic* s, char* v)
{
   if (s==NULL) {
      return NOT_IN_DIC;
   }

   if (strcmp(s->word, v)==0) {
      return IN_DIC;
   }

   if(0 < strcmp(s->word, v)) {
      return dic_isin(s->left, v);
   }
   else {
      return dic_isin(s->right, v);
   }
}

/*=======================
FREEING UP THE DICTIONARY
=========================*/
void dic_free(dic** s)
{
   dic* free_dic = *s;

   if(*s==NULL) {
      return;
   }

   dic_free(&(free_dic->left));
   dic_free(&(free_dic->right));

   free(free_dic->word);

   free(free_dic);
   *s = NULL;
}
