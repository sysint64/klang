#pragma once

class IntExprAST : public ExprAST {
public:
	int64_t val;
	int     size;

	IntExprAST (int64_t val, const int size = 32, const bool isUnsigned = false,
		const bool isChar = false) : val (val), size (size)
	{
		isConst  = true;
		numValue = val;
	}

	virtual std::unique_ptr<BaseIR> codegen() override { return nullptr; }

};

class UnaryExprAST : public ExprAST {
public:
	char op;
	std::unique_ptr<ExprAST> val;

	UnaryExprAST (char op, std::unique_ptr<ExprAST> val) : op(op), val(std::move(val)) {

	}

	virtual std::unique_ptr<BaseIR> codegen() override { return nullptr; }

};

class NumBinaryExprAST : public ExprAST {
public:
	std::unique_ptr<ExprAST> LHS, RHS;
	char op;

	NumBinaryExprAST (char op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS) :
		op(op), LHS (std::move(LHS)), RHS (std::move(RHS)) {}

	virtual std::unique_ptr<BaseIR> codegen() override { return nullptr; }

};
