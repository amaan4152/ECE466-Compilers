/*Amaan Rahman ECE466 Lexer*/
%option noyywrap
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <limits.h>
    #include "parser.tab.h"
    #include "extdef.h"

    YYSTYPE yylval;
    
    char filename[4096] = "<stdin>";
    int line_tick;

    char cesc_seq(char *);
    char nesc_seq(char *, char);
    char *print_kwop(int);
    void format(char, char **);
    void yyerror(char *);
%}

%x  LIT
%x  CHAR_LIT
%x  MARK
/* regular definitions */

ws          [ \t\r\v\f]+
digit       [0-9]
ID          [A-Za-z_]([A-Za-z_]|{digit})*
HEX         0[xX][0-9A-Fa-f]+
OCT         0[0-7]*
INT         ([1-9]+[0-9]*)|{HEX}|{OCT}
UL          [uU][lL]
LU          [lL][uU]
ULL         [uU]("LL"|"ll")
LLU         ("LL"|"ll")[uU]
DBL_HX      0[xX][0-9A-Fa-f]*(\.)?[0-9A-Fa-f]*([pP][-+]?{digit}+)?
DOUBLE      ([0-9]*\.[0-9]*)|([0-9]*(\.)?[0-9]*[eE][-+]?[0-9]+)|{DBL_HX}
FLT         ({DOUBLE}|{DBL_HX})[fF]
SING_CHAR   [!%\^&\*\-\+=~\|\.\<\>\/\?\(\)\[\]\{\},;:]
CHAR_ESC    \\[0ntbrfva?\\\'\"]
EOL         \n
%%

{ws}                      

#                               {BEGIN(MARK); memset(filename, 0, 4096);}                           

<MARK>{
[0-9]+/(" \"")                  {line_tick = atoi(yytext);}
\".+\"                          {strncpy(filename, yytext+1, strlen(yytext)-2);}
\n                              {BEGIN(INITIAL);}
.
}

auto        {return AUTO;}
char        {return CHAR;}
default     {return DEFAULT;}
else        {return ELSE;}
for         {return FOR;}
inline      {return INLINE;}
return      {return RETURN;}
static      {return STATIC;}
union       {return UNION;}
while       {return WHILE;}
_Bool       {return _BOOL;}
_Complex    {return _COMPLEX;}
restrict    {return RESTRICT;}
enum        {return ENUM;}
goto        {return GOTO;}
int         {return INT;}
short       {return SHORT;}
struct      {return STRUCT;}
unsigned    {return UNSIGNED;}
break       {return BREAK;}
const       {return CONST;}
do          {return DO;}
extern      {return EXTERN;}
if          {return IF;}
long        {return LONG;}
signed      {return SIGNED;}
switch      {return SWITCH;}
void        {return VOID;}
case        {return CASE;}
continue    {return CONTINUE;}
double      {return DOUBLE;}
float       {return FLOAT;}
_Imaginary  {return _IMAGINARY;}
register    {return REGISTER;}
sizeof      {return SIZEOF;}
typedef     {return TYPEDEF;}
volatile    {return VOLATILE;}

\"                              {BEGIN(LIT); yylval.STR.pbuf = yylval.STR.buf;}
\'                              {BEGIN(CHAR_LIT); yylval.STR.pbuf = yylval.STR.buf;}
<CHAR_LIT>\'                    {
                                    BEGIN(INITIAL);
                                    *yylval.STR.pbuf = '\0'; 
                                    if(strlen(yylval.STR.buf) > 2)  yyerror("Unsupported multibyte literal; truncated to first byte\n");
                                    yylval.STR._CHR_ = yylval.STR.buf[0];
                                    yylval.STR.len = 0;
                                    return CHARLIT;
                                }
<LIT>{
\"                              {
                                    BEGIN(INITIAL); 
                                    *yylval.STR.pbuf = '\0';
                                    if(++yylval.STR.len > 4096)
                                    {
                                        yyerror("Length of string greater than max length\n");
                                        yylval.STR.len = 4096;
                                    }
                                    memset(yylval.STR._STR_, '0', 4096);
                                    strcpy(yylval.STR._STR_, yylval.STR.buf);
                                    return STRING;
                                }
