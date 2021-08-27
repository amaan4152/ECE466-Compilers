#include "quad.h"
#include "parser.tab.h"

enum OPS Q_OPS;
enum BBCOND BB_CONDS;
enum MODE MODES;

bbl *bb_list = NULL;
bb *curr_bb = NULL, *curr_loop = NULL; 
char buf[4096];
str_dat *dat_list; 
int str_label_index = 0; 
int bb_fnum = 1; 
int bb_bnum = 1; // for BB labels
int temp_num = 0;             // for temp register names
int stack_offset;



int op2QuadOP(int op)
{
    switch(op)
    {
        case '+':   return ADD; 
        case '-':   return SUB;
        case '*':   return MUL; 
        case '/':   return DIV;
        case '%':   return MOD; 
    }
}

t_quad *emit(t_astn *r, int op, t_astn *s1, t_astn *s2)
{
    t_quad *quad = NULL; 
    if((quad = (t_quad *)malloc(sizeof(t_quad))) == NULL)
        fatal_err(strerror(errno));
    quad->res = r;
    quad->op = op;
    quad->src_l = s1; 
    quad->src_r = s2; 
    quad->next = NULL;
    q_append(&curr_bb, &quad);
    return quad; 
}

void q_append(bb **bb, t_quad **quad)
{
    if((*bb)->quad_head == NULL)
    {
        (*bb)->quad_head = *quad;
        (*bb)->quad_tail = *quad;
    }
    else
    {
        (*bb)->quad_tail->next = *quad; 
        (*bb)->quad_tail = *quad;
    }
}

bbl *bblnew(void)
{
    bbl *new_bbl = NULL;
    if((new_bbl = (bbl *)malloc(sizeof(bbl))) == NULL)
        fatal_err(strerror(errno));
    new_bbl->head = NULL;
    new_bbl->tail = NULL;
    return new_bbl;
}

bb *bbnew(void)
{
    bb *basic_block = NULL;
    if((basic_block = (bb *)malloc(sizeof(bb))) == NULL)
        fatal_err(strerror(errno));
    basic_block->f_num = bb_fnum; 
    basic_block->bb_index = bb_bnum++; 
    basic_block->head = NULL;
    basic_block->left = NULL, basic_block->right = NULL, basic_block->next = NULL;
    basic_block->quad_head = NULL, basic_block->quad_tail = NULL; 
    return basic_block;
}

bb *bballoc(void)
{
    bb *basic_block = NULL;
    if((basic_block = (bb *)malloc(sizeof(bb))) == NULL)
        fatal_err(strerror(errno));
    basic_block->f_num = bb_fnum; 
    basic_block->bb_index = bb_bnum++; 
    basic_block->left = NULL, basic_block->right = NULL, basic_block->next = NULL;
    basic_block->quad_head = NULL, basic_block->quad_tail = NULL; 
    bb_append(&bb_list, &basic_block);
    curr_bb = basic_block; 
    return basic_block; 
}

void bb_append(bbl **bb_list, bb **new_bb)
{
    bb *bb_cursor = (*bb_list)->head; //points to the current basic block in the bb_list
    if((*bb_list)->head == NULL)
    {
        (*bb_list)->head = *new_bb;
        (*bb_list)->tail = *new_bb;
    }
    else
    {
        (*bb_list)->tail->next = *new_bb;
        (*bb_list)->tail = *new_bb;
    }
}

void bb_brancher(bb *basic_block, int branch_cond, bb *bb_left, bb *bb_right)
{
    basic_block->branch_cond = branch_cond;
    basic_block->left = bb_left;
    basic_block->right = bb_right;
}

t_astn *gen_temp(void)
{
    t_astn *temp_n = astnode_lloc(AST_TEMP);
    temp_n->temp.temp_num = temp_num++;
    temp_n->temp.next = NULL;
    return temp_n; 
}

// NULL return => invalid lvalue
t_astn *gen_lval(t_astn *node, int *mode)
{
    switch(node->nodetype)
    {
        case AST_CHAR: return NULL;
        case AST_STR:  return NULL;
        case AST_NUM:  return NULL;
        case AST_IDENT: *mode = M_DIRECT; return node; 
        case AST_UOP: 
            if(node->uop.op == '*')
            {
                *mode = M_INDIRECT; 
                return gen_rval(node->uop.left, NULL);
            } break; 

    }
    return NULL; 
}

