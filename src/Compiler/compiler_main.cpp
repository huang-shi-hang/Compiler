#include "node.hpp"
#include "bindings.hpp"

#include <cstdio>
#include <string>
#include "hshlex.yy.hpp"

Node* parseAST();

int main(int argc, char *argv[])
{
	if ((yyin = fopen(argv[1], "r")) == NULL) {
		perror("Can't open file \n");
		return -1;
    }
	try
	{
		std::unique_ptr<Node> ast(parseAST());
		Bindings bindings;
		int label_count = 0;
		ast->printAsm(bindings, label_count);	
	}
	catch(const std::exception& e)
	{
		fprintf(stderr, "%s\n", e.what());
	}
	catch(...)
	{
		fprintf(stderr, "Error : Exception thrown\n");
	}

	return 0;
}
