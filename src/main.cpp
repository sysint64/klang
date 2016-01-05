#include <memory>
#include <iostream>
#include "compiler.h"
#include "codegen/llvm/codegen.h"

int main (int argc, char *argv[]) {

	std::unique_ptr<Compiler> compiler = std::make_unique<Compiler>();

	compiler->parseCmd (argc, argv);
	//compiler->compile();
	LLVMCodegen codegen;

	codegen.insert (std::move(codegen.createIntTyIR(32)), Codegen::Head);

	codegen.input = "test";
	codegen.emit();

	return 0;

}
