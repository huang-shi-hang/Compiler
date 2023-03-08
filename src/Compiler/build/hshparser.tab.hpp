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

#line 66 "hshparser.tab.hpp"

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

#line 142 "hshparser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HSHPARSER_TAB_HPP_INCLUDED  */
