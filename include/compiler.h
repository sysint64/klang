#pragma once

#include <memory>
#include <string>
#include <map>
#include <vector>

#include "parser/parser.h"

class TypeAST;
class PrototypeAST;
class VarExprAST;
class Codegen;
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
	void declareDefaultTypes();

public:
	typedef std::map<std::string, std::shared_ptr<TypeAST>>      TypesDict;
	typedef std::map<std::string, std::shared_ptr<PrototypeAST>> FuncsDict;
	typedef std::map<std::string, std::shared_ptr<VarExprAST>>   VarsDict;

	std::vector<std::shared_ptr<TypesDict>> typesDictsStack;
	std::vector<std::shared_ptr<FuncsDict>> funcsDictsStack;
	std::vector<std::shared_ptr<VarsDict >> varsDictsStack;

	std::unique_ptr<Parser> parser;
	std::string input  = "";
	std::string output = "a.out";
	std::string lang   = "en";
	std::string currentNamespace = "main";
	std::unique_ptr<Codegen> codegen;
	std::shared_ptr<PrototypeAST> currentPrototype = nullptr;

	void compile();
	void parseCmd (int argc, char *argv[]);
	inline Codegen *getCurrentCodegen() { return codegen.get(); };

	std::shared_ptr<TypeAST> findType (const std::string &id) const;

	template<typename T, typename DT>
	void declare (std::shared_ptr<T> obj, const DT &dicts);

	void declareType (std::shared_ptr<TypeAST>      type);
	void declareFunc (std::shared_ptr<PrototypeAST> func);
	void declareVar  (std::shared_ptr<VarExprAST>   var );

};
