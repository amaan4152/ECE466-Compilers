#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "symtab.h"

enum NMSPACE NAMESPACE; 
enum SYM_TYPE S_TYPE;
enum SCOPE VIS; //vis = visibility
enum STG STORAGE;

void debug(char *mssg, int line_num)
{
    fprintf(stderr, "---%s: [%d]---\n", mssg, line_num);
}

void install_decl(struct sym_tab **curr_stack, struct astnode **head, int *stgclass, int *offset)
{
    struct sym_attr attr; 
    struct astnode *temp = *head; 
    /* GATHER META DATA */
    int line_num = temp->ident.line_no;
    char *name = temp->ident.name, *filename = temp->ident.filename; 
    /* INSTALL DECLARATION INTO SYMBOL TABLE */
    struct astnode *type = temp->ident.next, *desig_node = get_symType(type);
    if(desig_node->nodetype == AST_SCALAR) //array of function pointers will NOT WORK!
    {
        attr.sym_type = SYM_VAR;
        if(*stgclass == 0)  
            *stgclass = ((*curr_stack)->scope != GLOBAL) ? AUTO_CLASS : 0; //for unspecified storage class
        else if(*stgclass == REGISTER_CLASS && (*curr_stack)->scope == GLOBAL) 
            yyerror("\'register\' storage class is not permitted in global scope declarations");
        else if(*stgclass == AUTO_CLASS && (*curr_stack)->scope == GLOBAL) 
            yyerror("\'auto\' storage class is not permitted in global scope declarations");
        attr.s_var.stg = *stgclass;
        attr.s_var.type = type;
        offset_update(&attr, offset); //update stack offset for auto storage class variables
    }
    else //implies function declaration
    {
        attr.sym_type = SYM_FUNC;                                                                         
        if(*stgclass == 0 || *stgclass == EXTERN_CLASS)
            attr.s_func.stg = EXTERN_CLASS;
        else    yyerror("Function declarations can only have an explicit \'extern\' storage class");
        attr.s_func.ret_type = desig_node->func.ret_type; 
        if(!attr.s_func.ret_type)   yyerror("Need to specify a return type for function declaration");
        attr.s_func.args_type = desig_node->func.params; 
        attr.s_func.fndef = NULL; 
        attr.s_func.body = NULL; 
        attr.s_func.fn_table = NULL; 
        attr.s_func.bool_fndef = 0;                                                                        
    }
    sym_enter(curr_stack, attr, (*curr_stack)->scope, OTHER, name, line_num, filename);
}

struct sym_tab *table_create(int scope)
{
    struct sym_tab *new_stack; 
    if((new_stack = (struct sym_tab *)malloc(sizeof(struct sym_tab))) == NULL)
        fatal_err(strerror(errno));
    new_stack->scope = scope; 
    new_stack->head = NULL;
    new_stack->tail = NULL;
    new_stack->next = NULL;
    return new_stack;
}

/*Pop the stack on the top (inner-most scope stack)*/
struct sym_tab *stack_pop(struct sym_tab **curr_stack)
{
    struct sym_tab *prev_stack = (*curr_stack)->next;
    free(*curr_stack);
    return prev_stack;
}

/*Push an inner scope onto the scope stack*/
void stack_push(struct sym_tab **curr_stack, int scope)
{
    struct sym_tab *new_stack = table_create(scope); 
    new_stack->next = *curr_stack; 
    *curr_stack = new_stack;
}

struct sym_ent *sym_create(int scope, int namespace, int entry_type, int line_num, char *file)
{
    struct sym_ent *new_entry; 
    if((new_entry = (struct sym_ent *)malloc(sizeof(struct sym_ent))) == NULL)
        fatal_err(strerror(errno));
    new_entry->scope = scope; 
    new_entry->namespace = namespace;
    new_entry->s_attr.sym_type = entry_type; 
    memcpy(new_entry->filename, file, sizeof(file));
    new_entry->line_no = line_num;
    new_entry->next = NULL;

    return new_entry;
}

/* in_curr_scope = pointer to int used to determine if entry was found in the given @scope */
struct sym_ent *sym_lookup(struct sym_tab **table, int scope, int namespace, char *name)
{
    struct sym_tab *curr_tab = *table; 
    while(curr_tab->scope != scope) curr_tab = curr_tab->next;
    struct sym_ent *table_entry = curr_tab->head;
    while(table_entry)
    {
        if (table_entry->s_attr.sym_type == SYM_STRUCTION && namespace == MEMBER)
            return sym_lookup(&(table_entry->s_attr.s_su.struction->su.mini_scope), scope, namespace, name); //work through struct/union scope
        if (table_entry->namespace == namespace && strcmp(table_entry->name, name) == 0)
            return table_entry;
        table_entry = table_entry->next;
    }
    if(curr_tab->next != NULL)
        return sym_lookup(&(curr_tab->next), curr_tab->next->scope, namespace, name); //work through outer enclosing scopes
    return NULL; //symbol does not exist
}

