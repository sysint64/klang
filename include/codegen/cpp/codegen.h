#pragma once

#include "codegen/codegen.h"
#include "codegen/ir_factory.h"
#include "codegen/cpp/ir.h"

class CPPCodegen : public Codegen {
public:

	CPPCodegen () { f = fopen ("a.out.cpp", "w"); }
	~CPPCodegen() { if (f != nullptr) fclose(f); }

	//CODEGEN_FACTORY(cpp_ir)

	virtual void emit() override {

		emitIR ("// ModuleID = '"+input+".k'");

		emitIR ("\n// Type declares" ); for (auto const &IR : blockDType) emitIR (IR->emit);
		emitIR ("\n// Global vars"   ); for (auto const &IR : blockHead ) emitIR (IR->emit);
		emitIR ("\n// Funcs declares"); for (auto const &IR : blockEnd  ) emitIR (IR->emit);
		emitIR ("\n// Implementation"); for (auto const &IR : blockBody ) emitIR (IR->emit);

	}

};
