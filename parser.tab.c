/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "parser.y" /* yacc.c:339  */

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


#line 87 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENT = 258,
    CHARLIT = 259,
    STRING = 260,
    NUMBER = 261,
    INDSEL = 262,
    PLUSPLUS = 263,
    MINUSMINUS = 264,
    SHL = 265,
    SHR = 266,
    LTEQ = 267,
    GTEQ = 268,
    EQEQ = 269,
    NOTEQ = 270,
    LOGAND = 271,
    LOGOR = 272,
    ELLIPSIS = 273,
    TIMESEQ = 274,
    DIVEQ = 275,
    MODEQ = 276,
    PLUSEQ = 277,
    MINUSEQ = 278,
    SHLEQ = 279,
    SHREQ = 280,
    ANDEQ = 281,
    OREQ = 282,
    XOREQ = 283,
    AUTO = 284,
    BREAK = 285,
    CASE = 286,
    CHAR = 287,
    CONST = 288,
    CONTINUE = 289,
    DEFAULT = 290,
    DO = 291,
    DOUBLE = 292,
    ELSE = 293,
    ENUM = 294,
    EXTERN = 295,
    FLOAT = 296,
    FOR = 297,
    GOTO = 298,
    IF = 299,
    INLINE = 300,
    INT = 301,
    LONG = 302,
    REGISTER = 303,
    RESTRICT = 304,
    RETURN = 305,
    SHORT = 306,
    SIGNED = 307,
    SIZEOF = 308,
    STATIC = 309,
    STRUCT = 310,
    SWITCH = 311,
    TYPEDEF = 312,
    UNION = 313,
    UNSIGNED = 314,
    VOID = 315,
    VOLATILE = 316,
    WHILE = 317,
    _BOOL = 318,
    _COMPLEX = 319,
    _IMAGINARY = 320,
    THEN = 321
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 24 "parser.y" /* yacc.c:355  */

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

#line 214 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 231 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  64
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   951

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  105
/* YYNRULES -- Number of rules.  */
#define YYNRULES  254
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  356

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,     2,     2,    84,    82,     2,
      70,    71,    74,    79,    72,    78,    77,    83,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    90,    69,
      85,    73,    86,    89,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    75,     2,    76,    88,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,    87,    68,    81,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    86,    86,    87,    90,    91,    94,    97,    98,    99,
     131,   135,   138,   142,   143,   146,   147,   150,   151,   157,
     157,   170,   171,   172,   173,   174,   175,   176,   177,   180,
     182,   182,   204,   207,   211,   217,   218,   219,   222,   227,
     232,   235,   236,   239,   240,   241,   242,   243,   244,   245,
     246,   249,   253,   257,   260,   264,   267,   276,   277,   280,
     284,   287,   313,   314,   315,   316,   317,   320,   321,   324,
     325,   328,   329,   332,   333,   336,   337,   338,   339,   342,
     351,   358,   362,   366,   370,   375,   379,   384,   385,   386,
     389,   391,   392,   403,   408,   414,   418,   423,   427,   434,
     435,   438,   441,   442,   443,   452,   453,   456,   458,   462,
     469,   470,   471,   474,   475,   478,   479,   482,   485,   486,
     489,   497,   500,   501,   502,   505,   509,   513,   516,   519,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   536,   537,   538,   539,   540,   541,
     542,   543,   546,   547,   548,   551,   555,   559,   563,   566,
     569,   574,   579,   585,   589,   600,   601,   604,   606,   607,
     608,   609,   610,   613,   621,   622,   625,   633,   642,   663,
     664,   668,   673,   674,   677,   682,   683,   684,   685,   688,
     689,   695,   699,   705,   710,   711,   712,   713,   714,   715,
     718,   727,   728,   729,   732,   733,   739,   740,   743,   744,
     750,   751,   754,   755,   761,   762,   763,   764,   766,   767,
     773,   774,   777,   778,   784,   785,   791,   792,   798,   799,
     805,   806,   812,   813,   819,   820,   830,   831,   832,   833,
     834,   835,   836,   837,   838,   839,   842,   843,   848,   857,
     858,   864,   866,   871,   876
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "CHARLIT", "STRING", "NUMBER",
  "INDSEL", "PLUSPLUS", "MINUSMINUS", "SHL", "SHR", "LTEQ", "GTEQ", "EQEQ",
  "NOTEQ", "LOGAND", "LOGOR", "ELLIPSIS", "TIMESEQ", "DIVEQ", "MODEQ",
  "PLUSEQ", "MINUSEQ", "SHLEQ", "SHREQ", "ANDEQ", "OREQ", "XOREQ", "AUTO",
  "BREAK", "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE",
  "ELSE", "ENUM", "EXTERN", "FLOAT", "FOR", "GOTO", "IF", "INLINE", "INT",
  "LONG", "REGISTER", "RESTRICT", "RETURN", "SHORT", "SIGNED", "SIZEOF",
  "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "UNION", "UNSIGNED", "VOID",
  "VOLATILE", "WHILE", "_BOOL", "_COMPLEX", "_IMAGINARY", "THEN", "'{'",
  "'}'", "';'", "'('", "')'", "','", "'='", "'*'", "'['", "']'", "'.'",
  "'-'", "'+'", "'!'", "'~'", "'&'", "'/'", "'%'", "'<'", "'>'", "'|'",
  "'^'", "'?'", "':'", "$accept", "translation_unit", "top_level_decl",
  "function_def", "function_def_specifier", "block_item",
  "declaration_list", "block_item_list_opt", "block_item_list",
  "fn_compound_statement", "$@1", "statement", "expression_statement",
  "compound_statement", "$@2", "conditional_statement", "if_statement",
  "iter_statement", "while_statement", "do_statement", "for_statement",
  "initial_clause", "for_expressions", "break_statement",
  "continue_statement", "return_statement", "null_statement",
  "declaration", "declaration_specifiers_opt", "declaration_specifiers",
  "storage_class_specifier", "init_declarator_list_opt",
  "init_declarator_list", "initialized_declarator", "declarator",
  "direct_declarator", "simple_declarator", "ptr_declarator", "pointer",
  "type_qualifier_list", "type_qualifier", "parameter_type_list",
  "parameter_list", "parameter_decl", "function_declarator",
  "array_declarator", "abstract_declarator_opt", "type_name",
  "abstract_declarator", "direct_abstract_declarator_opt",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "designation_opt", "designation", "designator_list", "designator",
  "constant_expr", "type_specifier", "int_type_specifier",
  "signed_type_specifier", "unsigned_type_specifier",
  "char_type_specifier", "bool_type_specifier", "float_type_specifier",
  "cmplx_type_specifier", "void_type_specifier", "primary_expr",
  "parenth_expr", "postfix_expr", "subscript_expr", "component_selec_expr",
  "direct_comp_selec", "indirect_comp_selec", "func_call", "expr_list",
  "prepost_pm_op", "postincdec_expr", "unary_expr", "cast_expr",
  "sizeof_expr", "unary_op_expr", "unary_op", "preincdec_expr", "mult_op",
  "mult_expr", "add_op", "add_expr", "shift_op", "shift_expr", "relate_op",
  "relate_expr", "eq_op", "eq_expr", "bit_or_expr", "bit_xor_expr",
  "bit_and_expr", "logical_or_expr", "logical_and_expr", "cond_expr",
  "assign_op", "assign_expr", "comma_expr", "expr", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   123,   125,    59,
      40,    41,    44,    61,    42,    91,    93,    46,    45,    43,
      33,   126,    38,    47,    37,    60,    62,   124,    94,    63,
      58
};
# endif

#define YYPACT_NINF -253

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-253)))

