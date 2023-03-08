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
#ifndef YY_YY_HSHPARSER_TAB_HPP_INCLUDED
# define YY_YY_HSHPARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "../hshparser.y"


#include "node.hpp"
#include "translation_unit.hpp"
#include "function.hpp"
#include "declaration.hpp"
#include "statement.hpp"
#include "expression.hpp"
#include "type.hpp"
    
    
extern Node* g_root;
void setTypeInformation(Type* type_ptr, std::string type_str);

int yylex(void);
void yyerror(const char *);

#line 129 "hshparser.tab.cpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_IDENTIFIER = 258,
    T_SC = 259,
    T_CMA = 260,
    T_LRB = 261,
    T_LCB = 262,
    T_RCB = 263,
    T_LSB = 264,
    T_RSB = 265,
    T_QU = 266,
    T_COL = 267,
    T_LOG_OR = 268,
    T_LOG_AND = 269,
    T_OR = 270,
    T_XOR = 271,
    T_AND = 272,
    T_EQUALITY_OP = 273,
    T_REL_OP = 274,
    T_SHIFT_OP = 275,
    T_MULT = 276,
    T_DIV = 277,
    T_REM = 278,
    T_TILDE = 279,
    T_NOT = 280,
    T_INCDEC = 281,
    T_ADDSUB_OP = 282,
    T_ASSIGN_OPER = 283,
    T_EQ = 284,
    T_INT_CONST = 285,
    T_IF = 286,
    T_WHILE = 287,
    T_DO = 288,
    T_FOR = 289,
    T_RETURN = 290,
    T_VOID = 291,
    T_CHAR = 292,
    T_SHORT = 293,
    T_INT = 294,
    T_LONG = 295,
    T_STATIC = 296,
    T_CONST = 297,
    T_GOTO = 298,
    T_BREAK = 299,
    T_CONTINUE = 300,
    T_CASE = 301,
    T_DEFAULT = 302,
    T_SWITCH = 303,
    T_ELLIPSIS = 304,
    T_STRINGLITERAL = 305,
    T_RRB = 306,
    T_ELSE = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "../hshparser.y"

    Node* node;
    TranslationUnit* trans_unit;
    Function* function;
    Statement* statement;
    Declaration* declaration;
    Expression* expression;
    Type* type;
    double number;
    std::string* string;

#line 205 "hshparser.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HSHPARSER_TAB_HPP_INCLUDED  */



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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   519

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  216

#define YYUNDEFTOK  2
#define YYMAXUTOK   307


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    80,    80,    86,    87,    91,    92,    98,   103,   104,
     107,   108,   111,   125,   131,   132,   135,   156,   162,   167,
     168,   169,   170,   171,   172,   173,   177,   178,   181,   182,
     185,   189,   190,   191,   201,   210,   211,   213,   216,   217,
     219,   220,   221,   225,   226,   231,   232,   235,   236,   237,
     238,   239,   240,   244,   245,   246,   250,   254,   255,   256,
     257,   261,   262,   263,   267,   268,   271,   272,   273,   274,
     275,   279,   280,   282,   288,   292,   293,   355,   356,   360,
     361,   366,   367,   371,   372,   376,   377,   381,   382,   385,
     386,   390,   391,   396,   397,   402,   403,   408,   409,   414,
     415,   419,   420,   421,   424,   425,   430,   431,   432,   435,
     436,   437,   438,   442,   443,   444,   451,   456,   457,   461,
     462,   466,   467,   468,   469,   472
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_IDENTIFIER", "T_SC", "T_CMA", "T_LRB",
  "T_LCB", "T_RCB", "T_LSB", "T_RSB", "T_QU", "T_COL", "T_LOG_OR",
  "T_LOG_AND", "T_OR", "T_XOR", "T_AND", "T_EQUALITY_OP", "T_REL_OP",
  "T_SHIFT_OP", "T_MULT", "T_DIV", "T_REM", "T_TILDE", "T_NOT", "T_INCDEC",
  "T_ADDSUB_OP", "T_ASSIGN_OPER", "T_EQ", "T_INT_CONST", "T_IF", "T_WHILE",
  "T_DO", "T_FOR", "T_RETURN", "T_VOID", "T_CHAR", "T_SHORT", "T_INT",
  "T_LONG", "T_STATIC", "T_CONST", "T_GOTO", "T_BREAK", "T_CONTINUE",
  "T_CASE", "T_DEFAULT", "T_SWITCH", "T_ELLIPSIS", "T_STRINGLITERAL",
  "T_RRB", "T_ELSE", "$accept", "ROOT", "TranslationUnit",
  "ExternalDeclaration", "FunctionDefinition", "ParameterTypeList",
  "ParameterList", "Parameter", "DeclarationList", "Declaration",
  "DeclarationSpecifierList", "DeclarationSpecifier", "InitDeclaratorList",
  "InitDeclarator", "Declarator", "DirectDeclarator", "IdentifierList",
  "Initializer", "InitializerList", "StatementList", "Statement",
  "LabeledStatement", "CompoundStatement", "CompoundStatement_2",
  "SelectionStatement", "ExpressionStatement", "JumpStatement",
  "IterationStatement", "Expression", "AssignmentExpression",
  "ASSIGN_OPER", "ConditionalExpression", "LogicalOrExpression",
  "LogicalAndExpression", "InclusiveOrExpression", "ExclusiveOrExpression",
  "AndExpression", "EqualityExpression", "RelationalExpression",
  "ShiftExpression", "AdditiveExpression", "MultiplicativeExpression",
  "MultDivRemOP", "CastExpression", "UnaryExpression", "UnaryOperator",
  "PostfixExpression", "PostfixExpression2", "ArgumentExpressionList",
  "PrimaryExpression", "Constant", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
# endif

