#ifndef AST_HPP
#define AST_hpp

#include "ast_base.hpp"
#include "ast_statement.hpp"
#include "ast_function.hpp"
#include "ast_declaration.hpp"
#include "ast_primitives.hpp"
#include "ast_top.hpp"
// #include "file_WR.hpp"
extern std::ofstream fpout;
class ast_Top;
ast_Top *parseAST();

#endif
