#include "ast.h"

enum TYPE _TYPE_; 
enum astnode_type AST_TYPE; 

void fatal_err(char *mssg)
{
    yyerror(mssg);
    exit(EXIT_FAILURE);
}

struct astnode* astnode_lloc(int type)
{
    struct astnode *node;
    if((node = (struct astnode *)malloc(sizeof(struct astnode))) == NULL)
        fatal_err(strerror(errno));
    node->nodetype = type;
    return node;
}


int node_search(t_astn *head, int nodetype)
{
    while(head)
    {
        switch(head->nodetype)
        {
            case AST_SCALAR:    
                if(head->nodetype == nodetype)  return nodetype; 
                head = head->scalar.next; break; 
            case AST_PTR:  
                if(head->nodetype == nodetype)  return nodetype;      
                head = head->ptr.next; break; 
            case AST_ARRAY:     
                if(head->nodetype == nodetype)  return nodetype; 
                head = head->array.next; break;
            case AST_TEMP:
                if(head->nodetype == nodetype)  return nodetype; 
                head = head->temp.next; break; 
        }
    }
    return -1; //specified nodetype not found!
}

struct astnode *for_node_init(struct astnode **arg1, struct astnode **arg2, struct astnode **arg3)
{
    struct astnode *for_node = astnode_lloc(AST_FOR);
    for_node->for_stmt.init_expr = *arg1;
    for_node->for_stmt.expr_1 = *arg2;
    for_node->for_stmt.expr_2 = *arg3;
}

void spacing(int depth, int n_type)
{
    for(int i = 0; i < depth && n_type != AST_ELIST; ++i)  
        fprintf(stderr, "  ");
}