void new_strDatum(int index, char *str)
{
    str_dat *new_datum = NULL;
    if((new_datum = (str_dat *)malloc(sizeof(str_dat))) == NULL)
        fatal_err(strerror(errno));
    new_datum->index = index; 
    memcpy(new_datum->str, str, strlen(str));
    new_datum->head = NULL;
    new_datum->tail = NULL;
    new_datum->next = NULL;
    strDatum_append(&dat_list, &new_datum);
}

void strDatum_append(str_dat **str_dlist, str_dat **datum)
{
    if(*str_dlist == NULL)
    {
        *str_dlist = *datum;
        (*str_dlist)->head = *datum;
        (*str_dlist)->tail = *datum;
    }
    else
    {
        (*str_dlist)->tail->next = *datum; 
        (*str_dlist)->tail = *datum;
    }
}

int get_strDataIndex(t_astn *str_node)
{
    str_dat *datum = dat_list->head;
    while(datum)
    {
        if(strcmp(datum->str, str_node->str_lit.str) == 0)
            return datum->index;
        datum = datum->next;
    }
    return -1; 
}

void STRING_ASMGEN(t_astn *node)
{
    new_strDatum(str_label_index++, node->str_lit.str);
    sprintf(buf + strlen(buf), "\t.section .rodata\n");
    sprintf(buf + strlen(buf), ".STR_RO_%d:\n", dat_list->tail->index);
    sprintf(buf + strlen(buf), "\t.string \"");
    for(int i = 0; i < node->str_lit.len; ++i)
    {
        char c = node->str_lit.str[i];
        char *buf_ptr = buf + strlen(buf);

        /* THANK YOU AMAAN FROM THE PAST FOR MAKING THIS PROCEDURE FROM ASSIGNMENT 1!!! */
        format(c, &buf_ptr);
    }

    sprintf(buf + strlen(buf), "\"\n");
    sprintf(buf + strlen(buf), "\t.data\n");
    sprintf(buf + strlen(buf), "\t.align 4\n");
    sprintf(buf + strlen(buf), ".str_%d:\n", dat_list->tail->index);
    sprintf(buf + strlen(buf), "\t.long .STR_RO_%d\n", dat_list->tail->index);
    
}