int type_equality(struct astnode *head_l, struct astnode *head_r)
{
    while(head_l && head_r)
    {
        if(head_l->nodetype != head_r->nodetype)    return 0; //nodes are not the same, thus types are not equal
        switch(head_l->nodetype)
        {
            case AST_DECL:
                if(!type_equality(head_l->declaration.decl->ident.next, head_r->declaration.decl->ident.next))
                    return 0;
                if(!type_equality(head_l->declaration.next, head_r->declaration.next))
                    return 0;
                break;
            case AST_SCALAR:
                if(!type_equality(head_l->scalar.qualifier, head_r->scalar.qualifier))  return 0; 
                head_l = head_l->scalar.next;
                head_r = head_r->scalar.next;
                break;
            case AST_PTR:
                if(!type_equality(head_l->ptr.qual_l, head_r->ptr.qual_l))  return 0;
                head_l = head_l->ptr.next;
                head_r = head_r->ptr.next;
                break;
            case AST_ARRAY:
                head_l = head_l->array.next;
                head_r = head_r->array.next;
                break;
            case AST_QUAL:
                if(!(head_l->qualif.qual == head_r->qualif.qual))   return 0;
                head_l->qualif.next;
                head_r->qualif.next;
                break;
        }
    }
    return (!head_l && !head_r); //types are equivalent iff their respective tail nodes point to NULL 
}

/*Precondition: function applies to entry that already exists*/
int redecl_boolstate(struct sym_ent *curr_ent, struct sym_attr new_attr, int curr_scope)
{
    int curr_stg_var = curr_ent->s_attr.s_var.stg, curr_stg_fn = curr_ent->s_attr.s_func.stg;
    int new_stg_var = new_attr.s_var.stg, new_stg_fn = new_attr.s_func.stg;
    switch(curr_ent->s_attr.sym_type)
    {

        /* 
            FILE SCOPE AND SAME SCOPE FOR BOTH DECLS: 
                PREV_DECL_STGCLASS = STATIC & NEW_DECL_STGCLASS = EXTERN ==> NEW_DECL_STGCLASS = STATIC (internal linkage)
                PREV_DECL_STGCLASS = EXTERN & NEW_DECL_STGCLASS = STATIC ==> EXTERNAL/INTERNAL LINKAGE CONFLICT! 
                PREV_DECL_STGCLASS = STATIC & NEW_DECL_STGCLASS = NONE ==> (internal linkage)
                PREV_DECL_STGCLASS = EXTERN & NEW_DECL_STGCLASS = NONE ==> (external linkage)
                PREV_DECL_STGCLASS = EXTERN & NEW_DECL_STGCLASS = EXTERN ==> NEW_DECL_STGCLASS = EXTERN (external linkage)
                PREV_DECL_STGCLASS = NONE & NEW_DECL_STGCLASS = EXTERN ==> (external linkage)
                PREV_DECL_STGCLASS = NONE & NEW_DECL_STGCLASS = STATIC ==> EXTERNAL/INTERNAL LINKAGE CONFLICT!
                PREV_DECL_STGCLASS = NONE & NEW_DECL_STGCLASS = NONE ==> (external linkage)
            
            NOT FILE SCOPE AND SAME SCOPE FOR BOTH DECLS: 
                PREV_DECL_STGCLASS = EXTERN & NEW_DECL_STGCLASS = EXTERN ==> NEW_DECL_STGCLASS = EXTERN (internal linkage)
                ANYTHING ELSE: ERROR
        */
        case SYM_VAR:
            if(!type_equality(curr_ent->s_attr.s_var.type, new_attr.s_var.type))
            {
                yyerror("[ERROR] Redclaration with conflicting types");
                return -1; //types are not equivalent
            }
            if(curr_scope == GLOBAL && (curr_ent->scope == curr_scope))
            {
                if(curr_stg_var == EXTERN_CLASS && new_stg_var == EXTERN_CLASS
                || curr_stg_var == 0 && new_stg_var == 0)
                    return 1; //replace previous declaration
                else if(curr_stg_var == STATIC_CLASS && new_stg_var == EXTERN_CLASS)
                    return 0; //retain previous declaration, but don't throw error; not too sure if this is a valid approach
                yyerror("[ERROR] External/internal linkage conflict");
                return -1; //throw error
            }
            else if(curr_scope != GLOBAL && (curr_ent->scope == curr_scope))
            {
                if(curr_stg_var == EXTERN_CLASS && new_stg_var == EXTERN_CLASS)
                    return 1;
                yyerror("[ERROR] Redclaration with no linkage");
                return -1;
            }
            return 1; 

        case SYM_FUNC: 
            if(curr_stg_fn != new_stg_fn)
            {    
                yyerror("[ERROR] Redclaration with inappropriate storage class");
                return -1;
            }
            /*check for return type and argument type equality */
            if(!type_equality(curr_ent->s_attr.s_func.ret_type, new_attr.s_func.ret_type) 
            && !type_equality(curr_ent->s_attr.s_func.args_type->declaration.decl, new_attr.s_func.args_type->declaration.decl))
            {
                yyerror("[ERROR] Redclaration with conflicting types");
                return -1; //types are not equivalent
            }
            if(curr_ent->s_attr.s_func.bool_fndef && new_attr.s_func.bool_fndef) 
            {
                yyerror("[ERROR] This is not C++ jackass, you can't override function definitions -.-");
                return -1; 
            }
            return 1;            
    }
}

