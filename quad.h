#ifndef __QUADS_H
#define __QUADS_H
#include "ast.h"

enum OPS {MOV = 1, LOAD, LEA, CMP, MUL, DIV, MOD, ADD, SUB, RET, CALL, STORE, ARG};
enum BBCOND {BR = 1, BREQ, BRNE, BRLT, BRLE, BRGT, BRGE};
enum MODE {M_DIRECT = 1, M_INDIRECT};

//res = op src_l, src_r
typedef struct quad
{
    int op; 
    t_astn *res;
    t_astn *src_l; 
    t_astn *src_r; 
    struct quad *next; 
}t_quad; 

//Format: .BB.F.N
typedef struct basic_block
{
    int f_num; // F
    int bb_index; // N
    int branch_cond; //branching condition
    t_quad *quad_head, *quad_tail; 
    struct basic_block *left, *right;
    struct basic_block *next, *head;  
}bb; 

typedef struct bb_list
{
    struct basic_block *head, *tail;
}bbl; 

typedef struct string_asm_data
{
    int index; 
    char str[4096]; 
    struct string_asm_data *head, *tail, *next;
}str_dat;

/*
    @arg1 -> res for new quad
    @arg2 -> OP for new quad
    @arg3 -> src1 for new quad
    @arg4 -> src2 for new quad

    Append new quad to list of quads
*/
int op2QuadOP(int);
t_quad *emit(t_astn *, int, t_astn *, t_astn *);
void q_append(bb **, t_quad **);

void new_strDatum(int, char *);
void strDatum_append(str_dat **, str_dat **);
int get_strDataIndex(t_astn *);

bb *bbnew(void);
bb *bballoc(void);
bbl *bblnew(void);
void bb_append(bbl **, bb **);
void bb_brancher(bb *, int , bb *, bb *);

t_astn *gen_lval(t_astn *, int *);
t_astn *gen_rval(t_astn *, t_astn *);
t_astn *gen_assign(t_astn *);
t_astn *gen_temp(void);
t_astn *gen_fncall(t_astn *, t_astn *);
void gen_cond(t_astn *, bb *, bb *);
void gen_if(t_astn *);
void gen_while(t_astn *);
void gen_ret(t_astn *);
void gen_cont(void);
void gen_break(void);
void stmt_qgen(t_astn *);

void print_rval(t_astn *);
void print_quads(t_quad *);
void print_bblabel(bb *);
void print_bb(bb *);

void IR_gen(FILE *, struct sym_tab *, t_astn *);

/* --- TARGET CODE GEN ---*/
void global_asm(FILE *, struct sym_ent *);
void local_asm(FILE *, bb *);
void QUAD_ASMGEN(FILE *, t_quad *);
void TARGET_ASMGEN(FILE *, t_astn *);

#endif