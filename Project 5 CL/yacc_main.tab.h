/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_YACC_MAIN_TAB_H_INCLUDED
# define YY_YY_YACC_MAIN_TAB_H_INCLUDED
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
    LPAREN_TOK = 258,
    RPAREN_TOK = 259,
    LCURL_TOK = 260,
    RCURL_TOK = 261,
    LSQUARE_TOK = 262,
    RSQUARE_TOK = 263,
    PLUS_TOK = 264,
    MINUS_TOK = 265,
    MULTIPLY_TOK = 266,
    DIVIDE_TOK = 267,
    MODULO_TOK = 268,
    LNOT_TOK = 269,
    LAND_TOK = 270,
    LOR_TOK = 271,
    LXOR_TOK = 272,
    SEMICOLON_TOK = 273,
    EQUAL_TOK = 274,
    COMA_TOK = 275,
    GT_TOK = 276,
    LT_TOK = 277,
    DOT_TOK = 278,
    NEWLINE_TOK = 279,
    GTEQ_TOK = 280,
    LTEQ_TOK = 281,
    NOTEQ_TOK = 282,
    PLUSEQ_TOK = 283,
    MINEQ_TOK = 284,
    MULEQ_TOK = 285,
    DIVEQ_TOK = 286,
    INCR_TOK = 287,
    DECR_TOK = 288,
    EQEQ_TOK = 289,
    DEFINE_TOK = 290,
    INCLUDE_TOK = 291,
    INT_TOK = 292,
    FLOAT_TOK = 293,
    DOUBLE_TOK = 294,
    LONG_TOK = 295,
    CHAR_TOK = 296,
    IF_TOK = 297,
    ELSE_TOK = 298,
    FOR_TOK = 299,
    WHILE_TOK = 300,
    INTCONST_TOK = 301,
    CHARCONST_TOK = 302,
    STRINGCONST_TOK = 303,
    FLOATCONST_TOK = 304,
    ID_TOK = 305,
    MAIN_TOK = 306,
    RETURN_TOK = 307,
    DELIM_TOK = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 173 "yacc_main.y"

        char* string;
        int dtype;

#line 116 "yacc_main.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_MAIN_TAB_H_INCLUDED  */
