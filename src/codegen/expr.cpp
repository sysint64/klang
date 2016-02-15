#include "ast/expr.h"
#include "config.h"

std::unique_ptr<BaseIR> IntExprAST::codegen() {

	if (!compiler) puts ("compiler");
	else if (!compiler->getCurrentCodegen()) puts ("codegenerator");

	return compiler->getCurrentCodegen()->createIntValIR (val, size);

}

std::unique_ptr<BaseIR> UnaryExprAST::codegen() {

	return nullptr;

}

std::unique_ptr<BaseIR> VarExprAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();
	return codegen->createArgIR (name, type->codegen());

}

std::unique_ptr<BaseIR> NumBinaryExprAST::codegen() {

	auto codegen = compiler->getCurrentCodegen();

	std::unique_ptr<BaseIR> L = LHS->codegen();
	std::unique_ptr<BaseIR> R = RHS->codegen();

	if (!L || !R)
		return nullptr;

	auto _L = L.get();
	auto _R = R.get();

	std::vector<std::unique_ptr<BaseIR>> stack;
	std::unique_ptr<BaseIR> bin = nullptr;

	if (!L->isConst) stack.push_back (std::move(L));
	if (!R->isConst) stack.push_back (std::move(R));

	switch (op) {

		case '+' : bin = compiler->getCurrentCodegen()->createAddIR (_L, _R); break;

	}

	if (!bin)
		return nullptr;

	stack.push_back (std::move(bin));
	return codegen->createStackIR (std::move(stack));

	/*if (L == 0 || R == 0) return 0;

	switch (Op) {
		case '+'	: return CreateAdd (L, R, LHS->GetTy());
		case '-'	: return CreateSub (L, R, LHS->GetTy());
		case '*'	: return CreateMul (L, R, LHS->GetTy());
		case '/'	: return CreateDiv (L, R, LHS->GetTy());
		case '%'	: return CreateRem (L, R, LHS->GetTy());

		// Int
		//case tok_div	: return CreateDiv (L, R, LHS->GetTy());
		//case tok_mod	: return CreateRem (L, R, LHS->GetTy());
		case tok_shl	: return CreateShl (L, R, LHS->GetTy());
		case tok_shr	: return CreateShr (L, R, LHS->GetTy());
		case tok_xor	: return CreateXor (L, R, LHS->GetTy());
		case tok_and	: return CreateAnd (L, R, LHS->GetTy());
		case tok_or		: return CreateOr  (L, R, LHS->GetTy());
		case '&'		: return CreateAnd (L, R, LHS->GetTy());
		case '|'		: return CreateOr  (L, R, LHS->GetTy());

		// Cmp
		case tok_eq	: return CreateCmpEQ (L, R, LHS->GetTy());
		case '<'	: return CreateCmpLT (L, R, LHS->GetTy());
		case '>'	: return CreateCmpGT (L, R, LHS->GetTy());

		case tok_le	: return CreateCmpLE (L, R, LHS->GetTy());
		case tok_ge	: return CreateCmpGE (L, R, LHS->GetTy());
		case tok_ne	: return CreateCmpNE (L, R, LHS->GetTy());
	}*/

}
