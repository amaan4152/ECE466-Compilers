%debug
%{
    #include "ast.h"
    #include "symtab.h"
    #include "quad.h"


    FILE *outfile = NULL; 
    struct sym_ent *curr_entry; //for tracking function definitions 
    struct sym_tab *curr_stack;
    struct astnode *scalar_quals = NULL; 
    char filename[BUFSIZE];
    int line_tick = 1;
    int offset = 0; 
    int stgclass;

    int yylex();
    void yyerror(char *);
    void fatal_err(char *);

%}

%union
{
    struct _NUMBER
    {
        unsigned long long _INT_;
        long double _FLT_;
        int _TYPE_;
    }VAL;

    struct _STRING
    {
        char _STR_[4096];
        char _CHR_;
        char buf[4096];
        char *pbuf;
        int len;
    }STR;

    struct astnode *ast;
}
%token <VAL._TYPE_> IDENT CHARLIT STRING NUMBER INDSEL PLUSPLUS MINUSMINUS SHL SHR LTEQ GTEQ EQEQ NOTEQ
%token <VAL._TYPE_> LOGAND LOGOR ELLIPSIS TIMESEQ DIVEQ MODEQ PLUSEQ MINUSEQ SHLEQ SHREQ ANDEQ OREQ XOREQ
%token <VAL._TYPE_> AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF 
%token <VAL._TYPE_> INLINE INT LONG REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF
%token <VAL._TYPE_> UNION UNSIGNED VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY THEN

%type <ast> primary_expr parenth_expr cast_expr expr direct_comp_selec indirect_comp_selec expr_list 
%type <ast> postfix_expr subscript_expr component_selec_expr func_call postincdec_expr 
%type <ast> unary_expr sizeof_expr unary_op_expr preincdec_expr
%type <ast> mult_expr add_expr shift_expr relate_expr eq_expr
%type <ast> bit_or_expr bit_xor_expr bit_and_expr logical_or_expr logical_and_expr cond_expr assign_expr comma_expr 
%type <ast> constant

%type <ast> declaration declaration_specifiers init_declarator_list declaration_specifiers_opt
%type <ast> init_declarator_list_opt initialized_declarator declarator initializer initializer_list type_specifier 
%type <ast> float_type_specifier int_type_specifier typedef_name void_type_specifier function_declarator
%type <ast> bool_type_specifier cmplx_type_specifier ptr_declarator direct_declarator array_declarator
%type <ast> simple_declarator pointer type_qualifier_list designation_opt designation designator_list 
%type <ast> designator constant_expr_opt constant_expr top_level_decl parameter_type_list parameter_list parameter_decl 

%type <ast> type_name abstract_declarator_opt abstract_declarator direct_abstract_declarator_opt direct_abstract_declarator 
%type <ast> translation_unit function_def function_def_specifier declaration_list compound_statement block_item_list_opt block_item_list block_item 
%type <ast> fn_compound_statement statement labeled_statement expression_statement iter_statement conditional_statement
%type <ast> break_statement continue_statement return_statement goto_statement null_statement if_statement if_else_statement do_statement
%type <ast> while_statement for_statement initial_clause for_expressions 

%type <VAL._TYPE_> unary_op mult_op add_op prepost_pm_op shift_op relate_op eq_op assign_op storage_class_specifier type_qualifier
%type <VAL._TYPE_> signed_type_specifier unsigned_type_specifier char_type_specifier 

%left IF

/*
    credit: https://stackoverflow.com/questions/12731922/reforming-the-grammar-to-remove-shift-reduce-conflict-in-if-then-else
        - helped fix the shift/reduce warning for if-else grammar
*/
%right THEN ELSE
%right SIGNED UNSIGNED INT SHORT LONG DOUBLE CHAR

%start translation_unit

%%


translation_unit: top_level_decl
                | translation_unit top_level_decl
                ;

top_level_decl: declaration 
              | function_def
              ;

function_def: function_def_specifier fn_compound_statement 
            ;

