#ifndef __AST_H
#define __AST_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include "symtab.h"
#include "extdef.h"

/* SYMBOL TABLE */
enum NMSPACE {TAG, MEMBER, OTHER}; //namespace OTHER => enum consts, typedef names, vars, or func names
enum SYM_TYPE {SYM_VAR, SYM_FUNC, SYM_STRUCTION, SYM_SU_MEM, SYM_ENUM, SYM_ECONST, SYM_BLOCK};
enum SCOPE {GLOBAL, BLOCK, FUNC, PROTO};

/*
    stgclass = 0 implies there is no explicit storage class
    This is especially important for declarations in file scope 
    because a variable with EXTERN_CLASS implies no machine code generation. 
    If it doesn't have EXTERN_CLASS then machine code generation occurs for that variable
*/
enum STG {EXTERN_CLASS = 1, STATIC_CLASS, AUTO_CLASS, REGISTER_CLASS, TYPEDEF_CLASS};

/* AST */ 
enum astnode_type {AST_TOP, AST_BOP, AST_FNCALL, AST_ELIST, AST_ASSIGN, AST_EQCOMP, AST_LOG, 
                   AST_TERN, AST_COMP_SEL, AST_UOP, AST_NUM, AST_IDENT, AST_STR, AST_CHAR,
                   AST_PTR, AST_SCALAR, AST_ARRAY, AST_STRUCTION, AST_QUAL, AST_STG, AST_DECL,
                   AST_FUNC, AST_CMPD, AST_ITEM, AST_IF, AST_IF_ELSE, AST_DO, AST_WHILE, AST_FOR,
                   AST_BREAK, AST_CONT, AST_RET, AST_CAST, AST_TEMP};

struct astnode_decl
{
    struct astnode *decl, *next;
};

struct astnode_compound
{
    struct astnode *item_list, *next; 
};

struct astnode_item 
{
    struct astnode *decl_or_stmt, *next; 
};

struct astnode_if
{
    struct astnode *expr, *body;
};

struct astnode_if_else
{
    struct astnode *expr, *if_body, *else_body;
};

struct astnode_do
{
    struct astnode *expr, *body;
};

struct astnode_while
{
    struct astnode *expr, *body;
};

struct astnode_for
{
    struct astnode *init_expr, *expr_1, *expr_2, *body;
};

struct astnode_break
{
    int op;
};

struct astnode_continue
{
    int op;
};

struct astnode_return
{
    int op; 
    struct astnode *ret_expr;
};

struct astnode_stgclass
{
    int stg; 
    struct astnode *next;
};

struct astnode_qual
{
    int qual; 
    struct astnode *next; 
};

struct astnode_ptr
{
    /*
        -in this case, *next points to the next node in parse tree
        -*ptr_to points to the correct node 
    */
    struct astnode *qual_l;
    struct astnode *next; 
};

struct astnode_scalar
{
    int type, signedness, cmplx_bool;
    struct astnode *next, *qualifier; 
};

//ARRAY TYPE != function, void, type of unkown size
struct astnode_array
{
    int arr_size;
    struct astnode *next;
};

struct astnode_struction
{
    int size;
    struct sym_tab *mini_scope;
    struct astnode *next;
};

struct astnode_funcall
{
    int argc;
    struct astnode *left, *right;
};

struct astnode_func
{
    struct astnode *ret_type, *params, *next; 
};

struct astnode_cast
{
    struct astnode *type, *to; 
};

struct astnode_bop 
{
    int op; 
    struct astnode *left, *right; 
};

struct astnode_elist
{
    int argnum;
    struct astnode *left, *right;
};

struct astnode_assign
{
    int op;
    struct astnode *left, *right; 
};

struct astnode_uop
{
    int op;
    struct astnode *left, *right;
};

struct astnode_comp_sel
{
    struct astnode *left, *right;
};

struct astnode_eqcomp
{
    int op;
    struct astnode *left, *right;
};

struct astnode_log
{
    int op; 
    struct astnode *left, *right;
};

struct astnode_tern
{
    int op;
    struct astnode *left, *right;
};

struct astnode_num
{
    unsigned long long i_val; 
    long double fd_val;
    int type : 4;
};

struct astnode_str
{
    char str[4096]; 
    int len; 
};

struct astnode_char
{
    char chr;
};

struct astnode_ident
{
    int line_no;
    char name[4096], filename[4096];
    struct sym_ent *metadata; 
    struct astnode *next, *head;
};

struct astnode_temp
{
    int temp_num;         //temp register index (unique)
    struct astnode *next, *type; 
};

typedef struct astnode
{
    int nodetype; //type of  astnode (capture value from enum)
    union //anonymous union; can call union memobers directly from struct astnode
    {
        struct astnode_cast cast; 
        struct astnode_compound cmpd_stmt; 
        struct astnode_item item;
        struct astnode_if if_stmt;
        struct astnode_if_else if_else_stmt; 
        struct astnode_do do_stmt; 
        struct astnode_while while_stmt; 
        struct astnode_for for_stmt; 
        struct astnode_break break_stmt; 
        struct astnode_continue cont_stmt; 
        struct astnode_return ret_stmt; 
        struct astnode_decl declaration; 
        struct astnode_stgclass stgclass; 
        struct astnode_qual qualif; 
        struct astnode_scalar scalar;
        struct astnode_ptr ptr;
        struct astnode_array array;
        struct astnode_struction su;
        struct astnode_func func; 
        struct astnode_bop bop;
        struct astnode_funcall fncall; 
        struct astnode_elist elist;
        struct astnode_assign assign;
        struct astnode_eqcomp eqcomp;
        struct astnode_log log;
        struct astnode_tern tern;
        struct astnode_comp_sel comp_sel;
        struct astnode_uop uop;
        struct astnode_num num;
        struct astnode_str str_lit;
        struct astnode_char char_lit;
        struct astnode_ident ident;

        struct astnode_temp temp; 
    }; 
}t_astn;

/* Functions */

int node_search(t_astn *, int);
struct astnode* astnode_lloc(int);
struct astnode *for_node_init(struct astnode **, struct astnode **, struct astnode **);
void ast_reverse(struct astnode **);
void append_ast(struct astnode **, struct astnode **);

char cesc_seq(char *);
char nesc_seq(char *, char);
char *print_kwop(int);
void format(char, char **);
void yyerror(char *);
void fatal_err(char *);

void print_ast(struct astnode *, int);
void check_typespec(struct astnode **);

#endif