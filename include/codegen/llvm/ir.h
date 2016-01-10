#pragma once
#include "codegen/codegen.h"
#include <cassert>

namespace llvm_ir {

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

		AddIR (std::unique_ptr<BaseIR> A, std::unique_ptr<BaseIR> B,
			const bool nsw = false, const bool nuw = false)
		{

			addr = "%add.1";
			type = A->type;
			std::string nw = " ";

			if (nsw) nw += "nsw ";
			else if (nuw) nw += "nuw ";
			else nw = "";

			emit = "  "+addr+" = add "+nw+A->type->emit+" "+A->addr+", "+B->addr;

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
			emit = "define "+type->emit+" @"+name+"("+argsEmit+") "+directivesEmit+"{";

		}

	};

	class RetIR : public BaseIR {

	};

	class BodyIR : public BaseIR {

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
