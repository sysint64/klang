#include "parser/parser.h"
#include "compiler.h"

std::shared_ptr<TypeAST> Parser::parseType() {

	auto type = compiler->findType (lexer->identifier);
	return type;

}