#define YYPACT_NINF (-76)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     192,   -76,   -76,   -76,   -76,   -76,   -76,   -76,    20,   192,
     -76,   -76,   -76,   454,   -76,   -76,   -76,   -76,    47,   -76,
      33,   -76,    19,    51,   -24,   -76,    47,   171,   397,   -76,
     121,   425,   -76,   -76,     3,    37,   -76,   369,   -76,   -76,
     -76,   -76,     4,   -76,   -76,    39,    45,   335,    50,   437,
      76,    81,    82,   453,    68,    85,   -76,   219,   -76,   454,
     267,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,    83,
     -76,   -76,    52,    78,    79,    77,    89,    92,    93,    91,
      86,    54,   -76,    55,   453,    38,   -76,   -76,   -76,   397,
     -76,   -76,   -76,   -76,    64,   113,   -76,   454,    18,   -76,
     115,   -76,   335,   468,    72,   453,   -76,   453,   453,    96,
     453,   -76,   125,   -76,   -76,   -76,   118,   335,   453,   -76,
     -76,   301,   -76,   -76,   -76,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   -76,   -76,   -76,   453,   -76,
     -76,   453,   -76,    16,   453,   -76,   -76,    53,   -76,   144,
     -76,   129,   -76,   -76,   -76,   453,   -76,    84,    94,   127,
     130,   -76,   335,   -76,    97,   -76,   124,    78,    79,    77,
      89,    92,    93,    91,    86,    54,   -76,   -76,   -76,   -76,
     -76,    31,   132,   114,   -76,   -76,   -76,   -76,   -76,   335,
     335,   453,   453,   -76,   335,   453,   453,   -76,   -76,   -76,
     -76,    98,   -76,   101,   133,   -76,   -76,   -76,   335,   139,
     453,   -76,   -76,   102,   335,   -76
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,     0,     2,
       3,     6,     5,     0,    17,     1,     4,    31,     0,    18,
       0,    26,    28,    30,     0,    16,     0,     0,     0,     7,
       0,     0,    32,    27,    28,   121,    64,     0,    57,   109,
     111,   112,     0,   110,   125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   123,     0,    14,     0,
       0,    45,    47,    48,    56,    49,    50,    51,    52,     0,
      74,    75,    79,    81,    83,    85,    87,    89,    91,    93,
      95,    97,    99,   104,     0,   106,   113,   122,   121,     0,
      29,    40,    38,    35,     0,     8,    10,    13,     0,    34,
       0,   104,     0,     0,     0,     0,   107,     0,     0,     0,
       0,    67,     0,    70,    68,    69,     0,     0,     0,    58,
      15,     0,    60,    46,    65,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   101,   102,   103,     0,    77,
      78,     0,   108,     0,     0,   116,    43,     0,    36,     0,
      12,     0,    37,    33,    53,     0,   124,     0,     0,     0,
       0,    66,     0,    55,     0,    59,     0,    82,    84,    86,
      88,    90,    92,    94,    96,    98,   100,    76,   117,   119,
     115,     0,     0,     0,    41,     9,    11,    39,   105,     0,
       0,     0,     0,    54,     0,     0,     0,   118,   114,    42,
      44,    61,    71,     0,     0,    63,    80,   120,     0,     0,
       0,    62,    72,     0,     0,    73
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   -76,   140,   -76,   -76,   -76,    21,   -76,   -18,
     -22,    -7,   -76,   142,    -2,   -76,   -76,   -75,   -76,   119,
     -43,   -76,   165,   -76,   -76,   -76,   -76,   -76,   -37,   -27,
     -76,   -28,   -76,    63,    65,    62,    70,    61,    69,    88,
     104,    60,   -76,   -66,   -29,   -76,   -76,   -76,   -76,   -76,
     -76
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    94,    95,    96,    57,    12,
      13,    14,    20,    21,    34,    23,    98,    90,   147,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
     141,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,   138,    82,    83,    84,    85,   180,   181,    86,
      87
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     104,    91,   101,   100,   109,    59,    19,    88,    97,    58,
     105,    22,   112,   106,   146,   103,    24,   123,   142,    88,
      15,    39,    37,   151,   101,   116,    27,    32,    40,    41,
      42,    43,    28,    39,    44,    59,   196,    25,    26,   120,
      40,    41,    42,    43,   143,   107,    44,   144,    28,   102,
      17,   108,    19,    18,    56,   101,   110,    30,   183,   154,
      31,   184,    91,   125,   145,   126,    56,   178,   104,   152,
     157,   158,   176,   160,   163,   135,   136,   137,   123,   113,
     117,   164,   197,   139,   140,   114,   115,   124,   166,   188,
      19,   118,   127,   129,   128,   150,    19,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   130,   182,   200,   101,
     131,   133,   132,   134,   177,   148,   179,    88,   149,   193,
      37,    89,   199,   156,    92,   153,   101,    97,   159,   161,
     162,    39,   187,   191,   192,   189,   195,   210,    40,    41,
      42,    43,   198,   212,    44,   190,   201,   202,   194,    16,
     208,   205,   209,   214,   203,   204,    91,     1,     2,     3,
       4,     5,     6,     7,    56,   211,   101,   206,    33,   207,
     186,   215,    93,   213,    35,    36,   121,    37,    27,    38,
       1,     2,     3,     4,     5,     6,     7,    29,    39,   167,
     169,   171,   168,   185,   175,    40,    41,    42,    43,   170,
     172,    44,    45,    46,    47,    48,    49,     1,     2,     3,
       4,     5,     6,     7,    50,    51,    52,    53,    54,    55,
     173,    56,    35,    36,     0,    37,    27,   119,     1,     2,
       3,     4,     5,     6,     7,     0,    39,   174,     0,     0,
       0,     0,     0,    40,    41,    42,    43,     0,     0,    44,
      45,    46,    47,    48,    49,     1,     2,     3,     4,     5,
       6,     7,    50,    51,    52,    53,    54,    55,     0,    56,
      35,    36,     0,    37,    27,   122,     0,     0,     0,     0,
       0,     0,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    40,    41,    42,    43,     0,     0,    44,    45,    46,
      47,    48,    49,     0,    35,    36,     0,    37,    27,   165,
      50,    51,    52,    53,    54,    55,     0,    56,    39,     0,
       0,     0,     0,     0,     0,    40,    41,    42,    43,     0,
       0,    44,    45,    46,    47,    48,    49,     0,    35,    36,
       0,    37,    27,     0,    50,    51,    52,    53,    54,    55,
       0,    56,    39,     0,     0,     0,     0,     0,     0,    40,
      41,    42,    43,     0,     0,    44,    45,    46,    47,    48,
      49,     0,    88,     0,     0,    37,     0,     0,    50,    51,
      52,    53,    54,    55,     0,    56,    39,     0,     0,     0,
       0,     0,     0,    40,    41,    42,    43,     0,     0,    44,
      88,     0,     0,    37,    89,     1,     2,     3,     4,     5,
       6,     7,     0,     0,    39,     0,     0,     0,     0,    56,
       0,    40,    41,    42,    43,     0,     0,    44,    88,     0,
       0,    37,     0,     0,     0,    99,     0,     0,     0,     0,
      88,   111,    39,    37,     0,     0,     0,    56,     0,    40,
      41,    42,    43,     0,    39,    44,    88,    17,     0,    37,
      18,    40,    41,    42,    43,     0,     0,    44,     0,     0,
      39,     0,     0,     0,     0,    56,     0,    40,    41,    42,
      43,     0,     0,    44,     0,     0,     0,    56,     0,     0,
       1,     2,     3,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,    56,     1,     2,     3,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,   155
};

