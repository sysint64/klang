#pragma once

#include "parser/parser.h"
#include <memory>
#include <string>

class Compiler {
private:

	struct Option {

		std::string name;
		std::string text;

	};

	// Command Line

	void displayOptimizersHelp (int argc, char *argv[]);
	void displayMainHelp       (int argc, char *argv[]);

	void loadMessages();

public:
	std::unique_ptr<Parser> parser;
	std::string input;
	std::string output = "a.out";
	std::string lang   = "en";

	void compile();
	void parseCmd (int argc, char *argv[]);

};
