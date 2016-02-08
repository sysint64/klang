#pragma once
#include "ast/ast.h"
#include "compiler.h"

class DirectiveAST : public NodeAST {
public:
	std::string name;
	std::string content;

	DirectiveAST (const std::string &name, const std::string &content = "")
		: name (name), content (content) {}

	virtual std::unique_ptr<BaseIR> codegen() override;

};

class DirectivesAST : public NodeAST {
public:
	std::vector<std::unique_ptr<DirectiveAST>> directives;

	DirectivesAST (std::vector<std::unique_ptr<DirectiveAST>> directives)
		: directives (std::move (directives)) {}

	virtual std::unique_ptr<BaseIR> codegen() override;

};

class ArgsAST : public NodeAST {
public:
	std::vector<std::shared_ptr<ExprAST>> args;

	ArgsAST (std::vector<std::shared_ptr<ExprAST>> args) : args (std::move(args)) {}
	virtual std::unique_ptr<BaseIR> codegen() override;

};

class PrototypeAST : public NodeAST {
public:
	std::shared_ptr<Compiler::VarsDict> varsDict;
	std::shared_ptr<TypeAST>            type;
	std::unique_ptr<DirectivesAST>      directives;
	std::unique_ptr<ArgsAST>            args;

	std::string name;
	bool external = true;

	PrototypeAST (const std::string &name, std::unique_ptr<ArgsAST> args,
		std::unique_ptr<DirectivesAST> directives, std::shared_ptr<TypeAST> type)
		: name (name), args (std::move(args)), directives (std::move(directives))
	{
		this->type = type;
	}

	virtual std::unique_ptr<BaseIR> codegen()        override;
	virtual std::unique_ptr<BaseIR> codegenDeclare() override;

};

class FunctionAST : public NodeAST {
public:
	std::unique_ptr<StmtAST>      body;
	std::shared_ptr<PrototypeAST> prototype;

	FunctionAST (std::unique_ptr<StmtAST> body, std::shared_ptr<PrototypeAST> prototype)
		: body(std::move(body)), prototype(prototype)
	{}

	virtual std::unique_ptr<BaseIR> codegen() override;
};

class ReturnStmtAST : public StmtAST {
public:
	std::unique_ptr<ExprAST> retVal = nullptr;
	std::shared_ptr<TypeAST> type;

	ReturnStmtAST (std::shared_ptr<TypeAST> type) {
		this->type = type;
	}

	ReturnStmtAST (std::shared_ptr<TypeAST> type, std::unique_ptr<ExprAST> retVal)
		: retVal (std::move(retVal))
	{
		this->type = type;
	}

	virtual std::unique_ptr<BaseIR> codegen() override;
};
