#define CODEGEN_FACTORY(ir) \
\
virtual inline std::unique_ptr<BaseIR> createIntTyIR (const int size) override { \
	return std::make_unique<ir::IntTyIR> (size); \
} \
\
virtual inline std::unique_ptr<BaseIR> createVoidTyIR() override \
{ \
	return std::make_unique<ir::VoidTyIR>(); \
} \
\
virtual inline std::unique_ptr<BaseIR> createIntValIR (const int64_t val, const int size) override { \
	return std::make_unique<ir::IntValIR> (val, size); \
} \
\
virtual inline std::unique_ptr<BaseIR> createAddIR (BaseIR *A, BaseIR *B, \
	const bool nsw = false, const bool nuw = false) override \
{ \
	return std::make_unique<ir::AddIR> (std::move(A), std::move(B), nsw, nuw); \
} \
\
virtual inline std::unique_ptr<BaseIR> createDefIR (const std::string &name, std::unique_ptr<BaseIR> args, \
	std::unique_ptr<BaseIR> directives, std::unique_ptr<BaseIR> type) override \
{ \
	return std::make_unique<ir::DefIR> (name, std::move(args), std::move(directives), std::move(type)); \
} \
\
virtual inline std::unique_ptr<BaseIR> createDeclareIR (const std::string &name, std::unique_ptr<BaseIR> args, \
	std::unique_ptr<BaseIR> directives, std::unique_ptr<BaseIR> type) override \
{ \
	return std::make_unique<ir::DeclareIR> (name, std::move(args), std::move(directives), std::move(type)); \
} \
\
virtual inline std::unique_ptr<BaseIR> createArgIR (const std::string &name, std::unique_ptr<BaseIR> type) override \
{ \
	if (!type) return nullptr; \
	return std::make_unique<ir::ArgIR> (name, std::move(type)); \
} \
\
virtual inline std::unique_ptr<BaseIR> createArgsIR (std::vector<std::unique_ptr<BaseIR>> args) override \
{ \
	return std::make_unique<ir::ArgsIR> (std::move(args)); \
} \
\
virtual inline std::unique_ptr<BaseIR> createInlineDirectiveIR() override { \
	return std::make_unique<ir::InlineDirectiveIR>(); \
} \
\
virtual inline std::unique_ptr<BaseIR> createFastCallDirectiveIR() override { \
	return std::make_unique<ir::FastCallDirectiveIR>(); \
} \
\
virtual inline std::unique_ptr<BaseIR> createStdCallDirectiveIR() override { \
	return std::make_unique<ir::StdCallDirectiveIR>(); \
} \
\
virtual inline std::unique_ptr<BaseIR> createDirectivesIR (std::vector<std::unique_ptr<BaseIR>> directives) override \
{ \
	return std::make_unique<ir::DirectivesIR> (std::move(directives)); \
} \
\
virtual inline std::unique_ptr<BaseIR> createStackIR (std::vector<std::unique_ptr<BaseIR>> stack) override \
{ \
	return std::make_unique<ir::StackIR> (std::move(stack)); \
} \
\
virtual inline std::unique_ptr<BaseIR> createRetVoidIR() override \
{ \
	return std::make_unique<ir::RetVoidIR>(); \
} \
\
virtual inline std::unique_ptr<BaseIR> createRetIR (BaseIR *val) override \
{ \
	return std::make_unique<ir::RetIR> (val); \
} \
\
virtual inline std::unique_ptr<BaseIR> createEndIR() override \
{ \
	return std::make_unique<ir::EndIR>(); \
} \
\