t_astn *gen_rval(t_astn *node, t_astn *target)
{
    int l_ntype, r_ntype;
    t_astn *addr = NULL, *expr = NULL, *num = NULL, *temp = NULL;
    t_astn *src_l = NULL, *src_r = NULL, *l_type = NULL, *r_type = NULL; 
    struct sym_ent *l_sym = NULL, *r_sym = NULL; 
    switch(node->nodetype)
    {
        case AST_NUM:   return node; 
        case AST_CHAR:  return node; 
        case AST_STR:
            STRING_ASMGEN(node); 
            return node;

        case AST_IDENT: 
            if(node->ident.metadata->s_attr.sym_type == SYM_VAR)
            {
                if(node->ident.metadata->s_attr.s_var.type->nodetype
                    == AST_ARRAY)
                {
                    temp = gen_temp();
                    temp->temp.type = node;
                    emit(temp, LEA, node, NULL);
                    return temp; 
                }
                else if(node->ident.metadata->s_attr.s_var.type->nodetype == AST_SCALAR
                && node->ident.metadata->s_attr.s_var.stg == AUTO_CLASS)
                {
                    temp = gen_temp();
                    temp->temp.type = node;
                    emit(temp, MOV, node, NULL);
                    return temp; 
                }
            }
            return node;

        case AST_UOP: 
            switch(node->uop.op)
            {
                case '*':
                    addr = gen_rval(node->uop.left, NULL);
                    if(!target)    target = gen_temp();
                    emit(target, LOAD, addr, NULL);
                    return target; 

                case '&':
                    expr = gen_rval(node->uop.left, target);
                    if(!target)    target = gen_temp();
                    emit(target, LEA, expr, NULL);
                    return target; 

                case PLUSPLUS: 
                    expr = gen_rval(node->uop.left, target);
                    if(!target)    target = gen_temp();
                    emit(target, MOV, node->uop.left, NULL);
                    num = astnode_lloc(AST_NUM);
                    num->num.i_val = 1; 
                    num->num.type = I;
                    emit(node->uop.left, ADD, node->uop.left, num);
                    return target; 

                case MINUSMINUS:
                    expr = gen_rval(node->uop.left, target);
                    if(!target)    target = gen_temp();
                    emit(node->uop.left, MOV, NULL, target);
                    num = astnode_lloc(AST_NUM);
                    num->num.i_val = 1; 
                    num->num.type = I;
                    emit(node->uop.left, SUB, node->uop.left, num);
                    return target; 
            }
            return target;

        case AST_BOP: 
            src_l = gen_rval(node->bop.left, target);
            src_r = gen_rval(node->bop.right, target);


            if(src_l->nodetype == AST_TEMP)    
                l_type = src_l->temp.type;
            else    l_type = src_l;

            if(src_r->nodetype == AST_TEMP)    
                r_type = src_r->temp.type;
            else    r_type = src_r;


            if(node->bop.op == '+' || node->bop.op == '-')
            {
                num = astnode_lloc(AST_NUM);
                num->num.type = I; //set type to INT

                if(l_type->nodetype == AST_IDENT)
                    l_sym = l_type->ident.metadata;
                if(r_type->nodetype == AST_IDENT)
                    r_sym = r_type->ident.metadata;

                if(l_sym || r_sym)
                {
                    l_ntype = (l_sym) ? l_sym->s_attr.s_var.type->nodetype : -1;
                    r_ntype = (r_sym) ? r_sym->s_attr.s_var.type->nodetype : -1;
                
                    // ptr + scalar (or num)
                    if((l_ntype == AST_PTR || l_ntype == AST_ARRAY)
                    && (r_type->nodetype == AST_NUM || r_ntype == AST_SCALAR))
                    {
                        temp = gen_temp();
                        num->num.i_val = (l_ntype == AST_PTR) 
                                           ? t_sizeof(l_sym->s_attr.s_var.type->ptr.next)
                                           : t_sizeof(l_sym->s_attr.s_var.type->array.next);
                        emit(temp, MUL, src_r, num);
                        src_r = temp; 
                    }
                    // scalar (or num) + ptr
                    else if((r_ntype == AST_PTR || r_ntype == AST_ARRAY)
                    && (l_type->nodetype == AST_NUM || l_ntype == AST_SCALAR))
                    {
                        temp = gen_temp();
                        num->num.i_val = (r_ntype == AST_PTR) 
                                           ? t_sizeof(r_sym->s_attr.s_var.type->ptr.next)
                                           : t_sizeof(r_sym->s_attr.s_var.type->array.next);
                        emit(temp, MUL, src_l, num);
                        src_l = temp; 
                    }
                    // ptr - ptr (addition NOT allowed)
                    else if((l_ntype == AST_PTR || l_ntype == AST_ARRAY) 
                    && (r_ntype == AST_PTR || r_ntype == AST_ARRAY))
                    {
                        if(node->bop.op == '+')
                            fatal_err("Expression must have integral type");

                        if(type_equality(l_sym->s_attr.s_var.type, r_sym->s_attr.s_var.type))
                        {
                            // %T0000N = SUB addr1, addr2
                            temp = gen_temp();
                            emit(temp, SUB, src_l, src_r);
                            num->num.i_val = (l_ntype == AST_PTR) 
                                           ? t_sizeof(l_sym->s_attr.s_var.type->ptr.next)
                                           : t_sizeof(l_sym->s_attr.s_var.type->array.next);
                            // %T0000(N+1) = DIV T0000N, num
                            emit(target, DIV, temp, num);
                            return target; 
                        }
                        else    fatal_err("[ERROR Incompatiable pointer types]");
                    }
                }             
            }

            if(!target)    target = gen_temp();
            emit(target, op2QuadOP(node->bop.op), src_l, src_r);
            return target;         

        case AST_FNCALL:    return gen_fncall(node, target);
    }
}

t_astn *gen_assign(t_astn *node)
{
    int mode; 
    t_astn *temp;
    t_astn *dst = gen_lval(node->assign.left, &mode);
    if(!dst)    yyerror("[ERROR] lvalue must be a modifiable expression");
    if(mode == M_DIRECT)
    {
        temp = gen_rval(node->assign.right, NULL);
        emit(dst, MOV, temp, NULL);
    }
    else
    {
        temp = gen_rval(node->assign.right, NULL);
        emit(NULL, STORE, temp, dst);
    }
    return dst; 
}

