#include "ast/type.h"
#include "config.h"

std::unique_ptr<BaseIR> IntTypeAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();
	return codegen->createIntTyIR (size);

}

std::unique_ptr<BaseIR> VoidTypeAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();
	return codegen->createVoidTyIR();

}
