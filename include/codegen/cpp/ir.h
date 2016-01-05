#pragma once
#include "codegen/codegen.h"

namespace cpp_ir {

	class IntTyIR : public BaseIR {
	public:

		IntTyIR (const int size) {

			switch (size) {
				case 1  : emit = "int";      break;
				case 8  : emit = "char";     break;
				case 16 : emit = "short";    break;
				case 32 : emit = "int";      break;
				case 64 : emit = "long int"; break;
				default :
					emit = "int"; align = 4; type = this;
					return;
			}

			addr  = emit;
			align = size/8;

			if (size < 8)
				align = 8;

			type = this;

		}

	};

}
