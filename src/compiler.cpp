#include "compiler.h"
#include "codegen/llvm/codegen.h"
#include "config.h"

void Compiler::compile() {

	parser  = std::make_unique<Parser>(this);
	codegen = std::make_unique<LLVMCodegen>();

	parser->parse();

}

void Compiler::loadMessages() {

}
