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

}
