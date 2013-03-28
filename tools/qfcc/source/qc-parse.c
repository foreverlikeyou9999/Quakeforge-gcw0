/* A Bison parser, made by GNU Bison 2.6.2.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.6.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         QC_YYSTYPE
/* Substitute the variable and function names.  */
#define yyparse         qc_yyparse
#define yylex           qc_yylex
#define yyerror         qc_yyerror
#define yylval          qc_yylval
#define yychar          qc_yychar
#define yydebug         qc_yydebug
#define yynerrs         qc_yynerrs

/* Copy the first part of user declarations.  */
/* Line 336 of yacc.c  */
#line 1 "../../../../tools/qfcc/source/qc-parse.y"

/*
	qc-parse.y

	parser for quakec

	Copyright (C) 2001 Bill Currie <bill@taniwha.org>

	Author: Bill Currie <bill@taniwha.org>
	Date: 2001/06/12

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to:

		Free Software Foundation, Inc.
		59 Temple Place - Suite 330
		Boston, MA  02111-1307, USA

*/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif
#include <stdlib.h>

#include <QF/hash.h>
#include <QF/sys.h>

#include "class.h"
#include "debug.h"
#include "def.h"
#include "diagnostic.h"
#include "emit.h"
#include "expr.h"
#include "function.h"
#include "method.h"
#include "options.h"
#include "qfcc.h"
#include "reloc.h"
#include "shared.h"
#include "strpool.h"
#include "struct.h"
#include "switch.h"
#include "symtab.h"
#include "type.h"
#include "value.h"

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#undef YYERROR_VERBOSE

extern char *qc_yytext;

static void
yyerror (const char *s)
{
#ifdef YYERROR_VERBOSE
	error (0, "%s %s\n", qc_yytext, s);
#else
	error (0, "%s before %s", s, qc_yytext);
#endif
}

static void
parse_error (void)
{
	error (0, "parse error before %s", qc_yytext);
}

#define PARSE_ERROR do { parse_error (); YYERROR; } while (0)

int yylex (void);


/* Line 336 of yacc.c  */
#line 168 "qc-parse.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "qc-parse.h".  */
#ifndef QC_YY_QC_PARSE_H
# define QC_YY_QC_PARSE_H
/* Enabling traces.  */
#ifndef QC_YYDEBUG
# if defined YYDEBUG
#  if YYDEBUG
#   define QC_YYDEBUG 1
#  else
#   define QC_YYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define QC_YYDEBUG 0
# endif /* ! defined QC_YYDEBUG */
#endif  /* ! defined QC_YYDEBUG */
#if QC_YYDEBUG
extern int qc_yydebug;
#endif

/* Tokens.  */
#ifndef QC_YYTOKENTYPE
# define QC_YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum qc_yytokentype {
     LOW = 258,
     IFX = 259,
     ELSE = 260,
     BREAK_PRIMARY = 261,
     CLASS_NOT_CATEGORY = 262,
     STORAGEX = 263,
     COMMA = 264,
     PAS = 265,
     ASX = 266,
     OR = 267,
     AND = 268,
     NE = 269,
     EQ = 270,
     GT = 271,
     LT = 272,
     GE = 273,
     LE = 274,
     SHR = 275,
     SHL = 276,
     INCOP = 277,
     UNARY = 278,
     SIZEOF = 279,
     HYPERUNARY = 280,
     CLASS_NAME = 281,
     NAME = 282,
     VALUE = 283,
     STRING = 284,
     LOCAL = 285,
     RETURN = 286,
     WHILE = 287,
     DO = 288,
     IF = 289,
     FOR = 290,
     BREAK = 291,
     CONTINUE = 292,
     ELLIPSIS = 293,
     NIL = 294,
     IFBE = 295,
     IFB = 296,
     IFAE = 297,
     IFA = 298,
     SWITCH = 299,
     CASE = 300,
     DEFAULT = 301,
     ENUM = 302,
     TYPEDEF = 303,
     ARGS = 304,
     EXTERN = 305,
     STATIC = 306,
     SYSTEM = 307,
     NOSAVE = 308,
     OVERLOAD = 309,
     STRUCT = 310,
     TYPE = 311,
     OBJECT = 312,
     TYPE_NAME = 313,
     CLASS = 314,
     DEFS = 315,
     ENCODE = 316,
     END = 317,
     IMPLEMENTATION = 318,
     INTERFACE = 319,
     PRIVATE = 320,
     PROTECTED = 321,
     PROTOCOL = 322,
     PUBLIC = 323,
     SELECTOR = 324,
     REFERENCE = 325,
     SELF = 326,
     THIS = 327
   };
#endif
/* Tokens.  */
#define LOW 258
#define IFX 259
#define ELSE 260
#define BREAK_PRIMARY 261
#define CLASS_NOT_CATEGORY 262
#define STORAGEX 263
#define COMMA 264
#define PAS 265
#define ASX 266
#define OR 267
#define AND 268
#define NE 269
#define EQ 270
#define GT 271
#define LT 272
#define GE 273
#define LE 274
#define SHR 275
#define SHL 276
#define INCOP 277
#define UNARY 278
#define SIZEOF 279
#define HYPERUNARY 280
#define CLASS_NAME 281
#define NAME 282
#define VALUE 283
#define STRING 284
#define LOCAL 285
#define RETURN 286
#define WHILE 287
#define DO 288
#define IF 289
#define FOR 290
#define BREAK 291
#define CONTINUE 292
#define ELLIPSIS 293
#define NIL 294
#define IFBE 295
#define IFB 296
#define IFAE 297
#define IFA 298
#define SWITCH 299
#define CASE 300
#define DEFAULT 301
#define ENUM 302
#define TYPEDEF 303
#define ARGS 304
#define EXTERN 305
#define STATIC 306
#define SYSTEM 307
#define NOSAVE 308
#define OVERLOAD 309
#define STRUCT 310
#define TYPE 311
#define OBJECT 312
#define TYPE_NAME 313
#define CLASS 314
#define DEFS 315
#define ENCODE 316
#define END 317
#define IMPLEMENTATION 318
#define INTERFACE 319
#define PRIVATE 320
#define PROTECTED 321
#define PROTOCOL 322
#define PUBLIC 323
#define SELECTOR 324
#define REFERENCE 325
#define SELF 326
#define THIS 327



#if ! defined QC_YYSTYPE && ! defined QC_YYSTYPE_IS_DECLARED
typedef union QC_YYSTYPE
{
/* Line 350 of yacc.c  */
#line 93 "../../../../tools/qfcc/source/qc-parse.y"

	int			op;
	int         size;
	specifier_t spec;
	void       *pointer;			// for ensuring pointer values are null
	struct type_s	*type;
	struct expr_s	*expr;
	struct function_s *function;
	struct switch_block_s *switch_block;
	struct param_s	*param;
	struct method_s	*method;
	struct class_s	*class;
	struct category_s *category;
	struct class_type_s	*class_type;
	struct protocol_s *protocol;
	struct protocollist_s *protocol_list;
	struct keywordarg_s *keywordarg;
	struct methodlist_s *methodlist;
	struct symbol_s *symbol;
	struct symtab_s *symtab;


/* Line 350 of yacc.c  */
#line 386 "qc-parse.c"
} QC_YYSTYPE;
# define QC_YYSTYPE_IS_TRIVIAL 1
# define qc_yystype QC_YYSTYPE /* obsolescent; will be withdrawn */
# define QC_YYSTYPE_IS_DECLARED 1
#endif

extern QC_YYSTYPE qc_yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int qc_yyparse (void *YYPARSE_PARAM);
#else
int qc_yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int qc_yyparse (void);
#else
int qc_yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !QC_YY_QC_PARSE_H  */

/* Copy the second part of user declarations.  */
/* Line 353 of yacc.c  */
#line 210 "../../../../tools/qfcc/source/qc-parse.y"


static switch_block_t *switch_block;
static expr_t *break_label;
static expr_t *continue_label;

static specifier_t
make_spec (type_t *type, storage_class_t storage, int is_typedef,
		   int is_overload)
{
	specifier_t spec;

	memset (&spec, 0, sizeof (spec));
	spec.type = type;
	spec.storage = storage;
	spec.is_typedef = is_typedef;
	spec.is_overload = is_overload;
	if (spec.storage && spec.is_typedef)
		internal_error (0, "setting both storage and is_typedef");
	return spec;
}

static specifier_t
spec_merge (specifier_t spec, specifier_t new)
{
	if (new.type) {
		if (spec.type && !spec.multi_type) {
			error (0, "two or more data types in declaration specifiers");
			spec.multi_type = 1;
		}
		spec.type = new.type;
	}
	if (new.is_typedef || new.storage) {
		if ((spec.is_typedef || spec.storage) && !spec.multi_store) {
			error (0, "multiple storage classes in declaration specifiers");
			spec.multi_store = 1;
		}
		spec.storage = new.storage;
		spec.is_typedef = new.is_typedef;
	}
	spec.is_overload |= new.is_overload;
	spec.nosave |= new.nosave;
	return spec;
}


/* Line 353 of yacc.c  */
#line 461 "qc-parse.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined QC_YYSTYPE_IS_TRIVIAL && QC_YYSTYPE_IS_TRIVIAL)))

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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1725

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  173
/* YYNRULES -- Number of rules.  */
#define YYNRULES  391
/* YYNRULES -- Number of states.  */
#define YYNSTATES  655

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    94,     2,    90,     2,    33,    20,     2,
      39,    92,    31,    29,    91,    30,    38,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    15,     7,
       2,    11,     2,    14,    96,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    93,    19,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,    18,    88,    95,     2,     2,     2,
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
       5,     6,     8,     9,    10,    12,    13,    16,    17,    21,
      22,    23,    24,    25,    26,    27,    28,    34,    35,    36,
      37,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87
};

