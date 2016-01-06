#pragma once

#include "codegen/codegen.h"
#include <memory>
#include <string>

class NodeAST {
public:
	virtual std::unique_ptr<BaseIR> codegen() { return nullptr; }
};

class TypeAST : public NodeAST {
public:
	enum TypeClass { Void, Func, Int, Float, Array, Vector, Pointer, Struct, Class, None };

	std::shared_ptr<TypeAST> child = nullptr;
	TypeClass typeClass = None;
	int  size = 8;
	std::string name;

	std::shared_ptr<TypeAST> autoCast();
	std::shared_ptr<TypeAST> staticCast();
	std::shared_ptr<TypeAST> dynamicCast();

	inline  std::shared_ptr<TypeAST> dereference()    { return child;   }
	virtual std::unique_ptr<BaseIR>  codegenDeclare() { return nullptr; }

};

/** \brief base expression abstract tree node */

class ExprAST : public NodeAST {
public:
	TypeAST      type;
	int          align     = 0;
	bool         isConst   = false;
	long double  numValue  = 0;
	std::string  strValue  = "";
	std::wstring wstrValue = L"";

	ExprAST() {

	}

};

/** \brief base statement abstract tree node */

class StmtAST : public NodeAST {
public:

};

class BlockStmtAST : public StmtAST {
public:
	std::vector<std::unique_ptr<StmtAST>> data;
};