t_astn *gen_fncall(t_astn *node, t_astn *target)
{
    t_astn *elist, *elist_cursor, *arg;
    t_astn *argc = astnode_lloc(AST_NUM);
    argc->num.type = I, argc->num.i_val = node->fncall.argc;

    elist = node->fncall.right;
    elist_cursor = elist;
    while(elist_cursor)
    {
        int arg_ntype = (elist_cursor->elist.right) ? elist_cursor->elist.right->nodetype : 0;
        if(!arg_ntype)     break;

        t_astn *argn = astnode_lloc(AST_NUM);
        argn->num.type = I, argn->num.i_val = argc->num.i_val - elist_cursor->elist.argnum;
        if(arg_ntype == AST_ASSIGN)
            arg = gen_assign(elist_cursor);
        else    arg = gen_rval(elist_cursor->elist.right, NULL);

        emit(NULL, ARG, argn, arg);
        elist_cursor = elist_cursor->elist.left;        
    }
    ast_reverse(&elist); //revert back so fncall AST is preserved
    if(!target)    target = gen_temp();
    emit(target, CALL, node->fncall.left, argc);
    return target;
}

void gen_cond(t_astn *node, bb *bb_false, bb *bb_true)
{
    t_astn *src_l = gen_rval(node->eqcomp.left, NULL);
    t_astn *src_r = gen_rval(node->eqcomp.right, NULL);
    emit(NULL, CMP, src_l, src_r);
    if(node->nodetype == AST_EQCOMP)
    {
        switch(node->eqcomp.op)
        {
            case '<':   
                bb_brancher(curr_bb, BRGE, bb_false, bb_true);
                break;

            case '>':
                bb_brancher(curr_bb, BRLE, bb_false, bb_true);
                break;

            case LTEQ:
                bb_brancher(curr_bb, BRGT, bb_false, bb_true);
                break;

            case GTEQ:
                bb_brancher(curr_bb, BRLT, bb_false, bb_true);
                break;

            case EQEQ:
                bb_brancher(curr_bb, BRNE, bb_false, bb_true);
                break;

            case NOTEQ:
                bb_brancher(curr_bb, BREQ, bb_false, bb_true);
                break;
        }
    }
}

void gen_if(t_astn *if_else_node)
{
    bb *bb_true = bbnew();
    bb *bb_false = bbnew();
    bb_append(&bb_list, &bb_true);
    bb_append(&bb_list, &bb_false);
    bb *bb_next;
    if(if_else_node->nodetype == AST_IF_ELSE)
        bb_next = bballoc();
    else    bb_next = bb_false;
    t_astn *cond_expr = (if_else_node->nodetype == AST_IF) ? if_else_node->if_stmt.expr : if_else_node->if_else_stmt.expr;
    t_astn *if_body = (if_else_node->nodetype == AST_IF) ? if_else_node->if_stmt.body : if_else_node->if_else_stmt.if_body;

    gen_cond(cond_expr, bb_false, bb_true);
    curr_bb = bb_true; 
    stmt_qgen(if_body);
    bb_brancher(curr_bb, BR, bb_next, NULL);
    if(if_else_node->nodetype == AST_IF_ELSE)
    {
        curr_bb = bb_false;
        stmt_qgen(if_else_node->if_else_stmt.else_body);
        bb_brancher(curr_bb, BR, bb_next, NULL);
    }
    curr_bb = bb_next;
}

void gen_while(t_astn *while_node)
{
    bb *bb_cond = bballoc();
    bb *bb_body = bballoc();
    bb *bb_next = bballoc();
    curr_bb = bb_list->head; // reset
    
    t_astn *cond_expr = while_node->while_stmt.expr;
    t_astn *while_body = while_node->while_stmt.body;
    //link previous BB with the condition BB
    bb_brancher(curr_bb, BR, bb_cond, NULL);
    curr_bb = bb_cond;
    curr_loop = curr_bb;
    gen_cond(cond_expr, bb_next, bb_body);
    curr_bb = bb_body; 

    stmt_qgen(while_body);
    bb_brancher(curr_bb, BR, bb_cond, NULL);
    curr_bb = bb_next; 
}

void gen_break()
{
    //curr_loop->left = false BB 
    bb_brancher(curr_bb, BR, curr_loop->left, NULL);
}

void gen_cont()
{
    //curr_loop->right = loop body
    bb_brancher(curr_bb, BR, curr_loop->right, NULL);
}

void gen_ret(t_astn *ret_node)
{
    t_astn *ret = (ret_node->ret_stmt.ret_expr) 
                ? gen_rval(ret_node->ret_stmt.ret_expr, NULL)
                : NULL;
    emit(NULL, RET, ret, NULL);
}