#define YYTABLE_NINF -107

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     783,  -253,  -253,  -253,  -253,    -9,  -253,    11,  -253,    14,
    -253,  -253,    31,    18,  -253,  -253,   103,  -253,  -253,  -253,
       4,   -15,   748,  -253,  -253,    56,  -253,     4,   888,   888,
     -38,  -253,  -253,    12,   888,  -253,  -253,   888,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,    54,  -253,
      86,  -253,  -253,  -253,    65,    91,  -253,  -253,    75,    98,
     -19,  -253,   -15,  -253,  -253,  -253,  -253,  -253,    78,    79,
    -253,   818,  -253,  -253,   888,  -253,     4,   855,    20,   -38,
    -253,  -253,  -253,  -253,  -253,   111,  -253,  -253,   116,  -253,
    -253,  -253,  -253,   232,  -253,     4,    99,   888,  -253,    97,
    -253,    40,    93,   104,  -253,    95,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,   106,   113,   455,   114,   117,
     334,   638,   118,  -253,  -253,   392,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,   115,   232,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,    49,  -253,  -253,  -253,  -253,  -253,   680,  -253,   223,
    -253,  -253,  -253,   693,  -253,   -12,    51,   145,     7,   153,
     102,   105,   108,     6,   170,  -253,  -253,   119,   123,  -253,
    -253,   120,  -253,  -253,    46,  -253,    19,  -253,  -253,   121,
     124,  -253,   888,  -253,  -253,  -253,   139,   312,   455,   693,
    -253,   133,   392,  -253,   693,   232,    -7,   135,   136,  -253,
    -253,   205,   693,   693,   206,  -253,   693,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,   693,   693,
    -253,  -253,  -253,  -253,  -253,   693,  -253,  -253,   693,  -253,
    -253,   693,  -253,  -253,  -253,  -253,   693,  -253,  -253,   693,
     693,   693,   693,   693,   693,   693,   693,  -253,   693,   -43,
      99,  -253,   -42,  -253,   140,   124,    22,  -253,   142,   414,
     141,  -253,  -253,  -253,   143,  -253,   148,   149,   154,   -26,
     -35,  -253,   693,  -253,  -253,    88,  -253,   147,  -253,  -253,
    -253,  -253,   -12,    51,   145,     7,   105,   108,   153,   170,
     126,   102,  -253,   150,  -253,  -253,   -54,  -253,  -253,  -253,
    -253,   151,  -253,   693,   473,   152,   506,   455,  -253,   455,
    -253,  -253,  -253,   693,  -253,   693,  -253,  -253,    99,  -253,
     158,  -253,   159,   557,   587,   155,   187,  -253,  -253,  -253,
    -253,   163,  -253,  -253,   168,  -253,   181,   600,   455,  -253,
    -253,  -253,  -253,   182,  -253,  -253
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    79,    62,   152,    87,   157,    63,   156,   133,   136,
      64,    89,   129,   134,    65,    66,   146,   163,    88,   155,
       0,    81,     0,     2,     5,     0,     4,    67,    57,     7,
      74,    75,    73,     0,    57,    77,    78,    57,   123,   125,
     126,   127,   128,   122,   159,   124,   161,   160,   158,   137,
     140,   130,   153,   135,   138,   131,   154,   147,   148,   144,
       0,    83,    82,    85,     1,     3,    19,     6,     0,    68,
      69,    71,    59,    58,     8,    13,    67,     0,     0,    80,
      61,    60,   162,   141,   139,   142,   132,   149,   150,   145,
      76,    84,    86,    15,    56,     0,     0,    10,    14,    71,
      96,    99,     0,    90,    91,     0,    97,   143,   151,   164,
     254,   253,   252,   182,   183,     0,     0,     0,     0,     0,
       0,     0,     0,    30,    55,     0,   199,   194,   195,   196,
     197,   198,    17,     0,    16,    12,    21,    22,    23,    32,
      24,    35,    36,    37,    25,    26,    27,    28,    11,   168,
     166,   185,   169,   170,   174,   175,   171,     0,   172,   189,
     204,   186,   187,     0,   188,   208,   212,   218,   222,   228,
     232,   224,   226,   234,   230,   246,   249,   251,     0,   165,
      70,   115,    72,   110,   105,    93,   102,    94,   100,     0,
     103,    95,     0,    98,    51,    52,     0,     0,     0,     0,
      53,     0,     0,   191,     0,    15,    99,     0,     0,    20,
      18,     0,   179,     0,     0,   184,     0,   200,   238,   239,
     240,   236,   237,   241,   242,   243,   245,   244,     0,     0,
     189,   193,   201,   202,   203,     0,   207,   206,     0,   210,
     211,     0,   215,   217,   214,   216,     0,   220,   221,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
       0,   116,     0,   118,     0,   104,     0,    92,     0,     0,
       0,    42,    41,    40,     0,    54,     0,     0,     0,   105,
     102,   101,     0,   167,   177,     0,   180,     0,   176,   247,
     248,   205,   209,   213,   219,   223,   225,   227,   229,   231,
       0,   233,   250,     0,   121,   111,   115,   113,   117,   119,
     107,     0,   108,     0,     0,     0,     0,     0,   192,     0,
      31,   190,   178,     0,   173,     0,   120,   112,     0,   109,
       0,    43,     0,     0,     0,     0,    33,    38,   181,   235,
     114,     0,    47,    45,     0,    44,     0,     0,     0,    39,
      46,    50,    48,     0,    34,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -253,  -253,   233,  -253,  -253,   122,   183,    52,  -253,  -253,
    -253,  -114,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,    16,    36,     2,
    -253,  -253,  -253,   164,   -10,   -28,  -253,  -253,   -21,  -253,
      -8,  -253,  -253,    68,  -253,  -253,    57,    69,  -178,  -253,
    -174,  -252,  -253,   -39,  -253,  -253,     8,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,   137,  -253,  -110,  -136,
    -253,  -253,  -253,  -253,  -253,    37,  -253,    59,  -253,    41,
    -253,    28,  -253,    38,    42,    48,    53,  -253,    50,  -216,
    -253,   -95,  -253,  -116,  -253
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    22,    23,    24,    25,   132,    74,   133,   134,    67,
      93,   135,   136,   137,   205,   138,   139,   140,   141,   142,
     143,   270,   198,   144,   145,   146,   147,   148,    72,    76,
      28,    68,    69,    70,    29,    30,    31,    32,    33,    62,
      34,   102,   103,   104,    35,    36,   187,   207,   188,   189,
     190,   182,   259,   260,   261,   262,   263,   303,    37,    38,
      39,    40,    41,    42,    43,    44,    45,   149,   150,   151,
     152,   153,   154,   155,   156,   285,   157,   158,   159,   160,
     161,   162,   163,   164,   235,   165,   238,   166,   241,   167,
     246,   168,   249,   169,   170,   171,   172,   173,   174,   175,
     229,   176,   177,   178,   179
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,   183,    27,   196,   201,    79,   264,     1,   307,   208,
      60,   203,   265,    63,   327,     1,    26,    71,     4,   242,
     243,   258,     1,   253,    27,   305,   105,   231,   311,   306,
      73,   308,    77,   258,    11,   279,    73,    78,    26,    73,
    -105,    91,   304,     1,   279,    75,    18,   217,    21,     1,
      52,    48,    90,   230,    92,    46,   211,   113,   114,    21,
      49,    50,   232,   279,    53,    54,    99,    21,  -105,    55,
      80,   233,   234,    81,    20,    47,   340,    51,    21,   101,
     186,   272,    20,   274,   273,    99,   208,    75,   277,   184,
      98,   185,   244,   245,  -105,   254,   106,   287,   312,   291,
     208,   264,   109,   110,   111,   112,   265,   113,   114,   339,
     184,    84,    85,    98,    21,  -105,   184,   286,    82,   212,
      21,    87,    88,    66,   213,   230,   214,   206,   230,   236,
     237,   230,    83,   289,   290,    56,   230,    86,   300,   230,
     230,   230,   230,   230,    89,   230,   321,    94,   230,    57,
      58,    95,   121,   315,    59,   239,   240,   107,    79,   322,
     323,   302,   108,   186,   191,   183,   181,   247,   248,   125,
      96,   193,   230,   126,    60,   194,   192,   127,   128,   129,
     130,   131,   195,   209,   197,   280,   255,   199,   204,   250,
     252,   256,   257,   251,   101,   258,   266,   330,   332,  -106,
     335,   268,   275,   336,   206,   337,   282,   283,   284,   288,
     316,   310,   313,   271,   317,   230,   325,   344,   346,   318,
     319,   333,   320,   324,   347,   348,   326,   329,   338,   341,
     342,   353,   349,   183,   354,   109,   110,   111,   112,   350,
     113,   114,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   351,   355,    97,    65,   210,   278,   280,   180,
     267,     2,   115,   281,     3,     4,   116,   328,   117,     5,
     309,   276,     6,     7,   118,   292,   119,   295,     8,     9,
      10,    11,   120,    12,    13,   121,    14,   294,   215,    15,
     298,    16,    17,    18,   122,    19,   228,   301,   296,   123,
     293,   124,   125,   299,   297,     0,   126,     0,     0,     0,
     127,   128,   129,   130,   131,   109,   110,   111,   112,     0,
     113,   114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   109,   110,   111,
     112,     2,   113,   114,     3,     4,     0,     0,     0,     5,
       0,     0,     6,     7,     0,     0,     0,     0,     8,     9,
      10,    11,     0,    12,    13,   121,    14,     0,     0,    15,
       0,    16,    17,    18,     0,    19,     0,     0,     0,     0,
       0,   269,   125,     0,     0,     0,   126,   121,     0,     0,
     127,   128,   129,   130,   131,   109,   110,   111,   112,     0,
     113,   114,     0,   200,   125,     0,     0,     0,   126,     0,
       0,     0,   127,   128,   129,   130,   131,   109,   110,   111,
     112,     2,   113,   114,     3,     4,     0,     0,     0,     5,
       0,     0,     6,     7,     0,     0,     0,     0,     8,     9,
      10,    11,     0,    12,    13,   121,    14,     0,     0,    15,
       0,    16,    17,    18,     0,    19,     0,     0,   109,   110,
     111,   112,   125,   113,   114,     0,   126,   121,     0,     0,
     127,   128,   129,   130,   131,     0,   109,   110,   111,   112,
       0,   113,   114,   314,   125,   115,     0,     0,   126,   116,
       0,   117,   127,   128,   129,   130,   131,   118,     0,   119,
       0,     0,     0,     0,     0,   120,     0,     0,   121,   109,
     110,   111,   112,     0,   113,   114,     0,   122,     0,     0,
       0,     0,   123,     0,   124,   125,   121,     0,     0,   126,
       0,     0,     0,   127,   128,   129,   130,   131,     0,     0,
       0,     0,     0,   125,   331,     0,     0,   126,     0,     0,
       0,   127,   128,   129,   130,   131,     0,     0,     0,   121,
     109,   110,   111,   112,     0,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,   334,   125,     0,     0,     0,
     126,     0,     0,     0,   127,   128,   129,   130,   131,     0,
     109,   110,   111,   112,     0,   113,   114,     0,     0,     0,
       0,     0,     0,   109,   110,   111,   112,     0,   113,   114,
     121,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   125,   343,     0,
       0,   126,     0,     0,     0,   127,   128,   129,   130,   131,
     121,   109,   110,   111,   112,     0,   113,   114,     0,     0,
       0,     0,     0,   121,     0,     0,     0,   125,   345,     0,
       0,   126,     0,     0,     0,   127,   128,   129,   130,   131,
     125,   352,     0,     0,   126,     0,     0,     0,   127,   128,
     129,   130,   131,   109,   110,   111,   112,     0,   113,   114,
       0,   121,     0,     0,     0,     0,   109,   110,   111,   112,
       0,   113,   114,     0,     0,     0,     0,     0,   202,     0,
       0,     0,   126,     0,     0,     0,   127,   128,   129,   130,
     131,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,     0,    64,     0,
     216,     1,     0,     0,   126,     0,     0,     0,   127,   128,
     129,   130,   131,   125,     0,     0,     0,   126,     0,     0,
       0,   127,   128,   129,   130,   131,     0,     2,     0,     0,
       3,     4,     0,     0,     0,     5,     1,     0,     6,     7,
       0,     0,     0,     0,     8,     9,    10,    11,     0,    12,
      13,     0,    14,     0,     0,    15,     0,    16,    17,    18,
       0,    19,     2,     0,     0,     3,     4,     0,    20,     0,
       5,     0,    21,     6,     7,     0,     0,     0,     0,     8,
       9,    10,    11,     0,    12,    13,     0,    14,     0,     0,
      15,     0,    16,    17,    18,     0,    19,     2,     0,     0,
       3,     4,     0,    20,     0,     5,     0,    21,     6,     7,
       0,     0,     0,     0,     8,     9,    10,    11,     0,    12,
      13,     0,    14,     0,     0,    15,     0,    16,    17,    18,
       0,    19,     0,     0,     2,    -9,     0,     3,     4,     0,
       0,    96,     5,     0,     0,     6,     7,     0,     0,     0,
       0,     8,     9,    10,    11,     0,    12,    13,     0,    14,
       0,     0,    15,     0,    16,    17,    18,     2,    19,     0,
       3,     4,     0,     0,     0,     5,   100,     0,     6,     7,
       0,     0,     0,     0,     8,     9,    10,    11,     0,    12,
      13,     0,    14,     0,     0,    15,     0,    16,    17,    18,
       0,    19
};