function_def_specifier: declarator 
                      | declarator declaration_list
                      | declaration_specifiers declarator           {struct sym_attr attr;
                                                                     append_ast(&$1, &$2);
                                                                     ast_reverse(&$1);
                                                                     int line_num = $1->ident.line_no;
                                                                     char *name = $1->ident.name, *filename = $1->ident.filename; 
                                                                     struct astnode *type = $1->ident.next, *desig_node = get_symType(type);
                                                                     if(desig_node->nodetype != AST_FUNC)   yyerror("Function definition requires"); 
                                                                     else
                                                                     {
                                                                        attr.sym_type = SYM_FUNC;                                                                         
                                                                        if(stgclass == 0 || stgclass == EXTERN_CLASS)
                                                                            attr.s_func.stg = EXTERN_CLASS;
                                                                        else    yyerror("Function declarations can only have an explicit \'extern\' storage class");
                                                                        attr.s_func.ret_type = desig_node->func.ret_type; 
                                                                        if(!attr.s_func.ret_type)   yyerror("Need to specify a return type for function declaration");
                                                                        attr.s_func.args_type = desig_node->func.params; 
                                                                        attr.s_func.bool_fndef = 1;                        
                                                                        curr_entry = sym_enter(&curr_stack, attr, curr_stack->scope, OTHER, name, line_num, filename);
                                                                        if(curr_entry) 
                                                                        {
                                                                            if(desig_node->func.params)     stack_push(&curr_stack, FUNC);
                                                                            struct astnode *params = desig_node->func.params; 
                                                                            while(params)
                                                                            {
                                                                                struct sym_attr param_attr; 
                                                                                install_decl(&curr_stack, &(params->declaration.decl), &stgclass, &offset);
                                                                                params = params->declaration.next; 
                                                                            }                                                                        
                                                                            scalar_quals = NULL, stgclass = 0;
                                                                        }
                                                                     }}

                      | declaration_specifiers declarator declaration_list
                      ;

//add statement grammar later
block_item: declaration {$$ = astnode_lloc(AST_ITEM);
                         $$->item.decl_or_stmt = $1;}

          | statement   {$$ = astnode_lloc(AST_ITEM);
                         $$->item.decl_or_stmt = $1;}
          ;

declaration_list: declaration 
                | declaration_list declaration
                ;

block_item_list_opt: %empty {$$ = NULL;}
                   | block_item_list
                   ;

block_item_list: block_item               
               | block_item_list block_item     {struct astnode *temp = $1;
                                                 while(temp->item.next)
                                                     temp = temp->item.next;
                                                 temp->item.next = $2;}
               ;

fn_compound_statement: '{' {if(curr_stack->scope != FUNC) stack_push(&curr_stack, FUNC);} block_item_list_opt '}'  {$$ = astnode_lloc(AST_CMPD);
                                                                                                                    $$->cmpd_stmt.item_list = $3;
                                                                                                                    if(curr_entry)
                                                                                                                    {
                                                                                                                        curr_entry->s_attr.s_func.body = $$;
                                                                                                                        curr_entry->s_attr.s_func.fn_table = curr_stack->head; //capture symbol table for function
                                                                                                                    }
                                                                                                                    IR_gen(outfile, curr_stack, $3);
                                                                                                                    debug("DONE WITH IR GEN", line_tick);
                                                                                                                    curr_stack = stack_pop(&curr_stack);}
                            
                     ;

statement: expression_statement
         | compound_statement 
         | conditional_statement
         | iter_statement
         | break_statement
         | continue_statement
         | return_statement
         | null_statement
         ;

expression_statement: expr ';' ;

compound_statement: '{' {stack_push(&curr_stack, BLOCK);} block_item_list_opt '}' {struct sym_attr block_table;
                                                                                   block_table.sym_type = SYM_BLOCK;
                                                                                   block_table.s_block.block_ent = curr_stack->head;
                                                                                   int decl_bool = 0;
                                                                                   struct astnode *temp = $3;
                                                                                   while(temp)
                                                                                   {
                                                                                       if(temp->item.decl_or_stmt->nodetype == AST_DECL)
                                                                                       {
                                                                                           debug("DECL FOUND!", line_tick);
                                                                                           decl_bool = 1;
                                                                                           break;
                                                                                       }
                                                                                       temp = temp->item.next;
                                                                                   }
                                                                                   if(decl_bool)
                                                                                       sym_enter(&(curr_stack->next), block_table, curr_stack->next->scope, OTHER, "BLOCK", 0, filename);
                                                                                   $$ = astnode_lloc(AST_CMPD);
                                                                                   $$->cmpd_stmt.item_list = $3;
                                                                                   curr_stack = stack_pop(&curr_stack);}
                  ;
            
conditional_statement: if_statement
                     ;

if_statement: IF '(' expr ')' statement %prec THEN              {$$ = astnode_lloc(AST_IF);
                                                                 $$->if_stmt.expr = $3;
                                                                 $$->if_stmt.body = $5;}

            | IF '(' expr ')' statement ELSE statement          {$$ = astnode_lloc(AST_IF_ELSE);
                                                                 $$->if_else_stmt.expr = $3;
                                                                 $$->if_else_stmt.if_body = $5;
                                                                 $$->if_else_stmt.else_body = $7;}
            ;