void print_ast(struct astnode *root, int depth)
{
    if(!root)   return;
    fprintf(stderr, "\r");
    spacing(depth, root->nodetype);
    switch(root->nodetype)
    {
        case AST_DECL:
            print_ast(root->declaration.next, depth); //skip printing declarations
            break;
        case AST_CMPD:
            print_ast(root->cmpd_stmt.item_list, depth);
            break; 

        case AST_ITEM:
            print_ast(root->item.decl_or_stmt, depth);
            fprintf(stderr, "\n");
            print_ast(root->item.next, depth);
            break;
        case AST_CAST:
            fprintf(stderr, "CAST (\n");
            print_ast(root->cast.type, depth + 1);
            spacing(depth, root->nodetype);
            fprintf(stderr, ") TO: \n");
            print_ast(root->cast.to, depth + 1);
            break;

        case AST_FOR:
            fprintf(stderr, "FOR\n");
            spacing(depth, root->nodetype);
            fprintf(stderr, "INIT:\n");
            print_ast(root->for_stmt.init_expr, depth + 1);
            spacing(depth, root->nodetype);
            fprintf(stderr, "COND:\n");
            print_ast(root->for_stmt.expr_1, depth + 1);
            spacing(depth, root->nodetype);
            fprintf(stderr, "BODY:\n");
            print_ast(root->for_stmt.body, depth + 1);
            spacing(depth, root->nodetype);
            fprintf(stderr, "INCR:\n");
            print_ast(root->for_stmt.expr_2, depth + 1);
            break;
        
        case AST_DO:
            fprintf(stderr, "DO\n");
            spacing(depth, root->nodetype);
            fprintf(stderr, "EXPR:\n");
            print_ast(root->do_stmt.expr, depth + 1);
            spacing(depth, root->nodetype);
            fprintf(stderr, "BODY:\n");
            print_ast(root->do_stmt.body, depth + 1);
            break;

        case AST_WHILE:
            fprintf(stderr, "WHILE\n");
            spacing(depth, root->nodetype);
            fprintf(stderr, "EXPR:\n");
            print_ast(root->while_stmt.expr, depth + 1);
            spacing(depth, root->nodetype);
            fprintf(stderr, "BODY:\n");
            print_ast(root->while_stmt.body, depth + 1);
            break;

        case AST_IF: 
            fprintf(stderr, "IF\n");
            spacing(depth, root->nodetype);
            fprintf(stderr, "COND:\n");
            print_ast(root->if_stmt.expr, depth + 1);
            spacing(depth, root->nodetype);
            fprintf(stderr, "TRUE BODY:\n");
            print_ast(root->if_stmt.body, depth + 1);
            break;

        case AST_IF_ELSE:
            fprintf(stderr, "IF\n");
            spacing(depth, root->nodetype);
            fprintf(stderr, "COND:\n");
            print_ast(root->if_else_stmt.expr, depth + 1);
            spacing(depth, root->nodetype);
            fprintf(stderr, "TRUE BODY:\n");
            print_ast(root->if_else_stmt.if_body, depth + 1);
            spacing(depth, root->nodetype);
            fprintf(stderr, "FALSE BODY:\n");
            print_ast(root->if_else_stmt.else_body, depth + 1);
            break;

        case AST_BREAK:
            fprintf(stderr, "BREAK\n");
            break;

        case AST_CONT:
            fprintf(stderr, "CONTINUE\n");
            break;

        case AST_RET:
            fprintf(stderr, "RETURN:\n");
            print_ast(root->ret_stmt.ret_expr, depth + 1);
            break;

        case AST_IDENT:
            fprintf(stderr, "stab_var name=%s ", root->ident.name);
            if(root->ident.metadata)
                fprintf(stderr, "def @%s:[%d] {%s}\n", root->ident.metadata->filename, 
                root->ident.metadata->line_no, scope_print(root->ident.metadata->scope));
            else     fprintf(stderr, "UNDEFINED IDENTIFIER\n");
            print_ast(root->ident.next, depth + 1);
            break;

        case AST_QUAL:
            fprintf(stderr, "%s ", print_kwop(root->qualif.qual));
            print_ast(root->qualif.next, 1);
            break;

        case AST_SCALAR:
            print_ast(root->scalar.qualifier, depth);
            switch(root->scalar.signedness)
            {
                case 0: break; 
                case U: fprintf(stderr, "unsigned "); break;
                case S: fprintf(stderr, "signed "); break;
            }
            switch(root->scalar.type)
            {
                case 0: break;
                case C: fprintf(stderr, "char "); break;
                case I: fprintf(stderr, "int ");  break;
                case SHRT: fprintf(stderr, "short "); break;
                case L: fprintf(stderr, "long "); break;
                case LL: fprintf(stderr, "long long "); break;
                case D: fprintf(stderr, "double "); break;
                case LD: fprintf(stderr, "long double "); break;
                case F: fprintf(stderr, "float "); break;
                case V: fprintf(stderr, "void "); break; 
            }
            if(root->scalar.cmplx_bool == CMPLX) fprintf(stderr, "_Complex ");
            else if(root->scalar.cmplx_bool == BOOL) fprintf(stderr, "_Bool ");
            fprintf(stderr, "\n");
            print_ast(root->scalar.next, depth + 1);
            break; 

        case AST_PTR:
            print_ast(root->ptr.qual_l, depth);
            fprintf(stderr, "pointer to\n");
            print_ast(root->ptr.next, depth + 1);
            break;

        case AST_ARRAY:
            if(root->array.arr_size != 0)
                fprintf(stderr, "array | SIZE: %d\n", root->array.arr_size);
            else    fprintf(stderr, "array | SIZE: INCOMPLETE\n");
            print_ast(root->array.next, depth + 1);
            break;

        case AST_FUNC:
            print_ast(root->func.ret_type, depth + 1);
            if(root->func.params)
            {
                fprintf(stderr, "args: \n");
                print_ast(root->func.params, depth + 1);
            }
            else    fprintf(stderr, "args:\n\t\tNONE\n");
            break;

        case AST_FNCALL: 
            fprintf(stderr, "FNCALL, %d arguments\n", root->fncall.argc);
            print_ast(root->fncall.left, depth + 1);
            print_ast(root->fncall.right, depth);
            break;
        
        case AST_ELIST:
            print_ast(root->elist.left, depth);
            for(int i = 0; i < depth; ++i)  fprintf(stderr, "  ");
            fprintf(stderr, "arg #%d:\n", root->elist.argnum);
            print_ast(root->elist.right, depth + 1);
            break;

        case AST_BOP:
            if(root->bop.op < 255)  fprintf(stderr, "BINARY OP %c\n", root->bop.op);
            else    fprintf(stderr, "BINARY OP %s\n", print_kwop(root->bop.op));
            print_ast(root->bop.left, depth + 1);
            print_ast(root->bop.right, depth + 1);
            break;

        case AST_ASSIGN:
            fprintf(stderr, "ASSIGNMENT\n");
            print_ast(root->assign.left, depth + 1);
            print_ast(root->assign.right, depth + 1);
            break;

        case AST_EQCOMP:
            if(root->eqcomp.op < 255)  
                fprintf(stderr, "COMPARISON OP %c\n", root->eqcomp.op);
            else    fprintf(stderr, "COMPARISON OP %s\n", print_kwop(root->eqcomp.op));
            print_ast(root->eqcomp.left, depth + 1);
            print_ast(root->eqcomp.right, depth + 1);
            break;

        case AST_LOG:
            if(root->eqcomp.op < 255)  
                fprintf(stderr, "LOGICAL OP %c\n", root->log.op);
            else    fprintf(stderr, "LOGICAL OP %s\n", print_kwop(root->log.op));
            print_ast(root->log.left, depth + 1);
            print_ast(root->log.right, depth + 1);
            break;

        case AST_TERN:
            switch(root->tern.op)
            {
                default: fprintf(stderr, "TERNARY OP, IF:\n"); break;
                case '?': fprintf(stderr, "THEN:\n"); break;
                case ':': fprintf(stderr, "ELSE:\n"); break;
            }
            print_ast(root->tern.left, depth + 1);
            print_ast(root->tern.right, depth);
            break;

        case AST_COMP_SEL:
            fprintf(stderr, "SELECT\n");
            print_ast(root->comp_sel.left, depth + 1);
            print_ast(root->comp_sel.right, depth + 1);
            break; 

        case AST_UOP:

            if(root->uop.op < 255)  
                fprintf(stderr, "UNARY OP %c\n", root->uop.op);
            else if(root->uop.op == (int)'*')   fprintf(stderr, "DEREF\n");
            else    fprintf(stderr, "UNARY OP %s\n", print_kwop(root->uop.op));
            print_ast(root->uop.left, depth + 1);
            print_ast(root->uop.right, depth + 1);
            break;

        case AST_NUM: 
            if(root->num.type < D)  fprintf(stderr, "CONSTANT: (numtype=int) %lld\n", root->num.i_val);
            else  fprintf(stderr, "CONSTANT: (numtype=double) %Lg\n", root->num.fd_val);
            break;

        case AST_STR: 
            fprintf(stderr, "STRING: %s\n", root->str_lit.str);
            break;

        case AST_CHAR:
            fprintf(stderr, "CHARLIT: %c\n", root->char_lit.chr);
            break;
    }
}