static const yytype_int16 yycheck[] =
{
      21,    96,     0,   117,   120,    33,   184,     3,   260,   125,
      20,   121,   186,    21,    68,     3,     0,    27,    33,    12,
      13,    75,     3,    17,    22,    68,     6,   163,     6,    72,
      28,    73,    70,    75,    49,    70,    34,    75,    22,    37,
      75,    62,   258,     3,    70,    29,    61,   157,    74,     3,
      32,    37,    71,   163,    62,    64,     7,     8,     9,    74,
      46,    47,    74,    70,    46,    47,    76,    74,    75,    51,
      34,    83,    84,    37,    70,    64,   328,    46,    74,    77,
     101,   197,    70,   199,   198,    95,   202,    71,   204,    70,
      74,   101,    85,    86,    75,    89,    76,   213,    76,   235,
     216,   279,     3,     4,     5,     6,   280,     8,     9,   325,
      70,    46,    47,    97,    74,    75,    70,   212,    64,    70,
      74,    46,    47,    67,    75,   235,    77,   125,   238,    78,
      79,   241,    46,   228,   229,    32,   246,    46,   254,   249,
     250,   251,   252,   253,    46,   255,   282,    69,   258,    46,
      47,    72,    53,   269,    51,    10,    11,    46,   186,    71,
      72,   256,    46,   184,    71,   260,    67,    14,    15,    70,
      73,    76,   282,    74,   184,    69,    72,    78,    79,    80,
      81,    82,    69,    68,    70,   206,    16,    70,    70,    87,
      82,    72,    69,    88,   192,    75,    75,   313,   314,    75,
     316,    62,    69,   317,   202,   319,    71,    71,     3,     3,
      69,    71,    70,   197,    71,   325,    90,   333,   334,    71,
      71,    69,    68,    76,    69,    38,    76,    76,   323,    71,
      71,   347,    69,   328,   348,     3,     4,     5,     6,    71,
       8,     9,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    71,    71,    71,    22,   134,   205,   279,    95,
     192,    29,    30,   206,    32,    33,    34,   306,    36,    37,
     262,   202,    40,    41,    42,   238,    44,   249,    46,    47,
      48,    49,    50,    51,    52,    53,    54,   246,   151,    57,
     252,    59,    60,    61,    62,    63,    73,   255,   250,    67,
     241,    69,    70,   253,   251,    -1,    74,    -1,    -1,    -1,
      78,    79,    80,    81,    82,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    29,     8,     9,    32,    33,    -1,    -1,    -1,    37,
      -1,    -1,    40,    41,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    -1,    -1,    57,
      -1,    59,    60,    61,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    69,    70,    -1,    -1,    -1,    74,    53,    -1,    -1,
      78,    79,    80,    81,    82,     3,     4,     5,     6,    -1,
       8,     9,    -1,    69,    70,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    78,    79,    80,    81,    82,     3,     4,     5,
       6,    29,     8,     9,    32,    33,    -1,    -1,    -1,    37,
      -1,    -1,    40,    41,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    -1,    -1,    57,
      -1,    59,    60,    61,    -1,    63,    -1,    -1,     3,     4,
       5,     6,    70,     8,     9,    -1,    74,    53,    -1,    -1,
      78,    79,    80,    81,    82,    -1,     3,     4,     5,     6,
      -1,     8,     9,    69,    70,    30,    -1,    -1,    74,    34,
      -1,    36,    78,    79,    80,    81,    82,    42,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    53,     3,
       4,     5,     6,    -1,     8,     9,    -1,    62,    -1,    -1,
      -1,    -1,    67,    -1,    69,    70,    53,    -1,    -1,    74,
      -1,    -1,    -1,    78,    79,    80,    81,    82,    -1,    -1,
      -1,    -1,    -1,    70,    71,    -1,    -1,    74,    -1,    -1,
      -1,    78,    79,    80,    81,    82,    -1,    -1,    -1,    53,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    70,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    78,    79,    80,    81,    82,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    -1,
      -1,    74,    -1,    -1,    -1,    78,    79,    80,    81,    82,
      53,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    70,    71,    -1,
      -1,    74,    -1,    -1,    -1,    78,    79,    80,    81,    82,
      70,    71,    -1,    -1,    74,    -1,    -1,    -1,    78,    79,
      80,    81,    82,     3,     4,     5,     6,    -1,     8,     9,
      -1,    53,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    78,    79,    80,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,     0,    -1,
      70,     3,    -1,    -1,    74,    -1,    -1,    -1,    78,    79,
      80,    81,    82,    70,    -1,    -1,    -1,    74,    -1,    -1,
      -1,    78,    79,    80,    81,    82,    -1,    29,    -1,    -1,
      32,    33,    -1,    -1,    -1,    37,     3,    -1,    40,    41,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    -1,    51,
      52,    -1,    54,    -1,    -1,    57,    -1,    59,    60,    61,
      -1,    63,    29,    -1,    -1,    32,    33,    -1,    70,    -1,
      37,    -1,    74,    40,    41,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    -1,    51,    52,    -1,    54,    -1,    -1,
      57,    -1,    59,    60,    61,    -1,    63,    29,    -1,    -1,
      32,    33,    -1,    70,    -1,    37,    -1,    74,    40,    41,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    -1,    51,
      52,    -1,    54,    -1,    -1,    57,    -1,    59,    60,    61,
      -1,    63,    -1,    -1,    29,    67,    -1,    32,    33,    -1,
      -1,    73,    37,    -1,    -1,    40,    41,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    -1,    51,    52,    -1,    54,
      -1,    -1,    57,    -1,    59,    60,    61,    29,    63,    -1,
      32,    33,    -1,    -1,    -1,    37,    71,    -1,    40,    41,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    -1,    51,
      52,    -1,    54,    -1,    -1,    57,    -1,    59,    60,    61,
      -1,    63
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    29,    32,    33,    37,    40,    41,    46,    47,
      48,    49,    51,    52,    54,    57,    59,    60,    61,    63,
      70,    74,    92,    93,    94,    95,   118,   120,   121,   125,
     126,   127,   128,   129,   131,   135,   136,   149,   150,   151,
     152,   153,   154,   155,   156,   157,    64,    64,    37,    46,
      47,    46,    32,    46,    47,    51,    32,    46,    47,    51,
     125,   129,   130,   131,     0,    93,    67,   100,   122,   123,
     124,   125,   119,   120,    97,   118,   120,    70,    75,   126,
     119,   119,    64,    46,    46,    47,    46,    46,    47,    46,
      71,   129,   131,   101,    69,    72,    73,    97,   118,   125,
      71,   120,   132,   133,   134,     6,    76,    46,    46,     3,
       4,     5,     6,     8,     9,    30,    34,    36,    42,    44,
      50,    53,    62,    67,    69,    70,    74,    78,    79,    80,
      81,    82,    96,    98,    99,   102,   103,   104,   106,   107,
     108,   109,   110,   111,   114,   115,   116,   117,   118,   158,
     159,   160,   161,   162,   163,   164,   165,   167,   168,   169,
     170,   171,   172,   173,   174,   176,   178,   180,   182,   184,
     185,   186,   187,   188,   189,   190,   192,   193,   194,   195,
     124,    67,   142,   192,    70,   125,   129,   137,   139,   140,
     141,    71,    72,    76,    69,    69,   102,    70,   113,    70,
      69,   194,    70,   169,    70,   105,   120,   138,   194,    68,
      96,     7,    70,    75,    77,   167,    70,   169,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    73,   191,
     169,   170,    74,    83,    84,   175,    78,    79,   177,    10,
      11,   179,    12,    13,    85,    86,   181,    14,    15,   183,
      87,    88,    82,    17,    89,    16,    72,    69,    75,   143,
     144,   145,   146,   147,   139,   141,    75,   134,    62,    69,
     112,   118,   194,   102,   194,    69,   138,   194,    98,    70,
     129,   137,    71,    71,     3,   166,   192,   194,     3,   192,
     192,   170,   176,   178,   180,   182,   186,   187,   184,   189,
     194,   185,   192,   148,   190,    68,    72,   142,    73,   147,
      71,     6,    76,    70,    69,   194,    69,    71,    71,    71,
      68,   170,    71,    72,    76,    90,    76,    68,   144,    76,
     194,    71,   194,    69,    69,   194,   102,   102,   192,   190,
     142,    71,    71,    71,   194,    71,   194,    69,    38,    69,
      71,    71,    71,   194,   102,    71
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    93,    93,    94,    95,    95,    95,
      95,    96,    96,    97,    97,    98,    98,    99,    99,   101,
     100,   102,   102,   102,   102,   102,   102,   102,   102,   103,
     105,   104,   106,   107,   107,   108,   108,   108,   109,   110,
     111,   112,   112,   113,   113,   113,   113,   113,   113,   113,
     113,   114,   115,   116,   116,   117,   118,   119,   119,   120,
     120,   120,   121,   121,   121,   121,   121,   122,   122,   123,
     123,   124,   124,   125,   125,   126,   126,   126,   126,   127,
     128,   129,   129,   129,   129,   130,   130,   131,   131,   131,
     132,   133,   133,   134,   134,   135,   135,   136,   136,   137,
     137,   138,   139,   139,   139,   140,   140,   141,   141,   141,
     142,   142,   142,   143,   143,   144,   144,   145,   146,   146,
     147,   148,   149,   149,   149,   150,   150,   150,   150,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   152,   152,   152,   152,   152,   152,
     152,   152,   153,   153,   153,   154,   155,   155,   155,   155,
     156,   156,   156,   157,   158,   158,   158,   159,   160,   160,
     160,   160,   160,   161,   162,   162,   163,   164,   165,   166,
     166,   166,   167,   167,   168,   169,   169,   169,   169,   170,
     170,   171,   171,   172,   173,   173,   173,   173,   173,   173,
     174,   175,   175,   175,   176,   176,   177,   177,   178,   178,
     179,   179,   180,   180,   181,   181,   181,   181,   182,   182,
     183,   183,   184,   184,   185,   185,   186,   186,   187,   187,
     188,   188,   189,   189,   190,   190,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   192,   192,   192,   193,
     193,   194,   195,   195,   195
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     2,     2,
       3,     1,     1,     1,     2,     0,     1,     1,     2,     0,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       0,     4,     1,     5,     7,     1,     1,     1,     5,     7,
       3,     1,     1,     4,     5,     5,     6,     5,     6,     7,
       6,     2,     2,     2,     3,     1,     3,     0,     1,     2,
       2,     2,     1,     1,     1,     1,     1,     0,     1,     1,
       3,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       2,     1,     2,     2,     3,     1,     2,     1,     1,     1,
       1,     1,     3,     2,     2,     4,     3,     3,     4,     0,
       1,     2,     1,     1,     2,     0,     1,     3,     3,     4,
       1,     3,     4,     2,     4,     0,     1,     2,     1,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     1,     1,     2,     1,     2,     2,     3,
       2,     3,     3,     4,     2,     3,     1,     2,     2,     3,
       3,     4,     1,     2,     2,     1,     1,     1,     2,     1,
       2,     2,     3,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     4,     1,     1,     3,     3,     4,     0,
       1,     3,     1,     1,     2,     1,     1,     1,     1,     1,
       4,     2,     4,     2,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     1,
       3,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 9:
#line 99 "parser.y" /* yacc.c:1646  */
    {struct sym_attr attr;
                                                                     append_ast(&(yyvsp[-1].ast), &(yyvsp[0].ast));
                                                                     ast_reverse(&(yyvsp[-1].ast));
                                                                     int line_num = (yyvsp[-1].ast)->ident.line_no;
                                                                     char *name = (yyvsp[-1].ast)->ident.name, *filename = (yyvsp[-1].ast)->ident.filename; 
                                                                     struct astnode *type = (yyvsp[-1].ast)->ident.next, *desig_node = get_symType(type);
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
#line 1771 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 135 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ITEM);
                         (yyval.ast)->item.decl_or_stmt = (yyvsp[0].ast);}
#line 1778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 138 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ITEM);
                         (yyval.ast)->item.decl_or_stmt = (yyvsp[0].ast);}