#if QC_YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    15,    18,    21,
      25,    28,    29,    34,    38,    39,    47,    48,    49,    50,
      56,    61,    63,    64,    69,    71,    74,    76,    78,    80,
      82,    84,    86,    88,    90,    91,    93,    96,    98,   101,
     103,   105,   107,   109,   111,   113,   116,   119,   122,   124,
     125,   127,   131,   134,   136,   137,   143,   144,   146,   147,
     152,   154,   158,   159,   166,   169,   172,   177,   179,   183,
     186,   188,   189,   194,   196,   198,   200,   204,   207,   209,
     211,   214,   217,   220,   224,   227,   230,   234,   237,   240,
     243,   248,   251,   256,   261,   262,   264,   268,   270,   274,
     277,   279,   281,   284,   287,   291,   293,   294,   299,   302,
     305,   309,   313,   316,   319,   321,   323,   324,   329,   332,
     334,   335,   339,   340,   345,   347,   349,   352,   356,   358,
     362,   364,   366,   369,   372,   374,   376,   378,   381,   384,
     386,   390,   393,   394,   395,   401,   402,   404,   407,   413,
     414,   421,   423,   427,   430,   431,   433,   437,   442,   444,
     445,   447,   448,   453,   454,   457,   458,   463,   465,   468,
     470,   472,   476,   479,   482,   486,   489,   497,   503,   511,
     523,   531,   541,   544,   546,   547,   548,   549,   550,   552,
     553,   555,   557,   559,   561,   563,   567,   572,   577,   581,
     584,   587,   590,   593,   596,   599,   602,   605,   608,   613,
     615,   620,   622,   624,   628,   632,   638,   643,   648,   652,
     656,   660,   664,   668,   672,   676,   680,   684,   688,   692,
     696,   700,   704,   708,   712,   714,   716,   717,   719,   721,
     725,   727,   729,   731,   733,   736,   738,   740,   742,   744,
     746,   748,   750,   751,   754,   756,   758,   762,   766,   768,
     770,   774,   778,   783,   788,   790,   795,   797,   798,   799,
     800,   801,   814,   815,   816,   817,   826,   827,   828,   829,
     830,   843,   844,   845,   846,   855,   856,   857,   865,   866,
     867,   875,   878,   879,   880,   888,   891,   894,   898,   902,
     903,   904,   905,   914,   915,   916,   921,   923,   927,   928,
     931,   935,   937,   939,   941,   943,   944,   948,   951,   953,
     954,   959,   960,   961,   969,   976,   978,   980,   981,   983,
     984,   987,   990,   994,   998,  1003,  1005,  1011,  1014,  1015,
    1018,  1021,  1026,  1028,  1030,  1033,  1035,  1037,  1039,  1041,
    1043,  1045,  1047,  1049,  1051,  1053,  1055,  1057,  1059,  1061,
    1063,  1065,  1067,  1069,  1071,  1073,  1075,  1077,  1084,  1088,
    1094,  1097,  1099,  1104,  1109,  1114,  1116,  1121,  1123,  1125,
    1127,  1129,  1131,  1134,  1138,  1141,  1143,  1145,  1147,  1150,
    1153,  1155
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      98,     0,    -1,    99,    -1,    -1,    99,   100,    -1,    99,
     196,    -1,     1,    77,    -1,     1,     7,    -1,     1,    88,
      -1,   111,   107,     7,    -1,   111,     7,    -1,    -1,   111,
     137,   101,   155,    -1,   111,   135,   104,    -1,    -1,   110,
      89,   103,   102,    99,    88,     7,    -1,    -1,    -1,    -1,
     168,   105,   103,   106,   174,    -1,    11,    90,   188,     7,
      -1,   109,    -1,    -1,   107,    91,   108,   109,    -1,   134,
      -1,   134,   167,    -1,   135,    -1,    65,    -1,    66,    -1,
      67,    -1,    63,    -1,    69,    -1,    68,    -1,   112,    -1,
      -1,   114,    -1,   112,   114,    -1,   115,    -1,   113,   115,
      -1,   115,    -1,   110,    -1,    71,    -1,   118,    -1,   125,
      -1,    73,    -1,    72,   234,    -1,    41,   234,    -1,    38,
     115,    -1,   117,    -1,    -1,    42,    -1,    62,   117,   119,
      -1,    62,   120,    -1,   120,    -1,    -1,    89,   121,   122,
     173,    88,    -1,    -1,   124,    -1,    -1,   122,    91,   123,
     124,    -1,   195,    -1,   195,    11,   189,    -1,    -1,    70,
     116,    89,   126,   127,    88,    -1,    70,   117,    -1,   128,
       7,    -1,    75,    39,   195,    92,    -1,   129,    -1,   128,
       7,   129,    -1,   113,   130,    -1,   113,    -1,    -1,   130,
      91,   131,   132,    -1,   132,    -1,   135,    -1,   134,    -1,
     134,    15,   188,    -1,    15,   188,    -1,    42,    -1,   133,
      -1,   134,   136,    -1,   134,   145,    -1,    31,   134,    -1,
      39,   134,    92,    -1,    31,   135,    -1,   135,   145,    -1,
      39,   135,    92,    -1,   135,   136,    -1,    42,   136,    -1,
      39,    92,    -1,    39,   138,   139,    92,    -1,    39,    92,
      -1,    39,   138,   140,    92,    -1,    39,   138,    71,    92,
      -1,    -1,   141,    -1,   139,    91,   141,    -1,   143,    -1,
     140,    91,   143,    -1,   113,   134,    -1,   142,    -1,    53,
      -1,   113,   144,    -1,   113,   133,    -1,   113,   137,   133,
      -1,    53,    -1,    -1,    39,   144,    92,   136,    -1,    31,
     144,    -1,   144,   145,    -1,    39,   144,    92,    -1,    40,
     189,    93,    -1,    40,    93,    -1,    45,   112,    -1,   112,
      -1,   149,    -1,    -1,   147,    91,   148,   149,    -1,   113,
     195,    -1,   152,    -1,    -1,   137,   151,   156,    -1,    -1,
     152,    91,   153,   154,    -1,   154,    -1,   135,    -1,   134,
     166,    -1,   156,   157,   158,    -1,   158,    -1,   156,   157,
     159,    -1,   159,    -1,    91,    -1,   161,     7,    -1,   160,
       7,    -1,   160,    -1,   161,    -1,   160,    -1,   162,   164,
      -1,   162,   163,    -1,   195,    -1,    11,    90,   189,    -1,
      11,   189,    -1,    -1,    -1,    11,   168,   103,   165,   174,
      -1,    -1,   167,    -1,    11,   189,    -1,    11,    89,   171,
     173,    88,    -1,    -1,    40,   189,    91,   169,   170,    93,
      -1,   195,    -1,    39,   189,    92,    -1,    91,   189,    -1,
      -1,   172,    -1,   171,    91,   172,    -1,    89,   171,   173,
      88,    -1,   189,    -1,    -1,    91,    -1,    -1,    89,   175,
     176,    88,    -1,    -1,   176,   179,    -1,    -1,   146,   178,
     150,     7,    -1,     7,    -1,     1,     7,    -1,   174,    -1,
     177,    -1,    46,   185,     7,    -1,    51,     7,    -1,    52,
       7,    -1,    60,   189,    15,    -1,    61,    15,    -1,    59,
     182,    39,   189,   184,    92,   174,    -1,    49,    39,   190,
      92,   179,    -1,    49,    39,   190,    92,   179,   180,   179,
      -1,    50,   182,   183,    39,   185,     7,   185,     7,   185,
      92,   179,    -1,    47,   182,   183,    39,   190,    92,   179,
      -1,    48,   182,   183,   179,    47,    39,   190,    92,     7,
      -1,   189,     7,    -1,     5,    -1,    -1,    -1,    -1,    -1,
     189,    -1,    -1,    42,    -1,    64,    -1,    86,    -1,    87,
      -1,   193,    -1,    39,   188,    92,    -1,   186,    39,   191,
      92,    -1,   186,    40,   188,    93,    -1,   186,    38,   186,
      -1,    34,   186,    -1,   186,    34,    -1,    29,   187,    -1,
      30,   187,    -1,    94,   187,    -1,    95,   187,    -1,    20,
     187,    -1,    31,   187,    -1,    36,   186,    -1,    36,    39,
     142,    92,    -1,   260,    -1,    39,   142,    92,   187,    -1,
     186,    -1,   187,    -1,   188,    11,   188,    -1,   188,    13,
     188,    -1,   188,    14,   188,    15,   188,    -1,   188,    17,
     181,   188,    -1,   188,    16,   181,   188,    -1,   188,    22,
     188,    -1,   188,    21,   188,    -1,   188,    26,   188,    -1,
     188,    25,   188,    -1,   188,    24,   188,    -1,   188,    23,
     188,    -1,   188,    28,   188,    -1,   188,    27,   188,    -1,
     188,    29,   188,    -1,   188,    30,   188,    -1,   188,    31,
     188,    -1,   188,    32,   188,    -1,   188,    20,   188,    -1,
     188,    18,   188,    -1,   188,    19,   188,    -1,   188,    33,
     188,    -1,   188,    -1,   189,    -1,    -1,   192,    -1,   189,
      -1,   192,    91,   189,    -1,    43,    -1,    54,    -1,   194,
      -1,    44,    -1,   194,    44,    -1,    42,    -1,    72,    -1,
      41,    -1,    73,    -1,   209,    -1,   199,    -1,   230,    -1,
      -1,   197,   245,    -1,    77,    -1,   195,    -1,   198,    91,
     195,    -1,    74,   198,     7,    -1,   195,    -1,   195,    -1,
     200,    15,   200,    -1,   201,    15,   200,    -1,   195,    39,
     195,    92,    -1,   195,    39,   195,    92,    -1,   195,    -1,
     195,    39,   195,    92,    -1,   195,    -1,    -1,    -1,    -1,
      -1,    79,   201,   234,   210,    89,   211,   237,    88,   212,
     249,   213,    77,    -1,    -1,    -1,    -1,    79,   201,   234,
     214,   215,   249,   216,    77,    -1,    -1,    -1,    -1,    -1,
      79,   203,   234,   217,    89,   218,   237,    88,   219,   249,
     220,    77,    -1,    -1,    -1,    -1,    79,   203,   234,   221,
     222,   249,   223,    77,    -1,    -1,    -1,    79,   205,   234,
     224,   249,   225,    77,    -1,    -1,    -1,    78,   200,   226,
      89,   227,   237,    88,    -1,    78,   200,    -1,    -1,    -1,
      78,   202,   228,    89,   229,   237,    88,    -1,    78,   202,
      -1,    78,   204,    -1,    85,   206,     7,    -1,    85,   207,
       7,    -1,    -1,    -1,    -1,    82,   231,   208,   234,   232,
     249,   233,    77,    -1,    -1,    -1,    24,   235,   236,    23,
      -1,   195,    -1,   236,    91,   195,    -1,    -1,   238,   239,
      -1,   239,   240,   241,    -1,   241,    -1,    80,    -1,    81,
      -1,    83,    -1,    -1,   241,   242,     7,    -1,   113,   243,
      -1,   132,    -1,    -1,   243,    91,   244,   132,    -1,    -1,
      -1,   248,   253,   168,   246,   103,   247,   174,    -1,   248,
     253,    11,    90,   193,     7,    -1,    29,    -1,    30,    -1,
      -1,   250,    -1,    -1,   251,   252,    -1,   250,   252,    -1,
      29,   253,     7,    -1,    30,   253,     7,    -1,    39,   142,
      92,   255,    -1,   255,    -1,    39,   142,    92,   256,   254,
      -1,   256,   254,    -1,    -1,    91,    53,    -1,    91,   147,
      -1,    91,   147,    91,    53,    -1,   257,    -1,   259,    -1,
     256,   259,    -1,    42,    -1,    41,    -1,    72,    -1,    71,
      -1,    73,    -1,   258,    -1,    45,    -1,    46,    -1,    47,
      -1,    48,    -1,    49,    -1,     5,    -1,    50,    -1,    51,
      -1,    52,    -1,    59,    -1,    60,    -1,    61,    -1,    54,
      -1,    70,    -1,    62,    -1,    63,    -1,   257,    15,    39,
     142,    92,   195,    -1,   257,    15,   195,    -1,    15,    39,
     142,    92,   195,    -1,    15,   195,    -1,   261,    -1,    84,
      39,   266,    92,    -1,    82,    39,   195,    92,    -1,    76,
      39,   142,    92,    -1,   269,    -1,    40,   262,   263,    93,
      -1,   189,    -1,    41,    -1,   257,    -1,   264,    -1,   265,
      -1,   264,   265,    -1,   257,    15,   192,    -1,    15,   192,
      -1,   257,    -1,   267,    -1,   268,    -1,   267,   268,    -1,
     257,    15,    -1,    15,    -1,    96,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   262,   262,   273,   276,   277,   278,   285,   292,   302,
     303,   305,   304,   322,   324,   323,   335,   342,   351,   341,
     364,   377,   378,   378,   383,   402,   422,   441,   442,   443,
     444,   445,   446,   454,   461,   467,   468,   475,   476,   480,
     481,   485,   489,   490,   491,   495,   506,   519,   528,   529,
     532,   535,   541,   550,   551,   555,   563,   570,   571,   571,
     580,   581,   586,   585,   604,   616,   617,   633,   634,   638,
     639,   643,   643,   645,   649,   657,   665,   666,   670,   681,
     686,   690,   694,   699,   703,   708,   713,   714,   720,   729,
     730,   734,   735,   736,   744,   747,   748,   760,   761,   773,
     780,   781,   785,   795,   800,   814,   818,   819,   824,   829,
     834,   841,   851,   855,   856,   860,   861,   861,   869,   877,
     879,   878,   898,   898,   899,   903,   904,   923,   924,   928,
     929,   935,   938,   939,   940,   944,   945,   949,   953,   957,
     969,   973,   983,  1002,  1000,  1018,  1019,  1023,  1024,  1028,
    1029,  1033,  1037,  1044,  1045,  1049,  1054,  1061,  1062,  1065,
    1067,  1072,  1071,  1088,  1091,  1099,  1098,  1114,  1115,  1116,
    1117,  1118,  1122,  1130,  1138,  1142,  1146,  1152,  1156,  1160,
    1168,  1174,  1181,  1188,  1197,  1204,  1212,  1220,  1228,  1230,
    1236,  1237,  1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,
    1246,  1247,  1248,  1249,  1250,  1251,  1252,  1253,  1254,  1258,
    1262,  1266,  1270,  1271,  1272,  1273,  1274,  1275,  1276,  1277,
    1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,  1286,  1287,
    1288,  1289,  1290,  1291,  1295,  1299,  1303,  1304,  1308,  1309,
    1317,  1318,  1319,  1323,  1324,  1328,  1329,  1330,  1331,  1337,
    1338,  1339,  1340,  1340,  1341,  1352,  1356,  1363,  1375,  1388,
    1407,  1416,  1424,  1435,  1453,  1460,  1468,  1483,  1484,  1486,
    1490,  1482,  1498,  1499,  1503,  1497,  1510,  1511,  1513,  1517,
    1509,  1525,  1526,  1530,  1524,  1538,  1542,  1536,  1548,  1549,
    1548,  1555,  1556,  1557,  1556,  1563,  1564,  1565,  1566,  1570,
    1572,  1573,  1570,  1582,  1583,  1583,  1588,  1592,  1600,  1600,
    1627,  1628,  1632,  1633,  1634,  1637,  1639,  1643,  1647,  1648,
    1648,  1653,  1661,  1652,  1685,  1700,  1701,  1705,  1706,  1710,
    1710,  1715,  1723,  1728,  1736,  1738,  1740,  1742,  1747,  1748,
    1749,  1750,  1758,  1762,  1763,  1767,  1768,  1769,  1770,  1771,
    1772,  1776,  1777,  1778,  1779,  1780,  1781,  1782,  1783,  1784,
    1785,  1786,  1787,  1788,  1789,  1790,  1791,  1795,  1797,  1799,
    1801,  1806,  1807,  1808,  1809,  1810,  1814,  1818,  1819,  1826,
    1827,  1831,  1832,  1840,  1841,  1845,  1846,  1850,  1851,  1859,
    1860,  1864
};
#endif

