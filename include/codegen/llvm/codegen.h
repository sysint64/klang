#pragma once

#include "codegen/codegen.h"
#include "codegen/llvm/ir.h"

class LLVMCodegen : public Codegen {
public:

	bool dataLayout = true;

	LLVMCodegen () { f = fopen ("a.out.ll", "w"); }
	~LLVMCodegen() { if (f != nullptr) fclose(f); }

	CODEGEN_FACTORY(llvm_ir)

	virtual void emit() override {

		emitIR ("; ModuleID = '"+input+".k'");

		if (dataLayout) {
			if (arch == x32) emitIR ("target datalayout = \"e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-f80:128:128-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S32\"\n"); else
			if (arch == x64) emitIR ("target datalayout = \"e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128\"\n");
		}

		emitIR ("\n; Type declares" ); for (auto const &IR : blockDType) emitIR (IR->emit);
		emitIR ("\n; Global vars"   ); for (auto const &IR : blockHead ) emitIR (IR->emit);
		emitIR ("\n; Funcs declares"); for (auto const &IR : blockEnd  ) emitIR (IR->emit);
		emitIR ("\n; Implementation"); for (auto const &IR : blockBody ) emitIR (IR->emit);

		emitIR ("\n; Metadata\n!0 = metadata !{ metadata !0 }");

	}

};
