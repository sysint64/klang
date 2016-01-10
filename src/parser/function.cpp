#include "ast/all.h"
#include "parser/parser.h"
#include "compiler.h"

/** \brief
	Parse arguments of function, `example` : `(Num a, b)`
	Grammar
	    ARGS ::= NONE | ARGS | ARGS ',' VAR
*/

std::unique_ptr<ArgsAST> Parser::parseArgs() {

	std::vector<std::shared_ptr<ExprAST>> args;

	do {

		lexer->getNextToken();
		auto arg = parseVar();
		args.push_back (std::move(arg));

	} while (lexer->currentToken == ';');

	return std::make_unique<ArgsAST> (std::move(args));

}

/** \brief
	Parse directive for function, `example` : `extern "llvm.fpow"`
	Grammar:
	    DIRECTIVE ::= ID | ID STRING
*/

std::unique_ptr<DirectiveAST> Parser::parseDirective() {

	if (lexer->currentToken != tok_id) {
		puts ("error :(");
		return nullptr;
	}

	auto name = lexer->identifier;
	puts (name.c_str());
	lexer->getNextToken();

	return std::make_unique<DirectiveAST> (name);

}

/** \brief
	Parse directives for function, `example` : `inline, extern "llvm.fpow"`
	Grammar:
	    DIRECTIVES ::= DIRECTIVES | DIRECTIVES ',' DIRECTIVE
*/

std::unique_ptr<DirectivesAST> Parser::parseDirectives() {

	std::vector<std::unique_ptr<DirectiveAST>> directives;

	do {

		lexer->getNextToken();
		auto directive = parseDirective();
		directives.push_back (std::move(directive));

	} while (lexer->currentToken == ',');

	return std::make_unique<DirectivesAST> (std::move(directives));

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

	std::string name = lexer->identifier;
	lexer->getNextToken();

	if (lexer->currentToken != '(') {

		puts ("Expected '('");
		return nullptr;

	}

	// Arguments

	auto args = parseArgs();

	if (!args)
		return nullptr;

	if (lexer->currentToken != ')') {

		puts ("Expected ')'");
		return nullptr;

	}

	// Type

	lexer->getNextToken();
	auto type = compiler->findType ("void");

	if (lexer->currentToken == tok_ra) {

		lexer->getNextToken();
		type = parseType();

		if (!type) {

			puts ("cant find type");
			return nullptr;

		}

	}

	lexer->getNextToken();

	// Directives

	std::unique_ptr<DirectivesAST> directives = nullptr;
	if (lexer->currentToken == tok_dd) {

		directives = parseDirectives();

	}

	return std::make_unique<PrototypeAST> (name, std::move(args), std::move(directives), type);

}
