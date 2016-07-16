#include "compiler.h"
#include "codegen/codegen.h"
#include "ast/all.h"
#include "codegen/llvm/codegen.h"
#include "config.h"
#include <boost/range/adaptor/reversed.hpp>

void Compiler::compile() {

	declareDefaultTypes();

	parser  = std::make_unique<Parser>(this);
	codegen = std::make_unique<LLVMCodegen>(output+".ll");

	parser->parse();

}

void Compiler::loadMessages() {

}

template<typename T, typename DT>
void Compiler::declare (std::shared_ptr<T> obj, const DT &dicts) {

	auto dict = dicts.front();
	dict->insert (std::pair<std::string, std::shared_ptr<T>>(obj->name, obj));

}

void Compiler::declareType (std::shared_ptr<TypeAST> type) {
	declare<TypeAST, std::vector<std::shared_ptr<TypesDict>>>(type, typesDictsStack);
}

void Compiler::declareFunc (std::shared_ptr<PrototypeAST> func) {
	declare<PrototypeAST, std::vector<std::shared_ptr<FuncsDict>>>(func, funcsDictsStack);
}

void Compiler::declareVar (std::shared_ptr<VarExprAST> var) {
	declare<VarExprAST, std::vector<std::shared_ptr<VarsDict>>>(var, varsDictsStack);
}

void Compiler::declareDefaultTypes() {

	std::shared_ptr<TypesDict> globalTypesDict = std::make_shared<TypesDict>();
	std::shared_ptr<FuncsDict> globalFuncsDict = std::make_shared<FuncsDict>();
	std::shared_ptr<VarsDict > globalVarsDict  = std::make_shared<VarsDict >();

	typesDictsStack.push_back (globalTypesDict);
	funcsDictsStack.push_back (globalFuncsDict);
	varsDictsStack .push_back (globalVarsDict );

	declareType (std::make_shared<VoidTypeAST> ("void"));

	// Signed

	declareType (std::make_shared<IntTypeAST> ("bool"    , 1));
	declareType (std::make_shared<IntTypeAST> ("shortint", 8));
	declareType (std::make_shared<IntTypeAST> ("smallint", 16));
	declareType (std::make_shared<IntTypeAST> ("int"     , 32));
	declareType (std::make_shared<IntTypeAST> ("longint" , 32));
	declareType (std::make_shared<IntTypeAST> ("int64"   , 64));

	// Unsigned

	declareType (std::make_shared<IntTypeAST> ("char"    , 8 , true));
	declareType (std::make_shared<IntTypeAST> ("byte"    , 8 , true));
	declareType (std::make_shared<IntTypeAST> ("wchar"   , 16, true));
	declareType (std::make_shared<IntTypeAST> ("word"    , 16, true));
	declareType (std::make_shared<IntTypeAST> ("widechar", 16, true));
	declareType (std::make_shared<IntTypeAST> ("cardinal", 32, true));
	declareType (std::make_shared<IntTypeAST> ("longword", 32, true));
	declareType (std::make_shared<IntTypeAST> ("uint64"  , 64, true));

}

std::shared_ptr<TypeAST> Compiler::findType (const std::string &id) const {

	for (const auto &dict : boost::adaptors::reverse(typesDictsStack)) {

		auto item = dict->find(id);

		if (item != dict->end())
			return item->second;

	}

	return nullptr;

}
