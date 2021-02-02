/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

/*
 * parser; Parser for PL-0
 */

#define MAXLENGTH 16

#include <stdio.h>
#include <string.h>

#include "./symtab/symtab.h"
#include "./llvm_code/llvm.h"
#include "./llvm_code/factor.h"

int yyparse();
int yyerror(char *);

extern int yylineno;
extern char *yytext;

int gRegnum;
Scope gScope;
Row *gProgram; // 定義処理中の関数名
Factor *gCalling; // 呼び出し処理中の関数
Factor *gRetval; // 関数の戻り値
int gArity;

#line 98 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SBEGIN = 258,
    DO = 259,
    ELSE = 260,
    SEND = 261,
    FOR = 262,
    FORWARD = 263,
    FUNCTION = 264,
    IF = 265,
    PROCEDURE = 266,
    PROGRAM = 267,
    READ = 268,
    THEN = 269,
    TO = 270,
    VAR = 271,
    WHILE = 272,
    WRITE = 273,
    PLUS = 274,
    MINUS = 275,
    MULT = 276,
    DIV = 277,
    EQ = 278,
    NEQ = 279,
    LE = 280,
    LT = 281,
    GE = 282,
    GT = 283,
    LPAREN = 284,
    RPAREN = 285,
    LBRACKET = 286,
    RBRACKET = 287,
    COMMA = 288,
    SEMICOLON = 289,
    COLON = 290,
    INTERVAL = 291,
    PERIOD = 292,
    ASSIGN = 293,
    NUMBER = 294,
    IDENT = 295
  };
#endif
/* Tokens.  */
#define SBEGIN 258
#define DO 259
#define ELSE 260
#define SEND 261
#define FOR 262
#define FORWARD 263
#define FUNCTION 264
#define IF 265
#define PROCEDURE 266
#define PROGRAM 267
#define READ 268
#define THEN 269
#define TO 270
#define VAR 271
#define WHILE 272
#define WRITE 273
#define PLUS 274
#define MINUS 275
#define MULT 276
#define DIV 277
#define EQ 278
#define NEQ 279
#define LE 280
#define LT 281
#define GE 282
#define GT 283
#define LPAREN 284
#define RPAREN 285
#define LBRACKET 286
#define RBRACKET 287
#define COMMA 288
#define SEMICOLON 289
#define COLON 290
#define INTERVAL 291
#define PERIOD 292
#define ASSIGN 293
#define NUMBER 294
#define IDENT 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "parser.y"

    int num;
    char ident[MAXLENGTH+1];

#line 235 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   120

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  145

#define YYUNDEFTOK  2
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    53,    53,    52,    75,    74,    88,    89,    93,    94,
      98,   102,   103,   107,   108,   112,   113,   118,   122,   117,
     146,   150,   145,   183,   203,   207,   208,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   224,   235,   234,   253,
     261,   260,   283,   290,   282,   316,   315,   391,   415,   419,
     428,   437,   441,   450,   458,   466,   474,   482,   493,   494,
     495,   504,   518,   528,   529,   536,   546,   553,   557,   558,
     562,   590,   606,   607,   611,   612,   616,   617,   621,   629,
     640,   660
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SBEGIN", "DO", "ELSE", "SEND", "FOR",
  "FORWARD", "FUNCTION", "IF", "PROCEDURE", "PROGRAM", "READ", "THEN",
  "TO", "VAR", "WHILE", "WRITE", "PLUS", "MINUS", "MULT", "DIV", "EQ",
  "NEQ", "LE", "LT", "GE", "GT", "LPAREN", "RPAREN", "LBRACKET",
  "RBRACKET", "COMMA", "SEMICOLON", "COLON", "INTERVAL", "PERIOD",
  "ASSIGN", "NUMBER", "IDENT", "$accept", "program", "$@1", "outblock",
  "$@2", "var_decl_part", "var_decl_list", "var_decl", "subprog_decl_part",
  "subprog_decl_list", "subprog_decl", "proc_decl", "$@3", "$@4",
  "func_decl", "$@5", "$@6", "subprog_name", "inblock", "statement_list",
  "statement", "assignment_statement", "if_statement", "$@7",
  "else_statement", "$@8", "while_statement", "$@9", "$@10",
  "for_statement", "$@11", "proc_call_statement", "block_statement",
  "read_statement", "write_statement", "null_statement", "condition",
  "expression", "term", "factor", "func_call_factor", "var_name", "args",
  "arg_list", "v_args", "v_arg_list", "id_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

