#pragma once

#include "ast/ast.h"
#include "ast/type.h"
#include "parser/parser.h"
#include "codegen/codegen.h"
#include <memory>
#include <string>
#include <map>

class Parser;
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
	void declareType (std::shared_ptr<TypeAST> type);
	void declareDefaultTypes();

public:
	typedef std::map<std::string, std::shared_ptr<TypeAST>>      TypesDict;
	typedef std::map<std::string, std::shared_ptr<PrototypeAST>> FuncsDict;

	std::vector<std::shared_ptr<TypesDict>> typesDictsStack;
	std::vector<std::shared_ptr<FuncsDict>> funcsDictsStack;

	std::unique_ptr<Parser> parser;
	std::string input  = "";
	std::string output = "a.out";
	std::string lang   = "en";
	std::unique_ptr<Codegen> codegen;

	void compile();
	void parseCmd (int argc, char *argv[]);
	inline Codegen *getCurrentCodegen() { return codegen.get(); };

	std::shared_ptr<TypeAST> findType (const std::string &id) const;

};
