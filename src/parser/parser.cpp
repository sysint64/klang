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

	while (true) {

		lexer->getNextToken();

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

		auto IR = def->codegen();
		compiler->getCurrentCodegen()->insert (std::move(IR), Codegen::Head);

	} else {

		lexer->getNextToken();

	}

}
