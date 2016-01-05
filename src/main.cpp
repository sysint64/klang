#include <memory>
#include <iostream>
#include "compiler.h"

int main (int argc, char *argv[]) {

	std::unique_ptr<Compiler> compiler = std::make_unique<Compiler>();

	compiler->parseCmd (argc, argv);
	compiler->compile();

	return 0;

}
