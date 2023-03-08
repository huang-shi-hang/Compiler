#include "ast.hpp"

#include <iostream>
#include <stdio.h>

#include <fstream>

#include "hshlex.yy.hpp"

std::ofstream fpout;

int main(int argc, char *argv[]) {

    // std::ifstream fpin;
    if ((yyin = fopen(argv[1], "r")) == NULL) {
        perror("Can't open file \n");
        return -1;
    }
    ast_Top *ast = parseAST();
    
    fpout.open("test.txt",std::ios::app);

    ast->print();

    fpout.close();
    
    return 0;
}
