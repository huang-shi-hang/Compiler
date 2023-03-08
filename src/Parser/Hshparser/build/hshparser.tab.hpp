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
#line 15 "../hshparser.y"

    #include "ast.hpp"
    extern ast_Top *ast_root;//AST's root
    using namespace std;
    /*声明flex的函数以便调用*/
    int yylex(void);
    void yyerror(const char *);

#line 57 "hshparser.tab.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    Y_INT = 258,
    Ident = 259,
    Y_CONST = 260,
    Y_VOID = 261,
    Y_Semicolon = 262,
    Y_Comma = 263,
    Y_L_RBracket = 264,
    Y_R_RBracket = 265,
    Y_L_CBracket = 266,
    Y_R_CBracket = 267,
    Y_L_SBracket = 268,
    Y_R_SBracket = 269,
    Y_Or = 270,
    Y_And = 271,
    Y_Equality = 272,
    Y_U_Equality = 273,
    Y_Relation = 274,
    Y_Mult = 275,
    Y_Div = 276,
    Y_Rem = 277,
    Y_Inc_Dec = 278,
    Y_Add_Sub = 279,
    Y_Equal = 280,
    Y_OPPOSIT = 281,
    INT_CONST = 282,
    Y_IF = 283,
    Y_ELSE = 284,
    Y_RETURN = 285,
    Y_WHILE = 286,
    Y_BREAK = 287,
    Y_CONTINUE = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 30 "../hshparser.y"

    const Base *stmnt;
    const opExp *stmnt1;
    int number;
    string *str;

#line 109 "hshparser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HSHPARSER_TAB_HPP_INCLUDED  */
