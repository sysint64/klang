#pragma once

#include "lexer/lexer.h"
#include "ast/all.h"

#include <memory>
#include <unordered_map>

class Parser {
private:
	std::unordered_map<char, int> binopPrecedence;

public:
	std::unique_ptr<Lexer> lexer;
	std::shared_ptr<ExprAST> parseExpr(); // -
};