#define YYPACT_NINF (-59)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-72)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -8,   -18,    47,    16,   -59,   -59,     9,    13,   -29,    65,
      41,   -59,   -59,    23,   -59,   -59,   -59,   -59,    50,   -59,
     -59,   -59,     9,    46,    49,    49,     2,    65,   -59,   -59,
     -59,    59,    59,     2,    51,    20,    61,   -59,    63,     8,
     -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,
      55,   -59,    54,    53,    64,     4,   -59,    57,    12,    12,
      20,   -59,    68,    85,    38,    48,   -59,   -59,   -59,    60,
      20,    20,    20,   -59,    20,   -59,   -27,   -59,   -59,   -59,
       2,    20,    48,    48,    -2,   -59,   -59,    20,    20,    20,
      20,    20,    20,    20,    20,    12,    12,   -59,    73,   100,
      25,    58,    -9,    58,   -59,    66,     9,     9,   -59,    52,
     -59,     2,   -59,   -59,    58,    58,    58,    58,    58,    58,
     -59,   -59,   -59,   -59,   -59,   -59,    20,   -59,     2,   -59,
     -59,    20,   103,     2,    58,   -59,     7,   -59,   -59,   -59,
     -59,     2,     2,   -59,   -59
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     6,     0,     0,    11,
       0,     9,    80,    10,     3,    20,    17,     4,     0,    13,
      15,    16,     7,     0,     0,     0,    51,    12,     8,    81,
      23,    76,    76,    51,     0,     0,     0,    42,     0,    72,
       5,    27,    28,    29,    30,    31,    33,    34,    35,    32,
       0,    14,     0,     0,     0,     0,    25,     0,     0,     0,
       0,    67,    71,     0,     0,    58,    63,    69,    66,     0,
       0,     0,     0,    47,     0,    78,     0,    21,    18,    48,
      51,     0,    59,    60,     0,    70,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,     0,     0,
       0,    74,     0,    36,    77,     0,     6,     6,    26,     0,
      68,    51,    61,    62,    52,    53,    57,    56,    55,    54,
      64,    65,    49,    43,    50,    73,     0,    79,    51,    22,
      19,     0,    39,    51,    75,    24,     0,    40,    38,    44,
      45,    51,    51,    41,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -59,   -59,   -59,   -59,   -59,    99,   -59,    89,   -59,   -59,
      86,   -59,   -59,   -59,   -59,   -59,   -59,    87,    10,   -59,
     -32,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,
     -59,   -59,   -59,   -59,   -59,   -59,    44,   -58,    22,   -13,
     -59,   -26,    56,   -59,    88,   -59,   -59
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     8,    26,   128,    10,    11,    17,    18,
      19,    20,    25,   107,    21,    24,   106,    31,   129,    55,
      40,    41,    42,   111,   138,   141,    43,    70,   133,    44,
     142,    45,    46,    47,    48,    49,    63,    64,    65,    66,
      67,    68,    73,   102,    53,    76,    13
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,    56,    84,   104,     1,    33,   105,    50,    14,    34,
      79,   140,    35,   100,   101,    36,   103,    87,    88,    37,
      38,   125,     3,   109,   126,     7,    87,    88,   110,   112,
     113,   114,   115,   116,   117,   118,   119,    72,    80,    58,
      59,    60,    39,    98,    87,    88,   -71,     4,   108,    60,
       5,    61,    62,    12,    50,   124,    23,    87,    88,    61,
      62,    89,    90,    91,    92,    93,    94,   131,   134,    95,
      96,    87,    88,   136,    15,    22,    16,    87,    88,   132,
      82,    83,   120,   121,    27,    50,    29,    77,    52,    30,
      69,    57,    71,    74,    75,    81,   135,    72,    78,    86,
      97,   139,    50,   122,   123,     9,   127,    50,   137,   143,
     144,    28,    32,    51,    99,    50,    50,   130,    85,     0,
      54
};