<CHAR_LIT>{
\n                              {yyerror("Unterminated string constant\n"); exit(EXIT_FAILURE);}
{CHAR_ESC}                      {*yylval.STR.pbuf++ = cesc_seq(yytext);}
                                
\\[0-7]{1,3}                    {*yylval.STR.pbuf++ = nesc_seq(yytext, 'o');}
\\x[0-9A-Fa-f]+                 {*yylval.STR.pbuf++ = nesc_seq(yytext, 'h');}
\\(.)                           {yyerror("Illegal escape sequence\n");}                             
[^\\]                           {
                                    char* yyptr = yytext;
                                    while(*yyptr)
                                    {
                                        *yylval.STR.pbuf++ = *yyptr++;
                                        yylval.STR.len++;
                                    }
                                }    
}
}

{ID}                            {memset(yylval.STR._STR_, '0', 4096);
                                 strcpy(yylval.STR._STR_, yytext); return IDENT;}

{SING_CHAR}                     {yylval.STR._CHR_ = yytext[0]; return (int)yytext[0];}

{OCT}                           {yylval.VAL._INT_ = strtol(yytext, NULL, 0);
                                yylval.VAL._TYPE_ = 0;
                                return NUMBER;} 

{INT}                           {yylval.VAL._INT_ = strtol(yytext, NULL, 0);
                                yylval.VAL._TYPE_ = 0;
                                return NUMBER;} 

{INT}[uU]                       {yylval.VAL._INT_ = strtoul(yytext, NULL, 0);
                                yylval.VAL._TYPE_ = U;
                                return NUMBER;} 

{INT}[lL]                       {yylval.VAL._INT_ = strtol(yytext, NULL, 0); 
                                yylval.VAL._TYPE_ = L;
                                return NUMBER;} 

{INT}({UL}|{LU})                {yylval.VAL._INT_ = strtoul(yytext, NULL, 0); 
                                yylval.VAL._TYPE_ = UL;
                                return NUMBER;} 

{INT}("ll"|"LL")                {yylval.VAL._INT_ = strtoll(yytext, NULL, 0); 
                                yylval.VAL._TYPE_ = LL; 
                                return NUMBER;} 

{INT}({ULL}|{LLU})              {yylval.VAL._INT_ = strtoull(yytext, NULL, 0); 
                                yylval.VAL._TYPE_ = ULL;
                                return NUMBER;} 

{DOUBLE}                        {yylval.VAL._FLT_ = strtold(yytext, NULL); 
                                yylval.VAL._TYPE_ = D;
                                return NUMBER;} 

{DOUBLE}[lL]                    {yylval.VAL._FLT_ = strtold(yytext, NULL); 
                                yylval.VAL._TYPE_ = LD;
                                return NUMBER;} 

{FLT}                           {yylval.VAL._FLT_ = strtod(yytext, NULL); 
                                yylval.VAL._TYPE_ = F;
                                return NUMBER;} 

"->"                            {return INDSEL;}
"++"                            {return PLUSPLUS;}
"--"                            {return MINUSMINUS;}
"<<"                            {return SHL;}
">>"                            {return SHR;}
"<="                            {return LTEQ;}
">="                            {return GTEQ;}
"=="                            {return EQEQ;}
"!="                            {return NOTEQ;}
"&&"                            {return LOGAND;}
"||"                            {return LOGOR;}
"..."                           {return ELLIPSIS;}
"*="                            {return TIMESEQ;}
"/="                            {return DIVEQ;}
"%="                            {return MODEQ;}
"+="                            {return PLUSEQ;}
"-="                            {return MINUSEQ;}
"<<="                           {return SHLEQ;}
">>="                           {return SHREQ;}
"&="                            {return ANDEQ;}
"|="                            {return OREQ;}
"^="                            {return XOREQ;}
"<%"                            {return (int)'{';}
"%>"                            {return (int)'}';}
"<:"                            {return (int)'[';}
":>"                            {return (int)']';}

{EOL}                           {++line_tick;}

<<EOF>>                         {return 0;}

.                               {yyerror("Illegal character");}

%%