#if QC_YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LOW", "IFX", "ELSE", "BREAK_PRIMARY",
  "';'", "CLASS_NOT_CATEGORY", "STORAGEX", "COMMA", "'='", "PAS", "ASX",
  "'?'", "':'", "OR", "AND", "'|'", "'^'", "'&'", "NE", "EQ", "GT", "LT",
  "GE", "LE", "SHR", "SHL", "'+'", "'-'", "'*'", "'/'", "'%'", "INCOP",
  "UNARY", "SIZEOF", "HYPERUNARY", "'.'", "'('", "'['", "CLASS_NAME",
  "NAME", "VALUE", "STRING", "LOCAL", "RETURN", "WHILE", "DO", "IF", "FOR",
  "BREAK", "CONTINUE", "ELLIPSIS", "NIL", "IFBE", "IFB", "IFAE", "IFA",
  "SWITCH", "CASE", "DEFAULT", "ENUM", "TYPEDEF", "ARGS", "EXTERN",
  "STATIC", "SYSTEM", "NOSAVE", "OVERLOAD", "STRUCT", "TYPE", "OBJECT",
  "TYPE_NAME", "CLASS", "DEFS", "ENCODE", "END", "IMPLEMENTATION",
  "INTERFACE", "PRIVATE", "PROTECTED", "PROTOCOL", "PUBLIC", "SELECTOR",
  "REFERENCE", "SELF", "THIS", "'}'", "'{'", "'#'", "','", "')'", "']'",
  "'!'", "'~'", "'@'", "$accept", "program", "external_def_list",
  "external_def", "@1", "$@2", "save_storage", "function_body", "@3", "@4",
  "external_decl_list", "@5", "external_decl", "storage_class",
  "optional_specifiers", "specifiers", "type",
  "type_specifier_or_storage_class", "type_specifier", "optional_tag",
  "tag", "enum_specifier", "optional_enum_list", "enum_list", "enum_init",
  "enumerator_list", "@6", "enumerator", "struct_specifier", "$@7",
  "struct_defs", "struct_def_list", "struct_def", "struct_decl_list", "@8",
  "struct_decl", "new_name", "var_decl", "function_decl",
  "function_params", "qc_func_params", "ps", "var_list", "qc_var_list",
  "param_declaration", "abstract_decl", "qc_param_decl", "abs_decl",
  "array_decl", "local_specifiers", "param_list", "@9", "param",
  "local_decl_list", "@10", "decl_list", "@11", "decl",
  "function_def_list", "func_def_list", "comma", "func_def_list_term",
  "func_def", "code_function", "non_code_funcion", "overloaded_identifier",
  "non_code_func", "code_func", "@12", "opt_initializer",
  "var_initializer", "optional_state_expr", "think", "opt_step",
  "element_list", "element", "optional_comma", "compound_statement",
  "$@13", "statements", "local_def", "@14", "statement", "else", "label",
  "break_label", "continue_label", "switch_block", "opt_expr",
  "unary_expr", "cast_expr", "expr", "fexpr", "texpr", "opt_arg_list",
  "arg_list", "const", "string", "identifier", "obj_def", "$@15",
  "identifier_list", "classdecl", "class_name", "new_class_name",
  "class_with_super", "new_class_with_super", "category_name",
  "new_category_name", "class_reference", "category_reference",
  "protocol_name", "classdef", "$@16", "@17", "@18", "$@19", "$@20", "@21",
  "$@22", "$@23", "@24", "@25", "$@26", "$@27", "@28", "$@29", "@30",
  "$@31", "$@32", "@33", "$@34", "@35", "protocoldef", "@36", "@37",
  "$@38", "protocolrefs", "@39", "protocol_list", "ivar_decl_list", "@40",
  "ivar_decl_list_2", "visibility_spec", "ivar_decls", "ivar_decl",
  "ivars", "@41", "methoddef", "@42", "@43", "ci", "methodprotolist",
  "methodprotolist2", "$@44", "methodproto", "methoddecl",
  "optional_param_list", "unaryselector", "keywordselector", "selector",
  "reserved_word", "keyworddecl", "obj_expr", "obj_messageexpr",
  "receiver", "messageargs", "keywordarglist", "keywordarg", "selectorarg",
  "keywordnamelist", "keywordname", "obj_string", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,    59,   262,   263,
     264,    61,   265,   266,    63,    58,   267,   268,   124,    94,
      38,   269,   270,   271,   272,   273,   274,   275,   276,    43,
      45,    42,    47,    37,   277,   278,   279,   280,    46,    40,
      91,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   125,   123,
      35,    44,    41,    93,    33,   126,    64
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,    97,    98,    99,    99,    99,    99,    99,    99,   100,
     100,   101,   100,   100,   102,   100,   103,   105,   106,   104,
     104,   107,   108,   107,   109,   109,   109,   110,   110,   110,
     110,   110,   110,   111,   111,   112,   112,   113,   113,   114,
     114,   115,   115,   115,   115,   115,   115,   115,   116,   116,
     117,   118,   118,   119,   119,   120,   121,   122,   123,   122,
     124,   124,   126,   125,   125,   127,   127,   128,   128,   129,
     129,   131,   130,   130,   132,   132,   132,   132,   133,   134,
     134,   134,   134,   134,   135,   135,   135,   135,   135,   136,
     136,   137,   137,   137,   138,   139,   139,   140,   140,   141,
     141,   141,   142,   143,   143,   143,   144,   144,   144,   144,
     144,   145,   145,   146,   146,   147,   148,   147,   149,   150,
     151,   150,   153,   152,   152,   154,   154,   155,   155,   156,
     156,   157,   158,   158,   158,   159,   159,   160,   161,   162,
     163,   163,   163,   165,   164,   166,   166,   167,   167,   168,
     168,   169,   169,   170,   170,   171,   171,   172,   172,   173,
     173,   175,   174,   176,   176,   178,   177,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   180,   181,   182,   183,   184,   185,   185,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     187,   187,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   189,   190,   191,   191,   192,   192,
     193,   193,   193,   194,   194,   195,   195,   195,   195,   196,
     196,   196,   197,   196,   196,   198,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   210,   211,   212,
     213,   209,   214,   215,   216,   209,   217,   218,   219,   220,
     209,   221,   222,   223,   209,   224,   225,   209,   226,   227,
     209,   209,   228,   229,   209,   209,   209,   209,   209,   231,
     232,   233,   230,   234,   235,   234,   236,   236,   238,   237,
     239,   239,   240,   240,   240,   241,   241,   242,   243,   244,
     243,   246,   247,   245,   245,   248,   248,   249,   249,   251,
     250,   250,   252,   252,   253,   253,   253,   253,   254,   254,
     254,   254,   255,   256,   256,   257,   257,   257,   257,   257,
     257,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   259,   259,   259,
     259,   260,   260,   260,   260,   260,   261,   262,   262,   263,
     263,   264,   264,   265,   265,   266,   266,   267,   267,   268,
     268,   269
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     2,     2,     3,
       2,     0,     4,     3,     0,     7,     0,     0,     0,     5,
       4,     1,     0,     4,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     1,     0,
       1,     3,     2,     1,     0,     5,     0,     1,     0,     4,
       1,     3,     0,     6,     2,     2,     4,     1,     3,     2,
       1,     0,     4,     1,     1,     1,     3,     2,     1,     1,
       2,     2,     2,     3,     2,     2,     3,     2,     2,     2,
       4,     2,     4,     4,     0,     1,     3,     1,     3,     2,
       1,     1,     2,     2,     3,     1,     0,     4,     2,     2,
       3,     3,     2,     2,     1,     1,     0,     4,     2,     1,
       0,     3,     0,     4,     1,     1,     2,     3,     1,     3,
       1,     1,     2,     2,     1,     1,     1,     2,     2,     1,
       3,     2,     0,     0,     5,     0,     1,     2,     5,     0,
       6,     1,     3,     2,     0,     1,     3,     4,     1,     0,
       1,     0,     4,     0,     2,     0,     4,     1,     2,     1,
       1,     3,     2,     2,     3,     2,     7,     5,     7,    11,
       7,     9,     2,     1,     0,     0,     0,     0,     1,     0,
       1,     1,     1,     1,     1,     3,     4,     4,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,     1,
       4,     1,     1,     3,     3,     5,     4,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     0,     1,     1,     3,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     1,     1,     3,     3,     1,     1,
       3,     3,     4,     4,     1,     4,     1,     0,     0,     0,
       0,    12,     0,     0,     0,     8,     0,     0,     0,     0,
      12,     0,     0,     0,     8,     0,     0,     7,     0,     0,
       7,     2,     0,     0,     7,     2,     2,     3,     3,     0,
       0,     0,     8,     0,     0,     4,     1,     3,     0,     2,
       3,     1,     1,     1,     1,     0,     3,     2,     1,     0,
       4,     0,     0,     7,     6,     1,     1,     0,     1,     0,
       2,     2,     3,     3,     4,     1,     5,     2,     0,     2,
       2,     4,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     3,     5,
       2,     1,     4,     4,     4,     1,     4,     1,     1,     1,
       1,     1,     2,     3,     2,     1,     1,     1,     2,     2,
       1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,    34,     7,     6,     8,     1,     0,   303,
       0,    30,    27,    28,    29,    32,    31,    49,    41,   303,
      44,     0,   254,     0,     0,   299,     0,     4,    40,     0,
      33,    35,    39,    42,    43,     5,     0,   250,   249,   251,
      47,   304,    46,    50,    56,    54,    52,     0,    64,    45,
     247,   245,   246,   248,   255,     0,   258,   291,   295,   296,
     259,   303,   303,   303,     0,   264,     0,     0,    16,    10,
       0,    94,    78,     0,    21,    79,    24,    26,    11,    40,
      36,   325,   326,   253,     0,     0,     0,    51,    53,    62,
     257,     0,     0,     0,     0,     0,     0,     0,   272,   281,
     285,   266,   303,     0,   297,   298,    14,     0,    82,    84,
      91,     0,     0,     0,    94,    88,     9,    22,     0,     0,
      80,    81,    25,     0,     0,    13,    87,    85,    17,     0,
     356,     0,     0,   346,   345,   351,   352,   353,   354,   355,
     357,   358,   359,   363,   360,   361,   362,   365,   366,   364,
     348,   347,   349,   149,   335,   338,   342,   350,   343,   306,
       0,   159,    57,    60,     0,   256,     0,   258,   260,   289,
     293,     0,   261,     0,   273,     0,   282,   329,   300,     0,
       0,    83,    86,   105,    41,     0,    37,     0,    97,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     190,   240,   243,   241,   191,     0,     0,     0,   192,   193,
       0,     0,     0,     0,   211,   212,   234,   147,   194,   242,
     209,   371,   375,   112,     0,     0,     0,    16,    12,     0,
     128,   130,   134,   135,   142,   139,     0,   370,   106,     0,
       0,     0,   321,     0,   337,     0,   344,     0,   305,     0,
      58,     0,     0,     0,    70,     0,     0,    67,   262,   308,
     308,   263,   268,   329,   277,   329,   286,   328,     0,   329,
     265,    34,    93,    94,    78,    38,   103,     0,     0,    92,
     101,   106,     0,    95,   100,    23,    26,   205,   201,   202,
     206,     0,   199,     0,   207,     0,     0,   378,   377,     0,
       0,     0,     0,     0,   159,   155,   158,   203,   204,   391,
     200,     0,   236,     0,     0,     0,     0,   184,   184,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   244,   111,     0,     0,    18,
     131,     0,   133,   132,   149,   138,   137,     0,   106,   106,
     102,     0,     0,     0,    16,   339,     0,   340,   115,     0,
     368,   307,     0,    55,    61,     0,     0,    69,    73,    75,
      74,    63,    65,     0,   315,     0,   308,   274,   308,   283,
       0,     0,     0,   331,   330,   301,     0,   104,    98,   106,
     106,    99,     0,    90,     0,     0,   195,     0,   379,     0,
     380,   381,     0,     0,   390,   385,     0,   386,   387,   159,
     160,     0,   198,   238,     0,   237,     0,   213,   214,     0,
       0,     0,   231,   232,   230,   219,   218,   223,   222,   221,
     220,   225,   224,   226,   227,   228,   229,   233,    20,     0,
     154,   151,     0,   127,   129,     0,     0,    16,   141,     0,
     108,     0,   109,   334,   338,     0,   322,   303,   303,    44,
     118,   116,     0,    59,     0,    77,    71,     0,    68,   290,
     309,   311,   294,     0,     0,     0,     0,   287,     0,     0,
       0,    15,    96,   208,   210,   384,     0,   376,     0,   382,
     374,   373,   389,   372,     0,   388,     0,   156,   148,   196,
       0,   197,     0,   217,   216,     0,     0,     0,   161,    19,
     377,   140,   143,   369,   110,   336,   324,     0,   341,     0,
       0,    66,     0,    76,   312,   313,   314,   315,     0,     0,
     269,   275,   278,   284,   332,   333,   302,   383,   157,   239,
     215,   152,   153,   150,   163,     0,   107,   323,   117,   367,
      72,   310,   318,   317,   316,   329,   329,     0,   144,   319,
     270,   279,     0,   167,     0,   189,   185,   185,     0,   185,
       0,     0,   185,     0,     0,   162,   114,   165,   169,   170,
     164,     0,     0,     0,     0,   168,   113,     0,   188,   186,
     186,     0,   186,   172,   173,     0,     0,   175,     0,   182,
     320,   271,   280,   171,     0,     0,   235,     0,     0,     0,
     174,   145,   125,   120,     0,   119,   124,     0,     0,     0,
     189,   187,   126,   146,     0,   166,   122,     0,     0,   177,
       0,     0,   121,   136,   135,     0,     0,     0,   183,     0,
     189,     0,     0,   123,   180,     0,   178,     0,   176,     0,
     189,   181,     0,     0,   179
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    27,   129,   180,   106,   125,   227,   442,
      73,   191,    74,    79,    29,   576,   238,    31,   186,    47,
      45,    33,    87,    46,    86,   161,   362,   162,    34,   164,
     255,   256,   257,   367,   522,   368,    75,   369,   370,   120,
      78,   113,   282,   187,   283,   284,   188,   350,   121,   577,
     357,   519,   358,   614,   624,   615,   635,   616,   228,   229,
     341,   230,   231,   232,   233,   234,   345,   346,   545,   622,
     122,   128,   440,   507,   304,   305,   251,   578,   544,   557,
     579,   598,   580,   639,   420,   589,   604,   631,   587,   214,
     215,   216,   581,   607,   414,   415,   218,   219,   235,    35,
      36,    55,    37,    57,    61,    58,    62,    59,    63,    66,
      67,   102,    38,   173,   376,   555,   583,   174,   263,   474,
     175,   378,   556,   584,   176,   265,   476,   177,   380,    94,
     259,    95,   260,    39,    64,   269,   480,    42,    85,   160,
     373,   374,   470,   527,   471,   529,   553,   582,    83,   354,
     517,    84,   266,   267,   268,   383,   153,   244,   154,   155,
     156,   157,   158,   220,   221,   299,   399,   400,   401,   406,
     407,   408,   222
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -492
static const yytype_int16 yypact[] =
{
     827,    53,   107,   878,  -492,  -492,  -492,  -492,   668,   105,
      23,  -492,  -492,  -492,  -492,  -492,  -492,    27,  -492,   105,
    -492,   143,  -492,   143,   143,  -492,   143,  -492,    49,    63,
     408,  -492,  -492,  -492,  -492,  -492,    45,  -492,  -492,  -492,
    -492,  -492,  -492,  -492,  -492,    80,  -492,    85,    94,  -492,
    -492,  -492,  -492,  -492,  -492,    31,   150,    25,   128,  -492,
     197,    47,   105,   105,   143,   206,   255,   259,  -492,  -492,
     218,    24,   244,    34,  -492,  -492,   167,   104,  -492,  -492,
    -492,  -492,  -492,  -492,  1352,   143,   143,  -492,  -492,  -492,
    -492,   143,   143,   143,   202,   216,   143,   143,   234,   240,
    -492,  -492,   105,   143,  -492,  -492,  -492,   218,   185,   185,
    -492,    18,    28,   214,   239,  -492,  -492,  -492,   316,  1030,
    -492,  -492,  -492,   247,  1030,  -492,  -492,  -492,  -492,   143,
    -492,   161,   668,  -492,  -492,  -492,  -492,  -492,  -492,  -492,
    -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,
    -492,  -492,  -492,    71,  -492,   800,   325,  -492,  -492,  -492,
      41,   258,  -492,   340,   139,  -492,   272,  -492,  -492,  -492,
    -492,   275,  -492,   280,  -492,   287,  -492,   311,  -492,   297,
     426,  -492,  -492,  -492,   298,   572,  -492,   226,  -492,  -492,
     353,   218,  1209,  1209,  1209,  1209,  1226,  1294,   962,  1056,
    -492,  -492,  -492,  -492,  -492,   356,   362,   369,  -492,  -492,
    1124,  1209,  1209,   365,   204,  -492,  1611,  -492,  -492,   370,
    -492,  -492,  -492,  -492,   320,  1209,   213,  -492,  -492,   326,
    -492,  -492,    40,   411,   410,  -492,   668,  -492,   209,   330,
     339,  1209,  -492,   366,  -492,   325,  -492,   222,  -492,   143,
     343,   344,  1209,   391,   156,   346,   428,  -492,  -492,  -492,
    -492,  -492,  -492,   311,  -492,   311,  -492,   201,   201,   311,
    -492,  1492,  -492,   348,  -492,  -492,  -492,   400,   504,  -492,
    -492,   271,   236,  -492,  -492,  -492,   185,  -492,  -492,  -492,
    -492,  1209,   204,   962,   204,   351,   948,  -492,  -492,  1390,
     668,   143,  1428,  1124,   359,  -492,  -492,  -492,  -492,  -492,
    -492,  1226,  1209,  1209,  1209,  1209,  1209,  -492,  -492,  1209,
    1209,  1209,  1209,  1209,  1209,  1209,  1209,  1209,  1209,  1209,
    1209,  1209,  1209,  1209,  1209,  -492,  -492,  1565,   324,  -492,
    -492,   143,  -492,  -492,  1141,  -492,  -492,   352,   142,   142,
     405,  1466,   178,   361,  -492,  -492,   445,   363,  -492,   668,
    -492,  -492,   143,  -492,  -492,   143,  1209,   368,  -492,    33,
     185,  -492,   668,   372,  -492,   373,  -492,  -492,  -492,  -492,
     376,  1352,  1352,  -492,  -492,  -492,   455,  -492,  -492,   257,
     257,   185,   353,  -492,   377,  1209,  -492,  1209,   457,   389,
    1390,  -492,   393,   409,  -492,   491,   417,  1428,  -492,   359,
    1124,   431,  -492,  -492,   429,   432,   904,  1611,  1611,  1588,
    1209,  1209,  1679,  1520,  1692,   594,   594,   354,   354,   354,
     354,   342,   342,   242,   242,  -492,  -492,  -492,  -492,  1209,
     433,  -492,   437,  -492,  -492,  1056,  1209,  -492,  -492,   143,
     405,    14,  -492,  -492,   800,   513,  -492,    69,    97,    79,
    -492,   469,   435,  -492,   436,  1611,  -492,  1209,  -492,  -492,
      74,   668,  -492,   441,   454,   444,   458,  -492,   527,   529,
     460,  -492,  -492,  -492,  -492,   432,  1209,  -492,   457,  -492,
    -492,  -492,  -492,  -492,   491,  -492,   450,  -492,  -492,  -492,
    1209,  -492,  1209,  1648,  1664,   448,  1209,   451,  -492,  -492,
     361,  -492,  -492,  -492,   244,  -492,  -492,   437,  -492,   668,
     143,  -492,   283,  1611,  -492,  -492,  -492,  -492,   156,   534,
    -492,  -492,  -492,  -492,  -492,  -492,  -492,   432,  -492,  -492,
    1631,  -492,  -492,  -492,  -492,   437,  -492,  -492,  -492,  -492,
    -492,   668,  -492,   456,  -492,   311,   311,   628,  -492,  -492,
    -492,  -492,   539,  -492,   408,  1209,  -492,  -492,   509,  -492,
     543,   544,  -492,  1209,   538,  -492,   408,  -492,  -492,  -492,
    -492,   548,   283,   482,   483,  -492,   408,   557,  -492,  -492,
    -492,  1209,  -492,  -492,  -492,   526,   552,  -492,   269,  -492,
    -492,  -492,  -492,  -492,   530,   730,  -492,   476,   532,  1209,
    -492,   167,   185,  -492,   575,   510,  -492,  1209,   553,   730,
    1209,  -492,  -492,  -492,   143,  -492,  -492,   511,   565,   600,
     599,   516,   326,  -492,  -492,   218,   730,  1209,  -492,   730,
    1209,   437,   143,  -492,  -492,   520,  -492,   608,  -492,   621,
    1209,  -492,   540,   730,  -492
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -492,  -492,   459,  -492,  -492,  -492,  -201,  -492,  -492,  -492,
    -492,  -492,   439,    21,  -492,    -1,  -103,   -24,    -3,  -492,
     620,  -492,  -492,   593,  -492,  -492,  -492,   278,  -492,  -492,
    -492,  -492,   274,  -492,  -492,  -469,  -150,   -28,   -26,   -63,
    -178,   533,  -492,  -492,   249,  -101,   371,  -199,   -73,  -492,
    -492,  -492,   132,  -492,  -492,  -492,  -492,    17,  -492,    29,
      22,   314,  -322,  -491,  -463,  -492,  -492,  -492,  -492,  -492,
      50,  -125,  -492,  -492,   357,   246,  -270,  -421,  -492,  -492,
    -492,  -492,  -477,  -492,   345,  -313,  -266,  -492,  -484,  -164,
     -94,   265,  -107,  -465,  -492,  -360,   313,  -492,    -8,  -492,
    -492,  -492,  -492,   111,  -492,  -492,  -492,  -492,  -492,  -492,
    -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,
    -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,
    -492,  -492,  -492,  -492,  -492,  -492,  -492,   -11,  -492,  -492,
    -230,  -492,  -492,  -492,   154,  -492,  -492,  -492,  -492,  -492,
    -492,  -492,  -240,  -492,  -492,   415,   -47,   230,   360,   367,
    -135,  -492,  -133,  -492,  -492,  -492,  -492,  -492,   302,  -492,
    -492,   296,  -492
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -328
static const yytype_int16 yytable[] =
{
      32,    76,    30,    77,   127,    40,    80,   277,    49,   115,
     185,   217,   224,    54,   126,    56,    60,   226,    65,   444,
     245,   509,   246,   377,    28,   379,   339,    32,   242,   385,
     375,   239,   292,   294,   411,   276,   127,   485,    90,   127,
      93,   116,   108,   111,   109,   112,   126,   342,   467,   126,
      98,    99,   100,   550,   119,    70,   101,   114,   119,   552,
       4,   254,    97,   107,   248,    43,    72,   114,   119,    43,
      69,    41,   114,   119,    81,    82,  -247,   159,   163,   111,
    -247,   112,   240,   165,   166,   167,  -248,   281,   171,   167,
    -248,   178,   298,    41,    70,   179,   547,   295,   287,   288,
     289,   290,    71,   306,  -246,    72,   514,     7,  -246,  -247,
     181,   241,    44,   600,  -288,   123,   110,   307,   308,  -248,
     182,    41,    91,   237,   558,   117,   537,   387,   618,    41,
       5,  -136,   249,   633,   353,   347,   630,  -246,    68,   496,
     356,     6,   629,   114,   124,   364,   473,   412,   475,   450,
     451,   633,   627,   456,   524,   525,   647,   526,  -247,   644,
    -247,   634,   646,    76,   398,   286,   652,   405,  -248,    44,
    -248,   366,   645,   348,    89,   185,   654,     8,   118,   634,
       9,   349,   275,   -48,    50,    51,  -246,    70,  -246,    92,
     450,   451,   394,  -149,     8,   107,   306,     9,    72,   402,
     236,    10,    50,    51,   168,   413,   114,   119,   172,    17,
      18,    19,    20,   127,   253,    52,    53,  -292,    10,   447,
     648,   201,   202,   126,   114,   119,    17,    18,    19,    20,
     381,   382,   203,    52,    53,   275,    96,   448,   310,   360,
     348,   361,   311,   312,   313,   103,   512,     8,   349,    70,
       9,   275,     8,   391,   590,     9,   592,   107,   462,   595,
      72,   359,   104,    50,    51,   488,   105,   183,    32,   254,
      30,    10,   494,   332,   333,   334,    10,   452,   275,    17,
      18,    19,    20,   114,    17,   184,    19,    20,   389,   281,
     413,   169,    28,   403,    52,    53,   390,   127,   366,   274,
      70,   484,   389,   306,   338,   170,   336,   126,    71,     8,
     390,    72,     9,   274,    70,   560,   561,   278,   279,   245,
     444,   246,   107,  -267,   605,    72,   608,   392,   393,  -276,
     441,   189,   505,    10,   478,   479,   192,   225,   510,   511,
     247,    17,    18,    19,    20,   193,   194,   195,   460,   250,
     196,   252,   197,   275,   163,   198,   199,   464,   200,   201,
     202,   108,   111,   439,   258,    50,    51,   261,   528,   262,
     203,   330,   331,   332,   333,   334,   264,   452,   452,   413,
     204,   328,   329,   330,   331,   332,   333,   334,  -327,   270,
     272,     8,   205,   539,     9,   300,    52,    53,   206,   542,
     207,   301,   208,   209,     8,   210,   280,     9,   302,   309,
     211,   212,   213,   336,   335,    10,   356,   340,   343,   355,
     613,   344,   351,    17,    18,    19,    20,     1,    10,   352,
     365,  -160,   363,    -3,   371,   372,    17,    18,    19,    20,
     110,   513,   274,   395,   449,   119,     8,    49,   528,     9,
     410,   546,   338,   477,   461,    -3,    -3,    -3,   588,   466,
     469,   472,   481,   296,    -3,    -3,   596,    -3,    -3,   483,
      10,    11,   486,    12,    13,    14,    15,    16,    17,    18,
      19,    20,   487,     8,   606,   490,   457,    51,    -3,    -3,
     337,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,   491,   621,    -3,    -3,    -3,   492,    10,    -3,   493,
     606,    -3,   549,   588,    -3,    17,    18,   458,   459,   498,
     516,   499,   518,   500,   506,   275,   508,   520,   521,   530,
     606,   531,   532,   588,   534,   533,   535,   536,   538,   127,
     541,   554,     8,   588,   543,     9,   585,   559,   591,   126,
     593,   594,    80,   597,    32,   599,   296,   183,   296,   601,
     602,    32,    80,   586,   603,   609,    10,   610,   619,   617,
     611,   620,   612,    32,    17,    18,    19,    20,   416,   417,
     418,   419,   625,    32,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     628,   626,    32,   636,   637,   638,   640,   611,   641,   612,
       8,   273,   649,     9,   274,   650,    32,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   651,   562,
     285,   465,   653,    32,    10,   563,    32,    48,    88,   271,
     463,   482,    17,    18,    19,    20,   468,   190,   192,   388,
      32,   548,   643,   632,   642,   443,   497,   193,   194,   195,
     409,   623,   196,   421,   197,   455,     8,   198,   199,     9,
     200,   201,   202,   564,   565,   566,   567,   568,   569,   570,
     571,   551,   203,   384,   515,   503,   504,   572,   573,   574,
      10,    11,   204,    12,    13,    14,    15,    16,    17,    18,
      19,    20,   489,   495,   205,     0,     8,     0,     0,     9,
     206,   453,   207,     0,   208,   209,   575,   508,   454,     0,
       0,     0,   211,   212,   213,     0,     0,     0,     0,     0,
      10,   562,   523,     0,     0,     0,     0,   563,    17,    18,
      19,    20,     0,     0,     0,     0,     0,     0,     0,     0,
     192,     0,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   195,     0,     0,   196,     0,   197,   540,     8,   198,
     199,     9,   200,   201,   202,   564,   565,   566,   567,   568,
     569,   570,   571,     0,   203,     0,     0,     0,     0,   572,
     573,   574,    10,    11,   204,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,   130,   205,     0,     0,     0,
       0,     0,   206,     0,   207,   131,   208,   209,     0,   508,
       0,     0,     0,     0,   211,   212,   213,    -3,     1,     0,
       0,     0,     0,     0,    -3,     0,     0,     0,     0,     0,
       0,   133,   134,     0,     0,   135,   136,   137,   138,   139,
     140,   141,   142,     0,   143,     0,    -3,    -3,    -3,   144,
     145,   146,   147,   148,     0,    -3,    -3,     0,    -3,    -3,
     149,   150,   151,   152,     0,     0,     0,     0,    -2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    -3,
      -3,   243,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,     0,     0,    -3,    -3,    -3,  -252,  -252,    -3,
       0,     0,    -3,     0,     0,   314,     8,   315,   316,     9,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,     0,     0,
      10,    11,     0,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     0,     0,    22,    23,    24,     0,   314,
      25,   315,   316,    26,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   192,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   194,   195,     0,     0,   196,   501,   197,     0,
       8,   198,   199,     9,   200,   201,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   203,     0,     0,     0,
       0,     0,     0,     0,    10,     0,   204,     0,     0,     0,
       0,     0,    17,    18,    19,    20,     0,     0,   205,     0,
     396,     0,     0,     0,   206,     0,   207,     0,   208,   209,
     192,     0,     0,     0,     0,     0,   211,   212,   213,   193,
     194,   195,     0,     0,   196,     0,   197,     0,     0,   198,
     199,     0,   200,   201,   202,     0,   192,     0,     0,     0,
       0,     0,     0,     0,   203,   193,   194,   195,     0,     0,
     196,     0,   197,     0,   204,   198,   199,   297,   200,   201,
     202,     0,     0,     0,     0,     0,   205,     0,     0,     0,
     203,     0,   206,     0,   207,     0,   208,   209,     0,     0,
     204,     0,     0,   223,   211,   212,   213,     0,     0,     0,
       0,     0,   205,     0,     0,     0,     0,     0,   206,     0,
     207,     0,   208,   209,   192,     0,     0,     0,     0,     0,
     211,   212,   213,   193,   194,   195,     0,     0,   196,     0,
     197,   192,     0,   198,   199,     0,   200,   201,   202,     0,
     193,   194,   195,     0,     0,   196,     0,   197,   203,     0,
     198,   445,     0,   200,   201,   202,     0,     0,   204,     0,
       0,     0,     0,     0,     0,   203,     0,     0,     0,     0,
     205,     0,     0,     0,     0,   204,   206,     0,   207,     0,
     208,   209,     0,   303,     0,     0,     0,   205,   211,   212,
     213,     0,     0,   206,     0,   207,     0,   208,   209,   192,
       0,   446,     0,     0,     0,   211,   212,   213,   193,   194,
     195,     0,     0,   196,     0,   197,   192,     0,   198,   199,
       0,   200,   201,   202,     0,   193,   194,   195,     0,     0,
     196,     0,   197,   203,     0,   291,   199,     0,   200,   201,
     202,     0,     0,   204,     0,     0,     0,     0,     0,     0,
     203,     0,     0,     0,     0,   205,     0,     0,     0,     0,
     204,   206,     0,   207,     0,   208,   209,     0,     0,     0,
       0,     0,   205,   211,   212,   213,     0,     0,   206,     0,
     207,     0,   208,   209,   192,     0,     0,     0,     0,     0,
     211,   212,   213,   193,   194,   195,     0,     0,   196,     0,
     197,     0,     0,   293,   199,     0,   200,   201,   202,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,     0,
       0,     0,     0,     0,     0,     0,     0,   130,   204,     0,
       0,     0,     0,     0,     0,     0,     0,   131,     0,     0,
     205,     0,     0,     0,     0,     0,   206,     0,   207,     0,
     208,   209,     0,     0,     0,     0,     0,     0,   211,   212,
     213,   132,     0,   133,   134,   130,     0,   135,   136,   137,
     138,   139,   140,   141,   142,   397,   143,     0,     0,     0,
       0,   144,   145,   146,   147,   148,     0,     0,     0,     0,
       0,     0,   149,   150,   151,   152,     0,     0,     0,     0,
       0,   133,   134,   130,     0,   135,   136,   137,   138,   139,
     140,   141,   142,   404,   143,     0,     0,     0,     0,   144,
     145,   146,   147,   148,     0,     0,     0,     0,     0,     0,
     149,   150,   151,   152,     0,     0,     0,     0,     0,   133,
     134,   130,     0,   135,   136,   137,   138,   139,   140,   141,
     142,   131,   143,     0,     0,     0,     0,   144,   145,   146,
     147,   148,     0,     0,     0,     0,     0,     0,   149,   150,
     151,   152,     0,     0,     0,     0,     0,   133,   134,     0,
       0,   135,   136,   137,   138,   139,   140,   141,   142,     0,
     143,  -252,  -252,     0,     0,   144,   145,   146,   147,   148,
       8,     0,     0,     9,     0,     0,   149,   150,   151,   152,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,    10,    11,     0,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     0,     0,    22,
      23,    24,   438,     0,    25,     0,   314,    26,   315,   316,
     386,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   314,
       0,   315,   316,   502,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   314,     0,   315,   316,     0,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   316,     0,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-492))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       3,    29,     3,    29,    77,     8,    30,   185,    19,    72,
     113,   118,   119,    21,    77,    23,    24,   124,    26,   341,
     155,   442,   155,   263,     3,   265,   227,    30,   153,   269,
     260,   132,   196,   197,   304,   185,   109,   397,     7,   112,
      15,     7,    70,    71,    70,    71,   109,     7,    15,   112,
      61,    62,    63,   522,    40,    31,    64,    39,    40,   528,
       7,   164,    15,    39,    23,    42,    42,    39,    40,    42,
       7,    24,    39,    40,    29,    30,     7,    85,    86,   107,
      11,   107,    11,    91,    92,    93,     7,   190,    96,    97,
      11,   102,   199,    24,    31,   103,   517,   198,   192,   193,
     194,   195,    39,   210,     7,    42,    92,     0,    11,    40,
      92,    40,    89,   582,    89,    11,    92,   211,   212,    40,
      92,    24,    91,   131,   545,    91,   486,   277,   605,    24,
      77,    91,    91,   624,   241,   236,   620,    40,    89,   409,
     243,    88,   619,    39,    40,   252,   376,   311,   378,   348,
     349,   642,   617,   354,    80,    81,   640,    83,    89,   636,
      91,   624,   639,   191,   299,   191,   650,   302,    89,    89,
      91,    15,   637,    31,    89,   278,   653,    38,    11,   642,
      41,    39,   185,    89,    41,    42,    89,    31,    91,    39,
     389,   390,   293,    89,    38,    39,   303,    41,    42,   300,
      39,    62,    41,    42,    93,   312,    39,    40,    97,    70,
      71,    72,    73,   286,    75,    72,    73,    89,    62,   344,
     641,    43,    44,   286,    39,    40,    70,    71,    72,    73,
      29,    30,    54,    72,    73,   238,    39,   344,    34,   247,
      31,   249,    38,    39,    40,    39,   447,    38,    39,    31,
      41,   254,    38,   281,   567,    41,   569,    39,   359,   572,
      42,    39,     7,    41,    42,   400,     7,    53,   271,   372,
     271,    62,   407,    31,    32,    33,    62,   350,   281,    70,
      71,    72,    73,    39,    70,    71,    72,    73,    31,   392,
     397,    89,   271,   301,    72,    73,    39,   370,    15,    42,
      31,   395,    31,   410,    91,    89,    93,   370,    39,    38,
      39,    42,    41,    42,    31,   555,   556,    91,    92,   454,
     642,   454,    39,    89,   590,    42,   592,    91,    92,    89,
     338,    92,   439,    62,   381,   382,    20,    90,   445,   446,
      15,    70,    71,    72,    73,    29,    30,    31,   356,    91,
      34,    11,    36,   356,   362,    39,    40,   365,    42,    43,
      44,   389,   390,    39,    92,    41,    42,    92,   471,    89,
      54,    29,    30,    31,    32,    33,    89,   450,   451,   486,
      64,    27,    28,    29,    30,    31,    32,    33,    77,    92,
      92,    38,    76,   500,    41,    39,    72,    73,    82,   506,
      84,    39,    86,    87,    38,    89,    53,    41,    39,    44,
      94,    95,    96,    93,    44,    62,   519,    91,     7,    53,
     598,    11,    92,    70,    71,    72,    73,     1,    62,    90,
      39,    88,    88,     7,    88,     7,    70,    71,    72,    73,
      92,   449,    42,    92,    92,    40,    38,   458,   551,    41,
      91,   514,    91,    77,    91,    29,    30,    31,   565,    91,
      88,    88,     7,   198,    38,    39,   573,    41,    42,    92,
      62,    63,    15,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    93,    38,   591,    92,    41,    42,    62,    63,
     225,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    92,   609,    77,    78,    79,    15,    62,    82,    92,
     617,    85,   520,   620,    88,    70,    71,    72,    73,    88,
       7,    92,    53,    91,    91,   528,    89,    92,    92,    88,
     637,    77,    88,   640,     7,    77,     7,    77,    88,   612,
      92,     7,    38,   650,    93,    41,     7,    91,    39,   612,
       7,     7,   576,    15,   557,     7,   291,    53,   293,    77,
      77,   564,   586,   564,     7,    39,    62,    15,    92,    39,
     598,    39,   598,   576,    70,    71,    72,    73,   313,   314,
     315,   316,     7,   586,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
      47,    91,   605,    92,    39,     5,     7,   635,    92,   635,
      38,    39,    92,    41,    42,     7,   619,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     7,     1,
     191,   366,    92,   636,    62,     7,   639,    17,    45,   180,
     362,   392,    70,    71,    72,    73,   372,   114,    20,   278,
     653,   519,   635,   624,   632,   341,   410,    29,    30,    31,
     303,   611,    34,   318,    36,   352,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,   527,    54,   268,   454,   420,   421,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,   400,   407,    76,    -1,    38,    -1,    -1,    41,
      82,   351,    84,    -1,    86,    87,    88,    89,   351,    -1,
      -1,    -1,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,
      62,     1,   467,    -1,    -1,    -1,    -1,     7,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    -1,    -1,    34,    -1,    36,   502,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    54,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    -1,     5,    76,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    84,    15,    86,    87,    -1,    89,
      -1,    -1,    -1,    -1,    94,    95,    96,     0,     1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    54,    -1,    29,    30,    31,    59,
      60,    61,    62,    63,    -1,    38,    39,    -1,    41,    42,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,     0,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    91,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    77,    78,    79,    29,    30,    82,
      -1,    -1,    85,    -1,    -1,    11,    38,    13,    14,    41,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    -1,    -1,
      62,    63,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    77,    78,    79,    -1,    11,
      82,    13,    14,    85,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    -1,    -1,    34,    93,    36,    -1,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    -1,    -1,    76,    -1,
      92,    -1,    -1,    -1,    82,    -1,    84,    -1,    86,    87,
      20,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    29,
      30,    31,    -1,    -1,    34,    -1,    36,    -1,    -1,    39,
      40,    -1,    42,    43,    44,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    29,    30,    31,    -1,    -1,
      34,    -1,    36,    -1,    64,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      54,    -1,    82,    -1,    84,    -1,    86,    87,    -1,    -1,
      64,    -1,    -1,    93,    94,    95,    96,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      84,    -1,    86,    87,    20,    -1,    -1,    -1,    -1,    -1,
      94,    95,    96,    29,    30,    31,    -1,    -1,    34,    -1,
      36,    20,    -1,    39,    40,    -1,    42,    43,    44,    -1,
      29,    30,    31,    -1,    -1,    34,    -1,    36,    54,    -1,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    64,    82,    -1,    84,    -1,
      86,    87,    -1,    89,    -1,    -1,    -1,    76,    94,    95,
      96,    -1,    -1,    82,    -1,    84,    -1,    86,    87,    20,
      -1,    90,    -1,    -1,    -1,    94,    95,    96,    29,    30,
      31,    -1,    -1,    34,    -1,    36,    20,    -1,    39,    40,
      -1,    42,    43,    44,    -1,    29,    30,    31,    -1,    -1,
      34,    -1,    36,    54,    -1,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,
      64,    82,    -1,    84,    -1,    86,    87,    -1,    -1,    -1,
      -1,    -1,    76,    94,    95,    96,    -1,    -1,    82,    -1,
      84,    -1,    86,    87,    20,    -1,    -1,    -1,    -1,    -1,
      94,    95,    96,    29,    30,    31,    -1,    -1,    34,    -1,
      36,    -1,    -1,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    82,    -1,    84,    -1,
      86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    39,    -1,    41,    42,     5,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    15,    54,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    41,    42,     5,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    15,    54,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    41,
      42,     5,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    15,    54,    -1,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    -1,
      54,    29,    30,    -1,    -1,    59,    60,    61,    62,    63,
      38,    -1,    -1,    41,    -1,    -1,    70,    71,    72,    73,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    62,    63,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    77,
      78,    79,     7,    -1,    82,    -1,    11,    85,    13,    14,
      88,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    11,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    11,    -1,    13,    14,    -1,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    14,    -1,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,    98,    99,     7,    77,    88,     0,    38,    41,
      62,    63,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    77,    78,    79,    82,    85,   100,   110,   111,
     112,   114,   115,   118,   125,   196,   197,   199,   209,   230,
     115,    24,   234,    42,    89,   117,   120,   116,   117,   234,
      41,    42,    72,    73,   195,   198,   195,   200,   202,   204,
     195,   201,   203,   205,   231,   195,   206,   207,    89,     7,
      31,    39,    42,   107,   109,   133,   134,   135,   137,   110,
     114,    29,    30,   245,   248,   235,   121,   119,   120,    89,
       7,    91,    39,    15,   226,   228,    39,    15,   234,   234,
     234,   195,   208,    39,     7,     7,   103,    39,   134,   135,
      92,   134,   135,   138,    39,   136,     7,    91,    11,    40,
     136,   145,   167,    11,    40,   104,   136,   145,   168,   101,
       5,    15,    39,    41,    42,    45,    46,    47,    48,    49,
      50,    51,    52,    54,    59,    60,    61,    62,    63,    70,
      71,    72,    73,   253,   255,   256,   257,   258,   259,   195,
     236,   122,   124,   195,   126,   195,   195,   195,   200,    89,
      89,   195,   200,   210,   214,   217,   221,   224,   234,   195,
     102,    92,    92,    53,    71,   113,   115,   140,   143,    92,
     138,   108,    20,    29,    30,    31,    34,    36,    39,    40,
      42,    43,    44,    54,    64,    76,    82,    84,    86,    87,
      89,    94,    95,    96,   186,   187,   188,   189,   193,   194,
     260,   261,   269,    93,   189,    90,   189,   105,   155,   156,
     158,   159,   160,   161,   162,   195,    39,   195,   113,   142,
      11,    40,   168,    91,   254,   257,   259,    15,    23,    91,
      91,   173,    11,    75,   113,   127,   128,   129,    92,   227,
     229,    92,    89,   215,    89,   222,   249,   250,   251,   232,
      92,    99,    92,    39,    42,   115,   133,   137,    91,    92,
      53,   113,   139,   141,   142,   109,   135,   187,   187,   187,
     187,    39,   186,    39,   186,   142,   188,    41,   189,   262,
      39,    39,    39,    89,   171,   172,   189,   187,   187,    44,
      34,    38,    39,    40,    11,    13,    14,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    44,    93,   188,    91,   103,
      91,   157,     7,     7,    11,   163,   164,   142,    31,    39,
     144,    92,    90,   189,   246,    53,   113,   147,   149,    39,
     195,   195,   123,    88,   189,    39,    15,   130,   132,   134,
     135,    88,     7,   237,   238,   237,   211,   249,   218,   249,
     225,    29,    30,   252,   252,   249,    88,   133,   143,    31,
      39,   134,    91,    92,   142,    92,    92,    15,   257,   263,
     264,   265,   142,   195,    15,   257,   266,   267,   268,   171,
      91,   173,   186,   189,   191,   192,   188,   188,   188,   188,
     181,   181,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,     7,    39,
     169,   195,   106,   158,   159,    40,    90,   168,   189,    92,
     144,   144,   145,   255,   256,   193,   103,    41,    72,    73,
     195,    91,   142,   124,   195,   188,    91,    15,   129,    88,
     239,   241,    88,   237,   216,   237,   223,    77,   253,   253,
     233,     7,   141,    92,   187,   192,    15,    93,   257,   265,
      92,    92,    15,    92,   257,   268,   173,   172,    88,    92,
      91,    93,    15,   188,   188,   189,    91,   170,    89,   174,
     189,   189,   103,   195,    92,   254,     7,   247,    53,   148,
      92,    92,   131,   188,    80,    81,    83,   240,   113,   242,
      88,    77,    88,    77,     7,     7,    77,   192,    88,   189,
     188,    92,   189,    93,   175,   165,   136,   174,   149,   195,
     132,   241,   132,   243,     7,   212,   219,   176,   174,    91,
     249,   249,     1,     7,    45,    46,    47,    48,    49,    50,
      51,    52,    59,    60,    61,    88,   112,   146,   174,   177,
     179,   189,   244,   213,   220,     7,   112,   185,   189,   182,
     182,    39,   182,     7,     7,   182,   189,    15,   178,     7,
     132,    77,    77,     7,   183,   183,   189,   190,   183,    39,
      15,   134,   135,   137,   150,   152,   154,    39,   179,    92,
      39,   189,   166,   167,   151,     7,    91,   190,    47,   179,
     185,   184,   156,   160,   161,   153,    92,    39,     5,   180,
       7,    92,   157,   154,   179,   190,   179,   185,   174,    92,
       7,     7,   185,    92,   179
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])



