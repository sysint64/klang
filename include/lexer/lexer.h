#pragma once

#include <string>
#include <vector>

enum TokenChar { // last: -10

	tok_eof = -1, tok_none = 0,
	tok_id = -2, tok_number = -3, tok_string = -4,

	tok_le = -5, tok_ge = -6, tok_ne = -7, tok_eq = -8,

	tok_def = -9, tok_cc = -10,

};

class Lexer {
public:
	struct Token {
		int token;
		std::string id;
		long double num;
	};

private:

	std::vector<Token> tokenStack;
	int currentToken;
	int tsCursor = 0;
	int lastChar = ' ';

	int getChar();
	int getToken();
	int pushToken();
	int popToken();

	//

	int lexId();
	int lexNumber();
	int lexDots();
	int lexChar();
	int lexString();
	int lexEq();
	int lexNe();
	int lexOr();
	int lexAnd();
	int lexLe();
	int lexGe();
	int lexComment();

public:

	FILE *inFile;

	int line = 1;
	int pos  = 1;

	std::string identifier;
	std::string meta;
	long double number;

	int getNextToken();
	int getPrevToken();

};