static const yytype_int16 yycheck[] =
{
      26,    33,    60,    30,    12,     3,    33,    33,    37,     7,
       6,     4,    10,    71,    72,    13,    74,    19,    20,    17,
      18,    30,    40,    81,    33,    16,    19,    20,    30,    87,
      88,    89,    90,    91,    92,    93,    94,    29,    34,    19,
      20,    29,    40,    69,    19,    20,    38,     0,    80,    29,
      34,    39,    40,    40,    80,    30,    33,    19,    20,    39,
      40,    23,    24,    25,    26,    27,    28,    15,   126,    21,
      22,    19,    20,   131,     9,    34,    11,    19,    20,   111,
      58,    59,    95,    96,    34,   111,    40,    34,    29,    40,
      29,    40,    29,    38,    40,    38,   128,    29,    34,    14,
      40,   133,   128,    30,     4,     6,    40,   133,     5,   141,
     142,    22,    25,    27,    70,   141,   142,   107,    62,    -1,
      32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    42,    40,     0,    34,    43,    16,    44,    46,
      47,    48,    40,    87,    37,     9,    11,    49,    50,    51,
      52,    55,    34,    33,    56,    53,    45,    34,    48,    40,
      40,    58,    58,     3,     7,    10,    13,    17,    18,    40,
      61,    62,    63,    67,    70,    72,    73,    74,    75,    76,
      82,    51,    29,    85,    85,    60,    61,    40,    19,    20,
      29,    39,    40,    77,    78,    79,    80,    81,    82,    29,
      68,    29,    29,    83,    38,    40,    86,    34,    34,     6,
      34,    38,    79,    79,    78,    83,    14,    19,    20,    23,
      24,    25,    26,    27,    28,    21,    22,    40,    82,    77,
      78,    78,    84,    78,    30,    33,    57,    54,    61,    78,
      30,    64,    78,    78,    78,    78,    78,    78,    78,    78,
      80,    80,    30,     4,    30,    30,    33,    40,    46,    59,
      59,    15,    61,    69,    78,    61,    78,     5,    65,    61,
       4,    66,    71,    61,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    43,    42,    45,    44,    46,    46,    47,    47,
      48,    49,    49,    50,    50,    51,    51,    53,    54,    52,
      56,    57,    55,    58,    59,    60,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    62,    64,    63,    65,
      66,    65,    68,    69,    67,    71,    70,    72,    73,    74,
      75,    76,    77,    77,    77,    77,    77,    77,    78,    78,
      78,    78,    78,    79,    79,    79,    80,    80,    80,    80,
      81,    82,    83,    83,    84,    84,    85,    85,    86,    86,
      87,    87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     6,     0,     4,     0,     2,     3,     1,
       2,     0,     2,     1,     3,     1,     1,     0,     0,     7,
       0,     0,     7,     1,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     6,     0,
       0,     3,     0,     0,     6,     0,     9,     2,     3,     4,
       4,     0,     3,     3,     3,     3,     3,     3,     1,     2,
       2,     3,     3,     1,     3,     3,     1,     1,     3,     1,
       2,     1,     0,     3,     1,     3,     0,     3,     1,     3,
       1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2:
#line 53 "parser.y"
        {
                fundecl_init();
                code_init();
                fstack_init();
                symtab_init();

                gScope = GLOBAL_VAR;
                gRegnum = 1;
                gArity = 0;

                symtab_push((yyvsp[-1].ident), 0, gScope);

                fundecl_add("__GlobalDecl");
        }
#line 1529 "y.tab.c"
    break;

  case 3:
#line 68 "parser.y"
        {
                print_LLVM_code();
        }
#line 1537 "y.tab.c"
    break;

  case 4:
#line 75 "parser.y"
        {
                fundecl_add("main");
                gRegnum = 1;
        }
#line 1546 "y.tab.c"
    break;

  case 5:
#line 80 "parser.y"
        {
                factor_push("", 0, CONSTANT);
                Factor *tRet = factor_pop();
                code_add(code_create(Ret, tRet, NULL, NULL, 0));
        }
#line 1556 "y.tab.c"
    break;

  case 17:
#line 118 "parser.y"
        {
                gScope = PROC_NAME;
        }
#line 1564 "y.tab.c"
    break;

  case 18:
#line 122 "parser.y"
        {
                if (gProgram->type != PROC_NAME)
                        yyerror("not decleared as procedure");

                if (gProgram->size == -1)
                        gProgram->size = gArity;

                if (gProgram->size == gArity) 
                        gRegnum = fundecl_add_arg_code(); // 引数周りのコード一気に生成
                else if (gProgram->size > gArity) 
                        yyerror("too much procedure argments");
                else 
                        yyerror("too few procedure argments");
        }
#line 1583 "y.tab.c"
    break;

  case 19:
#line 137 "parser.y"
        {
                code_add(code_create(Ret, NULL, NULL, NULL, 0)); // void
                gScope = GLOBAL_VAR;
                symtab_delete();
        }
#line 1593 "y.tab.c"
    break;

  case 20:
#line 146 "parser.y"
        {
                gScope = FUNC_NAME;
        }
#line 1601 "y.tab.c"
    break;

  case 21:
#line 150 "parser.y"
        {
                if (gProgram->type != FUNC_NAME)
                        yyerror("not decleared as function");

                if (gProgram->size == -1)
                        gProgram->size = gArity;

                if (gProgram->size == gArity) { 
                        gRegnum = fundecl_add_arg_code(); // 引数周りのコード一気に生成

                        factor_push("return val", gRegnum++, LOCAL_VAR);
                        gRetval = factor_pop();

                        code_add(code_create(Alloca, NULL, NULL, gRetval, 0)); // 戻り値を先に定義
                }
                else if (gProgram->size > gArity) 
                        yyerror("too much function argments");
                else 
                        yyerror("too few function argments");
        }
#line 1626 "y.tab.c"
    break;

  case 22:
#line 171 "parser.y"
        {
                factor_push("", gRegnum++, LOCAL_VAR); // 戻りのロード先
                Factor* tRetval = factor_pop();

                code_add(code_create(Load, gRetval, NULL, tRetval, 0));
                code_add(code_create(Ret, tRetval, NULL, NULL, 0)); // loadして返す
                gScope = GLOBAL_VAR;
                symtab_delete();
        }
#line 1640 "y.tab.c"
    break;

  case 23:
#line 184 "parser.y"
        {
                Row *tRow = symtab_lookup((yyvsp[0].ident));
                if (tRow == NULL) {
                        tRow = symtab_push((yyvsp[0].ident), 0, gScope);
                        tRow->size = -1;
                }

                if (gScope == PROC_NAME)
                        procdecl_add(tRow->name);
                else
                        fundecl_add(tRow->name);

                gProgram = tRow;
                gArity = gRegnum = 0;
                gScope = LOCAL_VAR;
        }
#line 1661 "y.tab.c"
    break;

  case 36:
#line 225 "parser.y"
        {
                Factor *tArg1 = factor_pop();
                Factor *tArg2 = factor_pop();

                code_add(code_create(Store, tArg1, tArg2, NULL, 0));
        }
#line 1672 "y.tab.c"
    break;

  case 37:
#line 235 "parser.y"
        {
                Factor *tCond = factor_pop();

                Factor *tEnd = factor_push("if.end.else", 0, LABEL);
                // バックパッチであとで正しい値をつける(elseの前に来る)

                factor_push("if.then", gRegnum++, LABEL);
                Factor *tThen = factor_pop();
                // 捨てラベル(icmpのtrueのときに飛ぶラベルを直後に置く)

                code_add(code_create(BrCond, tThen, tEnd, tCond, 0));
                code_add(code_create(Label, tThen, NULL, NULL, 0));
        }
#line 1690 "y.tab.c"
    break;

  case 39:
#line 253 "parser.y"
        {
                Factor *tEnd = factor_pop();
                tEnd->val=gRegnum++;

                code_add(code_create(BrUncond, tEnd, NULL, NULL, 0));
                code_add(code_create(Label, tEnd, NULL, NULL, 0));
        }
#line 1702 "y.tab.c"
    break;

  case 40:
#line 261 "parser.y"
        {
                Factor *tElse = factor_pop();
                tElse->val = gRegnum++;

                Factor *tEnd = factor_push("if.end", 0, LABEL);
                
                code_add(code_create(BrUncond, tEnd, NULL, NULL, 0));
                code_add(code_create(Label, tElse, NULL, NULL, 0));
        }
#line 1716 "y.tab.c"
    break;

  case 41:
#line 271 "parser.y"
        {
                Factor *tEnd = factor_pop();
                tEnd->val = gRegnum++;

                code_add(code_create(BrUncond, tEnd, NULL, NULL, 0));
                // Labelの前にはそれに対応するジャンプがないとダメっぽい?
                code_add(code_create(Label, tEnd, NULL, NULL, 0));
        }
#line 1729 "y.tab.c"
    break;

  case 42:
#line 283 "parser.y"
        {
                Factor *tLoop = factor_push("while.loop", gRegnum++, LABEL);

                code_add(code_create(BrUncond, tLoop, NULL, NULL, 0));
                code_add(code_create(Label, tLoop, NULL, NULL, 0));
        }
#line 1740 "y.tab.c"
    break;

  case 43:
#line 290 "parser.y"
        {
                Factor *tCond = factor_pop();

                factor_push("while.do", gRegnum++, LABEL);
                Factor *tDo = factor_pop(); // 捨てラベル

                Factor *tBreak = factor_push("while.break", 0, LABEL);
                // バックパッチであとで正しい値をつける(whileを抜ける)

                code_add(code_create(BrCond, tDo, tBreak, tCond, 0));
                code_add(code_create(Label, tDo, NULL, NULL, 0));
        }
#line 1757 "y.tab.c"
    break;

  case 44:
#line 303 "parser.y"
        {
                Factor *tBreak = factor_pop();
                tBreak->val = gRegnum++;
                Factor *tLoop= factor_pop();
                // ステートメント内ではFactorのスタックは必ず使い切られる

                code_add(code_create(BrUncond, tLoop, NULL, NULL, 0));
                code_add(code_create(Label, tBreak, NULL, NULL, 0));
        }
#line 1771 "y.tab.c"
    break;

  case 45:
#line 316 "parser.y"
        {
                Row *tRow = symtab_lookup((yyvsp[-5].ident));
                if (tRow == NULL)
                        yyerror("not decleared yet");

                Factor *tTo = factor_pop(); // tFromからtToまで
                Factor *tFrom = factor_pop();

                Factor *tCnt = factor_push(tRow->name, tRow->regnum, tRow->type);
                // カウンタ(インクリメントしていく変数)
                //popせずにとっておく

                code_add(code_create(Store, tFrom, tCnt, NULL, 0));

                Factor *tLoop = factor_push("for.loop", gRegnum++, LABEL);
                // ループで戻ってくる場所、あとからpopしてbr命令を書く

                code_add(code_create(BrUncond, tLoop, NULL, NULL, 0));
                code_add(code_create(Label, tLoop, NULL, NULL, 0));

                factor_push("", gRegnum++, LOCAL_VAR);
                Factor *tCntLocal = factor_pop();
                code_add(code_create(Load, tCnt, NULL, tCntLocal, 0)); // カウンタをレジスタに持ってくる

                factor_push("", gRegnum++, LOCAL_VAR);
                Factor *tCond = factor_pop(); // 条件を用意する

                code_add(code_create(Icmp, tCntLocal, tTo, tCond, SLE));

                factor_push("for.do", gRegnum++, LABEL);
                Factor *tDo = factor_pop(); // 条件でブレークしないときにここに飛ぶ

                Factor *tBreak = factor_push("for.break", 0, LABEL);
                // バックパッチであとから値入れたいのでpushしたままにする。

                code_add(code_create(BrCond, tDo, tBreak, tCond, 0));
                code_add(code_create(Label, tDo, NULL, NULL, 0));
        }
#line 1814 "y.tab.c"
    break;

  case 46:
#line 355 "parser.y"
        {
                // この順番で出てくる
                Factor *tBreak = factor_pop();
                Factor *tLoop = factor_pop();
                Factor *tCnt = factor_pop();

                // cntインクリメント部ここから
                factor_push("for.increment", gRegnum++, LABEL);
                Factor *tInc = factor_pop();
                code_add(code_create(BrUncond, tInc, NULL, NULL, 0));
                code_add(code_create(Label, tInc, NULL, NULL, 0));

                factor_push("", gRegnum++, LOCAL_VAR);
                Factor *tCntLocal = factor_pop();

                code_add(code_create(Load, tCnt, NULL, tCntLocal, 0)); // カウンタをレジスタに持ってくる

                factor_push("", 1, CONSTANT);
                Factor *tOne = factor_pop();

                factor_push("", gRegnum++, LOCAL_VAR);
                Factor *tRetval = factor_pop();

                code_add(code_create(Add, tCntLocal, tOne, tRetval, 0));

                code_add(code_create(Store, tRetval, tCnt, NULL, 0));
                // インクリメント部ここまで

                code_add(code_create(BrUncond, tLoop, NULL, NULL, 0));

                tBreak->val = gRegnum++; // バックパッチ
                code_add(code_create(Label, tBreak, NULL, NULL, 0));
        }
#line 1852 "y.tab.c"
    break;

  case 47:
#line 392 "parser.y"
        {
                Row *tRow = symtab_lookup((yyvsp[-1].ident));
                if (tRow == NULL)
                        yyerror("not decleared yet");
                else if(tRow->type != PROC_NAME)
                        yyerror("not decleared as procedure");

                factor_push(tRow->name, 0, PROC_NAME);
                gCalling = factor_pop();

                LLVMcode *tCode = code_create(Call, gCalling, NULL, NULL, 0);

                int tArity = tRow->size;
                for (int i = 0; i < tArity; i++){
                        // 引数は逆順でスタックに入ってる
                        tCode->args.call.proc_args[tArity - i - 1] = factor_pop();
                }
                code_add(tCode);
                gCalling = NULL;
        }
#line 1877 "y.tab.c"
    break;

  case 49:
#line 420 "parser.y"
        {
                Factor *tArg = factor_pop();
                gRegnum++; // 本当は返り値を持っとく分
                code_add(code_create(Read, tArg, NULL, NULL, 0));
        }
#line 1887 "y.tab.c"
    break;

  case 50:
#line 429 "parser.y"
        {
                Factor *tArg = factor_pop();
                code_add(code_create(Write, tArg, NULL, NULL, 0));
                gRegnum++; // print文は返り値を使わないけど、レジスタ番号は一応確保しないとエラー
        }
#line 1897 "y.tab.c"
    break;

  case 52:
#line 442 "parser.y"
        {
                // 四則演算と大体一緒
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, EQUAL));
        }
