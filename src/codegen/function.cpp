#include "ast/function.h"
#include "config.h"

std::unique_ptr<BaseIR> DirectiveAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();

	if (name == "inline")
		return codegen->createInlineDirectiveIR();

	if (name == "fastcall")
		return codegen->createFastCallDirectiveIR();

	if (name == "stdcall")
		return codegen->createStdCallDirectiveIR();

	return nullptr;

}

std::unique_ptr<BaseIR> DirectivesAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();
	std::vector<std::unique_ptr<BaseIR>> directivesIR;

	for (const auto &directive : directives)
		directivesIR.push_back (directive->codegen());

	return codegen->createDirectivesIR (std::move (directivesIR));

}

std::unique_ptr<BaseIR> ArgsAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();
	std::vector<std::unique_ptr<BaseIR>> argsIR;

	for (const auto &arg : args)
		argsIR.push_back (arg->codegen());

	return codegen->createArgsIR (std::move (argsIR));

}

std::unique_ptr<BaseIR> PrototypeAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();

	std::unique_ptr<BaseIR> argsIR       = args       ? args      ->codegen() : nullptr;
	std::unique_ptr<BaseIR> directivesIR = directives ? directives->codegen() : nullptr;

	auto typeIR = type->codegen();
	return codegen->createDefIR (name, std::move(argsIR), std::move(directivesIR), std::move(typeIR));

}

std::unique_ptr<BaseIR> PrototypeAST::codegenDeclare() {

	return nullptr;

}