/*
@attr = struct of attributes
*/
struct sym_ent *sym_enter(struct sym_tab **table, struct sym_attr attr, int scope, int namespace, char *name, int line_num, char *filename)
{
    int found = 0; 
    struct sym_tab *curr_tab = *table;
    struct sym_ent *new_sym = sym_lookup(&curr_tab, scope, namespace, name);
    if(new_sym)
    {
        switch(redecl_boolstate(new_sym, attr, scope))
        {
            case -1:   return NULL;  //continue parsing (don't install the new declaration, however)
            case 0:    
                if(new_sym->scope == scope)  
                    return NULL; //retain previous declaration
                found = 1;
                break;

            /*set found to indicate existence of old decl and allow for replacement
                - also for linking decls and defs of same type functions*/
            case 1:    found = 1; break;  
        }   
    }  
    else if(!new_sym)
        new_sym = sym_create(scope, namespace, attr.sym_type, line_num, filename);
    if(found && new_sym->scope != scope)
        new_sym = sym_create(scope, namespace, attr.sym_type, line_num, filename);
    if(curr_tab->head == NULL)
    {
        curr_tab->head = new_sym;
        curr_tab->tail = new_sym; 
    }
    else if(!found || (found && new_sym->scope != scope))
    {
        curr_tab->tail->next = new_sym;
        curr_tab->tail = new_sym;
    }
    else if(found && new_sym->s_attr.sym_type == SYM_VAR) //redeclaration is valid for VARIABLE
    {
        memcpy(new_sym->filename, filename, sizeof(filename)); 
        new_sym->line_no = line_num;
    }
    else if(found && new_sym->s_attr.sym_type == SYM_FUNC) //redeclaration is valid for FUNCTION
    {
        attr.s_func.fndef = new_sym; //link with previous reference/definition
        new_sym = sym_create(scope, namespace, attr.sym_type, line_num, filename);
        curr_tab->tail->next = new_sym;
        curr_tab->tail = new_sym;
    }
    memcpy(new_sym->name, name, sizeof(name)); 
    //install/update attributes to either new symbol entry or existing entry in symbol table
    switch(attr.sym_type)
    {
        case SYM_VAR:   
            new_sym->s_attr.s_var = attr.s_var; 
            break;
        case SYM_FUNC:
            new_sym->s_attr.s_func = attr.s_func;
            break;
        case SYM_BLOCK:
            new_sym->s_attr.s_block = attr.s_block;
            break;
        case SYM_STRUCTION:
            new_sym->s_attr.s_su = attr.s_su;
            break;
        case SYM_SU_MEM:
            new_sym->s_attr.s_su_mem = attr.s_su_mem;
            break;
        case SYM_ENUM:
            new_sym->s_attr.s_enum = attr.s_enum;
            break;
        case SYM_ECONST:
            new_sym->s_attr.s_econst = attr.s_econst;
            break;
    }
    return new_sym; 
}

//for variables with auto storage class
int t_sizeof(struct astnode *head)
{
    int data_type = 0, size = 0; 
    while(head)
    {
        switch(head->nodetype)
        {
            case AST_ARRAY: return t_sizeof(head->array.next);
            case AST_SCALAR:
                data_type = head->scalar.type;
                if(data_type == C)  size = 1;
                else if(data_type >= SHRT && data_type < I) size = 2;
                else if(data_type == I || data_type == F)    size = 4;
                else if (data_type >= L && data_type <= D)   size = 8;
                else if(data_type == LD)    size = 10; 
                return size;
            case AST_PTR:   return 8;
        }
    }
}

