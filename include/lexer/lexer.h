#pragma once

#include <string>
#include <vector>
#include <iostream>

enum TokenChar { // last: -20

	// tok_ra : ->
	// tok_la : <-
	// tok_ba : <->
	// tok_dd : ::

	tok_eof = -1, tok_none = 0,
	tok_id = -2, tok_number = -3, tok_string = -4,

	tok_le = -5, tok_ge = -6, tok_ne = -7, tok_eq = -8,

	tok_def = -9, tok_cc = -10,
	tok_shl = -11, tok_shr = -12, tok_or = -13, tok_and = -14,
	tok_true = -15, tok_false = -16,
	tok_ra = -17, tok_la = -18, tok_ba = -19,
	tok_dd = -20,

};

class Compiler;
class Lexer {
public:
	struct Token {
		int token;
		std::string id;
		long double num;
	};

private:

	Compiler *compiler;
	int tsCursor = 0;
	int lastChar = ' ';

	int  getChar();
	int  getToken();
	void pushToken();
	void popToken();

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

	std::vector<Token> tokenStack;
	std::vector<FILE*> inputs;
	FILE *inFile;

	int line = 1;
	int pos  = 1;

	std::string identifier;
	std::string meta;
	long double number;
	int currentToken;

	int getNextToken();
	int getPrevToken();

	inline void printToken() {

		std::cout << "Token code: " << currentToken << " "
		          << "Token char: " << static_cast<char>(currentToken)
		          << std::endl;

	}

	inline void openFile (const std::string &input) {

		inFile = fopen (input.c_str(), "r");

	}

	Lexer (Compiler *compiler);
	~Lexer() { fclose (inFile); }

};
