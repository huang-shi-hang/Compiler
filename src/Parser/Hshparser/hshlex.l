/*******************************************************
*            Compiler :hshconpiler for C               *
*           Shihang Huang, 304256263@qq.com            *
*               Buildtime:2022.5.2                     *
*                                                      *
*                   SysY Compiler                      *
*                                                      *
*           hshlex.l:   lexer by flex                  *
*******************************************************/

/*******************************************************
*               Chenge Log                             *
*       1.                                             *             
*******************************************************/
%option noyywrap

%{
    #include "hshparser.tab.hpp"
    #include <fstream>
    // YY_BUFFER_STATE bp;
    // FILE *f;
    // f = fopen("input.c", "r");
    // bp = yy_create_buffer(f, YY_BUF_SIZE);
    // yy_switch_to_buffer(bp);  
%}

KEYWORD         int|void|const|if|else|while|break|continue|return|main

IDENTIFIER      [_a-zA-Z][_a-zA-Z0-9]*

OPERATOR        [+][+]|[-][-]|[&][&]|[|][|]|[<>!=][=]|[+\-\*\/<>=!%]|[(){}\[\]\.,;]

/*number        */
DECIMALNUM      ([1-9][0-9]*)
OCTALNUM        ([0][0-7]*)
HEXNUM          ([0][Xx][0-9A-Fa-f]+)

/*comment       */
LINE_COMMENT    \/\/.*
BLOCK_COMMENT   \/\*([^\*]|(\*)*[^(\*\/)])*(\*)*\*\/

WHITESPACE      [ \t\r\n]+

ALL             .

%%

{LINE_COMMENT}|{BLOCK_COMMENT}|{WHITESPACE} {}

void                {yylval.str = new std::string(yytext);return Y_VOID;}

int                 {yylval.str = new std::string(yytext);return Y_INT;}

const               {return Y_CONST;}

[;]                 {return Y_Semicolon;}

[,]                 {return Y_Comma;}

[(]                 {return Y_L_RBracket;}

[)]                 {return Y_R_RBracket;}

[{]                 {return Y_L_CBracket;}

[}]                 {return Y_R_CBracket;}

[[]                 {return Y_L_SBracket;}

[]]                 {return Y_R_SBracket;}

[|][|]              {yylval.str = new std::string(yytext);return Y_Or;}

[&][&]              {yylval.str = new std::string(yytext);return Y_And;}

[=][=]              {yylval.str = new std::string(yytext);return Y_Equality;}

[!][=]              {yylval.str = new std::string(yytext);return Y_U_Equality;}

([<>][=])|[<>]      {yylval.str = new std::string(yytext);return Y_Relation;}

[*]                 {yylval.str = new std::string(yytext);return Y_Mult;}

[\/]                {yylval.str = new std::string(yytext);return Y_Div;}

[%]                 {yylval.str = new std::string(yytext);return Y_Rem;}

([+][+])|([-][-])   {yylval.str = new std::string(yytext);return Y_Inc_Dec;}

[+-]                {yylval.str = new std::string(yytext);return Y_Add_Sub;}

[=]                 {yylval.str = new std::string(yytext); return Y_Equal;}

[!]                 {yylval.str = new std::string(yytext);return Y_OPPOSIT;}

if                  {return Y_IF;}

else                {return Y_ELSE;}

return              {return Y_RETURN;}

while               {return Y_WHILE;}

break               {return Y_BREAK;}

continue            {return Y_CONTINUE;}

{IDENTIFIER}        {yylval.str = new std::string(yytext); return Ident;}

{DECIMALNUM}|{OCTALNUM}|{HEXNUM}  {yylval.number = strtol(yytext, nullptr, 0); return INT_CONST;}

.                   {return yytext[0];}

%%

void yyerror(char const *s) {
     fprintf (stderr, "Parse error : %s\n", s);
     exit(1);
}
