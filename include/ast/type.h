#pragma once
#include "ast/ast.h"

class AliasTypeAST : public TypeAST {
public:
};

class VoidTypeAST : public TypeAST {
public:
	VoidTypeAST (const std::string &name) : TypeAST (name) {}
	virtual std::unique_ptr<BaseIR> codegen() override;
};

class IntTypeAST : public TypeAST {
public:

	IntTypeAST (const std::string &name, int size, bool isUnsigned = false) : TypeAST (name) {

		//this->name = name;
		this->size = size;
		typeClass  = TypeAST::Int;

	}

	virtual std::unique_ptr<BaseIR> codegen() override;

};
