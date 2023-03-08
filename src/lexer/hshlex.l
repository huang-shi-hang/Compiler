/*******************************************************
*            Compiler :hshconpiler for C               *
*           Shihang Huang, 304256263@qq.com            *
*               Buildtime:2022.5.1                     *
*                                                      *
*                   SysY Compiler                      *
*                                                      *
*           hshlex.l:   lexer by flex                  *
*******************************************************/

/*******************************************************
*               Chenge Log                             *
*       1.                                             *             
*******************************************************/

%{
    #include <sstream>
    #include <string>
    #include <stdlib.h>
    #include "c_lexer.hpp"

    using namespace std;

    static int Countlines();

    /*counter         */
    int line_num = 1;
    int space_num = 1;
    int sourceline_num = 1;

    int charLength = 0; 

    std::string fileName;
    
%}

%option noyywrap

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

NEWLINE         [\n]

WHITESPACE      [ ]

TAB             [\t]

ALL             .



%%
{KEYWORD}       {
    yylval = new string(yytext);
    charLength = (int)yyleng;
    return Keyword;
}

{IDENTIFIER}    {
    yylval = new string(yytext);
    charLength = (int)yyleng;
    return Identifier;
}

{OPERATOR}      {
    yylval = new string(yytext);
    charLength = (int)yyleng;
    return Operator;
}

{DECIMALNUM}|{OCTALNUM}|{HEXNUM}    {
    yylval = new string(yytext);
    charLength = (int)yyleng;
    return Constant;
}

{LINE_COMMENT}   {


}

{BLOCK_COMMENT}  {
    int lines = Countlines();
    line_num += lines;
}

{NEWLINE}       {
    space_num = 1;
    line_num++;
    sourceline_num++;
}

{WHITESPACE}    {
    space_num++;
}

{TAB}           {
    space_num += 8;
}

{ALL}           {
    yylval = new string(yytext);
    charLength = (int)yyleng;
    return Invalid;
}

%%

//count line in BLOCK_COMMENT
int Countlines(){
	int lines = 0;
	while(*yytext){
		if(*yytext == '\n') {lines += 1;}
		yytext++;
	}
	return lines;
}










