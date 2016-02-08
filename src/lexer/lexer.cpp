#include "lexer/lexer.h"
#include "compiler.h"
#include "utility.cpp"
#include <math.h>

Lexer::Lexer (Compiler *compiler) {

	this->compiler = compiler;
	openFile (compiler->input);

}

int Lexer::getChar() {

	static int buf;
	if (feof (inFile)) return EOF;

	fread (&buf, sizeof(char), 1, inFile); ++pos;

	if (buf == '\n') {

		++line;
		pos = 1;

	}

	return buf;

}

void Lexer::pushToken() {

	Token tok;

	tok.token = currentToken;
	tok.id    = identifier;
	tok.num   = number;

	tokenStack.push_back(tok);

	if (tokenStack.size() > 4)
		tokenStack.erase (tokenStack.begin());

}

void Lexer::popToken() {

	currentToken = tokenStack[tsCursor-1].token;
	identifier   = tokenStack[tsCursor-1].id;
	number       = tokenStack[tsCursor-1].num;

}

int Lexer::getNextToken() {

	if (tsCursor < tokenStack.size()) {

		tsCursor++;
		popToken();

		return tokenStack[tsCursor].token;

	} else {

		int token    = getToken();
		currentToken = token;
		pushToken();
		tsCursor = tokenStack.size();

		return token;

	}

}

int Lexer::getPrevToken() {

	--tsCursor;
	popToken();

	return tokenStack[tsCursor-1].token;

}

/**
 */

int Lexer::getToken() {

	while (isspace (lastChar))
		lastChar = getChar();

	if (feof(inFile))
		return tok_eof;

	if (isalpha (lastChar)) return lexId();
	if (isdigit (lastChar)) return lexNumber();
	if (lastChar == '_')    return lexId();
	if (lastChar == '.')    return lexDots();
	if (lastChar == '\'')   return lexChar();
	if (lastChar == '\"')   return lexString();
	if (lastChar == '=')    return lexEq();
	if (lastChar == '!')    return lexNe();
	if (lastChar == '|')    return lexOr();
	if (lastChar == '&')    return lexAnd();
	if (lastChar == '<')    return lexLe();
	if (lastChar == '>')    return lexGe();
	if (lastChar == '/')    return lexComment();

	if (lastChar == '-') {
		lastChar = getChar();

		if (lastChar == '>') {
			lastChar = getChar();
			return tok_ra;
		}

		return '-';
	}

	if (lastChar == ':') {
		lastChar = getChar();

		if (lastChar == ':') {
			lastChar = getChar();
			return tok_dd;
		}

		return ':';
	}

	int thisChar = lastChar;
	    lastChar = getChar();

	return thisChar;

}

/**
 */

int Lexer::lexId() {

	identifier = "";

	while (isdigit(lastChar) || isalpha(lastChar) || lastChar == '_') {

		identifier += lastChar;
		lastChar    = getChar();

	}


	if (identifier == "def")      return tok_def;
	if (identifier == "end")      return tok_end;
	if (identifier == "return")   return tok_return;

	// Call Convs

	/*meta = identifier;

	if (identifier == "fastcc")   return tok_cc;
	if (identifier == "ccc")      return tok_cc;
	if (identifier == "coldcc")   return tok_cc;
	if (identifier == "cc")       return tok_cc;
	if (identifier == "fastcall") { meta = "x86_fastcallcc"; return tok_cc; }
	if (identifier == "stdcall")  { meta = "x86_stdcallcc";  return tok_cc; }
	if (identifier == "cdecl")    { meta = "";               return tok_cc; }*/

	meta = "";
	return tok_id;

}

/**
 */

int Lexer::lexNumber() {

	int state = 2;
	std::string numStr;
	std::string scaleStr;

	while (state < 8) { // Build state machine, 9 - finish state

		switch (state) {

			case 1: // Hex val
				{
					lastChar = getChar();

					numStr = "";
					lastChar = tolower (getChar());

					while ((lastChar >= '0' && lastChar <= '9') || (lastChar >= 'a' && lastChar <= 'f')) {

						numStr  += lastChar;
						lastChar = tolower (getChar());

					}


					number = HexIntToVal (numStr.c_str());
					return tok_number;
				}

			case 2:
				{
					numStr += lastChar;
					lastChar = getChar();

					switch (lastChar) {

						case 'x': state = 1; break;
						case '.': state = 3; break;
						case 'E':
						case 'e': state = 5; break;
						default: state = 9;

					}

					if (isdigit (lastChar)) state = 2;
					break;
				}

			case 3:
				numStr  += lastChar;
				lastChar = getChar();

				if (isdigit (lastChar)) state = 4;
				else                    state = 9; // TODO: Error

				break;

			case 4:
				numStr  += lastChar;
				lastChar = getChar();

				     if (lastChar == 'E' || lastChar == 'e') state = 5;
				else if (isdigit (lastChar))                 state = 4;
				else                                         state = 9;

				break;

			case 5:
				lastChar = getChar();

				     if (lastChar == '+' || lastChar == '-') state = 6;
				else if (isdigit (lastChar))                 state = 7;
				else                                         state = 9; // TODO: Error;

				break;

			case 6:
				scaleStr += lastChar;
				lastChar  = getChar();

				if (isdigit (lastChar)) state = 7;
				else                    state = 9; // Ошибка

				break;

			case 7:
				scaleStr += lastChar;
				lastChar  = getChar();

				if (isdigit (lastChar)) state = 7;
				else                    state = 8;

				break;

			default : ;

		}

		int scaleFactor = scaleStr == "" ? 0 : stod (scaleStr);
		number = stod (numStr)*pow (10, scaleFactor);
		return tok_number;

	}

	return tok_none;

}

/**
 */

int Lexer::lexDots() {
	return tok_none;
}

int Lexer::lexString() {
	return tok_none;
}

int Lexer::lexChar() {
	return tok_none;
}

int Lexer::lexEq() {
	return tok_none;
}

int Lexer::lexNe() {
	return tok_none;
}

int Lexer::lexOr() {
	return tok_none;
}

int Lexer::lexAnd() {
	return tok_none;
}

int Lexer::lexLe() {
	return tok_none;
}

int Lexer::lexGe() {
	return tok_none;
}

int Lexer::lexComment() {
	return '/';
}