/*
    quad generation for entire function body

    1st node -> AST_CMPD => list of AST_ITEM nodes in current inner scope
        AST_ITEM -> contains decl or statement node
                    ***skip decls***
*/
void stmt_qgen(t_astn *node)
{
    if(!node)   return;
    switch(node->nodetype)
    {
        case AST_CMPD:
            stmt_qgen(node->cmpd_stmt.item_list);
            break;

        case AST_ITEM: 
            if(node->item.decl_or_stmt->nodetype != AST_DECL)
                stmt_qgen(node->item.decl_or_stmt);
            stmt_qgen(node->item.next);
            break;

        case AST_RET:
            gen_ret(node);
            break;

        case AST_BREAK:
            gen_break();
            break;

        case AST_CONT:
            gen_cont();
            break;

        case AST_IF_ELSE: 
            gen_if(node);
            break;

        case AST_IF:
            gen_if(node);
            break;

        case AST_WHILE:
            gen_while(node);
            break;
        
        case AST_ASSIGN: 
            gen_assign(node);
            break;

        case AST_FNCALL:
            gen_fncall(node, NULL);
            break;            
    }
    return; 
}

void print_rval(t_astn *node)
{
    if(!node)   return;
    switch(node->nodetype)
    {
        case AST_IDENT:
            fprintf(stderr, "%s", node->ident.name);
            if(node->ident.metadata->s_attr.s_var.stg == AUTO_CLASS)
                fprintf(stderr, "{local}");
            else    fprintf(stderr, "{globl}");
            break;
        
        case AST_TEMP: 
            fprintf(stderr, "%%T%05d", node->temp.temp_num);
            break;
        
        case AST_NUM:
            fprintf(stderr, "%llu", node->num.i_val);
            break;

        case AST_CHAR:
            fprintf(stderr, "%c", node->char_lit.chr);
            break;

        case AST_STR: 
            fprintf(stderr, "%s", node->str_lit.str);
            break;
    }
    
}

void print_quads(t_quad *quad)
{
    if(!quad)   return;
    fprintf(stderr, "\t");
    if(quad->res)
    {
        if(quad->res->nodetype == AST_IDENT)
        {
            fprintf(stderr, "%s", quad->res->ident.name);
            if(quad->res->ident.metadata->s_attr.s_var.stg == AUTO_CLASS)
                fprintf(stderr, "{local} = ");
            else    fprintf(stderr, "{globl} = ");
        }
        else if(quad->res->nodetype == AST_TEMP)
            fprintf(stderr, "%%T%05d = ", quad->res->temp.temp_num);
    }
    switch(quad->op)
    {
        case MOV:
            fprintf(stderr, "MOV ");
            print_rval(quad->src_l);
            fprintf(stderr, "\n");
            break; 

        case LOAD:
            fprintf(stderr, "LOAD ");
            print_rval(quad->src_l);
            fprintf(stderr, "\n");
            break; 

        case LEA:
            fprintf(stderr, "LEA ");
            print_rval(quad->src_l);
            fprintf(stderr, "\n");
            break; 

        case CMP:   
            fprintf(stderr, "CMP ");
            print_rval(quad->src_l);
            fprintf(stderr, ", ");
            print_rval(quad->src_r);
            fprintf(stderr, "\n");
            break;

        case MUL:
            fprintf(stderr, "MUL ");
            print_rval(quad->src_l);
            fprintf(stderr, ", ");
            print_rval(quad->src_r);
            fprintf(stderr, "\n");
            break; 

        case DIV:
            fprintf(stderr, "DIV ");
            print_rval(quad->src_l);
            fprintf(stderr, ", ");
            print_rval(quad->src_r);
            fprintf(stderr, "\n");
            break; 

        case MOD:
            fprintf(stderr, "MOD ");
            print_rval(quad->src_l);
            fprintf(stderr, ", ");
            print_rval(quad->src_r);
            fprintf(stderr, "\n");
            break; 

        case ADD:
            fprintf(stderr, "ADD ");
            print_rval(quad->src_l);
            fprintf(stderr, ", ");
            print_rval(quad->src_r);
            fprintf(stderr, "\n");
            break; 

        case SUB:
            fprintf(stderr, "SUB ");
            print_rval(quad->src_l);
            fprintf(stderr, ", ");
            print_rval(quad->src_r);
            fprintf(stderr, "\n");
            break; 

        case RET:
            fprintf(stderr, "RET ");   
            print_rval(quad->src_l);
            fprintf(stderr, "\n");
            break; 
        case CALL:
            fprintf(stderr, "CALL ");
            print_rval(quad->src_l);
            fprintf(stderr, ", ");
            print_rval(quad->src_r);
            fprintf(stderr, "\n");
            break; 

        case STORE:
            fprintf(stderr, "STORE ");
            print_rval(quad->src_l);
            fprintf(stderr, "\n");
            break; 

        case ARG:
            fprintf(stderr, "ARG ");
            print_rval(quad->src_l);
            fprintf(stderr, ", ");
            print_rval(quad->src_r);
            fprintf(stderr, "\n");
            break; 
    }
}

