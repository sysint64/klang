#pragma once

#include "codegen/codegen.h"
#include "ast/type.h"

#include <memory>

/** \brief base expression abstract tree node */

class ExprAST {
public:
	TypeAST      type;
	int          align     = 0;
	bool         isConst   = false;
	long double  numValue  = 0;
	std::string  strValue  = "";
	std::wstring wstrValue = L"";

	ExprAST() {

	}

	virtual std::unique_ptr<BaseIR> codegen() { return nullptr; }
};

/** \brief base statement abstract tree node */

class StmtAST {

};
