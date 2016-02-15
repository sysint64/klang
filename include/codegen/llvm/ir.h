#pragma once
#include "codegen/codegen.h"
#include <cassert>
#include <map>

namespace llvm_ir {

	static std::map<std::string, int> namesCounter;

	static std::string getName (const std::string &name) {

		if (namesCounter.find(name) == namesCounter.end())
			namesCounter[name]++;
		else
			namesCounter[name] = 0;

		return name+"."+std::to_string (namesCounter[name]);

	}

	class IntTyIR : public BaseIR {
	public:

		IntTyIR (const int size) {

			emit  = "i"+std::to_string (size);
			addr  = emit;
			align = size/8;

			if (size < 8)
				align = 8;

		}

	};

	class VoidTyIR : public BaseIR {
	public:

		VoidTyIR() {

			emit = "void";
			addr = emit;

		}

	};

	class IntValIR : public BaseIR {
	public:

		IntValIR (const int64_t val, const int base) {

			type = new IntTyIR (base); // TODO: Lake Memory
			isConst = true;

			if (base == 1) { // Boolean

				if (val >= 1) emit = "true";
				else          emit = "false";

				addr = emit;

			} else {

				emit = std::to_string (val);
				addr = emit;

			}

		}

	};

	class AddIR : public BaseIR {
	public:

		AddIR (BaseIR *A, BaseIR *B, const bool nsw = false, const bool nuw = false) {

			addr = "%"+getName("add");
			type = A->type;
			std::string nw = " ";

			if (nsw) nw += "nsw ";
			else if (nuw) nw += "nuw ";
			else nw = "";

			emit = "  "+addr+" = add "+nw+A->type->emit+" "+A->addr+", "+B->addr+"\n";

		}

	};

	class ArgIR : public BaseIR {
	public:

		ArgIR (const std::string &name, std::unique_ptr<BaseIR> type) {

			//assert (!type);
			emit = "%"+type->addr+" %"+name;
			//%string* %s.arg, i32 %size.arg

		}

	};

	class ArgsIR : public BaseIR {
	public:

		ArgsIR (std::vector<std::unique_ptr<BaseIR>> args) {

			for (const auto &arg : args)
				emit += arg ? arg->emit+", " : "";

			if (emit.size() >= 2) { // Remove last ", "

				emit.pop_back();
				emit.pop_back();

			}

		}

	};

	class DirectivesIR : public BaseIR {
	public:

		DirectivesIR (std::vector<std::unique_ptr<BaseIR>> directives) {

			for (const auto &directive : directives)
				emit += directive ? directive->emit+" " : "";

			if (emit.size() >= 2) // Remove last " "
				emit.pop_back();

		}

	};

	class DefIR : public BaseIR {
	public:

		DefIR (const std::string &name, std::unique_ptr<BaseIR> args,
			std::unique_ptr<BaseIR> directives, std::unique_ptr<BaseIR> type)
		{

			std::string directivesEmit = directives ? directives->emit : "";
			std::string argsEmit       = args       ? args      ->emit : "";

			if (directivesEmit != "") directivesEmit += " ";
			emit = "define "+type->emit+" @"+name+"("+argsEmit+") "+directivesEmit+"{\n";

		}

	};

	class EndIR : public BaseIR {
	public:
		EndIR () { emit = "}\n"; }
	};

	class DeclareIR : public BaseIR {
	public:

		DeclareIR (const std::string &name, std::unique_ptr<BaseIR> args,
			std::unique_ptr<BaseIR> directives, std::unique_ptr<BaseIR> type)
		{

			std::string directivesEmit = directives ? directives->emit : "";
			std::string argsEmit       = args       ? args      ->emit : "";

			if (directivesEmit != "") directivesEmit += " ";
			emit = "declare "+type->emit+" @"+name+"("+argsEmit+") "+directivesEmit;

		}

	};

	class RetVoidIR : public BaseIR {
	public:

		RetVoidIR () {
			emit = "  ret void\n";
		}

	};

	class RetIR : public BaseIR {
	public:

		RetIR (BaseIR *val) {
			emit = "  ret "+val->type->emit+" "+val->addr+"\n";
		}

	};

	class StackIR : public BaseIR {
	public:

		StackIR (std::vector<std::unique_ptr<BaseIR>> body) {

			for (const auto &ir : body) {

				if (ir) {
					emit += ir->emit;
					addr  = ir->addr;
					type  = ir->type;
				}

			}

		}

	};

	class InlineDirectiveIR : public BaseIR {
	public:
		InlineDirectiveIR() { emit = "inlinehint"; }
	};

	class FastCallDirectiveIR : public BaseIR {
	public:
		FastCallDirectiveIR() { emit = "x86_fastcallcc"; }
	};

	class StdCallDirectiveIR : public BaseIR {
	public:
		StdCallDirectiveIR() { emit = "x86_stdcallcc"; }
	};

	class ExternDirectiveIR : public BaseIR {
	public:

	};

}