#line 1910 "y.tab.c"
    break;

  case 53:
#line 451 "parser.y"
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, NE));
        }
#line 1922 "y.tab.c"
    break;

  case 54:
#line 459 "parser.y"
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SGT));
        }
#line 1934 "y.tab.c"
    break;

  case 55:
#line 467 "parser.y"
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SGE));
        }
#line 1946 "y.tab.c"
    break;

  case 56:
#line 475 "parser.y"
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SLT));
        }
#line 1958 "y.tab.c"
    break;

  case 57:
#line 483 "parser.y"
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SLE));
        }
#line 1970 "y.tab.c"
    break;

  case 60:
#line 496 "parser.y"
        {
                // 単項演算はゼロからの足し引きで表現。
                Factor *tArg2 = factor_pop();
                factor_push("", 0, CONSTANT);
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);
                code_add(code_create(Sub, tArg1, tArg2, tRetval, 0));
        }
#line 1983 "y.tab.c"
    break;

  case 61:
#line 505 "parser.y"
        {
                // 四則演算は、全部これと一緒

                // オペランドをポップする(順番に注意)
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();

                // 代入先として局所変数を用意、popしないことで、次のオペランドとしてもそのまま使える
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                // Factorからのコード生成と追加を同時に行う
                code_add(code_create(Add, tArg1, tArg2, tRetval, 0));
        }