iter_statement: while_statement
              | do_statement
              | for_statement
              ;

while_statement: WHILE '(' expr ')' statement {$$ = astnode_lloc(AST_WHILE);
                                               $$->while_stmt.expr = $3;
                                               $$->while_stmt.body = $5;}
               ;

do_statement: DO statement WHILE '(' expr ')' ';' {$$ = astnode_lloc(AST_DO);
                                                   $$->do_stmt.expr = $5;
                                                   $$->do_stmt.body = $2;}
            ;

for_statement: FOR for_expressions statement               {$$ = $2; $$->for_stmt.body = $3;}
             ;

initial_clause: expr
              | declaration 
              ;

for_expressions: '(' ';' ';' ')'                            {$$ = for_node_init(NULL, NULL, NULL);}
               | '(' initial_clause ';' ';' ')'             {$$ = for_node_init(&$2, NULL, NULL);}
               | '(' ';' expr ';' ')'                       {$$ = for_node_init(NULL, &$3, NULL);}
               | '(' ';' expr ';' expr ')'                  {$$ = for_node_init(NULL, &$3, &$5);}
               | '(' ';' ';' expr ')'                       {$$ = for_node_init(NULL, NULL, &$4);}
               | '(' initial_clause ';' expr ';' ')'        {$$ = for_node_init(&$2, &$4, NULL);}
               | '(' initial_clause ';' expr ';' expr ')'   {$$ = for_node_init(&$2, &$4, &$6);}
               | '(' initial_clause ';' ';' expr ')'        {$$ = for_node_init(&$2, NULL, &$5);}
               ;

break_statement: BREAK ';'          {$$ = astnode_lloc(AST_BREAK);
                                     $$->break_stmt.op = BREAK;}
               ;

continue_statement: CONTINUE ';'    {$$ = astnode_lloc(AST_CONT);
                                     $$->cont_stmt.op = CONTINUE;}
                  ;

return_statement: RETURN ';'        {$$ = astnode_lloc(AST_RET);
                                     $$->ret_stmt.ret_expr = NULL;}

                | RETURN expr ';'   {$$ = astnode_lloc(AST_RET);
                                     $$->ret_stmt.ret_expr = $2;}
                ;

null_statement: ';'                 {$$ = NULL;}
              ;

declaration: declaration_specifiers init_declarator_list_opt ';'    {$$ = astnode_lloc(AST_DECL);
                                                                     append_ast(&$1, &$2); 
                                                                     /* REVERSE AST */
                                                                     ast_reverse(&$1);
                                                                     $$->declaration.decl = $1; 
                                                                     install_decl(&curr_stack, &$1, &stgclass, &offset);
                                                                     scalar_quals = NULL, stgclass = 0;}
           ;

declaration_specifiers_opt: %empty {$$ = NULL;}
                          | declaration_specifiers 
                          ;

declaration_specifiers: storage_class_specifier declaration_specifiers_opt  {if(stgclass != 0)  yyerror("More than one storage class may not be specified");
                                                                             $$ = $2; 
                                                                             stgclass = $1;}

                      | type_specifier  declaration_specifiers_opt          {$$->scalar.qualifier = scalar_quals;
                                                                             $$->scalar.next = $2;}

                      | type_qualifier declaration_specifiers_opt           {$$ = astnode_lloc(AST_QUAL);
                                                                             if($1 == RESTRICT)
                                                                             {
                                                                                 yyerror("[Error] \'restrict\' qualifier not permitted for non-pointers");
                                                                                 $$ = NULL; 
                                                                             }
                                                                             else 
                                                                             {
                                                                                $$->qualif.qual = $1;
                                                                                $$->qualif.next = NULL;
                                                                             }
                                                                             struct astnode *temp = scalar_quals;
                                                                             if(!scalar_quals)     scalar_quals = $$;  
                                                                             else
                                                                             {                             
                                                                                while(temp->qualif.next)   temp = temp->qualif.next;
                                                                                temp->qualif.next = $$;
                                                                                temp = temp->qualif.next;
                                                                             }
                                                                             if(!$$ && $2 && $2->nodetype == AST_QUAL)     
                                                                                temp->qualif.next = $2;
                                                                             else if($$ && $2 && $2->nodetype == AST_SCALAR)
                                                                                 $2->scalar.qualifier = scalar_quals;
                                                                             $$ = $2;}
                      ;

storage_class_specifier: AUTO       {$$ = AUTO_CLASS;}
                       | EXTERN     {$$ = EXTERN_CLASS;}
                       | REGISTER   {$$ = REGISTER_CLASS;}
                       | STATIC     {$$ = STATIC_CLASS;}
                       | TYPEDEF    {$$ = TYPEDEF_CLASS;}
                       ;