#line 1785 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 146 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = NULL;}
#line 1791 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 151 "parser.y" /* yacc.c:1646  */
    {struct astnode *temp = (yyvsp[-1].ast);
                                                 while(temp->item.next)
                                                     temp = temp->item.next;
                                                 temp->item.next = (yyvsp[0].ast);}
#line 1800 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 157 "parser.y" /* yacc.c:1646  */
    {if(curr_stack->scope != FUNC) stack_push(&curr_stack, FUNC);}
#line 1806 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 157 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_CMPD);
                                                                                                                    (yyval.ast)->cmpd_stmt.item_list = (yyvsp[-1].ast);
                                                                                                                    if(curr_entry)
                                                                                                                    {
                                                                                                                        curr_entry->s_attr.s_func.body = (yyval.ast);
                                                                                                                        curr_entry->s_attr.s_func.fn_table = curr_stack->head; //capture symbol table for function
                                                                                                                    }
                                                                                                                    IR_gen(outfile, curr_stack, (yyvsp[-1].ast));
                                                                                                                    debug("DONE WITH IR GEN", line_tick);
                                                                                                                    curr_stack = stack_pop(&curr_stack);}
#line 1821 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 182 "parser.y" /* yacc.c:1646  */
    {stack_push(&curr_stack, BLOCK);}