#line 2001 "y.tab.c"
    break;

  case 62:
#line 519 "parser.y"
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);
                code_add(code_create(Sub, tArg1, tArg2, tRetval, 0));
        }
#line 2012 "y.tab.c"
    break;

  case 64:
#line 530 "parser.y"
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);
                code_add(code_create(Mul, tArg1, tArg2, tRetval, 0));
        }
#line 2023 "y.tab.c"
    break;

  case 65:
#line 537 "parser.y"
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);
                code_add(code_create(Sdiv, tArg1, tArg2, tRetval, 0));
        }
#line 2034 "y.tab.c"
    break;

  case 66:
#line 547 "parser.y"
        {
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Load, tArg1, NULL, tRetval, 0));
        }
#line 2045 "y.tab.c"
    break;

  case 67:
#line 554 "parser.y"
        {
                factor_push("const", (yyvsp[0].num), CONSTANT);
        }
#line 2053 "y.tab.c"
    break;

  case 70:
#line 563 "parser.y"
        {
                Row *tRow = symtab_lookup((yyvsp[-1].ident));
                if (tRow == NULL)
                        yyerror("not decleared yet");
                else if(tRow->type != FUNC_NAME)
                        yyerror("not decleared as function");

                // 再帰的に呼び出しているときをケア
                factor_push(tRow->name, 0, FUNC_NAME);
                gCalling = factor_pop();

                factor_push("", gRegnum++, LOCAL_VAR); // 関数の戻り
                Factor *tRetval = factor_pop();
                LLVMcode *tCode = code_create(Call, gCalling, NULL, tRetval, 0);

                int tArity = tRow->size;
                for (int i = 0; i < tArity; i++){
                        // 引数は逆順でスタックに入ってる
                        tCode->args.call.proc_args[tArity - i - 1] = factor_pop();
                }
                code_add(tCode);
                factor_push("", tRetval->val, tRetval->type); // 関数の戻り
                gCalling = NULL;
        }
