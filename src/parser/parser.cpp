#include "parser/parser.h"

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
