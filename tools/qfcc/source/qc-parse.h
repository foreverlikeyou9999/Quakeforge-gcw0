/* A Bison parser, made by GNU Bison 2.6.2.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2049 of yacc.c  */
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


/* Line 2049 of yacc.c  */
#line 232 "qc-parse.h"
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