void print_bblabel(bb *basic_block)
{
    fprintf(stderr, ".BB.%d.%d ", basic_block->f_num, basic_block->bb_index);
}

void print_bb(bb *basic_block)
{
    if(!basic_block)    return;
    fprintf(stderr, ".BB.%d.%d:\n", basic_block->f_num, basic_block->bb_index);
    t_quad *quad_cursor = basic_block->quad_head;
    while(quad_cursor)
    {
        print_quads(quad_cursor);
        quad_cursor = quad_cursor->next;
    }
    fprintf(stderr, "\t");
    switch(basic_block->branch_cond)
    {
        case BR: 
            fprintf(stderr, "BR ");
            print_bblabel(basic_block->left);
            fprintf(stderr, "\n");
            break;

        case BRLE:
            fprintf(stderr, "BRLE ");
            print_bblabel(basic_block->left);
            print_bblabel(basic_block->right);
            fprintf(stderr, "\n");
            break;

        case BRLT:
            fprintf(stderr, "BRLT ");
            print_bblabel(basic_block->left);
            print_bblabel(basic_block->right);
            fprintf(stderr, "\n");
            break;

        case BRGE: 
            fprintf(stderr, "BRGE ");
            print_bblabel(basic_block->left);
            print_bblabel(basic_block->right);
            fprintf(stderr, "\n");
            break;

        case BRGT:
            fprintf(stderr, "BRGT ");
            print_bblabel(basic_block->left);
            print_bblabel(basic_block->right);
            fprintf(stderr, "\n");
            break;

        case BREQ:
            fprintf(stderr, "BREQ ");
            print_bblabel(basic_block->left);
            print_bblabel(basic_block->right);
            fprintf(stderr, "\n");
            break;

        case BRNE:
            fprintf(stderr, "BRNE ");
            print_bblabel(basic_block->left);
            print_bblabel(basic_block->right);
            fprintf(stderr, "\n");
            break;

    }
    print_bb(basic_block->next);
}

void IR_gen(FILE *fp, struct sym_tab *curr_scope, t_astn *fnbody)
{
    bb_list = bblnew();
    bballoc(); //init curr_bb; 
    //the tail node for GLOBAL scope table MUST be the function name!
    fprintf(stderr, "=== QUAD GENERATION ===\n");
    fprintf(stderr, "%s:\n", curr_scope->next->tail->name); 
    stmt_qgen(fnbody);
    if(bb_list->tail->quad_tail->op != RET)
    {
        t_astn *exit_ret = astnode_lloc(AST_RET);
        gen_ret(exit_ret);
    }
    print_bb(bb_list->head);
    
    /*--- TARGET CODE GEN --- */

    fprintf(stderr, "\n----------- TARGET CODE GENERATION -------------\n");
    global_asm(fp, curr_scope->next->head);

    int stack_space;
    struct sym_ent *entry = curr_scope->head;
    while(entry)
    {
        if(entry->s_attr.sym_type == SYM_VAR)
            stack_space = entry->s_attr.s_var.offset; //get the largest offset value
        entry = entry->next;
    }
    stack_space += (temp_num*4); 
    fprintf(fp, "\t.text\n");
    fprintf(fp, "%s:\n", curr_scope->next->tail->name); //function name
    fprintf(fp, "\tpushl %%ebp\n");
    fprintf(fp, "\tmovl %%esp, %%ebp\n");
    fprintf(fp, "\tsubl $%d, %%esp\n", stack_space);

    local_asm(fp, bb_list->head);

    bb_fnum++; 
    bb_bnum = 1;
    temp_num = 0;
}

/*----- TARGET CODE GENERATION ------ */

