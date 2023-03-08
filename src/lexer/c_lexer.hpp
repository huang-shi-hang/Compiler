#ifndef C_LEXER_HPP
#define C_LEXER_HPP

#include <string>

enum TokenType {
	None,
	Keyword,
	Identifier,
	Operator,
	Constant,
	Invalid
};

// Global variable that will be looked for by byson
extern std::string *yylval;

// flex function to run on input
extern int yylex();

extern int line_num;
extern int space_num;
extern int sourceline_num;

extern int charLength;


extern std::string fileName;

// get the correct output
std::string toJson(const std::string& classType, const std::string& text, const std::string& strLine, const std::string& srcCol, const std::string& srcLine, const std::string& fName);

#endif
