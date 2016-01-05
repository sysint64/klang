#define CODEGEN_FACTORY(ir) \
\
virtual inline std::unique_ptr<BaseIR> createIntTyIR (const int size) override { \
	return std::make_unique<ir::IntTyIR> (size); \
} \
\
virtual inline std::unique_ptr<BaseIR> createIntValIR (const int64_t val, const int size) override { \
	return std::make_unique<ir::IntValIR> (val, size); \
} \
\
virtual inline std::unique_ptr<BaseIR> createAddIR (std::unique_ptr<BaseIR> A, std::unique_ptr<BaseIR> B, \
	const bool nsw = false, const bool nuw = false) override \
{ \
	return std::make_unique<ir::AddIR> (std::move(A), std::move(B), nsw, nuw); \
} \
\
