#include "ast/all.h"
#include "parser/parser.h"

std::unique_ptr<ExprAST> Parser::parseNumber() {

	double val = lexer->number;
	int size = 32;

	lexer->getNextToken();

	if (val > 0x7fffffff) size = 64;

	int64_t ival = floor(val);

	//if (IsIntTy(ExprTy)) return new IntExprAST(ival, size);
	//else if (IsFloatTy(ExprTy)) return new FloatExprAST(val, size);

	if (val == ival) return std::make_unique<IntExprAST  > (ival, size);
	//else             return std::make_unique<FloatExprAST> ( val, size);

	return nullptr;

}

std::unique_ptr<ExprAST> Parser::parseBoolean (const bool val) const {

	lexer->getNextToken();
	return std::make_unique<IntExprAST> (val, 1, false);

}

std::unique_ptr<ExprAST> Parser::parseParen() {

	return nullptr;

}

// VAL ::= NUM | PAREN | ID | THIS

std::unique_ptr<ExprAST> Parser::parseValue() {

	switch (lexer->currentToken) {

		case tok_true   : return parseBoolean (true);
		case tok_false  : return parseBoolean (false);
		case tok_number : return parseNumber();
		case '('        : return parseParen();
		//case '['        : return parseArrVal();
		//case '<'        : return parseVecVal();
		/*case tok_number	: return ParseNumber();
		//
		case tok_true	: return ParseBool(true);
		case tok_false	: return ParseBool(false);
		//
		case tok_string	: return ParseString();
		case tok_char   : return ParseChar();
		//
		case '('	: return ParseParen();
		case tok_id	: return ParseId();
		case '['	: return ParseArrVal();
		case '<'	: return ParseVecVal();
		case tok_sizeof : return ParseSizeOf();
		case tok_args	: Lexer->GetNextToken(); return new ArgsTyAST();
		case tok_cast	: return ParseCast();*/

	}

	return nullptr;

}

/**
	\brief Parse Unary
	UNARY ::= '!' VAL | '-' VAL | '@' VAL | VAL PTR | VAL IDXS | VAL
 */

std::unique_ptr<ExprAST> Parser::parseUnary() {

	char op = lexer->currentToken;

	if (op != '!' && op != '-' && op != '@') {

		auto value = parseValue();
		return value;

	}

	lexer->getNextToken();
	auto value = parseUnary();

	return std::make_unique<UnaryExprAST> (op, std::move(value));

}

#include <iostream>
std::unique_ptr<ExprAST> Parser::foldingBinary (char op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS) {

	std::cout << LHS->numValue << op << RHS->numValue << std::endl;
	return std::make_unique<NumBinaryExprAST>(op, std::move(LHS), std::move(RHS));

}

/**
\brief
	Parse binary expression, example: `1+3*(4+b)`
	Grammar:
	    BINARY ::= ('+' NUM)* >
 */

std::unique_ptr<ExprAST> Parser::parseBinary (int exprPrec, std::unique_ptr<ExprAST> LHS) {

	bool relop = false;

	while (true) {

		int tokPrec = getTokPrecedence();

		if (tokPrec < exprPrec)
			return LHS;

		int binOp = lexer->currentToken;
		lexer->getNextToken();

		auto RHS = parseUnary();

		if (!RHS)
			return LHS;

		int nextPrec = getTokPrecedence();

		if (tokPrec < nextPrec) {

			RHS = parseBinary (tokPrec+1, std::move(RHS));

			if (!RHS)
				return LHS;

		}

		LHS = foldingBinary (binOp, std::move(LHS), std::move(RHS));

	}

}

/**
\brief
	Parse variable or variable list, examples: `Int a, b = 1, 3`, `Int a, b, c = 1, ...`
	Grammar:
	    VARS   ::= TYPE IDS | TYPE IDS '=' VALUES
	    IDS    ::= IDS | ID ',' IDS
	    VALUES ::= VALUES | VALUES ',' VALUE | VALUES ',' '...'
*/
#include <iostream>
std::shared_ptr<ExprAST> Parser::parseVar (const bool arg) {

	auto type = parseType();
	if (!type) {
		std::cout << "type " << lexer->identifier << " does not name" << std::endl;
		lexer->getNextToken();
		return nullptr;
	}

	lexer->getNextToken();

	if (lexer->currentToken != tok_id) {
		puts ("Expected identifier");
		return nullptr;
	}

	auto id = lexer->identifier;
	lexer->getNextToken();

	if (arg) id += ".arg";

	std::shared_ptr<VarExprAST> var = std::make_shared<VarExprAST> (id, nullptr, type);
	compiler->declareVar (var);

	return var;

}

std::unique_ptr<ExprAST> Parser::parseExpr() {

	auto LHS = parseUnary();
	lexer->printToken();

	if (!LHS)
		return nullptr;

	return parseBinary (0, std::move(LHS));

}
