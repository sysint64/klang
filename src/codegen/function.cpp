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

	auto codegen = compiler->getCurrentCodegen();

	std::unique_ptr<BaseIR> argsIR       = args       ? args      ->codegen() : nullptr;
	std::unique_ptr<BaseIR> directivesIR = directives ? directives->codegen() : nullptr;

	auto typeIR = type->codegen();
	return codegen->createDeclareIR (name, std::move(argsIR), std::move(directivesIR), std::move(typeIR));

}

std::unique_ptr<BaseIR> FunctionAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();

	std::unique_ptr<BaseIR> prototypeIR  = prototype  ? prototype->codegen() : nullptr;
	std::unique_ptr<BaseIR> bodyIR       = body       ? body     ->codegen() : nullptr;
	std::unique_ptr<BaseIR> endIR        = codegen->createEndIR();

	std::vector<std::unique_ptr<BaseIR>> stack;

	stack.push_back (std::move(prototypeIR));
	stack.push_back (std::move(bodyIR));
	stack.push_back (std::move(endIR));

	return codegen->createStackIR (std::move (stack));

}

std::unique_ptr<BaseIR> ReturnStmtAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();

	if (retVal == nullptr) {
		return codegen->createRetVoidIR();
	} else {
		auto  retValIR = retVal->codegen();
		auto _retValIR = retValIR.get();

		auto retIR = codegen->createRetIR (_retValIR);
		std::vector<std::unique_ptr<BaseIR>> stack;

		stack.push_back (std::move(retValIR));
		stack.push_back (std::move(retIR));

		return codegen->createStackIR (std::move (stack));

	}

}