#line 2082 "y.tab.c"
    break;

  case 71:
#line 591 "parser.y"
        {
                Row* tRow = symtab_lookup((yyvsp[0].ident));
                if (tRow == NULL)
                        yyerror("not decleared yet");
                else if (tRow->type == FUNC_NAME)
                        factor_push(gRetval->vname, gRetval->val, gRetval->type);
                else if(tRow->type != GLOBAL_VAR && tRow->type != LOCAL_VAR)
                        yyerror("not decleared as var");
                else 
                        factor_push(tRow->name, tRow->regnum, tRow->type);

        }
#line 2099 "y.tab.c"
    break;

  case 78:
#line 622 "parser.y"
        {
                gArity++;
                Row *tRow = symtab_push((yyvsp[0].ident), gRegnum++, LOCAL_VAR);

                factor_push(tRow->name, tRow->regnum, tRow->type);
                fundecl_add_arg(factor_pop());
        }
#line 2111 "y.tab.c"
    break;

  case 79:
#line 630 "parser.y"
        {
                gArity++;
                Row *tRow = symtab_push((yyvsp[0].ident), gRegnum++, LOCAL_VAR);

                factor_push(tRow->name, tRow->regnum, tRow->type);
                fundecl_add_arg(factor_pop());
        }
#line 2123 "y.tab.c"
    break;

  case 80:
