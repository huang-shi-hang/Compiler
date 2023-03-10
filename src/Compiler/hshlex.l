%option noyywrap

%{

#include "hshparser.tab.hpp"

%}

/*comment       */
LINE_COMMENT    \/\/.*
BLOCK_COMMENT   \/\*([^\*]|(\*)*[^(\*\/)])*(\*)*\*\/

IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*

ASSIGNMENT_OPERATOR (([<>][<>]|[*\/%+\-&^|])[=])

INTEGERSUFFIX ([uU][lL]|[lL][uU]|[uUlL])

DECIMALCONSTANT ([1-9][0-9]*)
OCTALCONSTANT ([0][0-7]*)
HEXCONSTANT ([0][xX][0-9A-Fa-f]+)

CHARCONSTANT (['](([\\]['])|([^']))*['])

STRINGLITERAL (["](([\\]["])|([^"]))*["])

WHITESPACE [ \t\r\n]+

PREPROC [#][ ][0-9]+[ ]{STRINGLITERAL}[ 0-9]*

ALL .

%%
(void)		{ return T_VOID; }
(char)		{ return T_CHAR; }
(short)		{ return T_SHORT; }
(int)		{ return T_INT; }
(long)		{ return T_LONG; }
(static)	{ return T_STATIC; }
(const)		{ return T_CONST; }

(continue)	{ return T_CONTINUE; }
(break)		{ return T_BREAK; }
(goto)		{ return T_GOTO; }
(case)		{ return T_CASE; }
(default)	     { return T_DEFAULT; }
(switch)	     { return T_SWITCH; }

{STRINGLITERAL}	{ std::string tmp(yytext); 
                         yylval.string = new std::string(tmp.substr(1, yyleng-2));
		               return T_STRINGLITERAL; 
                    }


{CHARCONSTANT} { yylval.number = yytext[1]; return T_INT_CONST; }


[.][.][.]	{ return T_ELLIPSIS; }
[;]		{ return T_SC; }
[,]		{ return T_CMA; }
[(]		{ return T_LRB; }
[)]		{ return T_RRB; }
[{]             { return T_LCB; }
[}]             { return T_RCB; }
[[]		{ return T_LSB; }
[]]		{ return T_RSB; }
[=]		{ yylval.string = new std::string(yytext); return T_EQ; }
{ASSIGNMENT_OPERATOR} { yylval.string = new std::string(yytext); return T_ASSIGN_OPER; }
[?]		{ return T_QU; }
[:]		{ return T_COL; }
[|][|]		{ return T_LOG_OR; }
[&][&]		{ return T_LOG_AND; }
[|]		{ return T_OR; }
[\^]		{ return T_XOR; }
[&]		{ yylval.string = new std::string(yytext); return T_AND; }
[=][=]		{ yylval.string = new std::string(yytext); return T_EQUALITY_OP; }
[!][=]		{ yylval.string = new std::string(yytext); return T_EQUALITY_OP; }
([<>][=])|[<>]	{ yylval.string = new std::string(yytext); return T_REL_OP; }
[<>][<>]	{ yylval.string = new std::string(yytext); return T_SHIFT_OP; }
[*] 		{ yylval.string = new std::string(yytext); return T_MULT; }
[\/]		{ yylval.string = new std::string(yytext); return T_DIV; }
[%]		{ yylval.string = new std::string(yytext); return T_REM; }
[~]		{ yylval.string = new std::string(yytext); return T_TILDE; }
[!]		{ yylval.string = new std::string(yytext); return T_NOT; }
[+-][+-]	{ yylval.string = new std::string(yytext); return T_INCDEC; }
[+-]		{ yylval.string = new std::string(yytext); return T_ADDSUB_OP; }

if		{ return T_IF; }
else		{ return T_ELSE; }
return		{ return T_RETURN; }
while		{ return T_WHILE; }
do		{ return T_DO; }
for		{ return T_FOR; }

{IDENTIFIER}	{ yylval.string = new std::string(yytext); return T_IDENTIFIER; }

({HEXCONSTANT}|{OCTALCONSTANT}|{DECIMALCONSTANT}){INTEGERSUFFIX}?	{ yylval.number = strtol(yytext, NULL, 0); return T_INT_CONST; }

{LINE_COMMENT}|{BLOCK_COMMENT}|{WHITESPACE}	{ ; }

.                   { fprintf(stderr, "Invalid token\n"); exit(1); }

%%

void yyerror(char const *s) {
     fprintf (stderr, "Parse error : %s\n", s);
     exit(1);
}
