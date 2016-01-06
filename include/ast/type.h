#pragma once
#include "ast/ast.h"

class AliasTypeAST : public TypeAST {
public:
};

class IntTypeAST : public TypeAST {
public:

	IntTypeAST (const std::string &name, int size, bool isUnsigned = false) {

		this->name = name;
		this->size = size;
		typeClass  = TypeAST::Int;

	}

};
