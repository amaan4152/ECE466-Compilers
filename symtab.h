#ifndef __SYMTAB_H
#define __SYMTAB_H

#include "ast.h"
/*
***ADD LABELS AND TYPEDEF LAST***
*/
struct sym_var
{
    int offset, stg;
    struct astnode *type; //stg = storage class
};

struct sym_func
{
    struct astnode *ret_type, *args_type, *body;
    struct sym_ent *fndef; //link a function declaration with its definition or vise versa
    struct sym_ent *fn_table; 
    int stg, bool_inline : 1, bool_fndef: 1;
};

struct sym_struction //symbol table for struct/union
{
    struct astnode *struction;
};

struct sym_struction_mem //symbol entry for struct/union member
{
    struct astnode *type; 
    int struct_offset, bit_width, bit_offset; //struct_offset = 0 for unions
};

struct sym_enum
{
    struct sym_ent *econsts; 
};

struct sym_econst //enum constant
{
    int value;
};

struct sym_block
{
    struct sym_ent *block_ent;
};

struct sym_attr
{
    int sym_type; 
    union
    {
        struct sym_var s_var;
        struct sym_func s_func;
        struct sym_struction s_su;
        struct sym_struction_mem s_su_mem; //struct/union member
        struct sym_enum s_enum;
        struct sym_econst s_econst; //enum constant
        struct sym_block s_block; 
    };
};

struct sym_ent 
{
    int scope, namespace, line_no; 
    char filename[4096], name[4096];
    struct sym_attr s_attr;

    struct sym_ent *next; //propogate HEAD/TAIL nodes throughout the table
};


/*
        -from innermost scope-stack to outermost scope-stack 
        -last stack is always file-scope stack
*/
struct sym_tab
{
    int scope;
    struct sym_ent *head,*tail; //head and tail of symbol table at scope 'scope'
    struct sym_tab *next;
};

void install_decl(struct sym_tab **, struct astnode **, int *, int *);
void debug(char *, int);

struct sym_tab *table_create(int);  //creates new symbol table
struct sym_ent *sym_create(int, int, int, int, char *);    //creates new symbol
struct sym_tab *stack_pop(struct sym_tab **); //returns previous symbol table in outer scope
void stack_push(struct sym_tab **, int);

/*
    ---Paramaters---
        @arg1 = table
        @arg2 = scope
        @arg3 = name
        @arg4 = namespace
        @arg5 = boolean pointer to verify if the entry has been found in the given scope or found in outer scopes
*/
struct sym_ent *sym_lookup(struct sym_tab **, int, int, char *); //returns associated symbol table entry

int type_equality(struct astnode *, struct astnode *);
int redecl_boolstate(struct sym_ent *, struct sym_attr , int);


/*
    @arg1 = entire scope stacks with their associated tables
    @arg2 = scope
    @arg3 = namespace
    @arg4 = name
    @arg5 = struct of attributes for the associated entry

    -Install symbol table entry into a table with a specific scope
*/
struct sym_ent *sym_enter(struct sym_tab **, struct sym_attr, int, int, char *, int, char *); 
int t_sizeof(struct astnode *);
void offset_update(struct sym_attr *, int *);
struct astnode *get_symType(struct astnode *);
char *scope_print(int);
void sym_print(struct sym_ent *, int);

#endif