init_declarator_list_opt: %empty    {$$ = NULL;}
                        | init_declarator_list
                        ;

init_declarator_list: initialized_declarator
                    | init_declarator_list ',' initialized_declarator
                    ;

initialized_declarator: declarator 
                      | declarator '=' initializer
                      ;

declarator: ptr_declarator 
          | direct_declarator
          ;

direct_declarator: simple_declarator
                 | '(' declarator ')'   {$$ = $2;}
                 | function_declarator
                 | array_declarator
                 ;

simple_declarator: IDENT    {$$ = astnode_lloc(AST_IDENT);
                             memset($$->ident.name, '0', 4096);
                             memset($$->ident.filename, '0', 4096);
                             memcpy($$->ident.name, yylval.STR._STR_, sizeof(yylval.STR._STR_));
                             memcpy($$->ident.filename, filename, sizeof(yylval.STR._STR_));
                             $$->ident.line_no = line_tick; 
                             $$->ident.next = NULL;}
                 ;

ptr_declarator: pointer direct_declarator   {$$ = $1;
                                             struct astnode *temp = $1; 
                                             while(temp->ptr.next != NULL)    temp = temp->ptr.next;
                                             temp->ptr.next = $2; //set tail of ptr list to decl
                                            }
              ;

pointer: '*'                                {$$ = astnode_lloc(AST_PTR);
                                             $$->ptr.qual_l = NULL;
                                             $$->ptr.next = NULL;}    
                                        
       | '*' type_qualifier_list            {$$ = astnode_lloc(AST_PTR);
                                             $$->ptr.qual_l = $2;
                                             $$->ptr.next = NULL;} 

       | '*' pointer                        {$$ = astnode_lloc(AST_PTR);
                                             $$->ptr.qual_l = NULL;
                                             $$->ptr.next = $2;}

       | '*' type_qualifier_list pointer    {$$ = astnode_lloc(AST_PTR);
                                             $$->ptr.qual_l = $2;
                                             $$->ptr.next = $3;}
       ;

type_qualifier_list: type_qualifier                         {$$ = astnode_lloc(AST_QUAL);
                                                             $$->qualif.qual = $1;
                                                             $$->qualif.next = NULL;}

                   | type_qualifier_list type_qualifier     {$$ = astnode_lloc(AST_QUAL);
                                                             $$->qualif.qual = $2;
                                                             $$->qualif.next = $1;}     
                   ;

type_qualifier: CONST       {$$ = CONST;}
              | VOLATILE    {$$ = VOLATILE;}
              | RESTRICT    {$$ = RESTRICT;}
              ;

parameter_type_list: parameter_list ;

parameter_list: parameter_decl
              | parameter_list ',' parameter_decl   {struct astnode *temp = $1; 
                                                     while(temp->declaration.next)    
                                                        temp = temp->declaration.next;
                                                     temp->declaration.next = $3;}
              ;

/* 
STORE THE ASTNODES OF THE PARAMETERS IN THE FUNCTION ASTNODE
        - @ FUNCTION DEFINITION, THEN INSTALL PARAMETERS IN 
          FUNCTION SYMBOL TABLE!
*/
parameter_decl: declaration_specifiers declarator               {$$ = astnode_lloc(AST_DECL);
                                                                 append_ast(&$1, &$2); 
                                                                 ast_reverse(&$1);
                                                                 $$->declaration.decl = $1;}

              | declaration_specifiers abstract_declarator_opt  {$$ = astnode_lloc(AST_DECL);
                                                                 append_ast(&$1, &$2); 
                                                                 ast_reverse(&$1);
                                                                 $$->declaration.decl = $1;}
              ;

function_declarator: direct_declarator '(' parameter_type_list ')'      {$$ = astnode_lloc(AST_FUNC);
                                                                         $$->func.ret_type = $1;
                                                                         $$->func.params = $3;}
                   
                   | direct_declarator '(' ')'                          {$$ = astnode_lloc(AST_FUNC);
                                                                         $$->func.ret_type = $1;
                                                                         $$->func.params = NULL;}
                   ;                   

array_declarator: direct_declarator '[' ']'    {$$ = astnode_lloc(AST_ARRAY);
                                                $$->array.arr_size = 0;
                                                $$->array.next = $1;}

                | direct_declarator '[' NUMBER ']'    {$$ = astnode_lloc(AST_ARRAY);
                                                       $$->array.arr_size = yylval.VAL._INT_;
                                                       if(yylval.VAL._TYPE_ >= D)
                                                            yyerror("[ERROR] size must be integer type");
                                                       $$->array.next = $1;}
                ;         

