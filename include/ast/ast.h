#pragma once

#include "codegen/codegen.h"
#include "ast/type.h"

#include <memory>

/** \brief base expression abstract tree node*/

class ExprAST {
public:
	TypeAST type;
	int     align   = 0;
	bool    isConst = false;

	virtual std::shared_ptr<BaseIR> codegen();
};

/** \brief base statement abstract tree node */

class StmtAST {

};