#line 1827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 182 "parser.y" /* yacc.c:1646  */
    {struct sym_attr block_table;
                                                                                   block_table.sym_type = SYM_BLOCK;
                                                                                   block_table.s_block.block_ent = curr_stack->head;
                                                                                   int decl_bool = 0;
                                                                                   struct astnode *temp = (yyvsp[-1].ast);
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
                                                                                   (yyval.ast) = astnode_lloc(AST_CMPD);
                                                                                   (yyval.ast)->cmpd_stmt.item_list = (yyvsp[-1].ast);
                                                                                   curr_stack = stack_pop(&curr_stack);}
#line 1852 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 207 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_IF);
                                                                 (yyval.ast)->if_stmt.expr = (yyvsp[-2].ast);
                                                                 (yyval.ast)->if_stmt.body = (yyvsp[0].ast);}
#line 1860 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 211 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_IF_ELSE);
                                                                 (yyval.ast)->if_else_stmt.expr = (yyvsp[-4].ast);
                                                                 (yyval.ast)->if_else_stmt.if_body = (yyvsp[-2].ast);
                                                                 (yyval.ast)->if_else_stmt.else_body = (yyvsp[0].ast);}
#line 1869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_WHILE);
                                               (yyval.ast)->while_stmt.expr = (yyvsp[-2].ast);
                                               (yyval.ast)->while_stmt.body = (yyvsp[0].ast);}
#line 1877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_DO);
                                                   (yyval.ast)->do_stmt.expr = (yyvsp[-2].ast);
                                                   (yyval.ast)->do_stmt.body = (yyvsp[-5].ast);}
#line 1885 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 232 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); (yyval.ast)->for_stmt.body = (yyvsp[0].ast);}
#line 1891 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 239 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = for_node_init(NULL, NULL, NULL);}
#line 1897 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 240 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = for_node_init(&(yyvsp[-3].ast), NULL, NULL);}
#line 1903 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 241 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = for_node_init(NULL, &(yyvsp[-2].ast), NULL);}
#line 1909 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 242 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = for_node_init(NULL, &(yyvsp[-3].ast), &(yyvsp[-1].ast));}
#line 1915 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 243 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = for_node_init(NULL, NULL, &(yyvsp[-1].ast));}
#line 1921 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 244 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = for_node_init(&(yyvsp[-4].ast), &(yyvsp[-2].ast), NULL);}
#line 1927 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 245 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = for_node_init(&(yyvsp[-5].ast), &(yyvsp[-3].ast), &(yyvsp[-1].ast));}
#line 1933 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 246 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = for_node_init(&(yyvsp[-4].ast), NULL, &(yyvsp[-1].ast));}
#line 1939 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 249 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_BREAK);
                                     (yyval.ast)->break_stmt.op = BREAK;}
#line 1946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 253 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_CONT);
                                     (yyval.ast)->cont_stmt.op = CONTINUE;}
#line 1953 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 257 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_RET);
                                     (yyval.ast)->ret_stmt.ret_expr = NULL;}
#line 1960 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 260 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_RET);
                                     (yyval.ast)->ret_stmt.ret_expr = (yyvsp[-1].ast);}
#line 1967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 264 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = NULL;}
#line 1973 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 267 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_DECL);
                                                                     append_ast(&(yyvsp[-2].ast), &(yyvsp[-1].ast)); 
                                                                     /* REVERSE AST */
                                                                     ast_reverse(&(yyvsp[-2].ast));
                                                                     (yyval.ast)->declaration.decl = (yyvsp[-2].ast); 
                                                                     install_decl(&curr_stack, &(yyvsp[-2].ast), &stgclass, &offset);
                                                                     scalar_quals = NULL, stgclass = 0;}
