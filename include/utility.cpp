// Hex To Val
inline uint64_t HexIntToVal (const char *Buffer) {

	uint64_t Result = 0;

	for (; *Buffer; ++Buffer) {
		uint64_t OldRes = Result;
		Result *= 16;
		char C = *Buffer;

		if (C >= '0' && C <= '9')
			Result += C-'0';
		else if (C >= 'A' && C <= 'F')
			Result += C-'A'+10;
		else if (C >= 'a' && C <= 'f')
			Result += C-'a'+10;

	//if (Result < OldRes)   // Uh, oh, overflow detected!!!
	//  ThrowException("constant bigger than 64 bits detected!");
	}

	return Result;
}