abstract_declarator_opt: %empty {$$ = NULL;}
                       | abstract_declarator
                       ;

type_name: declaration_specifiers abstract_declarator_opt   {append_ast(&$1, &$2);}
         ;  

abstract_declarator: pointer                                    
                   | direct_abstract_declarator
                   | pointer direct_abstract_declarator {if($1) 
                                                         {
                                                             struct astnode *temp = $1; 
                                                             while(temp->ptr.next)    temp = temp->ptr.next;
                                                             temp->ptr.next = $2; //set tail of ptr list to decl
                                                         } 
                                                         else   $$ = $2;}
                   ;

direct_abstract_declarator_opt: %empty {$$ = NULL;}
                              | direct_abstract_declarator
                              ;

direct_abstract_declarator: '(' abstract_declarator ')'                             {$$ = $2;}

                          | direct_abstract_declarator_opt '[' ']'                  {$$ = astnode_lloc(AST_ARRAY);
                                                                                     $$->array.arr_size = 0;
                                                                                     $$->array.next = $1;}      

                          | direct_abstract_declarator_opt '[' NUMBER ']'           {$$ = astnode_lloc(AST_ARRAY);
                                                                                     $$->array.arr_size = yylval.VAL._INT_;
                                                                                     if(yylval.VAL._TYPE_ >= D)
                                                                                             yyerror("[ERROR] size must be integer type");
                                                                                     $$->array.next = $1;}
                          ;

initializer: assign_expr
           | '{' initializer_list '}'       {$$ = $2;}
           | '{' initializer_list ',' '}'   {$$ = $2;}
           ;

initializer_list: designation_opt initializer
                | initializer_list ',' designation_opt initializer
                ;

designation_opt: %empty         {$$ = NULL;}
               | designation
               ;

designation: designator_list '='
           ;

designator_list: designator
               | designator_list designator
               ;

designator: '[' constant_expr ']'   {$$ = $2;}
          //| '.' IDENT               {$$ = $2;} //<--- FOR STRUCTS/UNIONS
          ;

constant_expr_opt: %empty {$$ = NULL;}
                 | constant_expr
                 ;

constant_expr: cond_expr
             ;

type_specifier: float_type_specifier 
              | int_type_specifier  
              | void_type_specifier
              ;

int_type_specifier: signed_type_specifier       {$$ = astnode_lloc(AST_SCALAR);
                                                 $$->scalar.type = $1;
                                                 $$->scalar.signedness = S;}

                  | unsigned_type_specifier     {$$ = astnode_lloc(AST_SCALAR);
                                                 $$->scalar.type = $1;
                                                 $$->scalar.signedness = U;}
                                                 
                  | char_type_specifier         {$$ = astnode_lloc(AST_SCALAR);
                                                 $$->scalar.type = C;
                                                 $$->scalar.signedness = $1;}
                  | bool_type_specifier
                  ;

signed_type_specifier: SHORT                   {$$ = SHRT;}
                     | SHORT INT               {$$ = SHRT;}
                     | SIGNED SHORT            {$$ = SHRT;}
                     | SIGNED SHORT INT        {$$ = SHRT;}
                     | INT                     {$$ = I;}
                     | SIGNED                  {$$ = I;}
                     | SIGNED INT              {$$ = I;}
                     | LONG                    {$$ = L;}
                     | LONG INT                {$$ = L;}
                     | SIGNED LONG             {$$ = L;}
                     | SIGNED LONG INT         {$$ = L;}
                     | LONG LONG               {$$ = LL;}
                     | LONG LONG INT           {$$ = LL;}
                     | SIGNED LONG LONG        {$$ = LL;}
                     | SIGNED LONG LONG INT    {$$ = LL;}
                     ;

unsigned_type_specifier: UNSIGNED SHORT          {$$ = SHRT;}
                       | UNSIGNED SHORT INT      {$$ = SHRT;}                               
                       | UNSIGNED                {$$ = I;}
                       | UNSIGNED INT            {$$ = I;}
                       | UNSIGNED LONG           {$$ = L;}
                       | UNSIGNED LONG INT       {$$ = L;}
                       | UNSIGNED LONG LONG      {$$ = LL;}
                       | UNSIGNED LONG LONG INT  {$$ = LL;}
                       ;

char_type_specifier: CHAR           {$$ = 0;}
                   | SIGNED CHAR    {$$ = S;}
                   | UNSIGNED CHAR  {$$ = U;}
                   ;

