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

#ifndef QP_YY_QP_PARSE_H
# define QP_YY_QP_PARSE_H
/* Enabling traces.  */
#ifndef QP_YYDEBUG
# if defined YYDEBUG
#  if YYDEBUG
#   define QP_YYDEBUG 1
#  else
#   define QP_YYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define QP_YYDEBUG 0
# endif /* ! defined QP_YYDEBUG */
#endif  /* ! defined QP_YYDEBUG */
#if QP_YYDEBUG
extern int qp_yydebug;
#endif

/* Tokens.  */
#ifndef QP_YYTOKENTYPE
# define QP_YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum qp_yytokentype {
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
     RELOP = 275,
     ADDOP = 276,
     MULOP = 277,
     UNARY = 278,
     TYPE = 279,
     TYPE_NAME = 280,
     ID = 281,
     VALUE = 282,
     PROGRAM = 283,
     VAR = 284,
     ARRAY = 285,
     OF = 286,
     FUNCTION = 287,
     PROCEDURE = 288,
     PBEGIN = 289,
     END = 290,
     IF = 291,
     THEN = 292,
     WHILE = 293,
     DO = 294,
     RANGE = 295,
     ASSIGNOP = 296,
     NOT = 297,
     ELLIPSIS = 298,
     RETURN = 299
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
#define RELOP 275
#define ADDOP 276
#define MULOP 277
#define UNARY 278
#define TYPE 279
#define TYPE_NAME 280
#define ID 281
#define VALUE 282
#define PROGRAM 283
#define VAR 284
#define ARRAY 285
#define OF 286
#define FUNCTION 287
#define PROCEDURE 288
#define PBEGIN 289
#define END 290
#define IF 291
#define THEN 292
#define WHILE 293
#define DO 294
#define RANGE 295
#define ASSIGNOP 296
#define NOT 297
#define ELLIPSIS 298
#define RETURN 299



#if ! defined QP_YYSTYPE && ! defined QP_YYSTYPE_IS_DECLARED
typedef union QP_YYSTYPE
{
/* Line 2049 of yacc.c  */
#line 82 "../../../../tools/qfcc/source/qp-parse.y"

	int			op;
	struct def_s *def;
	struct hashtab_s *def_list;
	struct type_s	*type;
	struct typedef_s *typename;
	struct expr_s	*expr;
	struct function_s *function;
	struct switch_block_s *switch_block;
	struct param_s	*param;
	struct struct_s *strct;
	struct symtab_s *symtab;
	struct symbol_s *symbol;
	int              storage;


/* Line 2049 of yacc.c  */
#line 170 "qp-parse.h"
} QP_YYSTYPE;
# define QP_YYSTYPE_IS_TRIVIAL 1
# define qp_yystype QP_YYSTYPE /* obsolescent; will be withdrawn */
# define QP_YYSTYPE_IS_DECLARED 1
#endif

extern QP_YYSTYPE qp_yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int qp_yyparse (void *YYPARSE_PARAM);
#else
int qp_yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int qp_yyparse (void);
#else
int qp_yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !QP_YY_QP_PARSE_H  */