/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if QC_YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !QC_YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !QC_YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
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

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
/* Line 1787 of yacc.c  */
#line 263 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if (current_class) {
				warning (0, "‘@end’ missing in implementation context");
				class_finish (current_class);
				current_class = 0;
			}
		}
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 273 "../../../../tools/qfcc/source/qc-parse.y"
    {
			current_symtab = pr.symtab;
		}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 279 "../../../../tools/qfcc/source/qc-parse.y"
    {
			yyerrok;
			current_class = 0;
			current_symtab = pr.symtab;
			current_storage = sc_global;
		}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 286 "../../../../tools/qfcc/source/qc-parse.y"
    {
			yyerrok;
			current_class = 0;
			current_symtab = pr.symtab;
			current_storage = sc_global;
		}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 293 "../../../../tools/qfcc/source/qc-parse.y"
    {
			yyerrok;
			current_class = 0;
			current_symtab = pr.symtab;
			current_storage = sc_global;
		}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 302 "../../../../tools/qfcc/source/qc-parse.y"
    { }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 303 "../../../../tools/qfcc/source/qc-parse.y"
    { }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 305 "../../../../tools/qfcc/source/qc-parse.y"
    {
			type_t    **type;
			(yyval.spec) = (yyvsp[(1) - (2)].spec);		// copy spec bits and storage
			// .float () foo; is a field holding a function variable rather
			// than a function that returns a float field.
			for (type = &(yyval.spec).type; *type && (*type)->type == ev_field;
				 type = &(*type)->t.fldptr.type)
				 ;
			*type = parse_params (*type, (yyvsp[(2) - (2)].param));
			(yyval.spec).type = find_type ((yyval.spec).type);
			if ((yyval.spec).type->type != ev_field)
				(yyval.spec).params = (yyvsp[(2) - (2)].param);
		}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 319 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(void) ((yyvsp[(3) - (4)].spec));
		}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 324 "../../../../tools/qfcc/source/qc-parse.y"
    {
			current_storage = (yyvsp[(1) - (3)].spec).storage;
		}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 328 "../../../../tools/qfcc/source/qc-parse.y"
    {
			current_storage = (yyvsp[(3) - (7)].spec).storage;
		}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 335 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.spec).storage = current_storage;
		}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 342 "../../../../tools/qfcc/source/qc-parse.y"
    {
			symbol_t   *sym = (yyvsp[(0) - (1)].symbol);

			if (!(yyvsp[(-1) - (1)].spec).type)
				(yyvsp[(-1) - (1)].spec).type = type_default;
			sym->type = find_type (append_type (sym->type, (yyvsp[(-1) - (1)].spec).type));
			(yyval.symbol) = function_symbol (sym, (yyvsp[(-1) - (1)].spec).is_overload, 1);
		}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 351 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symtab) = current_symtab;
			current_func = begin_function ((yyvsp[(2) - (3)].symbol), 0, current_symtab, 0);
			current_symtab = current_func->symtab;
			current_storage = sc_local;
		}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 358 "../../../../tools/qfcc/source/qc-parse.y"
    {
			build_code_function ((yyvsp[(2) - (5)].symbol), (yyvsp[(1) - (5)].expr), (yyvsp[(5) - (5)].expr));
			current_symtab = (yyvsp[(4) - (5)].symtab);
			current_storage = (yyvsp[(3) - (5)].spec).storage;
			current_func = 0;
		}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 365 "../../../../tools/qfcc/source/qc-parse.y"
    {
			symbol_t   *sym = (yyvsp[(0) - (4)].symbol);

			if (!(yyvsp[(-1) - (4)].spec).type)
				(yyvsp[(-1) - (4)].spec).type = type_default;
			sym->type = find_type (append_type (sym->type, (yyvsp[(-1) - (4)].spec).type));
			sym = function_symbol (sym, (yyvsp[(-1) - (4)].spec).is_overload, 1);
			build_builtin_function (sym, (yyvsp[(3) - (4)].expr), 0);
		}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 378 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = (yyvsp[(0) - (2)].spec); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 379 "../../../../tools/qfcc/source/qc-parse.y"
    { (void) ((yyvsp[(3) - (4)].spec)); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 384 "../../../../tools/qfcc/source/qc-parse.y"
    {
			specifier_t spec = (yyvsp[(0) - (1)].spec);
			type_t     *type;

			if (!spec.type)
				spec.type = type_default;
			type = find_type (append_type ((yyvsp[(1) - (1)].symbol)->type, spec.type));
			if (spec.is_typedef) {
				(yyvsp[(1) - (1)].symbol)->type = type;
				(yyvsp[(1) - (1)].symbol)->sy_type = sy_type;
				symtab_addsymbol (current_symtab, (yyvsp[(1) - (1)].symbol));
			} else {
				initialize_def ((yyvsp[(1) - (1)].symbol), type, 0, current_symtab->space,
								spec.storage);
				if ((yyvsp[(1) - (1)].symbol)->s.def)
					(yyvsp[(1) - (1)].symbol)->s.def->nosave |= spec.nosave;
			}
		}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 403 "../../../../tools/qfcc/source/qc-parse.y"
    {
			specifier_t spec = (yyvsp[(0) - (2)].spec);
			type_t     *type;

			if (!spec.type)
				spec.type = type_default;
			type = find_type (append_type ((yyvsp[(1) - (2)].symbol)->type, spec.type));
			if (spec.is_typedef) {
				error (0, "typedef %s is initialized", (yyvsp[(1) - (2)].symbol)->name);
				(yyvsp[(1) - (2)].symbol)->type = type;
				(yyvsp[(1) - (2)].symbol)->sy_type = sy_type;
				symtab_addsymbol (current_symtab, (yyvsp[(1) - (2)].symbol));
			} else {
				initialize_def ((yyvsp[(1) - (2)].symbol), type, (yyvsp[(2) - (2)].expr), current_symtab->space,
								spec.storage);
				if ((yyvsp[(1) - (2)].symbol)->s.def)
					(yyvsp[(1) - (2)].symbol)->s.def->nosave |= spec.nosave;
			}
		}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 423 "../../../../tools/qfcc/source/qc-parse.y"
    {
			specifier_t spec = (yyvsp[(0) - (1)].spec);
			if (!spec.type)
				spec.type = type_default;
			(yyvsp[(1) - (1)].symbol)->type = find_type (append_type ((yyvsp[(1) - (1)].symbol)->type, spec.type));
			if (spec.is_typedef) {
				(yyvsp[(1) - (1)].symbol)->sy_type = sy_type;
				symtab_addsymbol (current_symtab, (yyvsp[(1) - (1)].symbol));
			} else {
				(yyvsp[(1) - (1)].symbol) = function_symbol ((yyvsp[(1) - (1)].symbol), spec.is_overload, 1);
				// things might be a confused mess from earlier errors
				if ((yyvsp[(1) - (1)].symbol)->sy_type == sy_func)
					make_function ((yyvsp[(1) - (1)].symbol), 0, (yyvsp[(1) - (1)].symbol)->table->space, spec.storage);
			}
		}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 441 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = make_spec (0, sc_extern, 0, 0); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 442 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = make_spec (0, sc_static, 0, 0); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 443 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = make_spec (0, sc_system, 0, 0); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 444 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = make_spec (0, sc_global, 1, 0); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 445 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = make_spec (0, current_storage, 0, 1); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 447 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.spec) = make_spec (0, current_storage, 0, 0);
			(yyval.spec).nosave = 1;
		}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 455 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.spec) = (yyvsp[(1) - (1)].spec);
			if (!(yyval.spec).storage)
				(yyval.spec).storage = current_storage;
		}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 461 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.spec) = make_spec (0, current_storage, 0, 0);
		}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 469 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.spec) = spec_merge ((yyvsp[(1) - (2)].spec), (yyvsp[(2) - (2)].spec));
		}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 486 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.spec) = make_spec ((yyvsp[(1) - (1)].type), 0, 0, 0);
		}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 492 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.spec) = make_spec ((yyvsp[(1) - (1)].symbol)->type, 0, 0, 0);
		}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 496 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if ((yyvsp[(2) - (2)].protocol_list)) {
				type_t      type = *type_id.t.fldptr.type;
				type.next = 0;
				type.protos = (yyvsp[(2) - (2)].protocol_list);
				(yyval.spec) = make_spec (pointer_type (find_type (&type)), 0, 0, 0);
			} else {
				(yyval.spec) = make_spec (&type_id, 0, 0, 0);
			}
		}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 507 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if ((yyvsp[(2) - (2)].protocol_list)) {
				type_t      type = *(yyvsp[(1) - (2)].symbol)->type;
				type.next = 0;
				type.protos = (yyvsp[(2) - (2)].protocol_list);
				(yyval.spec) = make_spec (find_type (&type), 0, 0, 0);
			} else {
				(yyval.spec) = make_spec ((yyvsp[(1) - (2)].symbol)->type, 0, 0, 0);
			}
		}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 520 "../../../../tools/qfcc/source/qc-parse.y"
    {
			// avoid find_type()
			(yyval.spec) = make_spec (field_type (0), 0, 0, 0);
			(yyval.spec).type = append_type ((yyval.spec).type, (yyvsp[(2) - (2)].spec).type);
		}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 529 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = 0; }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 536 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.spec) = make_spec ((yyvsp[(3) - (3)].symbol)->type, 0, 0, 0);
			if (!(yyvsp[(3) - (3)].symbol)->table)
				symtab_addsymbol (current_symtab, (yyvsp[(3) - (3)].symbol));
		}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 542 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.spec) = make_spec ((yyvsp[(2) - (2)].symbol)->type, 0, 0, 0);
			if (!(yyvsp[(2) - (2)].symbol)->table)
				symtab_addsymbol (current_symtab, (yyvsp[(2) - (2)].symbol));
		}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 551 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = find_enum ((yyvsp[(0) - (0)].symbol)); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 556 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = finish_enum ((yyvsp[(3) - (5)].symbol));
		}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 563 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = find_enum ((yyvsp[(-1) - (0)].symbol));
			start_enum ((yyval.symbol));
		}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 570 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = (yyvsp[(0) - (1)].symbol); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 571 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = (yyvsp[(0) - (2)].symbol); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 573 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(0) - (4)].symbol);
			(void) ((yyvsp[(3) - (4)].symbol));
		}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 580 "../../../../tools/qfcc/source/qc-parse.y"
    { add_enum ((yyvsp[(0) - (1)].symbol), (yyvsp[(1) - (1)].symbol), 0); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 581 "../../../../tools/qfcc/source/qc-parse.y"
    { add_enum ((yyvsp[(0) - (3)].symbol), (yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].expr)); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 586 "../../../../tools/qfcc/source/qc-parse.y"
    {
			symbol_t   *sym;
			sym = find_struct ((yyvsp[(1) - (3)].op), (yyvsp[(2) - (3)].symbol), 0);
			if (!sym->table)
				symtab_addsymbol (current_symtab, sym);
			current_symtab = new_symtab (current_symtab, stab_local);
		}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 594 "../../../../tools/qfcc/source/qc-parse.y"
    {
			symbol_t   *sym;
			symtab_t   *symtab = current_symtab;
			current_symtab = symtab->parent;

			sym = build_struct ((yyvsp[(1) - (6)].op), (yyvsp[(2) - (6)].symbol), symtab, 0);
			(yyval.spec) = make_spec (sym->type, 0, 0, 0);
			if (!sym->table)
				symtab_addsymbol (current_symtab, sym);
		}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 605 "../../../../tools/qfcc/source/qc-parse.y"
    {
			symbol_t   *sym;

			sym = find_struct ((yyvsp[(1) - (2)].op), (yyvsp[(2) - (2)].symbol), 0);
			(yyval.spec) = make_spec (sym->type, 0, 0, 0);
			if (!sym->table)
				symtab_addsymbol (current_symtab, sym);
		}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 618 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(3) - (4)].symbol) = check_undefined ((yyvsp[(3) - (4)].symbol));
			if (!(yyvsp[(3) - (4)].symbol)->type || !obj_is_class ((yyvsp[(3) - (4)].symbol)->type)) {
				error (0, "`%s' is not a class", (yyvsp[(3) - (4)].symbol)->name);
			} else {
				// replace the struct symbol table with one built from
				// the class ivars and the current struct fields. ivars
				// will replace any fields of the same name.
				current_symtab = class_to_struct ((yyvsp[(3) - (4)].symbol)->type->t.class,
												  current_symtab);
			}
		}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 643 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = (yyvsp[(0) - (2)].spec); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 644 "../../../../tools/qfcc/source/qc-parse.y"
    { (void) ((yyvsp[(3) - (4)].spec)); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 650 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if (!(yyvsp[(0) - (1)].spec).type)
				(yyvsp[(0) - (1)].spec).type = type_default;
			(yyvsp[(1) - (1)].symbol)->type = append_type ((yyvsp[(1) - (1)].symbol)->type, (yyvsp[(0) - (1)].spec).type);
			(yyvsp[(1) - (1)].symbol)->type = find_type ((yyvsp[(1) - (1)].symbol)->type);
			symtab_addsymbol (current_symtab, (yyvsp[(1) - (1)].symbol));
		}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 658 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if (!(yyvsp[(0) - (1)].spec).type)
				(yyvsp[(0) - (1)].spec).type = type_default;
			(yyvsp[(1) - (1)].symbol)->type = append_type ((yyvsp[(1) - (1)].symbol)->type, (yyvsp[(0) - (1)].spec).type);
			(yyvsp[(1) - (1)].symbol)->type = find_type ((yyvsp[(1) - (1)].symbol)->type);
			symtab_addsymbol (current_symtab, (yyvsp[(1) - (1)].symbol));
		}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 665 "../../../../tools/qfcc/source/qc-parse.y"
    {}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 666 "../../../../tools/qfcc/source/qc-parse.y"
    {}
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 671 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(1) - (1)].symbol);
			// due to the way declarations work, we need a new symbol at all
			// times. redelcarations will be checked later
			if ((yyval.symbol)->table)
				(yyval.symbol) = new_symbol ((yyvsp[(1) - (1)].symbol)->name);
		}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 682 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(1) - (1)].symbol);
			(yyval.symbol)->type = 0;
		}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 687 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol)->type = append_type ((yyval.symbol)->type, parse_params (0, (yyvsp[(2) - (2)].param)));
		}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 691 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol)->type = append_type ((yyval.symbol)->type, array_type (0, (yyvsp[(2) - (2)].size)));
		}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 695 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
			(yyval.symbol)->type = append_type ((yyval.symbol)->type, pointer_type (0));
		}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 699 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 704 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
			(yyval.symbol)->type = append_type ((yyval.symbol)->type, pointer_type (0));
		}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 709 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(1) - (2)].symbol);
			(yyval.symbol)->type = append_type ((yyval.symbol)->type, array_type (0, (yyvsp[(2) - (2)].size)));
		}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 713 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 715 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(1) - (2)].symbol);
			(yyval.symbol)->params = (yyvsp[(2) - (2)].param);
			(yyval.symbol)->type = append_type ((yyval.symbol)->type, parse_params (0, (yyvsp[(2) - (2)].param)));
		}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 721 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(1) - (2)].symbol);
			(yyval.symbol)->params = (yyvsp[(2) - (2)].param);
			(yyval.symbol)->type = parse_params (0, (yyvsp[(2) - (2)].param));
		}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 729 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = 0; }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 730 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = check_params ((yyvsp[(3) - (4)].param)); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 734 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = 0; }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 735 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = check_params ((yyvsp[(3) - (4)].param)); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 737 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if ((yyvsp[(3) - (4)].type) != &type_void)
				PARSE_ERROR;
			(yyval.param) = 0;
		}
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 749 "../../../../tools/qfcc/source/qc-parse.y"
    {
			param_t    *p;

			for (p = (yyvsp[(1) - (3)].param); p->next; p = p->next)
				;
			p->next = (yyvsp[(3) - (3)].param);
			(yyval.param) = (yyvsp[(1) - (3)].param);
		}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 762 "../../../../tools/qfcc/source/qc-parse.y"
    {
			param_t    *p;

			for (p = (yyvsp[(1) - (3)].param); p->next; p = p->next)
				;
			p->next = (yyvsp[(3) - (3)].param);
			(yyval.param) = (yyvsp[(1) - (3)].param);
		}
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 774 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if (!(yyvsp[(1) - (2)].spec).type)
				(yyvsp[(1) - (2)].spec).type = type_default;
			(yyvsp[(2) - (2)].symbol)->type = find_type (append_type ((yyvsp[(2) - (2)].symbol)->type, (yyvsp[(1) - (2)].spec).type));
			(yyval.param) = new_param (0, (yyvsp[(2) - (2)].symbol)->type, (yyvsp[(2) - (2)].symbol)->name);
		}
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 780 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = new_param (0, (yyvsp[(1) - (1)].symbol)->type, 0); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 781 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = new_param (0, 0, 0); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 786 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
			if (!(yyvsp[(1) - (2)].spec).type)
				(yyvsp[(1) - (2)].spec).type = type_default;
			(yyval.symbol)->type = find_type (append_type ((yyval.symbol)->type, (yyvsp[(1) - (2)].spec).type));
		}
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 796 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(2) - (2)].symbol)->type = find_type ((yyvsp[(1) - (2)].spec).type);
			(yyval.param) = new_param (0, (yyvsp[(2) - (2)].symbol)->type, (yyvsp[(2) - (2)].symbol)->name);
		}
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 801 "../../../../tools/qfcc/source/qc-parse.y"
    {
			type_t    **type;
			// .float () foo; is a field holding a function variable rather
			// than a function that returns a float field.
			for (type = &(yyvsp[(1) - (3)].spec).type; *type && (*type)->type == ev_field;
				 type = &(*type)->t.fldptr.type)
				 ;
			*type = parse_params (*type, (yyvsp[(2) - (3)].param));
			(yyvsp[(3) - (3)].symbol)->type = find_type ((yyvsp[(1) - (3)].spec).type);
			if ((yyvsp[(3) - (3)].symbol)->type->type != ev_field)
				(yyvsp[(3) - (3)].symbol)->params = (yyvsp[(2) - (3)].param);
			(yyval.param) = new_param (0, (yyvsp[(3) - (3)].symbol)->type, (yyvsp[(3) - (3)].symbol)->name);
		}
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 814 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = new_param (0, 0, 0); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 818 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (""); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 820 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(2) - (4)].symbol);
			(yyval.symbol)->type = append_type ((yyval.symbol)->type, parse_params (0, (yyvsp[(4) - (4)].param)));
		}
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 825 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
			(yyval.symbol)->type = append_type ((yyval.symbol)->type, pointer_type (0));
		}
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 830 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(1) - (2)].symbol);
			(yyval.symbol)->type = append_type ((yyval.symbol)->type, array_type (0, (yyvsp[(2) - (2)].size)));
		}
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 835 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(2) - (3)].symbol);
		}
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 842 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(2) - (3)].expr) = fold_constants ((yyvsp[(2) - (3)].expr));
			if (!is_integer_val ((yyvsp[(2) - (3)].expr)) || expr_integer ((yyvsp[(2) - (3)].expr)) < 1) {
				error (0, "invalid array size");
				(yyval.size) = 0;
			} else {
				(yyval.size) = expr_integer ((yyvsp[(2) - (3)].expr));
			}
		}
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 851 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.size) = 0; }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 855 "../../../../tools/qfcc/source/qc-parse.y"
    {  (yyval.spec) = (yyvsp[(2) - (2)].spec); }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 856 "../../../../tools/qfcc/source/qc-parse.y"
    {  (yyval.spec) = (yyvsp[(1) - (1)].spec); }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 860 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = (yyvsp[(1) - (1)].param); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 861 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = (yyvsp[(1) - (2)].param); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 862 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.param) = (yyvsp[(4) - (4)].param);
			(void) ((yyvsp[(3) - (4)].symbol));
		}
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 870 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(2) - (2)].symbol) = check_redefined ((yyvsp[(2) - (2)].symbol));
			(yyval.param) = param_append_identifiers ((yyvsp[(0) - (2)].param), (yyvsp[(2) - (2)].symbol), (yyvsp[(1) - (2)].spec).type);
		}
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 879 "../../../../tools/qfcc/source/qc-parse.y"
    {
			type_t    **type;
			specifier_t spec = (yyvsp[(0) - (1)].spec);	// copy spec bits and storage
			// .float () foo; is a field holding a function variable rather
			// than a function that returns a float field.
			for (type = &spec.type; *type && (*type)->type == ev_field;
				 type = &(*type)->t.fldptr.type)
				 ;
			*type = parse_params (*type, (yyvsp[(1) - (1)].param));
			spec.type = find_type (spec.type);
			(yyval.spec) = spec;
		}
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 892 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(void) ((yyvsp[(2) - (3)].spec));
		}
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 898 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = (yyvsp[(0) - (2)].spec); }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 898 "../../../../tools/qfcc/source/qc-parse.y"
    { (void) ((yyvsp[(3) - (4)].spec)); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 903 "../../../../tools/qfcc/source/qc-parse.y"
    {}
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 905 "../../../../tools/qfcc/source/qc-parse.y"
    {
			specifier_t spec = (yyvsp[(0) - (2)].spec);
			type_t     *type;
			storage_class_t sc = (yyvsp[(0) - (2)].spec).storage;
			struct defspace_s *space = current_symtab->space;

			if (!spec.type)
				spec.type = type_default;
			if (sc == sc_static)
				space = pr.near_data;
			type = find_type (append_type ((yyvsp[(1) - (2)].symbol)->type, spec.type));
			initialize_def ((yyvsp[(1) - (2)].symbol), type, (yyvsp[(2) - (2)].expr), space, sc);
			if ((yyvsp[(1) - (2)].symbol)->s.def)
				(yyvsp[(1) - (2)].symbol)->s.def->nosave |= (yyvsp[(0) - (2)].spec).nosave;
		}
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 928 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = (yyvsp[(2) - (3)].spec); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 929 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = (yyvsp[(0) - (1)].spec); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 935 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = (yyvsp[(0) - (1)].spec); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 958 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symbol) = (yyvsp[(1) - (1)].symbol);
			(yyval.symbol)->type = (yyvsp[(0) - (1)].spec).type;
			if (!local_expr && (yyval.symbol)->type->type != ev_field) {
				(yyval.symbol) = function_symbol ((yyval.symbol), (yyvsp[(0) - (1)].spec).is_overload, 1);
				(yyval.symbol)->params = (yyvsp[(0) - (1)].spec).params;
			}
		}
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 970 "../../../../tools/qfcc/source/qc-parse.y"
    {
			build_builtin_function ((yyvsp[(0) - (3)].symbol), (yyvsp[(3) - (3)].expr), 0);
		}
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 974 "../../../../tools/qfcc/source/qc-parse.y"
    {
			symbol_t   *sym = (yyvsp[(0) - (2)].symbol);
			specifier_t spec = (yyvsp[(-1) - (2)].spec);
			initialize_def (sym, sym->type, (yyvsp[(2) - (2)].expr), current_symtab->space,
							spec.storage);
			if (sym->s.def)
				sym->s.def->nosave |= spec.nosave;
		}
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 983 "../../../../tools/qfcc/source/qc-parse.y"
    {
			symbol_t   *sym = (yyvsp[(0) - (0)].symbol);
			specifier_t spec = (yyvsp[(-1) - (0)].spec);
			if (!local_expr && sym->type->type != ev_field) {
				// things might be a confused mess from earlier errors
				if (sym->sy_type == sy_func)
					make_function (sym, 0, sym->table->space, spec.storage);
			} else {
				initialize_def (sym, sym->type, 0, current_symtab->space,
								spec.storage);
				if (sym->s.def)
					sym->s.def->nosave |= spec.nosave;
			}
		}
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 1002 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.symtab) = current_symtab;
			current_func = begin_function ((yyvsp[(0) - (3)].symbol), 0, current_symtab, 0);
			current_symtab = current_func->symtab;
			current_storage = sc_local;
		}
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 1009 "../../../../tools/qfcc/source/qc-parse.y"
    {
			build_code_function ((yyvsp[(0) - (5)].symbol), (yyvsp[(2) - (5)].expr), (yyvsp[(5) - (5)].expr));
			current_symtab = (yyvsp[(4) - (5)].symtab);
			current_storage = (yyvsp[(3) - (5)].spec).storage;
			current_func = 0;
		}
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 1018 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = 0; }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 1019 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 1023 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(2) - (2)].expr); }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 1024 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(3) - (5)].expr); }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 1028 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = 0; }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 1029 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = build_state_expr ((yyvsp[(2) - (6)].expr), (yyvsp[(4) - (6)].expr), (yyvsp[(5) - (6)].expr)); }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 1034 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = think_expr ((yyvsp[(1) - (1)].symbol));
		}
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 1038 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = (yyvsp[(2) - (3)].expr);
		}
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 1044 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(2) - (2)].expr); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 1045 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = 0; }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 1050 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = new_block_expr ();
			append_expr ((yyval.expr), (yyvsp[(1) - (1)].expr));
		}
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 1055 "../../../../tools/qfcc/source/qc-parse.y"
    {
			append_expr ((yyval.expr), (yyvsp[(3) - (3)].expr));
		}
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 1061 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(2) - (4)].expr); }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 1062 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 1072 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if (!options.traditional) {
				current_symtab = new_symtab (current_symtab, stab_local);
				current_symtab->space = current_symtab->parent->space;
			}
		}
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 1079 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if (!options.traditional)
				current_symtab = current_symtab->parent;
			(yyval.expr) = (yyvsp[(3) - (4)].expr);
		}
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 1088 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = new_block_expr ();
		}
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 1092 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = append_expr ((yyvsp[(1) - (2)].expr), (yyvsp[(2) - (2)].expr));
		}
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 1099 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if (!(yyvsp[(1) - (1)].spec).storage)
				(yyvsp[(1) - (1)].spec).storage = sc_local;
			(yyval.spec) = (yyvsp[(1) - (1)].spec);
			local_expr = new_block_expr ();
		}
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 1106 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = local_expr;
			local_expr = 0;
			(void) ((yyvsp[(2) - (4)].spec));
		}
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 1114 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = 0; }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 1115 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = 0; yyerrok; }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 1116 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 1117 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 1119 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = return_expr (current_func, (yyvsp[(2) - (3)].expr));
		}
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 1123 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = 0;
			if (break_label)
				(yyval.expr) = goto_expr (break_label);
			else
				error (0, "break outside of loop or switch");
		}
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 1131 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = 0;
			if (continue_label)
				(yyval.expr) = goto_expr (continue_label);
			else
				error (0, "continue outside of loop");
		}
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 1139 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = case_label_expr (switch_block, (yyvsp[(2) - (3)].expr));
		}
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 1143 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = case_label_expr (switch_block, 0);
		}
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 1147 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = switch_expr (switch_block, break_label, (yyvsp[(7) - (7)].expr));
			switch_block = (yyvsp[(5) - (7)].switch_block);
			break_label = (yyvsp[(2) - (7)].expr);
		}
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 1153 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = build_if_statement ((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].expr), 0, 0);
		}
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 1157 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = build_if_statement ((yyvsp[(3) - (7)].expr), (yyvsp[(5) - (7)].expr), (yyvsp[(6) - (7)].expr), (yyvsp[(7) - (7)].expr));
		}
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 1162 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = build_for_statement ((yyvsp[(5) - (11)].expr), (yyvsp[(7) - (11)].expr), (yyvsp[(9) - (11)].expr), (yyvsp[(11) - (11)].expr),
									  break_label, continue_label);
			break_label = (yyvsp[(2) - (11)].expr);
			continue_label = (yyvsp[(3) - (11)].expr);
		}
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 1169 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = build_while_statement ((yyvsp[(5) - (7)].expr), (yyvsp[(7) - (7)].expr), break_label, continue_label);
			break_label = (yyvsp[(2) - (7)].expr);
			continue_label = (yyvsp[(3) - (7)].expr);
		}
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 1175 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = build_do_while_statement ((yyvsp[(4) - (9)].expr), (yyvsp[(7) - (9)].expr),
										   break_label, continue_label);
			break_label = (yyvsp[(2) - (9)].expr);
			continue_label = (yyvsp[(3) - (9)].expr);
		}
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 1182 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = (yyvsp[(1) - (2)].expr);
		}
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 1189 "../../../../tools/qfcc/source/qc-parse.y"
    {
			// this is only to get the the file and line number info
			(yyval.expr) = new_nil_expr ();
		}
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 1197 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = new_label_expr ();
		}
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 1204 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = break_label;
			break_label = new_label_expr ();
		}
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 1212 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = continue_label;
			continue_label = new_label_expr ();
		}
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 1220 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.switch_block) = switch_block;
			switch_block = new_switch_block ();
			switch_block->test = (yyvsp[(0) - (0)].expr);
		}
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 1230 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = 0;
		}
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 1236 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = new_symbol_expr ((yyvsp[(1) - (1)].symbol)); }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 1237 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = new_name_expr (".args"); }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 1238 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = new_self_expr (); }
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 1239 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = new_this_expr (); }
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 1240 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 1241 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); (yyval.expr)->paren = 1; }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 1242 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = function_expr ((yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr)); }
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 1243 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = array_expr ((yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr)); }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 1244 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr ('.', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 1245 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = incop_expr ((yyvsp[(1) - (2)].op), (yyvsp[(2) - (2)].expr), 0); }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 1246 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = incop_expr ((yyvsp[(2) - (2)].op), (yyvsp[(1) - (2)].expr), 1); }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 1247 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(2) - (2)].expr); }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 1248 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = unary_expr ('-', (yyvsp[(2) - (2)].expr)); }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 1249 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = unary_expr ('!', (yyvsp[(2) - (2)].expr)); }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 1250 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = unary_expr ('~', (yyvsp[(2) - (2)].expr)); }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 1251 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = address_expr ((yyvsp[(2) - (2)].expr), 0, 0); }
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 1252 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = pointer_expr ((yyvsp[(2) - (2)].expr)); }
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 1253 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = sizeof_expr ((yyvsp[(2) - (2)].expr), 0); }
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 1255 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = sizeof_expr (0, (yyvsp[(3) - (4)].symbol)->type);
		}
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 1258 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 1263 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = cast_expr ((yyvsp[(2) - (4)].symbol)->type, (yyvsp[(4) - (4)].expr));
		}
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 1271 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = assign_expr ((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 214:
/* Line 1787 of yacc.c  */
#line 1272 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = asx_expr ((yyvsp[(2) - (3)].op), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 215:
/* Line 1787 of yacc.c  */
#line 1273 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = conditional_expr ((yyvsp[(1) - (5)].expr), (yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].expr)); }
    break;

  case 216:
/* Line 1787 of yacc.c  */
#line 1274 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = bool_expr (AND, (yyvsp[(3) - (4)].expr), (yyvsp[(1) - (4)].expr), (yyvsp[(4) - (4)].expr)); }
    break;

  case 217:
/* Line 1787 of yacc.c  */
#line 1275 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = bool_expr (OR,  (yyvsp[(3) - (4)].expr), (yyvsp[(1) - (4)].expr), (yyvsp[(4) - (4)].expr)); }
    break;

  case 218:
/* Line 1787 of yacc.c  */
#line 1276 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr (EQ,  (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 219:
/* Line 1787 of yacc.c  */
#line 1277 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr (NE,  (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 220:
/* Line 1787 of yacc.c  */
#line 1278 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr (LE,  (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 221:
/* Line 1787 of yacc.c  */
#line 1279 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr (GE,  (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 222:
/* Line 1787 of yacc.c  */
#line 1280 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr (LT,  (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 223:
/* Line 1787 of yacc.c  */
#line 1281 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr (GT,  (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 224:
/* Line 1787 of yacc.c  */
#line 1282 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr (SHL, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 225:
/* Line 1787 of yacc.c  */
#line 1283 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr (SHR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 226:
/* Line 1787 of yacc.c  */
#line 1284 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr ('+', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 227:
/* Line 1787 of yacc.c  */
#line 1285 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr ('-', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 228:
/* Line 1787 of yacc.c  */
#line 1286 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr ('*', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 229:
/* Line 1787 of yacc.c  */
#line 1287 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr ('/', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 230:
/* Line 1787 of yacc.c  */
#line 1288 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr ('&', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 231:
/* Line 1787 of yacc.c  */
#line 1289 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr ('|', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 232:
/* Line 1787 of yacc.c  */
#line 1290 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr ('^', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 233:
/* Line 1787 of yacc.c  */
#line 1291 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr ('%', (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 234:
/* Line 1787 of yacc.c  */
#line 1295 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = fold_constants ((yyvsp[(1) - (1)].expr)); }
    break;

  case 235:
/* Line 1787 of yacc.c  */
#line 1299 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = convert_bool ((yyvsp[(1) - (1)].expr), 1); }
    break;

  case 236:
/* Line 1787 of yacc.c  */
#line 1303 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = 0; }
    break;

  case 237:
/* Line 1787 of yacc.c  */
#line 1304 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 239:
/* Line 1787 of yacc.c  */
#line 1310 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(3) - (3)].expr)->next = (yyvsp[(1) - (3)].expr);
			(yyval.expr) = (yyvsp[(3) - (3)].expr);
		}
    break;

  case 241:
/* Line 1787 of yacc.c  */
#line 1318 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = new_nil_expr (); }
    break;

  case 244:
/* Line 1787 of yacc.c  */
#line 1324 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = binary_expr ('+', (yyvsp[(1) - (2)].expr), (yyvsp[(2) - (2)].expr)); }
    break;

  case 249:
/* Line 1787 of yacc.c  */
#line 1337 "../../../../tools/qfcc/source/qc-parse.y"
    { }
    break;

  case 252:
/* Line 1787 of yacc.c  */
#line 1340 "../../../../tools/qfcc/source/qc-parse.y"
    { if (!current_class) PARSE_ERROR; }
    break;

  case 254:
/* Line 1787 of yacc.c  */
#line 1342 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if (!current_class)
				PARSE_ERROR;
			else
				class_finish (current_class);
			current_class = 0;
		}
    break;

  case 255:
/* Line 1787 of yacc.c  */
#line 1353 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = append_expr (new_block_expr (), new_symbol_expr ((yyvsp[(1) - (1)].symbol)));
		}
    break;

  case 256:
/* Line 1787 of yacc.c  */
#line 1357 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = append_expr ((yyvsp[(1) - (3)].expr), new_symbol_expr ((yyvsp[(3) - (3)].symbol)));
		}
    break;

  case 257:
/* Line 1787 of yacc.c  */
#line 1364 "../../../../tools/qfcc/source/qc-parse.y"
    {
			expr_t     *e;
			for (e = (yyvsp[(2) - (3)].expr)->e.block.head; e; e = e->next) {
				get_class (e->e.symbol, 1);
				if (!e->e.symbol->table)
					symtab_addsymbol (current_symtab, e->e.symbol);
			}
		}
    break;

  case 258:
/* Line 1787 of yacc.c  */
#line 1376 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(1) - (1)].symbol) = check_undefined ((yyvsp[(1) - (1)].symbol));
			if (!(yyvsp[(1) - (1)].symbol)->type || !obj_is_class ((yyvsp[(1) - (1)].symbol)->type)) {
				error (0, "`%s' is not a class %p", (yyvsp[(1) - (1)].symbol)->name, (yyvsp[(1) - (1)].symbol)->type);
				(yyval.class) = get_class (0, 1);
			} else {
				(yyval.class) = (yyvsp[(1) - (1)].symbol)->type->t.class;
			}
		}
    break;

  case 259:
