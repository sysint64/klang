#include <memory>
#include <iostream>
#include "compiler.h"
#include "codegen/llvm/codegen.h"
#include "config.h"

extern Compiler *compiler (new Compiler());

int main (int argc, char *argv[]) {

	compiler->parseCmd (argc, argv);
	compiler->compile();
	compiler->getCurrentCodegen()->emit();

	delete compiler;
	return 0;

}