#line 1985 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 276 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = NULL;}
#line 1991 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 280 "parser.y" /* yacc.c:1646  */
    {if(stgclass != 0)  yyerror("More than one storage class may not be specified");
                                                                             (yyval.ast) = (yyvsp[0].ast); 
                                                                             stgclass = (yyvsp[-1].VAL._TYPE_);}
#line 1999 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 284 "parser.y" /* yacc.c:1646  */
    {(yyval.ast)->scalar.qualifier = scalar_quals;
                                                                             (yyval.ast)->scalar.next = (yyvsp[0].ast);}
#line 2006 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 287 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_QUAL);
                                                                             if((yyvsp[-1].VAL._TYPE_) == RESTRICT)
                                                                             {
                                                                                 yyerror("[Error] \'restrict\' qualifier not permitted for non-pointers");
                                                                                 (yyval.ast) = NULL; 
                                                                             }
                                                                             else 
                                                                             {
                                                                                (yyval.ast)->qualif.qual = (yyvsp[-1].VAL._TYPE_);
                                                                                (yyval.ast)->qualif.next = NULL;
                                                                             }
                                                                             struct astnode *temp = scalar_quals;
                                                                             if(!scalar_quals)     scalar_quals = (yyval.ast);  
                                                                             else
                                                                             {                             
                                                                                while(temp->qualif.next)   temp = temp->qualif.next;
                                                                                temp->qualif.next = (yyval.ast);
                                                                                temp = temp->qualif.next;
                                                                             }
                                                                             if(!(yyval.ast) && (yyvsp[0].ast) && (yyvsp[0].ast)->nodetype == AST_QUAL)     
                                                                                temp->qualif.next = (yyvsp[0].ast);
                                                                             else if((yyval.ast) && (yyvsp[0].ast) && (yyvsp[0].ast)->nodetype == AST_SCALAR)
                                                                                 (yyvsp[0].ast)->scalar.qualifier = scalar_quals;
                                                                             (yyval.ast) = (yyvsp[0].ast);}
#line 2035 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 313 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = AUTO_CLASS;}
#line 2041 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 314 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = EXTERN_CLASS;}
#line 2047 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 315 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = REGISTER_CLASS;}
#line 2053 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 316 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = STATIC_CLASS;}
#line 2059 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 317 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = TYPEDEF_CLASS;}
#line 2065 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 320 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = NULL;}
#line 2071 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 337 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast);}
#line 2077 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 342 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_IDENT);
                             memset((yyval.ast)->ident.name, '0', 4096);
                             memset((yyval.ast)->ident.filename, '0', 4096);
                             memcpy((yyval.ast)->ident.name, yylval.STR._STR_, sizeof(yylval.STR._STR_));
                             memcpy((yyval.ast)->ident.filename, filename, sizeof(yylval.STR._STR_));
                             (yyval.ast)->ident.line_no = line_tick; 
                             (yyval.ast)->ident.next = NULL;}
#line 2089 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 351 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast);
                                             struct astnode *temp = (yyvsp[-1].ast); 
                                             while(temp->ptr.next != NULL)    temp = temp->ptr.next;
                                             temp->ptr.next = (yyvsp[0].ast); //set tail of ptr list to decl
                                            }
#line 2099 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 358 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_PTR);
                                             (yyval.ast)->ptr.qual_l = NULL;
                                             (yyval.ast)->ptr.next = NULL;}
#line 2107 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 362 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_PTR);
                                             (yyval.ast)->ptr.qual_l = (yyvsp[0].ast);
                                             (yyval.ast)->ptr.next = NULL;}
#line 2115 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 366 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_PTR);
                                             (yyval.ast)->ptr.qual_l = NULL;
                                             (yyval.ast)->ptr.next = (yyvsp[0].ast);}
#line 2123 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 370 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_PTR);
                                             (yyval.ast)->ptr.qual_l = (yyvsp[-1].ast);
                                             (yyval.ast)->ptr.next = (yyvsp[0].ast);}
#line 2131 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 375 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_QUAL);
                                                             (yyval.ast)->qualif.qual = (yyvsp[0].VAL._TYPE_);
                                                             (yyval.ast)->qualif.next = NULL;}
#line 2139 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 379 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_QUAL);
                                                             (yyval.ast)->qualif.qual = (yyvsp[0].VAL._TYPE_);
                                                             (yyval.ast)->qualif.next = (yyvsp[-1].ast);}
#line 2147 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 384 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = CONST;}
#line 2153 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 385 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = VOLATILE;}
#line 2159 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 386 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = RESTRICT;}
#line 2165 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 392 "parser.y" /* yacc.c:1646  */
    {struct astnode *temp = (yyvsp[-2].ast); 
                                                     while(temp->declaration.next)    
                                                        temp = temp->declaration.next;
                                                     temp->declaration.next = (yyvsp[0].ast);}
#line 2174 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 403 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_DECL);
                                                                 append_ast(&(yyvsp[-1].ast), &(yyvsp[0].ast)); 
                                                                 ast_reverse(&(yyvsp[-1].ast));
                                                                 (yyval.ast)->declaration.decl = (yyvsp[-1].ast);}
#line 2183 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 408 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_DECL);
                                                                 append_ast(&(yyvsp[-1].ast), &(yyvsp[0].ast)); 
                                                                 ast_reverse(&(yyvsp[-1].ast));
                                                                 (yyval.ast)->declaration.decl = (yyvsp[-1].ast);}
#line 2192 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 414 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_FUNC);
                                                                         (yyval.ast)->func.ret_type = (yyvsp[-3].ast);
                                                                         (yyval.ast)->func.params = (yyvsp[-1].ast);}
#line 2200 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 418 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_FUNC);
                                                                         (yyval.ast)->func.ret_type = (yyvsp[-2].ast);
                                                                         (yyval.ast)->func.params = NULL;}
#line 2208 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 423 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ARRAY);
                                                (yyval.ast)->array.arr_size = 0;
                                                (yyval.ast)->array.next = (yyvsp[-2].ast);}
#line 2216 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 427 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ARRAY);
                                                       (yyval.ast)->array.arr_size = yylval.VAL._INT_;
                                                       if(yylval.VAL._TYPE_ >= D)
                                                            yyerror("[ERROR] size must be integer type");
                                                       (yyval.ast)->array.next = (yyvsp[-3].ast);}
#line 2226 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 434 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = NULL;}
#line 2232 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 438 "parser.y" /* yacc.c:1646  */
    {append_ast(&(yyvsp[-1].ast), &(yyvsp[0].ast));}
#line 2238 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 443 "parser.y" /* yacc.c:1646  */
    {if((yyvsp[-1].ast)) 
                                                         {
                                                             struct astnode *temp = (yyvsp[-1].ast); 
                                                             while(temp->ptr.next)    temp = temp->ptr.next;
                                                             temp->ptr.next = (yyvsp[0].ast); //set tail of ptr list to decl
                                                         } 
                                                         else   (yyval.ast) = (yyvsp[0].ast);}
#line 2250 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 452 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = NULL;}
#line 2256 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 456 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast);}
#line 2262 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 458 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ARRAY);
                                                                                     (yyval.ast)->array.arr_size = 0;
                                                                                     (yyval.ast)->array.next = (yyvsp[-2].ast);}
#line 2270 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 462 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ARRAY);
                                                                                     (yyval.ast)->array.arr_size = yylval.VAL._INT_;
                                                                                     if(yylval.VAL._TYPE_ >= D)
                                                                                             yyerror("[ERROR] size must be integer type");
                                                                                     (yyval.ast)->array.next = (yyvsp[-3].ast);}