bool_type_specifier: _BOOL  {$$ = astnode_lloc(AST_SCALAR);
                             $$->scalar.cmplx_bool = BOOL;}
                   ;

float_type_specifier: FLOAT                 {$$ = astnode_lloc(AST_SCALAR);
                                             $$->scalar.type = F;
                                             $$->scalar.signedness = S;}

                    | DOUBLE                {$$ = astnode_lloc(AST_SCALAR);
                                             $$->scalar.type = D;
                                             $$->scalar.signedness = S;}

                    | LONG DOUBLE           {$$ = astnode_lloc(AST_SCALAR);
                                             $$->scalar.type = LD;
                                             $$->scalar.signedness = S;}
                    | cmplx_type_specifier
                    ;

cmplx_type_specifier: FLOAT _COMPLEX        {$$ = astnode_lloc(AST_SCALAR);
                                             $$->scalar.type = F;
                                             $$->scalar.cmplx_bool = CMPLX;
                                             $$->scalar.signedness = S;}

                    | DOUBLE _COMPLEX       {$$ = astnode_lloc(AST_SCALAR);
                                             $$->scalar.type = D;
                                             $$->scalar.cmplx_bool = CMPLX;
                                             $$->scalar.signedness = S;}

                    | LONG DOUBLE _COMPLEX  {$$ = astnode_lloc(AST_SCALAR);
                                             $$->scalar.type = LD;
                                             $$->scalar.cmplx_bool = CMPLX;
                                             $$->scalar.signedness = S;}
                    ;

void_type_specifier: VOID   {$$ = astnode_lloc(AST_SCALAR);
                             $$->scalar.type = V;}
                   ;  

primary_expr: IDENT        {struct sym_ent *ident_symbol = NULL;
                            if(!(ident_symbol = sym_lookup(&curr_stack, curr_stack->scope, OTHER, yylval.STR._STR_)))
                            {
                                char mssg[5120];
                                sprintf(mssg, "Identifier \'%s\' is undefined", yylval.STR._STR_);
                                yyerror(mssg);
                            }
                            $$ = astnode_lloc(AST_IDENT);
                            memset($$->ident.name, '0', 4096);
                            strcpy($$->ident.name, yylval.STR._STR_);
                            $$->ident.metadata = ident_symbol;}
            | constant 
            | parenth_expr
            ;

parenth_expr: '(' expr ')'  {$$ = $2;} ;

postfix_expr: primary_expr
            | subscript_expr
            | component_selec_expr
            | func_call 
            | postincdec_expr
            ;

subscript_expr: postfix_expr '[' expr ']' {$$ = astnode_lloc(AST_UOP);
                                           $$->uop.op = '*';
                                           $$->uop.left = astnode_lloc(AST_BOP);
                                           $$->uop.left->bop.op = '+';
                                           $$->uop.left->bop.left = $1;
                                           $$->uop.left->bop.right = $3;}
              ;

component_selec_expr: direct_comp_selec
                    | indirect_comp_selec
                    ;

direct_comp_selec: postfix_expr '.' IDENT {$$ = astnode_lloc(AST_UOP);
                                           $$->uop.op = '.';
                                           $$->uop.left = $1;
                                           $$->uop.right = astnode_lloc(AST_IDENT);
                                           memset($$->uop.right->ident.name, '0', 4096);
                                           strcpy($$->uop.right->ident.name, yylval.STR._STR_);}
                 ;

indirect_comp_selec: postfix_expr INDSEL IDENT {$$ = astnode_lloc(AST_COMP_SEL);
                                                $$->comp_sel.left = astnode_lloc(AST_UOP);
                                                $$->comp_sel.left->uop.op = '*';
                                                $$->comp_sel.left->uop.left = $1;
                                                $$->comp_sel.right = astnode_lloc(AST_IDENT);
                                                memset($$->comp_sel.right->ident.name, '0', 4096);
                                                strcpy($$->comp_sel.right->ident.name, yylval.STR._STR_);}
                   ;

func_call: postfix_expr '(' expr_list ')' {int argc = 0, argnum;
                                           struct astnode *temp;
                                           $$ = astnode_lloc(AST_FNCALL);
                                           $$->fncall.left = $1;
                                           $$->fncall.right = $3;
                                           temp = $$->fncall.right;
                                           while(temp != NULL)
                                           {
                                               ++argc;
                                               temp = temp->elist.left;
                                           }
                                           temp = $$->fncall.right;
                                           argnum = argc;
                                           while(temp != NULL)
                                           {
                                               temp->elist.argnum = argnum--;
                                               temp = temp->elist.left;
                                           }
                                           $$->fncall.argc = argc;}
         ;

