#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

enum OPS {ADD, SUB, MUL, DIV, BRGE, BRLT, CMP, BR};
enum BB_T {FOR, IF, STD};

struct quad
{
   int op; 
   char res, src1, src2; 
   struct quad *next;
};

struct for_bb
{  
   struct basic_block *b_body, *b_break; 
};

struct if_bb
{
   struct basic_block *bt, *bf; 
};

struct std_bb
{
   struct basic_block *next; 
};

struct basic_block
{
   int bb_type; 
   struct quad *head, *tail;
   union 
   {
      struct for_bb for_bb; 
      struct if_bb if_bb; 
      struct std_bb std_bb; 
   };
   
};

struct quad *quad_create(int op, char res, char s1, char s2)
{
   struct quad *new_quad = NULL;
   if((new_quad = (struct quad *)malloc(sizeof(struct quad))) == NULL)
   {
      fprintf(stderr, "Error mallocating bhenchod: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
   new_quad->op = op;
   new_quad->res = res; 
   new_quad->src1 = s1;
   new_quad->src2 = s2;
   new_quad->next = NULL;
   return new_quad; 
}

struct basic_block *bb_create(int type)
{
   struct basic_block *new_bb = NULL;
   if((new_bb = (struct basic_block *)malloc(sizeof(struct basic_block))) == NULL)
   {
      fprintf(stderr, "Error mallocating bhenchod: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
   new_bb->bb_type = type; 
   new_bb->head = NULL;
   new_bb->tail = NULL;
   return new_bb;
}

void add_quad(struct basic_block **entry, struct quad **q)
{
   struct basic_block *bb_temp = *entry;
   if(!bb_temp->head)
   {
      bb_temp->head = *q; 
      bb_temp->tail = *q;
   }
   else
   {
      bb_temp->tail->next = *q; 
      bb_temp->tail = *q; 
   }
}

void test_bed()
{
   //BB0
   struct basic_block *bb0 = bb_create(STD);
   struct quad *quads_bb0[] = {quad_create(ADD, 'x', 'l', 'r'),
                              quad_create(MUL, 'a', 'x', 'a'),
                              quad_create(ADD, 'b', 'l', 'a')};
   for(int i = 0; i < 3; ++i)
      add_quad(&bb0, &quads_bb0[i]);

   //BB1
   struct basic_block *bb1 = bb_create(FOR);
   struct quad *quads_bb1[] = {quad_create(ADD, 'a', 'a', 'b'),
                              quad_create(CMP, 0, 'a', 100)};     //char 0 implies no result; char 100 implies int 100
   for(int i = 0; i < 2; ++i)
      add_quad(&bb0, &quads_bb1[i]);

   //BB2
   struct basic_block *bb1 = bb_create(IF);
   struct quad *quads_bb1[] = {quad_create(ADD, 'y', 'a', 'l'),
                              quad_create(CMP, 0, 'y', 'x')};     //char 0 implies no result; char 100 implies int 100
   for(int i = 0; i < 2; ++i)
      add_quad(&bb0, &quads_bb1[i]);
}

int main(void)
{ 
   int a = 0;
   while(a += 2 && a < 100)
   {

   }
   return 1;
}