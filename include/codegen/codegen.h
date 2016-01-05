#pragma once

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

	inline void emitIR (const std::string &line, const bool F = false) {

		if (emitConsole) puts (line.c_str());
		fputs ((line+"\n").c_str(), f);

	}

	inline void insert (std::unique_ptr<BaseIR> IR, IRBlock block) {

		if (skipInsert)
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

};

#define CODEGEN_FACTORY(ir) \
	inline std::unique_ptr<BaseIR> createIntTyIR (const int size) { \
		return std::make_unique<ir::IntTyIR> (size); \
	} \

#include "codegen/llvm/codegen.h"
#include "codegen/cpp/codegen.h"
