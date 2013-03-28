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

#ifndef YY_FBSET_MODES_Y_H
# define YY_FBSET_MODES_Y_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MODE = 258,
     GEOMETRY = 259,
     TIMINGS = 260,
     HSYNC = 261,
     VSYNC = 262,
     CSYNC = 263,
     GSYNC = 264,
     EXTSYNC = 265,
     BCAST = 266,
     LACED = 267,
     DOUBLE = 268,
     RGBA = 269,
     NONSTD = 270,
     ACCEL = 271,
     GRAYSCALE = 272,
     ENDMODE = 273,
     POLARITY = 274,
     BOOLEAN = 275,
     NUMBER = 276,
     STRING = 277
   };
#endif
/* Tokens.  */
#define MODE 258
#define GEOMETRY 259
#define TIMINGS 260
#define HSYNC 261
#define VSYNC 262
#define CSYNC 263
#define GSYNC 264
#define EXTSYNC 265
#define BCAST 266
#define LACED 267
#define DOUBLE 268
#define RGBA 269
#define NONSTD 270
#define ACCEL 271
#define GRAYSCALE 272
#define ENDMODE 273
#define POLARITY 274
#define BOOLEAN 275
#define NUMBER 276
#define STRING 277



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2049 of yacc.c  */
#line 42 "fbset_modes_y.y"

	int		int_val;
	const char	*string;


/* Line 2049 of yacc.c  */
#line 107 "fbset_modes_y.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_FBSET_MODES_Y_H  */