/* Line 1787 of yacc.c  */
#line 1389 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if (current_class) {
				warning (0, "‘@end’ missing in implementation context");
				class_finish (current_class);
				current_class = 0;
			}
			(yyval.class) = get_class ((yyvsp[(1) - (1)].symbol), 0);
			if (!(yyval.class)) {
				(yyvsp[(1) - (1)].symbol) = check_redefined ((yyvsp[(1) - (1)].symbol));
				(yyval.class) = get_class ((yyvsp[(1) - (1)].symbol), 1);
			}
			current_class = &(yyval.class)->class_type;
			if (!(yyvsp[(1) - (1)].symbol)->table)
				symtab_addsymbol (current_symtab, (yyvsp[(1) - (1)].symbol));
		}
    break;

  case 260:
/* Line 1787 of yacc.c  */
#line 1408 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if ((yyvsp[(1) - (3)].class)->super_class != (yyvsp[(3) - (3)].class))
				error (0, "%s is not a super class of %s", (yyvsp[(3) - (3)].class)->name, (yyvsp[(1) - (3)].class)->name);
			(yyval.class) = (yyvsp[(1) - (3)].class);
		}
    break;

  case 261:
/* Line 1787 of yacc.c  */
#line 1417 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(1) - (3)].class)->super_class = (yyvsp[(3) - (3)].class);
			(yyval.class) = (yyvsp[(1) - (3)].class);
		}
    break;

  case 262:
/* Line 1787 of yacc.c  */
#line 1425 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.category) = get_category ((yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].symbol)->name, 0);
			if (!(yyval.category)) {
				error (0, "undefined category `%s (%s)'", (yyvsp[(1) - (4)].symbol)->name, (yyvsp[(3) - (4)].symbol)->name);
				(yyval.category) = get_category (0, 0, 1);
			}
		}
    break;

  case 263:
/* Line 1787 of yacc.c  */
#line 1436 "../../../../tools/qfcc/source/qc-parse.y"
    {
			if (current_class) {
				warning (0, "‘@end’ missing in implementation context");
				class_finish (current_class);
				current_class = 0;
			}
			(yyval.category) = get_category ((yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].symbol)->name, 1);
			if ((yyval.category)->defined) {
				error (0, "redefinition of category `%s (%s)'",
					   (yyvsp[(1) - (4)].symbol)->name, (yyvsp[(3) - (4)].symbol)->name);
				(yyval.category) = get_category (0, 0, 1);
			}
			current_class = &(yyval.category)->class_type;
		}
    break;

  case 264:
/* Line 1787 of yacc.c  */
#line 1454 "../../../../tools/qfcc/source/qc-parse.y"
    {
			emit_class_ref ((yyvsp[(1) - (1)].symbol)->name);
		}
    break;

  case 265:
/* Line 1787 of yacc.c  */
#line 1461 "../../../../tools/qfcc/source/qc-parse.y"
    {
			emit_category_ref ((yyvsp[(1) - (4)].symbol)->name, (yyvsp[(3) - (4)].symbol)->name);
		}
    break;

  case 266:
/* Line 1787 of yacc.c  */
#line 1469 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.protocol) = get_protocol ((yyvsp[(1) - (1)].symbol)->name, 0);
			if ((yyval.protocol)) {
				error (0, "redefinition of %s", (yyvsp[(1) - (1)].symbol)->name);
				(yyval.protocol) = get_protocol (0, 1);
			} else {
				(yyval.protocol) = get_protocol ((yyvsp[(1) - (1)].symbol)->name, 1);
			}
			current_class = &(yyval.protocol)->class_type;
		}
    break;

  case 267:
/* Line 1787 of yacc.c  */
#line 1483 "../../../../tools/qfcc/source/qc-parse.y"
    { class_add_protocols ((yyvsp[(2) - (3)].class), (yyvsp[(3) - (3)].protocol_list)); }
    break;

  case 268:
/* Line 1787 of yacc.c  */
#line 1484 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.class) = (yyvsp[(2) - (5)].class); }
    break;

  case 269:
/* Line 1787 of yacc.c  */
#line 1486 "../../../../tools/qfcc/source/qc-parse.y"
    {
			class_add_ivars ((yyvsp[(2) - (8)].class), (yyvsp[(7) - (8)].symtab));
			(yyval.class) = (yyvsp[(2) - (8)].class);
		}
    break;

  case 270:
/* Line 1787 of yacc.c  */
#line 1490 "../../../../tools/qfcc/source/qc-parse.y"
    { class_add_methods ((yyvsp[(2) - (10)].class), (yyvsp[(10) - (10)].methodlist)); }
    break;

  case 271:
/* Line 1787 of yacc.c  */
#line 1492 "../../../../tools/qfcc/source/qc-parse.y"
    {
			current_class = 0;
			(void) ((yyvsp[(6) - (12)].class));
			(void) ((yyvsp[(9) - (12)].class));
		}
    break;

  case 272:
/* Line 1787 of yacc.c  */
#line 1498 "../../../../tools/qfcc/source/qc-parse.y"
    { class_add_protocols ((yyvsp[(2) - (3)].class), (yyvsp[(3) - (3)].protocol_list)); }
    break;

  case 273:
/* Line 1787 of yacc.c  */
#line 1499 "../../../../tools/qfcc/source/qc-parse.y"
    {
			class_add_ivars ((yyvsp[(2) - (4)].class), class_new_ivars ((yyvsp[(2) - (4)].class)));
			(yyval.class) = (yyvsp[(2) - (4)].class);
		}
    break;

  case 274:
/* Line 1787 of yacc.c  */
#line 1503 "../../../../tools/qfcc/source/qc-parse.y"
    { class_add_methods ((yyvsp[(2) - (6)].class), (yyvsp[(6) - (6)].methodlist)); }
    break;

  case 275:
/* Line 1787 of yacc.c  */
#line 1505 "../../../../tools/qfcc/source/qc-parse.y"
    {
			current_class = 0;
			(void) ((yyvsp[(5) - (8)].class));
		}
    break;

  case 276:
/* Line 1787 of yacc.c  */
#line 1510 "../../../../tools/qfcc/source/qc-parse.y"
    { class_add_protocols ((yyvsp[(2) - (3)].class), (yyvsp[(3) - (3)].protocol_list));}
    break;

  case 277:
/* Line 1787 of yacc.c  */
#line 1511 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.class) = (yyvsp[(2) - (5)].class); }
    break;

  case 278:
/* Line 1787 of yacc.c  */
#line 1513 "../../../../tools/qfcc/source/qc-parse.y"
    {
			class_add_ivars ((yyvsp[(2) - (8)].class), (yyvsp[(7) - (8)].symtab));
			(yyval.class) = (yyvsp[(2) - (8)].class);
		}
    break;

  case 279:
/* Line 1787 of yacc.c  */
#line 1517 "../../../../tools/qfcc/source/qc-parse.y"
    { class_add_methods ((yyvsp[(2) - (10)].class), (yyvsp[(10) - (10)].methodlist)); }
    break;

  case 280:
/* Line 1787 of yacc.c  */
#line 1519 "../../../../tools/qfcc/source/qc-parse.y"
    {
			current_class = 0;
			(void) ((yyvsp[(6) - (12)].class));
			(void) ((yyvsp[(9) - (12)].class));
		}
    break;

  case 281:
/* Line 1787 of yacc.c  */
#line 1525 "../../../../tools/qfcc/source/qc-parse.y"
    { class_add_protocols ((yyvsp[(2) - (3)].class), (yyvsp[(3) - (3)].protocol_list)); }
    break;

  case 282:
/* Line 1787 of yacc.c  */
#line 1526 "../../../../tools/qfcc/source/qc-parse.y"
    {
			class_add_ivars ((yyvsp[(2) - (4)].class), class_new_ivars ((yyvsp[(2) - (4)].class)));
			(yyval.class) = (yyvsp[(2) - (4)].class);
		}
    break;

  case 283:
/* Line 1787 of yacc.c  */
#line 1530 "../../../../tools/qfcc/source/qc-parse.y"
    { class_add_methods ((yyvsp[(2) - (6)].class), (yyvsp[(6) - (6)].methodlist)); }
    break;

  case 284:
/* Line 1787 of yacc.c  */
#line 1532 "../../../../tools/qfcc/source/qc-parse.y"
    {
			current_class = 0;
			(void) ((yyvsp[(5) - (8)].class));
		}
    break;

  case 285:
/* Line 1787 of yacc.c  */
#line 1538 "../../../../tools/qfcc/source/qc-parse.y"
    {
			category_add_protocols ((yyvsp[(2) - (3)].category), (yyvsp[(3) - (3)].protocol_list));
			(yyval.class) = (yyvsp[(2) - (3)].category)->class;
		}
    break;

  case 286:
/* Line 1787 of yacc.c  */
#line 1542 "../../../../tools/qfcc/source/qc-parse.y"
    { category_add_methods ((yyvsp[(2) - (5)].category), (yyvsp[(5) - (5)].methodlist)); }
    break;

  case 287:
/* Line 1787 of yacc.c  */
#line 1544 "../../../../tools/qfcc/source/qc-parse.y"
    {
			current_class = 0;
			(void) ((yyvsp[(4) - (7)].class));
		}
    break;

  case 288:
/* Line 1787 of yacc.c  */
#line 1548 "../../../../tools/qfcc/source/qc-parse.y"
    { class_begin (&(yyvsp[(2) - (2)].class)->class_type); }
    break;

  case 289:
/* Line 1787 of yacc.c  */
#line 1549 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.class) = (yyvsp[(2) - (4)].class); }
    break;

  case 290:
/* Line 1787 of yacc.c  */
#line 1551 "../../../../tools/qfcc/source/qc-parse.y"
    {
			class_check_ivars ((yyvsp[(2) - (7)].class), (yyvsp[(6) - (7)].symtab));
			(void) ((yyvsp[(5) - (7)].class));
		}
    break;

  case 291:
/* Line 1787 of yacc.c  */
#line 1555 "../../../../tools/qfcc/source/qc-parse.y"
    { class_begin (&(yyvsp[(2) - (2)].class)->class_type); }
    break;

  case 292:
/* Line 1787 of yacc.c  */
#line 1556 "../../../../tools/qfcc/source/qc-parse.y"
    { class_begin (&(yyvsp[(2) - (2)].class)->class_type); }
    break;

  case 293:
/* Line 1787 of yacc.c  */
#line 1557 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.class) = (yyvsp[(2) - (4)].class); }
    break;

  case 294:
/* Line 1787 of yacc.c  */
#line 1559 "../../../../tools/qfcc/source/qc-parse.y"
    {
			class_check_ivars ((yyvsp[(2) - (7)].class), (yyvsp[(6) - (7)].symtab));
			(void) ((yyvsp[(5) - (7)].class));
		}
    break;

  case 295:
/* Line 1787 of yacc.c  */
#line 1563 "../../../../tools/qfcc/source/qc-parse.y"
    { class_begin (&(yyvsp[(2) - (2)].class)->class_type); }
    break;

  case 296:
/* Line 1787 of yacc.c  */
#line 1564 "../../../../tools/qfcc/source/qc-parse.y"
    { class_begin (&(yyvsp[(2) - (2)].category)->class_type); }
    break;

  case 297:
/* Line 1787 of yacc.c  */
#line 1565 "../../../../tools/qfcc/source/qc-parse.y"
    { }
    break;

  case 298:
/* Line 1787 of yacc.c  */
#line 1566 "../../../../tools/qfcc/source/qc-parse.y"
    { }
    break;

  case 299:
/* Line 1787 of yacc.c  */
#line 1570 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.class_type) = current_class; }
    break;

  case 300:
/* Line 1787 of yacc.c  */
#line 1572 "../../../../tools/qfcc/source/qc-parse.y"
    { protocol_add_protocols ((yyvsp[(3) - (4)].protocol), (yyvsp[(4) - (4)].protocol_list)); (yyval.class) = 0; }
    break;

  case 301:
/* Line 1787 of yacc.c  */
#line 1573 "../../../../tools/qfcc/source/qc-parse.y"
    { protocol_add_methods ((yyvsp[(3) - (6)].protocol), (yyvsp[(6) - (6)].methodlist)); }
    break;

  case 302:
/* Line 1787 of yacc.c  */
#line 1575 "../../../../tools/qfcc/source/qc-parse.y"
    {
			current_class = (yyvsp[(2) - (8)].class_type);
			(void) ((yyvsp[(5) - (8)].class));
		}
    break;

  case 303:
/* Line 1787 of yacc.c  */
#line 1582 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.protocol_list) = 0; }
    break;

  case 304:
/* Line 1787 of yacc.c  */
#line 1583 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.protocol_list) = new_protocol_list (); }
    break;

  case 305:
/* Line 1787 of yacc.c  */
#line 1584 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.protocol_list) = (yyvsp[(3) - (4)].protocol_list); (void) ((yyvsp[(2) - (4)].protocol_list)); }
    break;

  case 306:
/* Line 1787 of yacc.c  */
#line 1589 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.protocol_list) = add_protocol ((yyvsp[(0) - (1)].protocol_list), (yyvsp[(1) - (1)].symbol)->name);
		}
    break;

  case 307:
/* Line 1787 of yacc.c  */
#line 1593 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.protocol_list) = add_protocol ((yyvsp[(1) - (3)].protocol_list), (yyvsp[(3) - (3)].symbol)->name);
		}
    break;

  case 308:
/* Line 1787 of yacc.c  */
#line 1600 "../../../../tools/qfcc/source/qc-parse.y"
    {
			symtab_t   *tab, *ivars;
			ivars = class_new_ivars ((yyvsp[(0) - (0)].class));
			for (tab = ivars; tab->parent; tab = tab->parent)
				;
			if (tab == current_symtab)
				internal_error (0, "ivars already linked to parent scope");
			(yyval.symtab) = tab;
			tab->parent = current_symtab;
			current_symtab = ivars;

			current_visibility = vis_protected;
		}
    break;

  case 309:
/* Line 1787 of yacc.c  */
#line 1614 "../../../../tools/qfcc/source/qc-parse.y"
    {
			symtab_t   *tab = (yyvsp[(1) - (2)].symtab);
			(yyval.symtab) = current_symtab;
			current_symtab = tab->parent;
			tab->parent = 0;

			tab = (yyval.symtab)->parent;	// preserve the ivars inheritance chain
			build_struct ('s', 0, (yyval.symtab), 0);
			(yyval.symtab)->parent = tab;
		}
    break;

  case 312:
/* Line 1787 of yacc.c  */
#line 1632 "../../../../tools/qfcc/source/qc-parse.y"
    { current_visibility = vis_private; }
    break;

  case 313:
/* Line 1787 of yacc.c  */
#line 1633 "../../../../tools/qfcc/source/qc-parse.y"
    { current_visibility = vis_protected; }
    break;

  case 314:
/* Line 1787 of yacc.c  */
#line 1634 "../../../../tools/qfcc/source/qc-parse.y"
    { current_visibility = vis_public; }
    break;

  case 319:
/* Line 1787 of yacc.c  */
#line 1648 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.spec) = (yyvsp[(0) - (2)].spec); }
    break;

  case 320:
/* Line 1787 of yacc.c  */
#line 1648 "../../../../tools/qfcc/source/qc-parse.y"
    { (void) ((yyvsp[(3) - (4)].spec)); }
    break;

  case 321:
/* Line 1787 of yacc.c  */
#line 1653 "../../../../tools/qfcc/source/qc-parse.y"
    {
			method_t   *method = (yyvsp[(2) - (3)].method);

			method->instance = (yyvsp[(1) - (3)].op);
			(yyvsp[(2) - (3)].method) = method = class_find_method (current_class, method);
			(yyval.symbol) = method_symbol (current_class, method);
		}
    break;

  case 322:
/* Line 1787 of yacc.c  */
#line 1661 "../../../../tools/qfcc/source/qc-parse.y"
    {
			method_t   *method = (yyvsp[(2) - (5)].method);
			const char *nicename = method_name (method);
			symbol_t   *sym = (yyvsp[(4) - (5)].symbol);
			symtab_t   *ivar_scope;

			(yyval.symtab) = current_symtab;

			ivar_scope = class_ivar_scope (current_class, current_symtab);
			current_func = begin_function (sym, nicename, ivar_scope, 1);
			class_finish_ivar_scope (current_class, ivar_scope,
									 current_func->symtab);
			method->func = sym->s.func;
			method->def = sym->s.func->def;
			current_symtab = current_func->symtab;
			current_storage = sc_local;
		}
    break;

  case 323:
/* Line 1787 of yacc.c  */
#line 1679 "../../../../tools/qfcc/source/qc-parse.y"
    {
			build_code_function ((yyvsp[(4) - (7)].symbol), (yyvsp[(3) - (7)].expr), (yyvsp[(7) - (7)].expr));
			current_symtab = (yyvsp[(6) - (7)].symtab);
			current_storage = (yyvsp[(5) - (7)].spec).storage;
			current_func = 0;
		}
    break;

  case 324:
/* Line 1787 of yacc.c  */
#line 1686 "../../../../tools/qfcc/source/qc-parse.y"
    {
			symbol_t   *sym;
			method_t   *method = (yyvsp[(2) - (6)].method);

			method->instance = (yyvsp[(1) - (6)].op);
			method = class_find_method (current_class, method);
			sym = method_symbol (current_class, method);
			build_builtin_function (sym, (yyvsp[(5) - (6)].expr), 1);
			method->func = sym->s.func;
			method->def = sym->s.func->def;
		}
    break;

  case 325:
/* Line 1787 of yacc.c  */
#line 1700 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.op) = 0; }
    break;

  case 326:
/* Line 1787 of yacc.c  */
#line 1701 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.op) = 1; }
    break;

  case 327:
/* Line 1787 of yacc.c  */
#line 1705 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.methodlist) = 0; }
    break;

  case 329:
/* Line 1787 of yacc.c  */
#line 1710 "../../../../tools/qfcc/source/qc-parse.y"
    { }
    break;

  case 330:
/* Line 1787 of yacc.c  */
#line 1711 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.methodlist) = new_methodlist ();
			add_method ((yyval.methodlist), (yyvsp[(2) - (2)].method));
		}
    break;

  case 331:
/* Line 1787 of yacc.c  */
#line 1716 "../../../../tools/qfcc/source/qc-parse.y"
    {
			add_method ((yyvsp[(1) - (2)].methodlist), (yyvsp[(2) - (2)].method));
			(yyval.methodlist) = (yyvsp[(1) - (2)].methodlist);
		}
    break;

  case 332:
/* Line 1787 of yacc.c  */
#line 1724 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(2) - (3)].method)->instance = 0;
			(yyval.method) = (yyvsp[(2) - (3)].method);
		}
    break;

  case 333:
/* Line 1787 of yacc.c  */
#line 1729 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(2) - (3)].method)->instance = 1;
			(yyval.method) = (yyvsp[(2) - (3)].method);
		}
    break;

  case 334:
/* Line 1787 of yacc.c  */
#line 1737 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.method) = new_method ((yyvsp[(2) - (4)].symbol)->type, (yyvsp[(4) - (4)].param), 0); }
    break;

  case 335:
/* Line 1787 of yacc.c  */
#line 1739 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.method) = new_method (&type_id, (yyvsp[(1) - (1)].param), 0); }
    break;

  case 336:
/* Line 1787 of yacc.c  */
#line 1741 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.method) = new_method ((yyvsp[(2) - (5)].symbol)->type, (yyvsp[(4) - (5)].param), (yyvsp[(5) - (5)].param)); }
    break;

  case 337:
/* Line 1787 of yacc.c  */
#line 1743 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.method) = new_method (&type_id, (yyvsp[(1) - (2)].param), (yyvsp[(2) - (2)].param)); }
    break;

  case 338:
/* Line 1787 of yacc.c  */
#line 1747 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = 0; }
    break;

  case 339:
/* Line 1787 of yacc.c  */
#line 1748 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = new_param (0, 0, 0); }
    break;

  case 340:
/* Line 1787 of yacc.c  */
#line 1749 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = (yyvsp[(2) - (2)].param); }
    break;

  case 341:
/* Line 1787 of yacc.c  */
#line 1751 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.param) = new_param (0, 0, 0);
			(yyval.param)->next = (yyvsp[(2) - (4)].param);
		}
    break;

  case 342:
/* Line 1787 of yacc.c  */
#line 1758 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = new_param ((yyvsp[(1) - (1)].symbol)->name, 0, 0); }
    break;

  case 344:
/* Line 1787 of yacc.c  */
#line 1763 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyvsp[(2) - (2)].param)->next = (yyvsp[(1) - (2)].param); (yyval.param) = (yyvsp[(2) - (2)].param); }
    break;

  case 345:
/* Line 1787 of yacc.c  */
#line 1767 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = (yyvsp[(1) - (1)].symbol); }
    break;

  case 346:
/* Line 1787 of yacc.c  */
#line 1768 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = (yyvsp[(1) - (1)].symbol); }
    break;

  case 347:
/* Line 1787 of yacc.c  */
#line 1769 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 348:
/* Line 1787 of yacc.c  */
#line 1770 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 349:
/* Line 1787 of yacc.c  */
#line 1771 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = (yyvsp[(1) - (1)].symbol); }
    break;

  case 351:
/* Line 1787 of yacc.c  */
#line 1776 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 352:
/* Line 1787 of yacc.c  */
#line 1777 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 353:
/* Line 1787 of yacc.c  */
#line 1778 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 354:
/* Line 1787 of yacc.c  */
#line 1779 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 355:
/* Line 1787 of yacc.c  */
#line 1780 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 356:
/* Line 1787 of yacc.c  */
#line 1781 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 357:
/* Line 1787 of yacc.c  */
#line 1782 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 358:
/* Line 1787 of yacc.c  */
#line 1783 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 359:
/* Line 1787 of yacc.c  */
#line 1784 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 360:
/* Line 1787 of yacc.c  */
#line 1785 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 361:
/* Line 1787 of yacc.c  */
#line 1786 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 362:
/* Line 1787 of yacc.c  */
#line 1787 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 363:
/* Line 1787 of yacc.c  */
#line 1788 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 364:
/* Line 1787 of yacc.c  */
#line 1789 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 365:
/* Line 1787 of yacc.c  */
#line 1790 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 366:
/* Line 1787 of yacc.c  */
#line 1791 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.symbol) = new_symbol (qc_yytext); }
    break;

  case 367:
/* Line 1787 of yacc.c  */
#line 1796 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = new_param ((yyvsp[(1) - (6)].symbol)->name, (yyvsp[(4) - (6)].symbol)->type, (yyvsp[(6) - (6)].symbol)->name); }
    break;

  case 368:
/* Line 1787 of yacc.c  */
#line 1798 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = new_param ((yyvsp[(1) - (3)].symbol)->name, &type_id, (yyvsp[(3) - (3)].symbol)->name); }
    break;

  case 369:
/* Line 1787 of yacc.c  */
#line 1800 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = new_param ("", (yyvsp[(3) - (5)].symbol)->type, (yyvsp[(5) - (5)].symbol)->name); }
    break;

  case 370:
/* Line 1787 of yacc.c  */
#line 1802 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.param) = new_param ("", &type_id, (yyvsp[(2) - (2)].symbol)->name); }
    break;

  case 372:
/* Line 1787 of yacc.c  */
#line 1807 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = selector_expr ((yyvsp[(3) - (4)].keywordarg)); }
    break;

  case 373:
/* Line 1787 of yacc.c  */
#line 1808 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = protocol_expr ((yyvsp[(3) - (4)].symbol)->name); }
    break;

  case 374:
/* Line 1787 of yacc.c  */
#line 1809 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = encode_expr ((yyvsp[(3) - (4)].symbol)->type); }
    break;

  case 376:
/* Line 1787 of yacc.c  */
#line 1814 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.expr) = message_expr ((yyvsp[(2) - (4)].expr), (yyvsp[(3) - (4)].keywordarg)); }
    break;

  case 378:
/* Line 1787 of yacc.c  */
#line 1820 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyval.expr) = new_symbol_expr ((yyvsp[(1) - (1)].symbol));
		}
    break;

  case 379:
/* Line 1787 of yacc.c  */
#line 1826 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.keywordarg) = new_keywordarg ((yyvsp[(1) - (1)].symbol)->name, 0); }
    break;

  case 382:
/* Line 1787 of yacc.c  */
#line 1833 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(2) - (2)].keywordarg)->next = (yyvsp[(1) - (2)].keywordarg);
			(yyval.keywordarg) = (yyvsp[(2) - (2)].keywordarg);
		}
    break;

  case 383:
/* Line 1787 of yacc.c  */
#line 1840 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.keywordarg) = new_keywordarg ((yyvsp[(1) - (3)].symbol)->name, (yyvsp[(3) - (3)].expr)); }
    break;

  case 384:
/* Line 1787 of yacc.c  */
#line 1841 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.keywordarg) = new_keywordarg ("", (yyvsp[(2) - (2)].expr)); }
    break;

  case 385:
/* Line 1787 of yacc.c  */
#line 1845 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.keywordarg) = new_keywordarg ((yyvsp[(1) - (1)].symbol)->name, 0); }
    break;

  case 388:
/* Line 1787 of yacc.c  */
#line 1852 "../../../../tools/qfcc/source/qc-parse.y"
    {
			(yyvsp[(2) - (2)].keywordarg)->next = (yyvsp[(1) - (2)].keywordarg);
			(yyval.keywordarg) = (yyvsp[(2) - (2)].keywordarg);
		}
    break;

  case 389:
/* Line 1787 of yacc.c  */
#line 1859 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.keywordarg) = new_keywordarg ((yyvsp[(1) - (2)].symbol)->name, new_nil_expr ()); }
    break;

  case 390:
/* Line 1787 of yacc.c  */
#line 1860 "../../../../tools/qfcc/source/qc-parse.y"
    { (yyval.keywordarg) = new_keywordarg ("", new_nil_expr ()); }
    break;

  case 391:
/* Line 1787 of yacc.c  */
#line 1865 "../../../../tools/qfcc/source/qc-parse.y"
    {
			//FIXME string object
			(yyval.expr) = (yyvsp[(2) - (2)].expr);
		}
    break;


/* Line 1787 of yacc.c  */
#line 5192 "qc-parse.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2048 of yacc.c  */
#line 1871 "../../../../tools/qfcc/source/qc-parse.y"