#line 2280 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 470 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast);}
#line 2286 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 471 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-2].ast);}
#line 2292 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 478 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = NULL;}
#line 2298 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 489 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast);}
#line 2304 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 505 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                                                 (yyval.ast)->scalar.type = (yyvsp[0].VAL._TYPE_);
                                                 (yyval.ast)->scalar.signedness = S;}
#line 2312 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 509 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                                                 (yyval.ast)->scalar.type = (yyvsp[0].VAL._TYPE_);
                                                 (yyval.ast)->scalar.signedness = U;}
#line 2320 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 513 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                                                 (yyval.ast)->scalar.type = C;
                                                 (yyval.ast)->scalar.signedness = (yyvsp[0].VAL._TYPE_);}
#line 2328 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 519 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = SHRT;}
#line 2334 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 520 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = SHRT;}
#line 2340 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 521 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = SHRT;}
#line 2346 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 522 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = SHRT;}
#line 2352 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 523 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = I;}
#line 2358 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 524 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = I;}
#line 2364 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 525 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = I;}
#line 2370 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 526 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = L;}
#line 2376 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 527 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = L;}
#line 2382 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 528 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = L;}
#line 2388 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 529 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = L;}
#line 2394 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 530 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = LL;}
#line 2400 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 531 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = LL;}
#line 2406 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 532 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = LL;}
#line 2412 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 533 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = LL;}
#line 2418 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 536 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = SHRT;}
#line 2424 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 537 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = SHRT;}
#line 2430 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 538 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = I;}
#line 2436 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 539 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = I;}
#line 2442 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 540 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = L;}
#line 2448 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 541 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = L;}
#line 2454 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 542 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = LL;}
#line 2460 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 543 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = LL;}
#line 2466 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 546 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = 0;}
#line 2472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 547 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = S;}
#line 2478 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 548 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = U;}
#line 2484 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 551 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                             (yyval.ast)->scalar.cmplx_bool = BOOL;}
#line 2491 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 555 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                                             (yyval.ast)->scalar.type = F;
                                             (yyval.ast)->scalar.signedness = S;}
#line 2499 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 559 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                                             (yyval.ast)->scalar.type = D;
                                             (yyval.ast)->scalar.signedness = S;}
#line 2507 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 563 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                                             (yyval.ast)->scalar.type = LD;
                                             (yyval.ast)->scalar.signedness = S;}
#line 2515 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 569 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                                             (yyval.ast)->scalar.type = F;
                                             (yyval.ast)->scalar.cmplx_bool = CMPLX;
                                             (yyval.ast)->scalar.signedness = S;}
#line 2524 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 574 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                                             (yyval.ast)->scalar.type = D;
                                             (yyval.ast)->scalar.cmplx_bool = CMPLX;
                                             (yyval.ast)->scalar.signedness = S;}
#line 2533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 579 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                                             (yyval.ast)->scalar.type = LD;
                                             (yyval.ast)->scalar.cmplx_bool = CMPLX;
                                             (yyval.ast)->scalar.signedness = S;}
#line 2542 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 585 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_SCALAR);
                             (yyval.ast)->scalar.type = V;}
#line 2549 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 589 "parser.y" /* yacc.c:1646  */
    {struct sym_ent *ident_symbol = NULL;
                            if(!(ident_symbol = sym_lookup(&curr_stack, curr_stack->scope, OTHER, yylval.STR._STR_)))
                            {
                                char mssg[5120];
                                sprintf(mssg, "Identifier \'%s\' is undefined", yylval.STR._STR_);
                                yyerror(mssg);
                            }
                            (yyval.ast) = astnode_lloc(AST_IDENT);
                            memset((yyval.ast)->ident.name, '0', 4096);
                            strcpy((yyval.ast)->ident.name, yylval.STR._STR_);
                            (yyval.ast)->ident.metadata = ident_symbol;}
#line 2565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 604 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast);}
#line 2571 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 613 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_UOP);
                                           (yyval.ast)->uop.op = '*';
                                           (yyval.ast)->uop.left = astnode_lloc(AST_BOP);
                                           (yyval.ast)->uop.left->bop.op = '+';
                                           (yyval.ast)->uop.left->bop.left = (yyvsp[-3].ast);
                                           (yyval.ast)->uop.left->bop.right = (yyvsp[-1].ast);}
#line 2582 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 625 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_UOP);
                                           (yyval.ast)->uop.op = '.';
                                           (yyval.ast)->uop.left = (yyvsp[-2].ast);
                                           (yyval.ast)->uop.right = astnode_lloc(AST_IDENT);
                                           memset((yyval.ast)->uop.right->ident.name, '0', 4096);
                                           strcpy((yyval.ast)->uop.right->ident.name, yylval.STR._STR_);}
#line 2593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 633 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_COMP_SEL);
                                                (yyval.ast)->comp_sel.left = astnode_lloc(AST_UOP);
                                                (yyval.ast)->comp_sel.left->uop.op = '*';
                                                (yyval.ast)->comp_sel.left->uop.left = (yyvsp[-2].ast);
                                                (yyval.ast)->comp_sel.right = astnode_lloc(AST_IDENT);
                                                memset((yyval.ast)->comp_sel.right->ident.name, '0', 4096);
                                                strcpy((yyval.ast)->comp_sel.right->ident.name, yylval.STR._STR_);}
#line 2605 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 642 "parser.y" /* yacc.c:1646  */
    {int argc = 0, argnum;
                                           struct astnode *temp;
                                           (yyval.ast) = astnode_lloc(AST_FNCALL);
                                           (yyval.ast)->fncall.left = (yyvsp[-3].ast);
                                           (yyval.ast)->fncall.right = (yyvsp[-1].ast);
                                           temp = (yyval.ast)->fncall.right;
                                           while(temp != NULL)
                                           {
                                               ++argc;
                                               temp = temp->elist.left;
                                           }
                                           temp = (yyval.ast)->fncall.right;
                                           argnum = argc;
                                           while(temp != NULL)
                                           {
                                               temp->elist.argnum = argnum--;
                                               temp = temp->elist.left;
                                           }
                                           (yyval.ast)->fncall.argc = argc;}
#line 2629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 663 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = NULL;}
#line 2635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 664 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ELIST);
                                      (yyval.ast)->elist.left = NULL;
                                      (yyval.ast)->elist.right = (yyvsp[0].ast);}
#line 2643 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 668 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ELIST);
                                      (yyval.ast)->elist.left = (yyvsp[-2].ast);
                                      (yyval.ast)->elist.right = (yyvsp[0].ast);}
#line 2651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 673 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = PLUSPLUS;}
#line 2657 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 674 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = MINUSMINUS;}
#line 2663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 677 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_UOP);
                                             (yyval.ast)->uop.op = (yyvsp[0].VAL._TYPE_);
                                             (yyval.ast)->uop.left = (yyvsp[-1].ast);}
#line 2671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 689 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_CAST);
                                         ast_reverse(&(yyvsp[-2].ast));
                                         (yyval.ast)->cast.type = (yyvsp[-2].ast);
                                         (yyval.ast)->cast.to = (yyvsp[0].ast);}
#line 2680 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 695 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_UOP);
                                         (yyval.ast)->uop.op = SIZEOF;
                                         (yyval.ast)->uop.left = (yyvsp[0].ast);}
#line 2688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 699 "parser.y" /* yacc.c:1646  */
    {ast_reverse(&(yyvsp[-1].ast));
                                         (yyval.ast) = astnode_lloc(AST_UOP);
                                         (yyval.ast)->uop.op = SIZEOF;
                                         (yyval.ast)->uop.left = (yyvsp[-1].ast);}
