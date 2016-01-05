#pragma once
#include "codegen/codegen.h"

namespace llvm_ir {

	class IntTyIR : public BaseIR {
	public:

		IntTyIR (const int size) {

			emit  = "i"+std::to_string (size);
			addr  = emit;
			align = size/8;

			if (size < 8)
				align = 8;

			type = this;

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

}
