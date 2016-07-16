#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>

class BaseIR {
public:
	std::string emit;
	std::string addr;
	BaseIR *type;
	bool isConst = false;
	int  align = 8;
};

static const std::string sTmp  = "tmp";
static const std::string sStr  = "str";
static const std::string sPtr  = "ptr";
static const std::string sArg  = "arg";
static const std::string sCall = "call";

class Codegen {
protected:
	std::vector<std::unique_ptr<BaseIR>> blockDType;
	std::vector<std::unique_ptr<BaseIR>> blockHead;
	std::vector<std::unique_ptr<BaseIR>> blockBody;
	std::vector<std::unique_ptr<BaseIR>> blockEnd;

public:

	enum IRBlock { Head, DType, Body, End };
	enum Arch    { x32, x64 };

	FILE *f;
	bool emitConsole = true;
	std::string input;
	std::string output;
	Arch arch = x32;
	bool skipInsert = false;

	virtual inline void emitIR (const std::string &line, const bool F = false) {

		if (emitConsole) std::cout << line << std::endl;
		fputs ((line+"\n").c_str(), f);

	}

	inline void insert (std::unique_ptr<BaseIR> IR, IRBlock block) {

		if (skipInsert || !IR)
			return;

		switch (block) {

			case DType : blockDType.push_back (std::move(IR)); break;
			case Head  : blockHead .push_back (std::move(IR)); break;
			case Body  : blockBody .push_back (std::move(IR)); break;
			case End   : blockEnd  .push_back (std::move(IR)); break;

		}

	}

	virtual void emit()     {}
	virtual void optimize() {}
	virtual void save()     {}

	// Types

	virtual inline std::unique_ptr<BaseIR> createVoidTyIR  () { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createIntTyIR   (const int size) { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createIntValIR  (const int64_t val, const int size) { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createDefIR     (const std::string &name, std::unique_ptr<BaseIR> args, std::unique_ptr<BaseIR> directives, std::unique_ptr<BaseIR> type) { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createDeclareIR (const std::string &name, std::unique_ptr<BaseIR> args, std::unique_ptr<BaseIR> directives, std::unique_ptr<BaseIR> type) { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createArgIR     (const std::string &name, std::unique_ptr<BaseIR> type) { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createArgsIR    (std::vector<std::unique_ptr<BaseIR>> args) { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createInlineDirectiveIR () { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createDirectivesIR (std::vector<std::unique_ptr<BaseIR>> directives) { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createFastCallDirectiveIR() { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createStdCallDirectiveIR() { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createStackIR (std::vector<std::unique_ptr<BaseIR>> stack) { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createRetVoidIR() { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createRetIR (BaseIR *val) { return nullptr; }
	virtual inline std::unique_ptr<BaseIR> createEndIR() { return nullptr; }

	// Arithmetic

	virtual inline std::unique_ptr<BaseIR> createAddIR (BaseIR *A, BaseIR *B,
		const bool nsw = false, const bool nuw = false) { return nullptr; }

};

#include "codegen/llvm/codegen.h"
#include "codegen/cpp/codegen.h"