char* print_kwop(int f)
{
    switch(f)
    {
        case INDSEL: return "->"; break;
        case PLUSPLUS: return "++"; break;
        case MINUSMINUS: return "--"; break;
        case SHL: return "<<"; break;
        case SHR: return ">>"; break;
        case LTEQ: return "<="; break;
        case GTEQ: return ">="; break;
        case EQEQ: return "=="; break;
        case NOTEQ: return "!="; break;
        case LOGAND: return "&&"; break;
        case LOGOR: return "||"; break;
        case ELLIPSIS: return "..."; break;
        case TIMESEQ: return "*="; break;
        case DIVEQ: return "/="; break;
        case MODEQ: return "%="; break;
        case PLUSEQ: return "+="; break;
        case MINUSEQ: return "-="; break;
        case SHLEQ: return "<<="; break;
        case SHREQ: return ">>="; break;
        case ANDEQ: return "&="; break;
        case OREQ: return "|="; break;
        case XOREQ: return "^="; break;
        case AUTO: return "AUTO"; break;
        case BREAK: return "BREAK"; break;
        case CASE: return "CASE"; break;
        case CHAR: return "CHAR"; break;
        case CONST: return "CONST"; break;
        case CONTINUE: return "CONTINUE"; break;
        case DEFAULT: return "DEFAULT"; break;
        case DO: return "DO"; break;
        case DOUBLE: return "DOUBLE"; break;
        case ELSE: return "ELSE"; break;
        case ENUM: return "ENUM"; break;
        case EXTERN: return "EXTERN"; break;
        case FLOAT: return "FLOAT"; break;
        case FOR: return "FOR"; break;
        case GOTO: return "GOTO"; break;
        case IF: return "IF"; break;
        case INLINE: return "INLINE"; break;
        case INT: return "INT"; break;
        case LONG: return "LONG"; break;
        case REGISTER: return "REGISTER"; break;
        case RETURN: return "RETURN"; break;
        case SHORT: return "SHORT"; break;
        case SIGNED: return "SIGNED"; break;
        case SIZEOF: return "SIZEOF"; break;
        case STATIC: return "STATIC"; break;
        case STRUCT: return "STRUCT"; break;
        case SWITCH: return "SWITCH"; break;
        case TYPEDEF: return "TYPEDEF"; break;
        case UNION: return "UNION"; break;
        case UNSIGNED: return "UNSIGNED"; break;
        case VOID: return "VOID"; break;
        case VOLATILE: return "VOLATILE"; break;
        case RESTRICT: return "RESTRICT"; break;
        case WHILE: return "WHILE"; break;
        case _BOOL: return "_BOOL"; break;
        case _COMPLEX: return "_COMPLEX"; break;
        case _IMAGINARY: return "_IMAGINARY"; break;        
    }
}

char cesc_seq(char* seq)
{
    yylval.STR.len++;
    switch(seq[1])
    {
        case '0':   return '\0';
        case 'n':   return '\n';
        case 't':   return '\t';
        case 'b':   return '\b';
        case 'r':   return '\r';
        case 'f':   return '\f';
        case 'v':   return '\v';
        case 'a':   return '\a';
        case '\\':  return '\\';
        case '\'':  return '\'';
        case '\"':  return '\"';
        case '?':   return '\?';
    }
}

char nesc_seq(char* seq, char type)
{
    unsigned int val; 
    switch(type)
    {
        case 'h': //hex
            sscanf(seq+2, "%x", &val);
            if(val > 0XFF)  yyerror("Hex constant out-of-bounds\n");
            break;
        case 'o': //octal
            sscanf(seq+1, "%o", &val);
            if(val > 0XFF)  yyerror("Octal constant out-of-bounds\n");
            break;
    }
    yylval.STR.len++;
    return (char)val; 
}

void format(char c, char **str)
{
    switch(c)
    {
        case '\0':   sprintf(*str, "\\0"); break;
        case '\n':   sprintf(*str, "\\n"); break;
        case '\t':   sprintf(*str, "\\t"); break;
        case '\b':   sprintf(*str, "\\b"); break;
        case '\r':   sprintf(*str, "\\r"); break;
        case '\f':   sprintf(*str, "\\f"); break;
        case '\v':   sprintf(*str, "\\v"); break;
        case '\a':   sprintf(*str, "\\a"); break;
        case '\\':   sprintf(*str, "\\\\"); break;
        case '\'':   sprintf(*str, "\\\'"); break;
        case '\"':   sprintf(*str, "\\\""); break;
        case '\?':   sprintf(*str, "\?"); break;
        default: 
            if(c > 31 && c < 127) 
                sprintf(*str, "%c", c);
            else
            {
                if((unsigned int)c > 0XFF)   c = 0XFF;
                sprintf(*str, "\\%03o", (unsigned char)c);
            }
            break;
    }
}


