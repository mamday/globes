/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     SFNCT = 259,
     BOGUS = 260,
     LVAR = 261,
     VAR = 262,
     FNCT = 263,
     IDN = 264,
     CROSS = 265,
     FLUXP = 266,
     FLUXM = 267,
     NUFLUX = 268,
     SYS_ON_FUNCTION = 269,
     SYS_OFF_FUNCTION = 270,
     GRP = 271,
     GID = 272,
     FNAME = 273,
     VERS = 274,
     SIGNAL = 275,
     BG = 276,
     GRPOPEN = 277,
     GRPCLOSE = 278,
     PM = 279,
     FLAVOR = 280,
     NOGLOBES = 281,
     CHANNEL = 282,
     RULESEP = 283,
     RULEMULT = 284,
     ENERGY = 285,
     NAME = 286,
     RDF = 287,
     NDEF = 288,
     NEG = 289
   };
#endif
#define NUM 258
#define SFNCT 259
#define BOGUS 260
#define LVAR 261
#define VAR 262
#define FNCT 263
#define IDN 264
#define CROSS 265
#define FLUXP 266
#define FLUXM 267
#define NUFLUX 268
#define SYS_ON_FUNCTION 269
#define SYS_OFF_FUNCTION 270
#define GRP 271
#define GID 272
#define FNAME 273
#define VERS 274
#define SIGNAL 275
#define BG 276
#define GRPOPEN 277
#define GRPCLOSE 278
#define PM 279
#define FLAVOR 280
#define NOGLOBES 281
#define CHANNEL 282
#define RULESEP 283
#define RULEMULT 284
#define ENERGY 285
#define NAME 286
#define RDF 287
#define NDEF 288
#define NEG 289




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 1022 "glb_parser.y"
typedef union YYSTYPE {
  double  val;  /* For returning numbers.                   */
  double *dpt;  /* for rules */
  glb_List *ptr; 
  glb_List **ptrq;
  glb_symrec  *tptr;  /* For returning symbol-table pointers      */
  char *name;
  char *iname;
  int in;
  glb_namerec *nameptr;
} YYSTYPE;
/* Line 1249 of yacc.c.  */
#line 116 "glb_parser.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