//global ASM is setup just once; entries are ONLY in GLOBAL SCOPE TABLE
void global_asm(FILE *file, struct sym_ent *entry)
{
    if(bb_fnum != 1)    return; 
    char *filename = entry->filename;
    fprintf(file, "\t.file \"%s\"\n", filename);
    while(entry)
    {
        int sym_type = entry->s_attr.sym_type;
        char *name = entry->name;
        if(sym_type == SYM_VAR)
        {
            t_astn *type = entry->s_attr.s_var.type;
            int size = t_sizeof(type);
            int alignment = (size == 1) ? size : 4; // no greater than 4 byte alignment
            if(type->nodetype == AST_ARRAY)
                size *= type->array.arr_size; 
            fprintf(file, "\t.comm %s, %d, %d\n", name, size, t_sizeof(type));
        }
        else //implies symbol entry is of function type
        {
            fprintf(file, "\t.globl %s\n", name);
            fprintf(file, "\t.type %s, @function\n", name);
        }
        entry = entry->next; 
    }
    fprintf(file, "%s", buf);
}

//rest of the ASM that needs to be generated
void local_asm(FILE *file, bb *basic_block)
{
    if(!basic_block)    return; 
    //get function name (most recent entry in global scope table)
    t_quad *quad = basic_block->quad_head;
    fprintf(file, ".BB.%d.%d:\n", basic_block->f_num, basic_block->bb_index);
    while(quad)
    {
        QUAD_ASMGEN(file, quad);
        quad = quad->next;
    }
    switch(basic_block->branch_cond)
    {
        case BR: 
            fprintf(file, "\tjmp .BB.%d.%d\n", basic_block->f_num, basic_block->bb_index);
            break;

        case BREQ:
            fprintf(file, "\tje .BB.%d.%d\n", basic_block->right->f_num, basic_block->right->bb_index);
            fprintf(file, "\tjmp .BB.%d.%d\n", basic_block->left->f_num, basic_block->left->bb_index);
            break;

        case BRNE:
            fprintf(file, "\tjne .BB.%d.%d\n", basic_block->right->f_num, basic_block->right->bb_index);
            fprintf(file, "\tjmp .BB.%d.%d\n", basic_block->left->f_num, basic_block->left->bb_index);
            break;

        case BRGT:
            fprintf(file, "\tjg .BB.%d.%d\n", basic_block->right->f_num, basic_block->right->bb_index);
            fprintf(file, "\tjmp .BB.%d.%d\n", basic_block->left->f_num, basic_block->left->bb_index);
            break;

        case BRGE:
            fprintf(file, "\tjge .BB.%d.%d\n", basic_block->right->f_num, basic_block->right->bb_index);
            fprintf(file, "\tjmp .BB.%d.%d\n", basic_block->left->f_num, basic_block->left->bb_index);
            break;

        case BRLT:
            fprintf(file, "\tjl .BB.%d.%d\n", basic_block->right->f_num, basic_block->right->bb_index);
            fprintf(file, "\tjmp .BB.%d.%d\n", basic_block->left->f_num, basic_block->left->bb_index);
            break;

        case BRLE:
            fprintf(file, "\tjle .BB.%d.%d\n", basic_block->right->f_num, basic_block->right->bb_index);
            fprintf(file, "\tjmp .BB.%d.%d\n", basic_block->left->f_num, basic_block->left->bb_index);
            break;
    }
    local_asm(file, basic_block->next);
    //get function 

}

