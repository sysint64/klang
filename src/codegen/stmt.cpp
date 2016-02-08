#include "ast/ast.h"
#include "config.h"

std::unique_ptr<BaseIR> BlockStmtAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();
	std::vector<std::unique_ptr<BaseIR>> stack;

	for (const auto &item : data) {

		auto IR = item->codegen();
		stack.push_back (std::move(IR));

	}

	return codegen->createStackIR (std::move (stack));

}