static const yytype_int16 yycheck[] =
{
      37,    28,    31,    31,    47,    27,    13,     3,    30,    27,
       6,    13,    49,    42,    89,    37,    18,    60,    84,     3,
       0,    17,     6,     5,    53,    53,     7,    51,    24,    25,
      26,    27,    29,    17,    30,    57,     5,     4,     5,    57,
      24,    25,    26,    27,     6,     6,    30,     9,    29,    12,
       3,     6,    59,     6,    50,    84,     6,     6,     5,   102,
       9,     8,    89,    11,    26,    13,    50,    51,   105,    51,
     107,   108,   138,   110,   117,    21,    22,    23,   121,     3,
      12,   118,    51,    28,    29,     4,     4,     4,   125,   155,
      97,     6,    14,    16,    15,    97,   103,   126,   127,   128,
     129,   130,   131,   132,   133,   134,    17,   144,   183,   138,
      18,    20,    19,    27,   141,    51,   143,     3,     5,   162,
       6,     7,     8,    51,     3,    10,   155,   149,    32,     4,
      12,    17,     3,     6,     4,    51,    12,     4,    24,    25,
      26,    27,    10,     4,    30,    51,   189,   190,    51,     9,
      52,   194,    51,    51,   191,   192,   183,    36,    37,    38,
      39,    40,    41,    42,    50,   208,   195,   195,    26,   196,
     149,   214,    51,   210,     3,     4,    57,     6,     7,     8,
      36,    37,    38,    39,    40,    41,    42,    22,    17,   126,
     128,   130,   127,    49,   134,    24,    25,    26,    27,   129,
     131,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
     132,    50,     3,     4,    -1,     6,     7,     8,    36,    37,
      38,    39,    40,    41,    42,    -1,    17,   133,    -1,    -1,
      -1,    -1,    -1,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    50,
       3,     4,    -1,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,     3,     4,    -1,     6,     7,     8,
      43,    44,    45,    46,    47,    48,    -1,    50,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,     3,     4,
      -1,     6,     7,    -1,    43,    44,    45,    46,    47,    48,
      -1,    50,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,     3,    -1,    -1,     6,    -1,    -1,    43,    44,
      45,    46,    47,    48,    -1,    50,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    25,    26,    27,    -1,    -1,    30,
       3,    -1,    -1,     6,     7,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    17,    -1,    -1,    -1,    -1,    50,
      -1,    24,    25,    26,    27,    -1,    -1,    30,     3,    -1,
      -1,     6,    -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,
       3,     4,    17,     6,    -1,    -1,    -1,    50,    -1,    24,
      25,    26,    27,    -1,    17,    30,     3,     3,    -1,     6,
       6,    24,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      17,    -1,    -1,    -1,    -1,    50,    -1,    24,    25,    26,
      27,    -1,    -1,    30,    -1,    -1,    -1,    50,    -1,    -1,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    36,    37,    38,    39,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    36,    37,    38,    39,    40,    41,    42,    54,    55,
      56,    57,    62,    63,    64,     0,    56,     3,     6,    64,
      65,    66,    67,    68,    67,     4,     5,     7,    29,    75,
       6,     9,    51,    66,    67,     3,     4,     6,     8,    17,
      24,    25,    26,    27,    30,    31,    32,    33,    34,    35,
      43,    44,    45,    46,    47,    48,    50,    61,    62,    63,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    96,    97,    98,    99,   102,   103,     3,     7,
      70,    82,     3,    51,    58,    59,    60,    63,    69,    10,
      84,    97,    12,    63,    81,     6,    97,     6,     6,    73,
       6,     4,    81,     3,     4,     4,    84,    12,     6,     8,
      62,    72,     8,    73,     4,    11,    13,    14,    15,    16,
      17,    18,    19,    20,    27,    21,    22,    23,    95,    28,
      29,    83,    96,     6,     9,    26,    70,    71,    51,     5,
      67,     5,    51,    10,    73,    51,    51,    81,    81,    32,
      81,     4,    12,    73,    81,     8,    81,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    96,    82,    51,    82,
     100,   101,    81,     5,     8,    49,    60,     3,    96,    51,
      51,     6,     4,    73,    51,    12,     5,    51,    10,     8,
      70,    73,    73,    81,    81,    73,    84,    82,    52,    51,
       4,    73,     4,    81,    51,    73
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    65,    65,    66,    66,
      67,    68,    68,    68,    68,    68,    68,    68,    69,    69,
      70,    70,    70,    71,    71,    72,    72,    73,    73,    73,
      73,    73,    73,    74,    74,    74,    75,    76,    76,    76,
      76,    77,    77,    77,    78,    78,    79,    79,    79,    79,
      79,    80,    80,    80,    81,    82,    82,    83,    83,    84,
      84,    85,    85,    86,    86,    87,    87,    88,    88,    89,
      89,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    95,    95,    95,    96,    96,    97,    97,    97,    98,
      98,    98,    98,    99,    99,    99,    99,   100,   100,   101,
     101,   102,   102,   102,   102,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     3,
       1,     3,     2,     1,     1,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       1,     1,     3,     4,     3,     3,     4,     4,     1,     3,
       1,     3,     4,     1,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     3,     4,     3,     2,     1,     2,     3,
       2,     5,     7,     5,     1,     2,     3,     2,     2,     2,
       2,     5,     7,     9,     1,     1,     3,     1,     1,     1,
       5,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     4,     1,     2,     2,     1,
       1,     1,     1,     1,     4,     3,     2,     1,     2,     1,
       3,     1,     1,     1,     3,     1
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
#line 80 "../hshparser.y"
                                { g_root = (yyvsp[0].trans_unit); }
#line 1610 "hshparser.tab.cpp"
    break;

  case 3:
#line 86 "../hshparser.y"
                                    { (yyval.trans_unit) = new TranslationUnit((yyvsp[0].node)); }
#line 1616 "hshparser.tab.cpp"
    break;

  case 4:
#line 87 "../hshparser.y"
                                                    { (yyval.trans_unit)->push((yyvsp[0].node)); }
#line 1622 "hshparser.tab.cpp"
    break;

  case 5:
#line 91 "../hshparser.y"
                            { (yyval.node) = (yyvsp[0].declaration); }
#line 1628 "hshparser.tab.cpp"
    break;

  case 6:
#line 92 "../hshparser.y"
                                   { (yyval.node) = (yyvsp[0].function); }
#line 1634 "hshparser.tab.cpp"
    break;

  case 7:
#line 99 "../hshparser.y"
                { (yyval.function) = new Function((yyvsp[-1].declaration)->getId(), (yyvsp[0].statement), (yyvsp[-1].declaration)->getNext()); delete (yyvsp[-2].type); }
#line 1640 "hshparser.tab.cpp"
    break;

  case 8:
#line 103 "../hshparser.y"
                              { (yyval.declaration) = (yyvsp[0].declaration); }
#line 1646 "hshparser.tab.cpp"
    break;

  case 9:
#line 104 "../hshparser.y"
                                               { (yyval.declaration) = (yyvsp[-2].declaration); }
#line 1652 "hshparser.tab.cpp"
    break;

  case 10:
#line 107 "../hshparser.y"
                          { (yyval.declaration) = (yyvsp[0].declaration); }
#line 1658 "hshparser.tab.cpp"
    break;

  case 11:
#line 108 "../hshparser.y"
                                              { (yyvsp[0].declaration)->linkDeclaration((yyval.declaration)); (yyval.declaration) = (yyvsp[0].declaration); }
#line 1664 "hshparser.tab.cpp"
    break;

  case 12:
#line 112 "../hshparser.y"
                {
			//获得标识和类型信息
		    (yyval.declaration) = (yyvsp[0].declaration);
		    std::shared_ptr<Type> tmp_type;
		    if((yyval.declaration)->getType() == nullptr)
				tmp_type = std::make_shared<TypeContainer>();
		    else
				tmp_type = (yyval.declaration)->getType();

		    tmp_type->type((yyvsp[-1].type)->type());
		    (yyval.declaration)->setType(tmp_type);
		    delete (yyvsp[-1].type);
		}
#line 1682 "hshparser.tab.cpp"
    break;

  case 13:
#line 125 "../hshparser.y"
                                         { (yyval.declaration) = new IdentifierDeclaration(); delete (yyvsp[0].type); }
#line 1688 "hshparser.tab.cpp"
    break;

  case 14:
#line 131 "../hshparser.y"
                            { (yyval.declaration) = (yyvsp[0].declaration); }
#line 1694 "hshparser.tab.cpp"
    break;

  case 15:
#line 132 "../hshparser.y"
                                            { (yyvsp[0].declaration)->linkDeclaration((yyval.declaration)); (yyval.declaration) = (yyvsp[0].declaration); }
#line 1700 "hshparser.tab.cpp"
    break;

  case 16:
#line 136 "../hshparser.y"
                {
			//声明语句
		    (yyval.declaration) = (yyvsp[-1].declaration);
		    Declaration *tmp_decl = (yyvsp[-1].declaration);
		    std::shared_ptr<Type> tmp_type;
		    if(tmp_decl->getType() == nullptr)
				tmp_type = std::make_shared<TypeContainer>();
		    else
				tmp_type = tmp_decl->getType();
		
		    while(tmp_decl != nullptr) 
			{
				tmp_type->type((yyvsp[-2].type)->type());
				tmp_decl->setType(tmp_type);
				tmp_decl = tmp_decl->getNextListItem().get();
		    }
		    delete (yyvsp[-2].type);
		}
#line 1723 "hshparser.tab.cpp"
    break;

  case 17:
#line 157 "../hshparser.y"
                {
		    (yyval.type) = new TypeContainer();
		    setTypeInformation((yyval.type), *(yyvsp[0].string));
		    delete (yyvsp[0].string);
		}
#line 1733 "hshparser.tab.cpp"
    break;

  case 18:
#line 163 "../hshparser.y"
                { setTypeInformation((yyval.type), *(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1739 "hshparser.tab.cpp"
    break;

  case 19:
#line 167 "../hshparser.y"
                       { (yyval.string) = new std::string("void"); }
#line 1745 "hshparser.tab.cpp"
    break;

  case 20:
#line 168 "../hshparser.y"
                       { (yyval.string) = new std::string("char"); }
#line 1751 "hshparser.tab.cpp"
    break;

  case 21:
#line 169 "../hshparser.y"
                        { (yyval.string) = new std::string("short"); }
#line 1757 "hshparser.tab.cpp"
    break;

  case 22:
#line 170 "../hshparser.y"
                      { (yyval.string) = new std::string("int"); }
#line 1763 "hshparser.tab.cpp"
    break;

  case 23:
#line 171 "../hshparser.y"
                       { (yyval.string) = new std::string("long"); }
#line 1769 "hshparser.tab.cpp"
    break;

  case 24:
#line 172 "../hshparser.y"
                         { (yyval.string) = new std::string("static"); }
#line 1775 "hshparser.tab.cpp"
    break;

  case 25:
#line 173 "../hshparser.y"
                        { (yyval.string) = new std::string("const"); }
#line 1781 "hshparser.tab.cpp"
    break;

  case 26:
#line 177 "../hshparser.y"
                               { (yyval.declaration) = (yyvsp[0].declaration); }
#line 1787 "hshparser.tab.cpp"
    break;

  case 27:
#line 178 "../hshparser.y"
                                                        { (yyvsp[0].declaration)->linkListDeclaration((yyval.declaration)); (yyval.declaration) = (yyvsp[0].declaration); }
#line 1793 "hshparser.tab.cpp"
    break;

  case 28:
#line 181 "../hshparser.y"
                           { (yyval.declaration) = (yyvsp[0].declaration); }
#line 1799 "hshparser.tab.cpp"
    break;

  case 29:
#line 182 "../hshparser.y"
                                            { (yyval.declaration) = (yyvsp[-2].declaration); (yyval.declaration)->setInitializer((yyvsp[0].expression)); delete (yyvsp[-1].string); }
#line 1805 "hshparser.tab.cpp"
    break;

  case 30:
#line 185 "../hshparser.y"
                                 { (yyval.declaration) = (yyvsp[0].declaration); }
#line 1811 "hshparser.tab.cpp"
    break;

  case 31:
#line 189 "../hshparser.y"
                             { (yyval.declaration) = new IdentifierDeclaration(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1817 "hshparser.tab.cpp"
    break;

  case 32:
#line 190 "../hshparser.y"
                                       { (yyval.declaration) = (yyvsp[-1].declaration); }
#line 1823 "hshparser.tab.cpp"
    break;

  case 33:
#line 192 "../hshparser.y"
                {
			//数组，设定数组类型。
		    (yyval.declaration) = new ArrayDeclaration((yyvsp[-3].declaration), (yyvsp[-3].declaration)->getInitializer(), (yyvsp[-1].expression)->constantFold());
		    TypePtr tmp_ptr = std::make_shared<Array>((yyvsp[-1].expression)->constantFold());
		    if((yyval.declaration)->getType() == nullptr)
				(yyval.declaration)->setType(tmp_ptr);
		    else
				(yyval.declaration)->getType()->type(tmp_ptr);
		}
#line 1837 "hshparser.tab.cpp"
    break;

  case 34:
#line 202 "../hshparser.y"
                {
		    (yyval.declaration) = new ArrayDeclaration((yyvsp[-2].declaration), (yyvsp[-2].declaration)->getInitializer());
		    TypePtr tmp_ptr = std::make_shared<Array>(0);
		    if((yyval.declaration)->getType() == nullptr)
				(yyval.declaration)->setType(tmp_ptr);
		    else
				(yyval.declaration)->getType()->type(tmp_ptr);
		}
#line 1850 "hshparser.tab.cpp"
    break;

  case 35:
#line 210 "../hshparser.y"
                                             { (yyval.declaration) = (yyvsp[-2].declaration); (yyval.declaration)->setExternDeclaration(true); }
#line 1856 "hshparser.tab.cpp"
    break;

  case 36:
#line 212 "../hshparser.y"
                { (yyvsp[-3].declaration)->linkDeclaration((yyvsp[-1].declaration)); (yyval.declaration) = (yyvsp[-3].declaration); (yyval.declaration)->setExternDeclaration(true); }
#line 1862 "hshparser.tab.cpp"
    break;

  case 37:
#line 213 "../hshparser.y"
                                                            { (yyval.declaration) = (yyvsp[-3].declaration); (yyval.declaration)->setExternDeclaration(true); }
#line 1868 "hshparser.tab.cpp"
    break;

  case 38:
#line 216 "../hshparser.y"
                             { (yyval.declaration) = new IdentifierDeclaration(); }
#line 1874 "hshparser.tab.cpp"
    break;

  case 39:
#line 217 "../hshparser.y"
                                                  { (yyval.declaration) = new IdentifierDeclaration(); }
#line 1880 "hshparser.tab.cpp"
    break;

  case 40:
#line 219 "../hshparser.y"
                                     { (yyval.expression) = (yyvsp[0].expression); }
#line 1886 "hshparser.tab.cpp"
    break;

  case 41:
#line 220 "../hshparser.y"
                                            { (yyval.expression) = new Initializer((yyvsp[-1].expression)); }
#line 1892 "hshparser.tab.cpp"
    break;

  case 42:
#line 221 "../hshparser.y"
                                                  { (yyval.expression) = new Initializer((yyvsp[-2].expression)); }
#line 1898 "hshparser.tab.cpp"
    break;

  case 43:
#line 225 "../hshparser.y"
                            { (yyval.expression) = (yyvsp[0].expression); }
#line 1904 "hshparser.tab.cpp"
    break;

  case 44:
#line 226 "../hshparser.y"
                                                  { (yyvsp[0].expression)->linkExpression((yyval.expression)); (yyval.expression) = (yyvsp[0].expression); }
#line 1910 "hshparser.tab.cpp"
    break;

  case 45:
#line 231 "../hshparser.y"
                          { (yyval.statement) = (yyvsp[0].statement); }
#line 1916 "hshparser.tab.cpp"
    break;

  case 46:
#line 232 "../hshparser.y"
                                        { (yyvsp[0].statement)->linkStatement((yyval.statement)); (yyval.statement) = (yyvsp[0].statement); }
#line 1922 "hshparser.tab.cpp"
    break;

  case 47:
#line 235 "../hshparser.y"
                                 { (yyval.statement) = (yyvsp[0].statement); }
#line 1928 "hshparser.tab.cpp"
    break;

  case 48:
#line 236 "../hshparser.y"
                                  { (yyval.statement) = (yyvsp[0].statement); }
#line 1934 "hshparser.tab.cpp"
    break;

  case 49:
#line 237 "../hshparser.y"
                                   { (yyval.statement) = (yyvsp[0].statement); }
#line 1940 "hshparser.tab.cpp"
    break;

  case 50:
#line 238 "../hshparser.y"
                                    { (yyval.statement) = (yyvsp[0].statement); }
#line 1946 "hshparser.tab.cpp"
    break;

  case 51:
#line 239 "../hshparser.y"
                              { (yyval.statement) = (yyvsp[0].statement); }
#line 1952 "hshparser.tab.cpp"
    break;

  case 52:
#line 240 "../hshparser.y"
                                   { (yyval.statement) = (yyvsp[0].statement); }
#line 1958 "hshparser.tab.cpp"
    break;

  case 53:
#line 244 "../hshparser.y"
                                             { (yyval.statement) = new LabelStatement(*(yyvsp[-2].string), (yyvsp[0].statement)); }
#line 1964 "hshparser.tab.cpp"
    break;

  case 54:
#line 245 "../hshparser.y"
                                                             { (yyval.statement) = new CaseStatement((yyvsp[0].statement), (yyvsp[-2].expression)); }
#line 1970 "hshparser.tab.cpp"
    break;

  case 55:
#line 246 "../hshparser.y"
                                          { (yyval.statement) = new CaseStatement((yyvsp[0].statement), nullptr, true); }
#line 1976 "hshparser.tab.cpp"
    break;

  case 56:
#line 250 "../hshparser.y"
                                          { (yyval.statement) = (yyvsp[0].statement); }
#line 1982 "hshparser.tab.cpp"
    break;

  case 57:
#line 254 "../hshparser.y"
                      { (yyval.statement) = new CompoundStatement; }
#line 1988 "hshparser.tab.cpp"
    break;

  case 58:
#line 255 "../hshparser.y"
                                      { (yyval.statement) = new CompoundStatement((yyvsp[-1].declaration)); }
#line 1994 "hshparser.tab.cpp"
    break;

  case 59:
#line 256 "../hshparser.y"
                                                    { (yyval.statement) = new CompoundStatement((yyvsp[-2].declaration), (yyvsp[-1].statement)); }
#line 2000 "hshparser.tab.cpp"
    break;

  case 60:
#line 257 "../hshparser.y"
                                    { (yyval.statement) = new CompoundStatement((yyvsp[-1].statement)); }
#line 2006 "hshparser.tab.cpp"
    break;

  case 61:
#line 261 "../hshparser.y"
                                                      { (yyval.statement) = new IfElseStatement((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2012 "hshparser.tab.cpp"
    break;

  case 62:
#line 262 "../hshparser.y"
                                                                       { (yyval.statement) = new IfElseStatement((yyvsp[-4].expression), (yyvsp[-2].statement), (yyvsp[0].statement)); }
#line 2018 "hshparser.tab.cpp"
    break;

  case 63:
#line 263 "../hshparser.y"
                                                          { (yyval.statement) = new SwitchStatement((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2024 "hshparser.tab.cpp"
    break;

  case 64:
#line 267 "../hshparser.y"
                     { (yyval.statement) = new ExpressionStatement(); }
#line 2030 "hshparser.tab.cpp"
    break;

  case 65:
#line 268 "../hshparser.y"
                        { (yyval.statement) = new ExpressionStatement((yyvsp[-1].expression)); }
#line 2036 "hshparser.tab.cpp"
    break;

  case 66:
#line 271 "../hshparser.y"
                                         { (yyval.statement) = new ReturnStatement((yyvsp[-1].expression)); }
#line 2042 "hshparser.tab.cpp"
    break;

  case 67:
#line 272 "../hshparser.y"
                              { (yyval.statement) = new ReturnStatement(); }
#line 2048 "hshparser.tab.cpp"
    break;

  case 68:
#line 273 "../hshparser.y"
                             { (yyval.statement) = new BreakStatement(); }
#line 2054 "hshparser.tab.cpp"
    break;

  case 69:
#line 274 "../hshparser.y"
                                { (yyval.statement) = new ContinueStatement(); }
#line 2060 "hshparser.tab.cpp"
    break;

  case 70:
#line 275 "../hshparser.y"
                                    { (yyval.statement) = new GotoStatement(*(yyvsp[0].string)); }
#line 2066 "hshparser.tab.cpp"
    break;

  case 71:
#line 279 "../hshparser.y"
                                                         { (yyval.statement) = new WhileLoop((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2072 "hshparser.tab.cpp"
    break;

  case 72:
#line 281 "../hshparser.y"
                { (yyval.statement) = new WhileLoop((yyvsp[-2].expression), (yyvsp[-5].statement), false); }
#line 2078 "hshparser.tab.cpp"
    break;

  case 73:
#line 283 "../hshparser.y"
                { (yyval.statement) = new ForLoop((yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2084 "hshparser.tab.cpp"
    break;

  case 74:
#line 288 "../hshparser.y"
                                     { (yyval.expression) = (yyvsp[0].expression); }
#line 2090 "hshparser.tab.cpp"
    break;

  case 75:
#line 292 "../hshparser.y"
                                      { (yyval.expression) = (yyvsp[0].expression); }
#line 2096 "hshparser.tab.cpp"
    break;

  case 76:
#line 294 "../hshparser.y"
                {
		    OperationExpression* tmp;
		    if(*(yyvsp[-1].string) == "=") 
			{
				(yyval.expression) = new AssignmentExpression((yyvsp[-2].expression), (yyvsp[0].expression));
		    } 
			else if(*(yyvsp[-1].string) == "+=") 
			{
				tmp = new AdditiveExpression((yyvsp[-2].expression), "+", (yyvsp[0].expression));
				(yyval.expression) = new AssignmentExpression(tmp->getLhs(), tmp);
		    } 
			else if(*(yyvsp[-1].string) == "-=") 
			{
				tmp = new AdditiveExpression((yyvsp[-2].expression), "-", (yyvsp[0].expression));
				(yyval.expression) = new AssignmentExpression(tmp->getLhs(), tmp);
		    } 
			else if(*(yyvsp[-1].string) == "*=") 
			{
				tmp = new MultiplicativeExpression((yyvsp[-2].expression), "*", (yyvsp[0].expression));
				(yyval.expression) = new AssignmentExpression(tmp->getLhs(), tmp);
		    } 
			else if(*(yyvsp[-1].string) == "/=") 
			{
				tmp = new MultiplicativeExpression((yyvsp[-2].expression), "/", (yyvsp[0].expression));
				(yyval.expression) = new AssignmentExpression(tmp->getLhs(), tmp);
		    } 
			else if(*(yyvsp[-1].string) == "%=") 
			{
				tmp = new MultiplicativeExpression((yyvsp[-2].expression), "%", (yyvsp[0].expression));
				(yyval.expression) = new AssignmentExpression(tmp->getLhs(), tmp);
		    } 
			else if(*(yyvsp[-1].string) == "&=") 
			{
				tmp = new AndExpression((yyvsp[-2].expression), (yyvsp[0].expression));
				(yyval.expression) = new AssignmentExpression(tmp->getLhs(), tmp);
		    } 
			else if(*(yyvsp[-1].string) == "^=") 
			{
				tmp = new ExclusiveOrExpression((yyvsp[-2].expression), (yyvsp[0].expression));
				(yyval.expression) = new AssignmentExpression(tmp->getLhs(), tmp);
		    }
			else if(*(yyvsp[-1].string) == "|=") 
			{
				tmp = new InclusiveOrExpression((yyvsp[-2].expression), (yyvsp[0].expression));
				(yyval.expression) = new AssignmentExpression(tmp->getLhs(), tmp);
		    } 
			else if(*(yyvsp[-1].string) == "<<=")
			{
				tmp = new ShiftExpression((yyvsp[-2].expression), "<<", (yyvsp[0].expression));
				(yyval.expression) = new AssignmentExpression(tmp->getLhs(), tmp);
		    } 
			else 
			{
				tmp = new ShiftExpression((yyvsp[-2].expression), ">>", (yyvsp[0].expression));
				(yyval.expression) = new AssignmentExpression(tmp->getLhs(), tmp);
		    }
		    
		    delete (yyvsp[-1].string);
		}
#line 2160 "hshparser.tab.cpp"
    break;

  case 77:
#line 355 "../hshparser.y"
                              { ; }
#line 2166 "hshparser.tab.cpp"
    break;

  case 78:
#line 356 "../hshparser.y"
                     { ; }
#line 2172 "hshparser.tab.cpp"
    break;

  case 79:
#line 360 "../hshparser.y"
                                    { (yyval.expression) = (yyvsp[0].expression); }
#line 2178 "hshparser.tab.cpp"
    break;

  case 80:
#line 362 "../hshparser.y"
                { (yyval.expression) = new ConditionalExpression((yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2184 "hshparser.tab.cpp"
    break;

  case 81:
#line 366 "../hshparser.y"
                                     { (yyval.expression) = (yyvsp[0].expression); }
#line 2190 "hshparser.tab.cpp"
    break;

  case 82:
#line 367 "../hshparser.y"
                                                                  { (yyval.expression) = new LogicalOrExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2196 "hshparser.tab.cpp"
    break;

  case 83:
#line 371 "../hshparser.y"
                                      { (yyval.expression) = (yyvsp[0].expression); }
#line 2202 "hshparser.tab.cpp"
    break;

  case 84:
#line 372 "../hshparser.y"
                                                                     { (yyval.expression) = new LogicalAndExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2208 "hshparser.tab.cpp"
    break;

  case 85:
#line 376 "../hshparser.y"
                                      { (yyval.expression) = (yyvsp[0].expression); }
#line 2214 "hshparser.tab.cpp"
    break;

  case 86:
#line 377 "../hshparser.y"
                                                                 { (yyval.expression) = new InclusiveOrExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2220 "hshparser.tab.cpp"
    break;

  case 87:
#line 381 "../hshparser.y"
                              { (yyval.expression) = (yyvsp[0].expression); }
#line 2226 "hshparser.tab.cpp"
    break;

  case 88:
#line 382 "../hshparser.y"
                                                          { (yyval.expression) = new ExclusiveOrExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2232 "hshparser.tab.cpp"
    break;

  case 89:
#line 385 "../hshparser.y"
                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 2238 "hshparser.tab.cpp"
    break;

  case 90:
#line 386 "../hshparser.y"
                                                       { (yyval.expression) = new AndExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2244 "hshparser.tab.cpp"
    break;

  case 91:
#line 390 "../hshparser.y"
                                     { (yyval.expression) = (yyvsp[0].expression); }
#line 2250 "hshparser.tab.cpp"
    break;

  case 92:
#line 392 "../hshparser.y"
                { (yyval.expression) = new EqualityExpression((yyvsp[-2].expression), *(yyvsp[-1].string), (yyvsp[0].expression)); delete (yyvsp[-1].string); }
#line 2256 "hshparser.tab.cpp"
    break;

  case 93:
#line 396 "../hshparser.y"
                                { (yyval.expression) = (yyvsp[0].expression); }
#line 2262 "hshparser.tab.cpp"
    break;

  case 94:
#line 398 "../hshparser.y"
                { (yyval.expression) = new RelationalExpression((yyvsp[-2].expression), *(yyvsp[-1].string), (yyvsp[0].expression)); delete (yyvsp[-1].string); }
#line 2268 "hshparser.tab.cpp"
    break;

  case 95:
#line 402 "../hshparser.y"
                                   { (yyval.expression) = (yyvsp[0].expression); }
#line 2274 "hshparser.tab.cpp"
    break;

  case 96:
#line 404 "../hshparser.y"
                { (yyval.expression) = new ShiftExpression((yyvsp[-2].expression), *(yyvsp[-1].string), (yyvsp[0].expression)); }
#line 2280 "hshparser.tab.cpp"
    break;

  case 97:
#line 408 "../hshparser.y"
                                         { (yyval.expression) = (yyvsp[0].expression); }
#line 2286 "hshparser.tab.cpp"
    break;

  case 98:
#line 410 "../hshparser.y"
                { (yyval.expression) = new AdditiveExpression((yyvsp[-2].expression), *(yyvsp[-1].string), (yyvsp[0].expression)); delete (yyvsp[-1].string); }
#line 2292 "hshparser.tab.cpp"
    break;

  case 99:
#line 414 "../hshparser.y"
                               { (yyval.expression) = (yyvsp[0].expression); }
#line 2298 "hshparser.tab.cpp"
    break;

  case 100:
#line 416 "../hshparser.y"
                { (yyval.expression) = new MultiplicativeExpression((yyvsp[-2].expression), *(yyvsp[-1].string), (yyvsp[0].expression)); delete (yyvsp[-1].string); }
#line 2304 "hshparser.tab.cpp"
    break;

  case 101:
#line 419 "../hshparser.y"
                       { (yyval.string) = (yyvsp[0].string); }
#line 2310 "hshparser.tab.cpp"
    break;

  case 102:
#line 420 "../hshparser.y"
                      { (yyval.string) = (yyvsp[0].string); }
#line 2316 "hshparser.tab.cpp"
    break;

  case 103:
#line 421 "../hshparser.y"
                      { (yyval.string) = (yyvsp[0].string); }
#line 2322 "hshparser.tab.cpp"
    break;

  case 104:
#line 424 "../hshparser.y"
                                { (yyval.expression) = (yyvsp[0].expression); }
#line 2328 "hshparser.tab.cpp"
    break;

  case 105:
#line 426 "../hshparser.y"
                { new CastExpression((yyvsp[-2].type), (yyvsp[0].expression)); delete (yyvsp[-2].type); }
#line 2334 "hshparser.tab.cpp"
    break;

  case 106:
#line 430 "../hshparser.y"
                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 2340 "hshparser.tab.cpp"
    break;

  case 107:
#line 431 "../hshparser.y"
                                         { (yyval.expression) = new UnaryPreIncDecExpression(*(yyvsp[-1].string), (yyvsp[0].expression)); delete (yyvsp[-1].string); }
#line 2346 "hshparser.tab.cpp"
    break;

  case 108:
#line 432 "../hshparser.y"
                                             { (yyval.expression) = new OperatorUnaryExpression(*(yyvsp[-1].string), (yyvsp[0].expression)); delete (yyvsp[-1].string); }
#line 2352 "hshparser.tab.cpp"
    break;

  case 109:
#line 435 "../hshparser.y"
                      { (yyval.string) = (yyvsp[0].string); }
#line 2358 "hshparser.tab.cpp"
    break;

  case 110:
#line 436 "../hshparser.y"
                            { (yyval.string) = (yyvsp[0].string); }
#line 2364 "hshparser.tab.cpp"
    break;

  case 111:
#line 437 "../hshparser.y"
                        { (yyval.string) = (yyvsp[0].string); }
#line 2370 "hshparser.tab.cpp"
    break;

  case 112:
#line 438 "../hshparser.y"
                      { (yyval.string) = (yyvsp[0].string); }
#line 2376 "hshparser.tab.cpp"
    break;

  case 113:
#line 442 "../hshparser.y"
                                  { (yyval.expression) = (yyvsp[0].expression); }
#line 2382 "hshparser.tab.cpp"
    break;

  case 114:
#line 443 "../hshparser.y"
                                                         { (yyval.expression) = new PostfixArrayElement((yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 2388 "hshparser.tab.cpp"
    break;

  case 115:
#line 445 "../hshparser.y"
                {
		    (yyval.expression) = (yyvsp[0].expression);
		    PostfixFunctionCall *tmp = dynamic_cast<PostfixFunctionCall *>((yyval.expression));
		    if(tmp != nullptr)
				tmp->setPostfixExpression((yyvsp[-2].expression));
		}
#line 2399 "hshparser.tab.cpp"
    break;

  case 116:
#line 452 "../hshparser.y"
                { (yyval.expression) = new PostfixPostIncDecExpression(*(yyvsp[0].string), (yyvsp[-1].expression)); delete (yyvsp[0].string); }
#line 2405 "hshparser.tab.cpp"
    break;

  case 117:
#line 456 "../hshparser.y"
                      { (yyval.expression) = new PostfixFunctionCall(); }
#line 2411 "hshparser.tab.cpp"
    break;

  case 118:
#line 457 "../hshparser.y"
                                             { (yyval.expression) = new PostfixFunctionCall((yyvsp[-1].expression)); }
#line 2417 "hshparser.tab.cpp"
    break;

  case 119:
#line 461 "../hshparser.y"
                                     { (yyval.expression) = (yyvsp[0].expression); }
#line 2423 "hshparser.tab.cpp"
    break;

  case 120:
#line 462 "../hshparser.y"
                                                                  { (yyvsp[0].expression)->linkExpression((yyval.expression));(yyval.expression) = (yyvsp[0].expression); }
#line 2429 "hshparser.tab.cpp"
    break;

  case 121:
#line 466 "../hshparser.y"
                             { (yyval.expression) = new Identifier(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2435 "hshparser.tab.cpp"
    break;

  case 122:
#line 467 "../hshparser.y"
                         { (yyval.expression) = (yyvsp[0].expression); }
#line 2441 "hshparser.tab.cpp"
    break;

  case 123:
#line 468 "../hshparser.y"
                                { (yyval.expression) = new StringLiteral(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2447 "hshparser.tab.cpp"
    break;

  case 124:
#line 469 "../hshparser.y"
                                       { (yyval.expression) = (yyvsp[-1].expression); }
#line 2453 "hshparser.tab.cpp"
    break;

  case 125:
#line 472 "../hshparser.y"
                            { (yyval.expression) = new Constant((yyvsp[0].number)); }
#line 2459 "hshparser.tab.cpp"
    break;


#line 2463 "hshparser.tab.cpp"

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
#line 475 "../hshparser.y"


Node* g_root;

Node* parseAST()
{
    g_root = 0;
    yyparse();
    return g_root;
}

void setTypeInformation(Type* type_ptr, std::string type_str)
{
    if(type_str == "void") 
	{
		type_ptr->type(new Void());
    } 
	else if(type_str == "char") 
	{
		type_ptr->type(new Char());
    }
	else if(type_str == "short") 
	{
		type_ptr->type(new Short());
    }
	else if(type_str == "int") 
	{
		if(type_ptr->type() == nullptr)
	    	type_ptr->type(new Int());
    } 
	else if(type_str == "long") {
		type_ptr->type(new Int());
    } 
	else if(type_str == "static") 
	{
		if(type_ptr == nullptr)
	    type_ptr->type(new Int());
		type_ptr->setStatic(true);
    } 
	else if(type_str == "const") 
	{
		if(type_ptr == nullptr)
	    	type_ptr->type(new Int());
		type_ptr->setConst(true);
    } 
	else 
	{
			
    }
}
