#include "compiler.h"

void Compiler::compile() {

	parser = std::make_unique<Parser>(this);
	parser->lexer->getNextToken();
	parser->parseExpr();

}

void Compiler::loadMessages() {

}
