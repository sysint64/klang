#include "compiler.h"
#include "codegen/llvm/codegen.h"
#include "config.h"
#include <boost/range/adaptor/reversed.hpp>

void Compiler::compile() {

	declareDefaultTypes();

	parser  = std::make_unique<Parser>(this);
	codegen = std::make_unique<LLVMCodegen>();

	parser->parse();

}

void Compiler::loadMessages() {

}

void Compiler::declareType (std::shared_ptr<TypeAST> type) {

	std::shared_ptr<TypesDict> dict = typesDictsStack[0];
	dict->insert (std::pair<std::string, std::shared_ptr<TypeAST>>(type->name, type));

}

void Compiler::declareDefaultTypes() {

	std::shared_ptr<TypesDict> globalTypeDict = std::make_shared<TypesDict>();
	typesDictsStack.push_back (globalTypeDict);

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