#line 641 "parser.y"
        {
                // 大域変数と局所変数の場合で処理分けた
                // 局所だと、レジスタ番号をSSAで管理する必要がある
                LLVMcommand tCommand;
                if(gScope == GLOBAL_VAR){
                        tCommand = Global;
                        symtab_push((yyvsp[0].ident), 0, gScope);
                } else{
                        tCommand = Alloca;
                        symtab_push((yyvsp[0].ident), gRegnum++, gScope);
                }

                Row *tRow = symtab_lookup((yyvsp[0].ident));

                factor_push(tRow->name, tRow->regnum, tRow->type);
                Factor *tRetval = factor_pop();

                code_add(code_create(tCommand, NULL, NULL, tRetval, 0));
        }
#line 2147 "y.tab.c"
    break;

  case 81:
#line 661 "parser.y"
        {
                // ↑と同じ
                LLVMcommand tCommand;
                if(gScope == GLOBAL_VAR){
                        tCommand = Global;
                        symtab_push((yyvsp[0].ident), 0, gScope);
                } else{
                        tCommand = Alloca;
                        symtab_push((yyvsp[0].ident), gRegnum++, gScope);
                }
                Row *tRow = symtab_lookup((yyvsp[0].ident));
                factor_push(tRow->name, tRow->regnum, tRow->type);
                Factor *tRetval = factor_pop();

                code_add(code_create(tCommand, NULL, NULL, tRetval, 0));
        }
#line 2168 "y.tab.c"
    break;


#line 2172 "y.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 680 "parser.y"
 
int yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
  fprintf(stderr, "line: %d\n%s\n", yylineno, yytext);
  return yylineno;
}