#line 2697 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 705 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_UOP);
                                    (yyval.ast)->uop.op = (yyvsp[-1].VAL._TYPE_);
                                    (yyval.ast)->uop.left = (yyvsp[0].ast);}
#line 2705 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 710 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '-';}
#line 2711 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 711 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '+';}
#line 2717 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 712 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '!';}
#line 2723 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 713 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '~';}
#line 2729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 714 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '&';}
#line 2735 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 715 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '*';}
#line 2741 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 718 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ASSIGN);
                                          (yyval.ast)->assign.left = (yyvsp[0].ast);
                                          (yyval.ast)->assign.right = astnode_lloc(AST_BOP);
                                          int p_op = (yyvsp[-1].VAL._TYPE_) == PLUSPLUS ? '+' : '-';
                                          (yyval.ast)->assign.right->bop.op = p_op;
                                          (yyval.ast)->assign.right->bop.left = (yyvsp[0].ast);
                                          (yyval.ast)->assign.right->bop.right = astnode_lloc(AST_NUM);
                                          (yyval.ast)->assign.right->bop.right->num.i_val = 1;}
#line 2754 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 727 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '*';}
#line 2760 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 728 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '/';}
#line 2766 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 729 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '%';}
#line 2772 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 733 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_BOP);
                                        (yyval.ast)->bop.op = (yyvsp[-1].VAL._TYPE_);
                                        (yyval.ast)->bop.left = (yyvsp[-2].ast);
                                        (yyval.ast)->bop.right = (yyvsp[0].ast);}
#line 2781 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 739 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '+';}
#line 2787 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 740 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '-';}
#line 2793 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 744 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_BOP);
                                     (yyval.ast)->bop.op = (yyvsp[-1].VAL._TYPE_);
                                     (yyval.ast)->bop.left = (yyvsp[-2].ast);
                                     (yyval.ast)->bop.right = (yyvsp[0].ast);}
#line 2802 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 750 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = SHL;}
#line 2808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 751 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = SHR;}
#line 2814 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 755 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_BOP);
                                         (yyval.ast)->bop.op = (yyvsp[-1].VAL._TYPE_);
                                         (yyval.ast)->bop.left = (yyvsp[-2].ast);
                                         (yyval.ast)->bop.right = (yyvsp[0].ast);}
#line 2823 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 761 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '<';}
#line 2829 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 762 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = LTEQ;}
#line 2835 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 763 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = '>';}
#line 2841 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 764 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = GTEQ;}
#line 2847 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 767 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_EQCOMP);
                                               (yyval.ast)->eqcomp.op = (yyvsp[-1].VAL._TYPE_);
                                               (yyval.ast)->eqcomp.left = (yyvsp[-2].ast);
                                               (yyval.ast)->eqcomp.right = (yyvsp[0].ast);}
#line 2856 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 773 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = EQEQ;}
#line 2862 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 774 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = NOTEQ;}
#line 2868 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 778 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_EQCOMP);
                                    (yyval.ast)->eqcomp.op = (yyvsp[-1].VAL._TYPE_);
                                    (yyval.ast)->eqcomp.left = (yyvsp[-2].ast);
                                    (yyval.ast)->eqcomp.right = (yyvsp[0].ast);}
#line 2877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 785 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_BOP);
                                           (yyval.ast)->bop.op = '|';
                                           (yyval.ast)->bop.left = (yyvsp[-2].ast);
                                           (yyval.ast)->bop.right = (yyvsp[0].ast);}
#line 2886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 792 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_BOP);
                                             (yyval.ast)->bop.op = '^';
                                             (yyval.ast)->bop.left = (yyvsp[-2].ast);
                                             (yyval.ast)->bop.right = (yyvsp[0].ast);}
#line 2895 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 799 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_BOP);
                                        (yyval.ast)->bop.op = '&';
                                        (yyval.ast)->bop.left = (yyvsp[-2].ast);
                                        (yyval.ast)->bop.right = (yyvsp[0].ast);}
#line 2904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 806 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_LOG);
                                                         (yyval.ast)->log.op = LOGOR;
                                                         (yyval.ast)->log.left = (yyvsp[-2].ast);
                                                         (yyval.ast)->log.right = (yyvsp[0].ast);}
#line 2913 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 813 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_LOG);
                                                       (yyval.ast)->log.op = LOGAND;
                                                       (yyval.ast)->log.left = (yyvsp[-2].ast);
                                                       (yyval.ast)->log.right = (yyvsp[0].ast);}
#line 2922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 820 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_TERN);
                                                   (yyval.ast)->tern.left = (yyvsp[-4].ast);
                                                   (yyval.ast)->tern.right = astnode_lloc(AST_TERN);
                                                   (yyval.ast)->tern.right->tern.op = '?';
                                                   (yyval.ast)->tern.right->tern.left = (yyvsp[-2].ast);
                                                   (yyval.ast)->tern.right->tern.right = astnode_lloc(AST_TERN);
                                                   (yyval.ast)->tern.right->tern.right->tern.op = ':';
                                                   (yyval.ast)->tern.right->tern.right->tern.left = (yyvsp[0].ast);}
#line 2935 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 830 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = PLUSEQ;}
#line 2941 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 831 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = MINUSEQ;}
#line 2947 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 832 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = TIMESEQ;}
#line 2953 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 833 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = DIVEQ;}
#line 2959 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 834 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = MODEQ;}
#line 2965 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 835 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = SHLEQ;}
#line 2971 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 836 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = SHREQ;}
#line 2977 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 837 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = ANDEQ;}
#line 2983 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 838 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = XOREQ;}
#line 2989 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 839 "parser.y" /* yacc.c:1646  */
    {(yyval.VAL._TYPE_) = OREQ;}
#line 2995 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 843 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ASSIGN);
                                         (yyval.ast)->assign.op = '=';
                                         (yyval.ast)->assign.left = (yyvsp[-2].ast);
                                         (yyval.ast)->assign.right = (yyvsp[0].ast);}
#line 3004 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 848 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_ASSIGN);
                                               (yyval.ast)->assign.op = '=';
                                               (yyval.ast)->assign.left = (yyvsp[-2].ast);
                                               (yyval.ast)->assign.right = astnode_lloc(AST_BOP);
                                               (yyval.ast)->assign.right->bop.op = (yyvsp[-1].VAL._TYPE_) < 255 ? (yyvsp[-1].VAL._TYPE_) : print_kwop((yyvsp[-1].VAL._TYPE_))[0];
                                               (yyval.ast)->assign.right->bop.left = (yyvsp[-2].ast);
                                               (yyval.ast)->assign.right->bop.right = (yyvsp[0].ast);}
#line 3016 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 858 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_BOP);
                                        (yyval.ast)->bop.op = ',';
                                        (yyval.ast)->bop.left = (yyvsp[-2].ast);
                                        (yyval.ast)->bop.right = (yyvsp[0].ast);}
#line 3025 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 866 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_NUM);
                     (yyval.ast)->num.i_val = yylval.VAL._INT_;
                     (yyval.ast)->num.fd_val = yylval.VAL._FLT_;
                     (yyval.ast)->num.type = yylval.VAL._TYPE_;}
#line 3034 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 871 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_STR);
                     memset((yyval.ast)->str_lit.str, '0', 4096);
                     strcpy((yyval.ast)->str_lit.str, yylval.STR._STR_);
                     (yyval.ast)->str_lit.len = yylval.STR.len;}
#line 3043 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 876 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = astnode_lloc(AST_CHAR);
                     (yyval.ast)->char_lit.chr = yylval.STR._CHR_;}
#line 3050 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 3054 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 879 "parser.y" /* yacc.c:1906  */


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
