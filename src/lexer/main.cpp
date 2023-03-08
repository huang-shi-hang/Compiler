#include "c_lexer.hpp"

#include <cassert>
#include <sstream>
#include <vector>

std::string *yylval;

int main() {
	printf("[\n");
	std::string sourceLine, streamLine, sourceCol, classType, text;
	while(1) {
		// get the token type and run the lexer
		std::stringstream str_line, src_col, src_line;

		TokenType type = (TokenType)yylex();
		str_line << line_num;
		streamLine = str_line.str();

		src_col << space_num;
		sourceCol = src_col.str();

		src_line << sourceline_num;
		sourceLine = src_line.str();

        switch (type)
        {
        case None:
            break;
        case Invalid:
            text = *yylval;
            classType = "Invalid";
            delete yylval;
            break;
        case Keyword:
            text = *yylval;
            classType = "Keyword";
            delete yylval;
            break;
        case Identifier:
            text = *yylval;
            classType = "Identifier";
            delete yylval;
            break; 
        case Operator:
            text = *yylval;
            classType = "Operator";
            delete yylval;
            break;
        case Constant:
            text = *yylval;
            classType = "Constant";
            delete yylval;
            break;
        default:
            assert(0);
            return 1;
            break;
        }



		printf("%s,\n", toJson(classType, text, streamLine, sourceCol, sourceLine, fileName).c_str());

		space_num += charLength;
	}

	printf("{}\n]\n");

	return 0;
}
