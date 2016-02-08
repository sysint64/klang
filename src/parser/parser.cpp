#include "ast/all.h"
#include "parser/parser.h"
#include "compiler.h"

Parser::Parser (Compiler *compiler) {

	this->compiler = compiler;
	lexer = std::make_unique<Lexer>(compiler);

	// Precedencies

	binopPrecedence[tok_le]  = 1;  binopPrecedence[tok_ge]  = 1;
	binopPrecedence[tok_ne]  = 1;  binopPrecedence[tok_eq]  = 1;
	binopPrecedence['>']     = 1;  binopPrecedence['<']     = 1;

	binopPrecedence['+']     = 2;  binopPrecedence['-']     = 2;
	binopPrecedence['|']     = 3;  binopPrecedence['^']     = 2;
	binopPrecedence['*']     = 3;  binopPrecedence['/']     = 3;
	binopPrecedence['%']     = 3;  binopPrecedence['&']     = 3;
	binopPrecedence[tok_shl] = 3;  binopPrecedence[tok_shr] = 3;
	binopPrecedence[tok_or]  = 5;  binopPrecedence[tok_and] = 5;

}

void Parser::parse() {

	lexer->tokenStack.clear();
	lexer->getNextToken();

	while (true) {

		switch (lexer->currentToken) {

			case tok_def : handleDefinition(); break;
			case tok_eof : return;
			default:
				//auto e  = parseExpr();
				//auto ir = e->codegen();

				//compiler->getCurrentCodegen()->insert (std::move(ir), Codegen::Head);
				lexer->getNextToken();
				break;
				//return;

		}

	}

}

void Parser::handleDefinition() {

	if (auto def = parsePrototype()) {

		compiler->currentPrototype = def;
		compiler->declareFunc (def);

		// TODO: Move to one function check is break token for definition
		if (lexer->currentToken == tok_def || lexer->currentToken == tok_eof) {

			if (def->external) {

				auto IR = def->codegenDeclare();
				compiler->getCurrentCodegen()->insert (std::move(IR), Codegen::Head);

			}

			return;

		} else if (auto func = parseFunction (def)) {

			auto IR = func->codegen();
			compiler->getCurrentCodegen()->insert (std::move(IR), Codegen::Body);

		} else {

			// TODO: display error
			lexer->getNextToken();

		}

	} else {

		lexer->getNextToken();

	}

}

// parse statement

std::unique_ptr<StmtAST> Parser::parseStatement() {

	switch (lexer->currentToken) {

		case tok_return: return parseReturn(); break;
		default: lexer->getNextToken();

	}

	return nullptr;

}

// Parse Statements

std::unique_ptr<StmtAST> Parser::parseStatements() {

	std::vector<std::unique_ptr<StmtAST>> items;

	while (lexer->currentToken != tok_end) {

		auto stmt = parseStatement();
		items.push_back (std::move(stmt));

	}

	if (lexer->currentToken == tok_end)
		puts ("END :o");

	return std::make_unique<BlockStmtAST>(std::move(items));

}