expr_list: %empty   {$$ = NULL;}
         | assign_expr               {$$ = astnode_lloc(AST_ELIST);
                                      $$->elist.left = NULL;
                                      $$->elist.right = $1;}

         | expr_list ',' assign_expr {$$ = astnode_lloc(AST_ELIST);
                                      $$->elist.left = $1;
                                      $$->elist.right = $3;}
         ;

prepost_pm_op: PLUSPLUS     {$$ = PLUSPLUS;}
             | MINUSMINUS   {$$ = MINUSMINUS;}
             ;

postincdec_expr: postfix_expr prepost_pm_op {$$ = astnode_lloc(AST_UOP);
                                             $$->uop.op = $2;
                                             $$->uop.left = $1;}
             ;

unary_expr: postfix_expr
          | sizeof_expr
          | unary_op_expr
          | preincdec_expr
          ;

cast_expr: unary_expr 
         | '(' type_name ')' cast_expr  {$$ = astnode_lloc(AST_CAST);
                                         ast_reverse(&$2);
                                         $$->cast.type = $2;
                                         $$->cast.to = $4;}
         ;

sizeof_expr: SIZEOF unary_expr          {$$ = astnode_lloc(AST_UOP);
                                         $$->uop.op = SIZEOF;
                                         $$->uop.left = $2;}

           | SIZEOF '(' type_name ')'   {ast_reverse(&$3);
                                         $$ = astnode_lloc(AST_UOP);
                                         $$->uop.op = SIZEOF;
                                         $$->uop.left = $3;}
           ;

unary_op_expr: unary_op cast_expr  {$$ = astnode_lloc(AST_UOP);
                                    $$->uop.op = $1;
                                    $$->uop.left = $2;}
             ;

unary_op: '-' {$$ = '-';}
        | '+' {$$ = '+';}
        | '!' {$$ = '!';}
        | '~' {$$ = '~';}
        | '&' {$$ = '&';}
        | '*' {$$ = '*';}
        ;

preincdec_expr: prepost_pm_op unary_expr {$$ = astnode_lloc(AST_ASSIGN);
                                          $$->assign.left = $2;
                                          $$->assign.right = astnode_lloc(AST_BOP);
                                          int p_op = $1 == PLUSPLUS ? '+' : '-';
                                          $$->assign.right->bop.op = p_op;
                                          $$->assign.right->bop.left = $2;
                                          $$->assign.right->bop.right = astnode_lloc(AST_NUM);
                                          $$->assign.right->bop.right->num.i_val = 1;}

mult_op: '*' {$$ = '*';}
       | '/' {$$ = '/';}
       | '%' {$$ = '%';}
       ;

mult_expr: cast_expr
         | mult_expr mult_op cast_expr {$$ = astnode_lloc(AST_BOP);
                                        $$->bop.op = $2;
                                        $$->bop.left = $1;
                                        $$->bop.right = $3;}
         ;

add_op: '+' {$$ = '+';}
      | '-' {$$ = '-';}
      ;

add_expr: mult_expr
        | add_expr add_op mult_expr {$$ = astnode_lloc(AST_BOP);
                                     $$->bop.op = $2;
                                     $$->bop.left = $1;
                                     $$->bop.right = $3;}
        ;

shift_op: SHL {$$ = SHL;}
        | SHR {$$ = SHR;}
        ;

shift_expr: add_expr
          | shift_expr shift_op add_expr {$$ = astnode_lloc(AST_BOP);
                                         $$->bop.op = $2;
                                         $$->bop.left = $1;
                                         $$->bop.right = $3;}
          ;

relate_op: '<'  {$$ = '<';}
         | LTEQ {$$ = LTEQ;}
         | '>'  {$$ = '>';}
         | GTEQ {$$ = GTEQ;}
         ;
relate_expr: shift_expr
           | relate_expr relate_op shift_expr {$$ = astnode_lloc(AST_EQCOMP);
                                               $$->eqcomp.op = $2;
                                               $$->eqcomp.left = $1;
                                               $$->eqcomp.right = $3;}
           ;

eq_op: EQEQ  {$$ = EQEQ;}
     | NOTEQ {$$ = NOTEQ;}
     ;

eq_expr: relate_expr
       | eq_expr eq_op relate_expr {$$ = astnode_lloc(AST_EQCOMP);
                                    $$->eqcomp.op = $2;
                                    $$->eqcomp.left = $1;
                                    $$->eqcomp.right = $3;}
       ;

bit_or_expr: bit_xor_expr
           | bit_or_expr '|' bit_xor_expr {$$ = astnode_lloc(AST_BOP);
                                           $$->bop.op = '|';
                                           $$->bop.left = $1;
                                           $$->bop.right = $3;}
           ;