//for variables with auto storage class
/*Precondition: attribute of symbol entry is a variable*/
void offset_update(struct sym_attr *attr, int *curr_offset)
{
    if(attr->sym_type == SYM_VAR && attr->s_var.stg == AUTO_CLASS)
    {
        int data_type = 0, signedness = 0, size = 0;
        struct astnode *temp = attr->s_var.type;
        size = t_sizeof(temp);
        attr->s_var.offset = *curr_offset + size; 
        *curr_offset += (temp->nodetype == AST_ARRAY) ? (size*temp->array.arr_size) : size; 
    }    
}

struct astnode *get_symType(struct astnode *head)
{
    while(head)
    {
        switch(head->nodetype)
        {
            case AST_SCALAR:    return head; 
            case AST_PTR:       head = head->ptr.next; break; 
            case AST_ARRAY:     head = head->array.next; break;
            case AST_FUNC:      return head; 
        }
    }
}

char *scope_print(int scope)
{
    switch(scope)
    {
        case GLOBAL:    return "GLOBAL SCOPE";
        case FUNC:      return "FUNC SCOPE";    
        case BLOCK:     return "BLOCK SCOPE";
        case PROTO:     return "PROTO SCOPE";
    }
}

char *stgclass_print(int stgclass)
{
    switch(stgclass)
    {
        case 0:                 return "NONE";
        case EXTERN_CLASS:      return "EXTERN";
        case STATIC_CLASS:      return "STATIC";
        case AUTO_CLASS:        return "AUTO";
        case REGISTER_CLASS:    return "REGISTER";
        case TYPEDEF_CLASS:     return "TYPEDEF";
    }
}

void sym_print(struct sym_ent *entry, int scope)
{
    char *def_or_decl[2] = {"defined", "declared"};
    while(entry)
    {
        int line_n = entry->line_no, sym_type = entry->s_attr.sym_type, index = 0; 
        char *name = entry->name, *filename = entry->filename; 
        fprintf(stderr, "\n~------------------------~\n");
        switch(sym_type)
        {
            case SYM_VAR: 
                fprintf(stderr, "{%s} VARIABLE: %s ~~> defined at %s:%d [declared at %s:%d | %s]\n\t TYPE:\n\r",
                        stgclass_print(entry->s_attr.s_var.stg), name, filename, line_n, filename, line_n, scope_print(scope));
                print_ast(entry->s_attr.s_var.type, 6);
                break;
            case SYM_FUNC:
                if(entry->s_attr.s_func.bool_fndef)    index = 0;
                else    index = 1;
                fprintf(stderr, "{%s} FUNCTION: %s ~~> %s at %s:%d ",
                        stgclass_print(entry->s_attr.s_func.stg), name, def_or_decl[index], filename, line_n);
                if(entry->s_attr.s_func.fndef)
                    fprintf(stderr, "[%s at %s:%d | GLOBAL SCOPE]\n\t RET TYPE:\n", def_or_decl[!index],
                            entry->s_attr.s_func.fndef->filename, entry->s_attr.s_func.fndef->line_no);
                else    fprintf(stderr, "[declared at %s:%d | %s]\n\t RET TYPE:\n", filename, line_n, scope_print(scope));
                print_ast(entry->s_attr.s_func.ret_type, 6);
                fprintf(stderr, "\tPARAMTER TYPES:\n");
                struct astnode *param = entry->s_attr.s_func.args_type;
                while(param)
                {
                    print_ast(param->declaration.decl->ident.next, 6);
                    param = param->declaration.next;
                }
                if(entry->s_attr.s_func.fn_table)
                    sym_print(entry->s_attr.s_func.fn_table, entry->s_attr.s_func.fn_table->scope);
                /*---DUMP AST LIST FOR CURRENT FUNCTION---*/
                if(entry->s_attr.s_func.bool_fndef)
                {
                    fprintf(stderr, "\nAST Dump for function:\n");
                    fprintf(stderr, "LIST {\n");
                    print_ast(entry->s_attr.s_func.body,0);
                    fprintf(stderr, "\n}\n");
                }
                break;

            case SYM_BLOCK: 
                if(entry->s_attr.s_block.block_ent)
                    sym_print(entry->s_attr.s_block.block_ent, entry->s_attr.s_block.block_ent->scope);
                break;
        }
        entry = entry->next;
    }
}