%option noyywrap
%{
    #include <stdlib.h>
    #include <stdbool.h>
    #include <algorithm>
    #include <string>
    
    #include <iostream>
    #include "types.hpp"
    #include "hshparser.tab.hpp"
    int line = 1;
%}

space       (\ |\t)+

/*comment       */
LINE_COMMENT    \/\/.*
BLOCK_COMMENT   \/\*([^\*]|(\*)*[^(\*\/)])*(\*)*\*\/

id          [A-Za-z][0-9A-Za-z]*
num         [0-9]+
real    [0-9]+(\.[0-9]+)?(E[+-]?[0-9]+)?
char    '.'

%%

{space}     {}
"\n"        {line++; }

if      { return IF; }
else    { return ELSE; }
do      { return DO; }
while   { return WHILE; }
break   { return BREAK; }

int     { yylval.val_type = INT; return BASIC; }
float   { yylval.val_type = FLOAT; return BASIC; }
char    { yylval.val_type = CHAR; return BASIC; }
bool    { yylval.val_type = BOOL; return BASIC; }


true    { yylval.val_type = BOOL; yylval.val.boolean = true; return CONST; }
false   { yylval.val_type = BOOL; yylval.val.boolean = false; return CONST; }
{num}   { yylval.val_type = INT; yylval.val.num = atoi(yytext); return CONST; }
{real}  { yylval.val_type = FLOAT; yylval.val.real = atof(yytext); return CONST; }
{char}  { yylval.val_type = CHAR; yylval.val.ch = yytext[1]; return CONST; }

LINE_COMMENT   {}
BLOCK_COMMENT  { 
                std::string temp(yytext);
                int num = count(temp.begin(),temp.end(),'\n');
                line += num;
                }

{id}    { strcpy(yylval.name, yytext); return ID;}

"=="    { return EQ; }
"!="    { return NE; }
"<"     { return LT; }
"<="    { return LE; }
">"     { return GT; }
">="    { return GE; }
"&&"    { return AND; }
"||"    { return OR; }

"!"     { return '!'; }
"="     { return '='; }
"+"     { return '+'; }
"-"     { return '-'; }
"*"     { return '*'; }
"/"     { return '/'; }
";"     { return ';'; }
"("     { return '('; }
")"     { return ')'; }
"["     { return '['; }
"]"     { return ']'; }
"{"     { return '{'; }
"}"     { return '}'; }

%%
