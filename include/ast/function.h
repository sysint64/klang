#pragma once
#include "ast/ast.h"

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
	std::vector<std::unique_ptr<ExprAST>> args;
	ArgsAST (std::vector<std::unique_ptr<ExprAST>> args) : args (std::move(args)) {}
	virtual std::unique_ptr<BaseIR> codegen() override;

};

class PrototypeAST : public NodeAST {
public:
	std::shared_ptr<TypeAST>       type;
	std::unique_ptr<DirectivesAST> directives;
	std::unique_ptr<ArgsAST>       args;

	std::string name;

	PrototypeAST (const std::string &name, std::unique_ptr<ArgsAST> args,
		std::unique_ptr<DirectivesAST> directives, std::shared_ptr<TypeAST> type)
		: name (name), args (std::move(args)), directives (std::move(directives))
	{
		this->type = type;
	}

	virtual std::unique_ptr<BaseIR> codegen()        override;
	virtual std::unique_ptr<BaseIR> codegenDeclare() override;
	
};