//{MOV = 1, LOAD, LEA, CMP, MUL, DIV, MOD, ADD, SUB, RET, CALL, STORE, ARG};
void QUAD_ASMGEN(FILE *file, t_quad *quad)
{
    switch(quad->op)
    {
        case MOV: 
            fprintf(file, "# res MOV src1\n");
            fprintf(file, "\tmovl ");
            TARGET_ASMGEN(file, quad->src_l);
            fprintf(file, ", %%ebx\n");
            fprintf(file, "\tmovl %%ebx, ");
            TARGET_ASMGEN(file, quad->res);
            fprintf(file, "\n");
            break;

        case LOAD: 
            fprintf(file, "# res LOAD src_l\n");
            fprintf(file, "\tmovl ");
            TARGET_ASMGEN(file, quad->src_l);
            fprintf(file, ", %%esi\n");
            fprintf(file, "\tmovl (%%esi), %%ebx\n");
            fprintf(file, "\tmovl %%ebx, ");
            TARGET_ASMGEN(file, quad->res);
            fprintf(file, "\n");
            break;

        case LEA: 
            fprintf(file, "# res LEA src_l\n");
            fprintf(file, "\tlea ");
            TARGET_ASMGEN(file, quad->src_l);
            fprintf(file, ", %%edi\n");
            fprintf(file, "\tmovl %%edi, ");
            TARGET_ASMGEN(file, quad->res);
            fprintf(file, "\n");
            break;

        case CMP: 
            fprintf(file, "# CMP src_l src_r\n");
            fprintf(file, "\tmovl ");
            TARGET_ASMGEN(file, quad->src_l);
            fprintf(file, ", %%ecx\n");
            fprintf(file, "\tmovl ");
            TARGET_ASMGEN(file, quad->src_r);
            fprintf(file, ", %%ebx\n");
            fprintf(file, "\tcmp %%ebx, %%ecx\n");
            break;

        case ADD: 
            fprintf(file, "# res ADD src_l src_r\n");
            fprintf(file, "\tmovl ");
            TARGET_ASMGEN(file, quad->src_l);
            fprintf(file, ", %%ebx\n");
            fprintf(file, "\taddl ");
            TARGET_ASMGEN(file, quad->src_r);
            fprintf(file, ", %%ebx\n");
            fprintf(file, "\tmovl %%ebx, ");
            TARGET_ASMGEN(file, quad->res);
            fprintf(file, "\n");
            break;

        case SUB: 
            fprintf(file, "# res SUB src_l src_r\n");            
            fprintf(file, "\tmovl ");
            TARGET_ASMGEN(file, quad->src_l);
            fprintf(file, ", %%ebx\n");
            fprintf(file, "\tsubl ");
            TARGET_ASMGEN(file, quad->src_r);
            fprintf(file, ", %%ebx\n");
            fprintf(file, "\tmovl %%ebx, ");
            TARGET_ASMGEN(file, quad->res);
            fprintf(file, "\n");
            break;    

        case STORE: 
            fprintf(file, "# STORE src_l src_r\n");
            fprintf(file, "\tmovl ");
            TARGET_ASMGEN(file, quad->src_l);
            fprintf(file, ", %%edi\n");
            fprintf(file, "\tmovl ");
            TARGET_ASMGEN(file, quad->src_r);
            fprintf(file, ", %%edi\n");
            fprintf(file, "\tmovl %%edi, (%%ebx)\n");
            break;
        
        case ARG: 
            fprintf(file, "# ARG NUM src_r\n");
            fprintf(file, "\tmovl ");
            TARGET_ASMGEN(file, quad->src_r);
            fprintf(file, ", %%ecx\n");
            fprintf(file, "\tpushl %%ecx\n"); 
            break;

        case CALL: 
            fprintf(file, "# CALL src_l ARGC\n");
            fprintf(file, "\tcall ");
            TARGET_ASMGEN(file, quad->src_l);
            fprintf(file, "\n");
            t_astn *aligned_argc = astnode_lloc(AST_NUM);
            aligned_argc->num.i_val = 4 * quad->src_r->num.i_val; 
            fprintf(file, "\taddl ");
            TARGET_ASMGEN(file, aligned_argc);
            fprintf(file, ", %%esp\n");
            break;

        case RET: 
            fprintf(file, "\t# RET src1\n");
            if(quad->src_l)
            {
                fprintf(file, "\tmovl ");                
                TARGET_ASMGEN(file, quad->src_l);
                fprintf(file, ", %%eax\n");                
            }
            fprintf(file, "\tleave\n");
            fprintf(file, "\tret\n");
            break;
    }
}

void TARGET_ASMGEN(FILE *file, t_astn *node)
{
    int t_offset, dat_index;
    if(!node)   return;
    switch(node->nodetype)
    {
        case AST_IDENT:
            if(node->ident.metadata->s_attr.sym_type == SYM_VAR)
            {
                if(node->ident.metadata->s_attr.s_var.stg == AUTO_CLASS)
                    fprintf(file, "-%d(%%ebp)", node->ident.metadata->s_attr.s_var.offset);
                else if(node->ident.metadata->s_attr.s_var.stg != STATIC_CLASS)
                {
                    if(node->ident.metadata->scope == GLOBAL)
                        fprintf(file, "%s(%%eip)", node->ident.name);
                    else fprintf(file, "%s", node->ident.name);
                }
            }
            else    fprintf(file, "%s", node->ident.name);
            break;

        case AST_NUM:
            fprintf(file, "$%lld", node->num.i_val);
            break;

        case AST_TEMP: 
            t_offset = (stack_offset - (4*temp_num)) + (4*node->temp.temp_num); //temporaries take up lower part of stack   
            fprintf(file, "%d(%%ebp)", t_offset);
            break;
        case AST_STR:
            dat_index = get_strDataIndex(node); //valid assumption that there will always be a datum index found
            fprintf(file, ".str_%d", dat_index);
    }
}