bit_xor_expr: bit_and_expr
            | bit_xor_expr '^' bit_and_expr {$$ = astnode_lloc(AST_BOP);
                                             $$->bop.op = '^';
                                             $$->bop.left = $1;
                                             $$->bop.right = $3;}
            ;

bit_and_expr: eq_expr
            | bit_and_expr '&' eq_expr {$$ = astnode_lloc(AST_BOP);
                                        $$->bop.op = '&';
                                        $$->bop.left = $1;
                                        $$->bop.right = $3;}
            ;

logical_or_expr: logical_and_expr 
               | logical_or_expr LOGOR logical_and_expr {$$ = astnode_lloc(AST_LOG);
                                                         $$->log.op = LOGOR;
                                                         $$->log.left = $1;
                                                         $$->log.right = $3;}
               ;

logical_and_expr: bit_or_expr 
                | logical_and_expr LOGAND bit_or_expr {$$ = astnode_lloc(AST_LOG);
                                                       $$->log.op = LOGAND;
                                                       $$->log.left = $1;
                                                       $$->log.right = $3;}
                ;

cond_expr: logical_or_expr
         | logical_or_expr '?' expr ':' cond_expr {$$ = astnode_lloc(AST_TERN);
                                                   $$->tern.left = $1;
                                                   $$->tern.right = astnode_lloc(AST_TERN);
                                                   $$->tern.right->tern.op = '?';
                                                   $$->tern.right->tern.left = $3;
                                                   $$->tern.right->tern.right = astnode_lloc(AST_TERN);
                                                   $$->tern.right->tern.right->tern.op = ':';
                                                   $$->tern.right->tern.right->tern.left = $5;}
         ;

assign_op: PLUSEQ   {$$ = PLUSEQ;}
         | MINUSEQ  {$$ = MINUSEQ;}
         | TIMESEQ  {$$ = TIMESEQ;}
         | DIVEQ    {$$ = DIVEQ;}
         | MODEQ    {$$ = MODEQ;}
         | SHLEQ    {$$ = SHLEQ;}
         | SHREQ    {$$ = SHREQ;}
         | ANDEQ    {$$ = ANDEQ;}
         | XOREQ    {$$ = XOREQ;}
         | OREQ     {$$ = OREQ;}
         ; 

assign_expr: cond_expr
           | unary_expr '=' assign_expr {$$ = astnode_lloc(AST_ASSIGN);
                                         $$->assign.op = '=';
                                         $$->assign.left = $1;
                                         $$->assign.right = $3;}
                                         
           | unary_expr assign_op assign_expr {$$ = astnode_lloc(AST_ASSIGN);
                                               $$->assign.op = '=';
                                               $$->assign.left = $1;
                                               $$->assign.right = astnode_lloc(AST_BOP);
                                               $$->assign.right->bop.op = $2 < 255 ? $2 : print_kwop($2)[0];
                                               $$->assign.right->bop.left = $1;
                                               $$->assign.right->bop.right = $3;}
           ;

comma_expr: assign_expr
          | comma_expr ',' assign_expr {$$ = astnode_lloc(AST_BOP);
                                        $$->bop.op = ',';
                                        $$->bop.left = $1;
                                        $$->bop.right = $3;}
          ;

expr: comma_expr;

constant: NUMBER    {$$ = astnode_lloc(AST_NUM);
                     $$->num.i_val = yylval.VAL._INT_;
                     $$->num.fd_val = yylval.VAL._FLT_;
                     $$->num.type = yylval.VAL._TYPE_;}

        | STRING    {$$ = astnode_lloc(AST_STR);
                     memset($$->str_lit.str, '0', 4096);
                     strcpy($$->str_lit.str, yylval.STR._STR_);
                     $$->str_lit.len = yylval.STR.len;}

        | CHARLIT   {$$ = astnode_lloc(AST_CHAR);
                     $$->char_lit.chr = yylval.STR._CHR_;}
        ;
%%

void yyerror(char *mssg)
{
    fprintf(stderr, "%s:[%d] WARNING: %s\n", filename, line_tick, mssg);
}

int main(void)
{
    if((outfile = fopen("target_code.S", "w+")) == NULL)
        fatal_err(strerror(errno));
    curr_stack = table_create(GLOBAL);
    yyparse();
    struct sym_ent *temp = curr_stack->head; 
    if(!curr_stack->head->next) debug("NULL", line_tick);
    sym_print(curr_stack->head, curr_stack->scope);
    fclose(outfile);
    return 1; 
}
