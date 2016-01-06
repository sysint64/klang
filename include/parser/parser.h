#pragma once

#include "lexer/lexer.h"
#include "ast/all.h"

#include <memory>
#include <unordered_map>

#define sptr std::shared_ptr
#define uptr std::unique_ptr

class Compiler;
class Lexer;
class Parser {
private:
	std::unordered_map<char, int> binopPrecedence;
	Compiler *compiler;

public:
	std::unique_ptr<Lexer> lexer;

	Parser (Compiler *compiler);

	// Expr

	std::unique_ptr<ExprAST> parseValue(); // -
	std::unique_ptr<ExprAST> parseUnary(); // -
	std::unique_ptr<ExprAST> foldingBinary (char op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS); // -
	std::unique_ptr<ExprAST> parseBinary (int exprPrec, std::unique_ptr<ExprAST> LHS); // -
	std::unique_ptr<ExprAST> parseExpr(); // -
	std::unique_ptr<ExprAST> parseVar(); // -

	// Values

	std::unique_ptr<ExprAST> parseBoolean (const bool val) const; // +
	std::unique_ptr<ExprAST> parseNumber(); // -
	std::unique_ptr<ExprAST> parseParen(); // -

	// Function

	std::unique_ptr<ArgsAST>       parseArgs(); // -
	std::unique_ptr<DirectivesAST> parseDirectives(); // -
	std::unique_ptr<PrototypeAST>  parsePrototype(); // -

	// Type

	std::shared_ptr<TypeAST> parseType(); // -

	// Handles

	void handleDefinition();
	void parse();

	inline int getTokPrecedence() {

		int tokPrec = binopPrecedence[lexer->currentToken];
		if (tokPrec <= 0) return -1;

		return tokPrec;

	}

};
