#include "parser/parser.h"

/** \brief
	Parse arguments of function, `example` : `(Num a, b)`
	Grammar
	    ARGS ::= NONE | ARGS | ARGS ',' VAR
*/

std::unique_ptr<ArgsAST> Parser::parseArgs() {

	lexer->getNextToken(); //Eat token `(`
	parseVar();

	return nullptr;

}

/** \brief
	Parse directives for function, `example` : `inline, extern "llvm.fpow"`
	Grammar:
	    DIRECTIVES ::= DIRECTIVES | DIRECTIVES ',' DIRECTIVE
	    DIRECTIVE  ::=
*/

std::unique_ptr<DirectivesAST> Parser::parseDirectives() {

}

/** \brief
	Parse prototype of function, `example` : `def sum (Num a, b) -> Num :: inline`
	Grammar:
	    PROTOTYPE ::= DEF ID '(' ARGS ')' |
	                  DEF ID '(' ARGS ')' '->' TYPE |
	                  DEF ID '(' ARGS ')' '::' DIRECTICES
	                  DEF ID '(' ARGS ')' '->' TYPE '::' DIRECTICES
*/

std::unique_ptr<PrototypeAST> Parser::parsePrototype() {

	lexer->getNextToken(); //Eat tokenn `def`

	if (lexer->currentToken != tok_id) {

		puts ("Expected identifier");
		return nullptr;

	}

	lexer->getNextToken();

	if (lexer->currentToken != '(') {

		puts ("Expected '('");
		return nullptr;

	}

	auto args = parseArgs();

	//if (!args)
	//	return nullptr;

	if (lexer->currentToken != ')') {

		puts ("Expected ')'");
		return nullptr;

	}

	puts ("NEXT");
	return nullptr;

}