//reverse the AST to aquire correct ordering of nodes 
void ast_reverse(struct astnode **node)
{
    struct astnode *prev = NULL, *curr = *node, *next = NULL;
    while(curr)
    {
        switch(curr->nodetype)
        {
            case AST_SCALAR:
                next = curr->scalar.next;
                curr->scalar.next = prev;
                break;

            case AST_PTR:
                next = curr->ptr.next;
                curr->ptr.next = prev;
                break;

            case AST_ARRAY:
                next = curr->array.next;
                curr->array.next = prev;
                break;

            case AST_FUNC: 
                next = curr->func.ret_type;
                curr->func.ret_type = prev; 
                break; 

            case AST_IDENT:
                next = curr->ident.next;
                curr->ident.next = prev;
                break;

            case AST_ELIST:
                next = curr->elist.left;
                curr->elist.left = prev;
                break;
        }
        prev = curr;
        curr = next;
    }
    *node = prev; 
}

/*
Precodintion: head_l is the head of declspecs, which ONLY contain scalar nodes 
(since there are no struct/union/enum implenetations)

The reason why we loop through the declspecs, even though the nodes are only scalars,
is due to the fact of irregular cases such as 'static long extern long int', which 
will generate 2 scalar nodes: 'long' and 'long int'. This is due to how my code is setup,
unfortunately. 

*** I have many regrets in how I setup my parser/semantic analysis framework, but too late to undo ***
*/
void append_ast(struct astnode **head_l, struct astnode **head_r)
{
    struct astnode *temp_l = *head_l;
    while(temp_l->scalar.next)   temp_l = temp_l->scalar.next;
    temp_l->scalar.next = *head_r;
}
