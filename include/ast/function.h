#pragma once
#include "ast/ast.h"

class DirectivesAST : public NodeAST {

};

class ArgsAST : public NodeAST {

};

class PrototypeAST : public NodeAST {
public:
	std::unique_ptr<DirectivesAST> directives;
	std::unique_ptr<ArgsAST>       args;

	std::string name;
};
